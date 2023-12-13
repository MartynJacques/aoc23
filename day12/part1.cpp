#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class condition_record {
 public:
  std::string record{};
  std::vector<std::uint32_t> groups{};
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

int main() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::vector<condition_record> records{};
  std::string line{};
  while (std::getline(infile, line)) {
    std::vector<std::string> space_split = split(line, ' ');
    std::string record = space_split[0];

    std::vector<std::string> nums_split = split(space_split[1], ',');
    std::vector<std::uint32_t> groups{};
    for (auto const& num : nums_split) {
      groups.push_back(std::stoi(num));
    }

    records.push_back(condition_record{record, groups});
  }
}