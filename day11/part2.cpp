#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& target, char c) {
  std::string temp;
  std::stringstream stringstream{target};
  std::vector<std::string> result;

  while (std::getline(stringstream, temp, c)) {
    result.push_back(temp);
  }

  return result;
}

std::vector<std::vector<char>> rotate(
    std::vector<std::vector<char>> const& in) {
  int rows = in.size();
  int cols = in[0].size();

  std::vector<std::vector<char>> rotated(cols, std::vector<char>(rows));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      rotated[j][rows - 1 - i] = in[i][j];
    }
  }

  return rotated;
}

std::vector<int> rows_with_no_galaxies{};
std::vector<int> cols_with_no_galaxies{};
std::vector<std::vector<char>> get_image() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::string line{};
  std::vector<std::vector<char>> grid{};
  int row_count = 0;
  while (std::getline(infile, line)) {
    std::vector<char> grid_line{};
    bool no_galaxies = true;
    for (int i = 0; i < line.size(); i++) {
      char curr_char = line.at(i);
      if (curr_char != '.') {
        no_galaxies = false;
      }
      grid_line.push_back(line.at(i));
    }
    if (no_galaxies) {
      rows_with_no_galaxies.push_back(row_count);
    }
    grid.push_back(grid_line);
    row_count++;
  }

  auto result = rotate(grid);
  for (int i = 0; i < result.size(); i++) {
    bool no_galaxies = true;
    for (int j = 0; j < result.at(0).size(); j++) {
      if (result.at(i).at(j) != '.') {
        no_galaxies = false;
      }
    }
    if (no_galaxies) {
      cols_with_no_galaxies.push_back(i);
    }
  }
  return grid;
}

void print_image(std::vector<std::vector<char>> const& image) {
  for (auto const& row : image) {
    for (auto const& c : row) {
      std::cout << c;
    }
    std::cout << '\n';
  }
}

std::vector<std::pair<std::uint32_t, std::uint32_t>> get_galaxy_coords(
    std::vector<std::vector<char>> const& image) {
  std::vector<std::pair<std::uint32_t, std::uint32_t>> result{};
  for (int i = 0; i < image.size(); i++) {
    for (int j = 0; j < image.at(0).size(); j++) {
      if (image.at(i).at(j) != '.') {
        result.push_back({i, j});
      }
    }
  }
  return result;
}

std::vector<std::pair<std::uint32_t, std::uint32_t>> get_pairs(
    std::uint32_t num_galaxies) {
  // num_galaxies--;
  std::vector<std::uint32_t> nums(num_galaxies);
  for (int i = 0; i < num_galaxies; i++) {
    nums[i] = i;
  }

  std::vector<std::pair<std::uint32_t, std::uint32_t>> result{};
  for (int i = 0; i < num_galaxies; i++) {
    for (int j = i; j < num_galaxies; j++) {
      result.push_back({nums[i], nums[j]});
    }
  }

  return result;
}

std::uint32_t empty_between_count(int start, int end, std::vector<int> empty) {
  if (start > end) {
    int tmp = end;
    end = start;
    start = tmp;
  }
  int count = 0;
  for (int i = 0; i < empty.size(); i++) {
    if (empty.at(i) >= start && empty.at(i) <= end) {
      count++;
    }
  }
  return count;
}

int main() {
  std::vector<std::vector<char>> image = get_image();
  std::vector<std::pair<std::uint32_t, std::uint32_t>> galaxy_coords =
      get_galaxy_coords(image);
  std::uint32_t node_count = galaxy_coords.size();
  std::vector<std::pair<std::uint32_t, std::uint32_t>> pairs =
      get_pairs(node_count);

  auto rows_with_no_galaxiess = rows_with_no_galaxies;
  auto cols_with_no_galaxiess = cols_with_no_galaxies;

  std::uint64_t total = 0;
  for (auto const& pair : pairs) {
    auto const from = galaxy_coords.at(pair.first);
    auto const to = galaxy_coords.at(pair.second);
    std::int32_t a_between =
        empty_between_count(from.first, to.first, rows_with_no_galaxies);
    std::int32_t b_between =
        empty_between_count(from.second, to.second, cols_with_no_galaxies);
    std::int32_t a = from.first - to.first;
    std::int32_t b = from.second - to.second;
    auto manhattan_dist = std::abs(a) + (a_between * (1000000 - 1)) +
                          std::abs(b) + (b_between * (1000000 - 1));
    total += manhattan_dist;
  }
  std::cout << total << '\n';
}