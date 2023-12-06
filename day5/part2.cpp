#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::string dir = "real-input/";

class tuple {
 public:
  std::uint64_t dest_start;
  std::uint64_t source_start;
  std::uint64_t len;
};

std::vector<std::string> split(const std::string& target, char c) {
  std::string temp;
  std::stringstream stringstream{target};
  std::vector<std::string> result;

  while (std::getline(stringstream, temp, c)) {
    result.push_back(temp);
  }

  return result;
}

std::vector<std::uint64_t> parse_seeds() {
  std::ifstream infile(dir + "seeds.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::vector<std::uint64_t> res{};
  std::string line{};
  while (std::getline(infile, line)) {
    std::vector<std::string> the_split = split(line, ' ');
    for (auto const& s : the_split) {
      try {
        res.push_back(std::stoll(s));
      } catch (std::exception& e) {
        // do nothing
      }
    }
  }

  std::vector<std::uint64_t> actual_res{};
  for (int i = 0; i < res.size() - 1; i += 2) {
    for (int j = 0; j < res[i + 1]; j++) {
      actual_res.push_back(res[i] + j);
    }
  }

  return actual_res;
}

std::vector<tuple> parse_ranges(std::string&& filename) {
  std::ifstream infile(filename);
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::vector<tuple> res{};
  std::string line{};
  while (std::getline(infile, line)) {
    std::vector<std::string> the_split = split(line, ' ');
    std::vector<std::uint64_t> tmp{};
    for (auto const& s : the_split) {
      try {
        tmp.push_back(std::stoll(s));
      } catch (std::exception& e) {
        // do nothing
      }
    }
    res.push_back({tmp[0], tmp[1], tmp[2]});
  }

  return res;
}

std::uint64_t get_mapping(std::uint64_t const seed_num,
                          std::vector<tuple> const& seed_to_soil) {
  for (auto const& tup : seed_to_soil) {
    if (seed_num >= tup.source_start &&
        seed_num < (tup.source_start + tup.len)) {
      // seed is in this range
      std::uint64_t diff = seed_num - tup.source_start;
      return tup.dest_start + diff;
    }
  }
  return seed_num;
}

int main() {
  std::vector<std::uint64_t> seeds = parse_seeds();
  std::vector<tuple> seed_to_soil = parse_ranges(dir + "seed-to-soil.txt");
  std::vector<tuple> soil_to_fertilizer =
      parse_ranges(dir + "soil-to-fertilizer.txt");
  std::vector<tuple> fertilizer_to_water =
      parse_ranges(dir + "fertilizer-to-water.txt");
  std::vector<tuple> water_to_light = parse_ranges(dir + "water-to-light.txt");
  std::vector<tuple> light_to_temperature =
      parse_ranges(dir + "light-to-temperature.txt");
  std::vector<tuple> temperate_to_humidity =
      parse_ranges(dir + "temperature-to-humidity.txt");
  std::vector<tuple> humidity_to_location =
      parse_ranges(dir + "humidity-to-location.txt");

  std::uint64_t min = 0 - 1;
  for (auto const& seed : seeds) {
    std::uint64_t soil_number = get_mapping(seed, seed_to_soil);
    std::uint64_t fert_num = get_mapping(soil_number, soil_to_fertilizer);
    std::uint64_t water_num = get_mapping(fert_num, fertilizer_to_water);
    std::uint64_t light_num = get_mapping(water_num, water_to_light);
    std::uint64_t temp_num = get_mapping(light_num, light_to_temperature);
    std::uint64_t humidity_num = get_mapping(temp_num, temperate_to_humidity);
    std::uint64_t location_num =
        get_mapping(humidity_num, humidity_to_location);
    // std::cout << "seed: " << seed << " loc: " << location_num << '\n';
    if (location_num < min) {
      min = location_num;
    }
  }
  std::cout << min << '\n';
}