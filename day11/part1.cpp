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

std::vector<std::vector<char>> get_expanded_image() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::string line{};
  std::vector<std::vector<char>> grid{};
  std::vector<int> rows_with_no_galaxies{};
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
      rows_with_no_galaxies.push_back(grid.size());
    }
    grid.push_back(grid_line);
  }

  std::vector<std::vector<char>> result{};
  for (int i = 0; i < grid.size(); i++) {
    if (std::find(rows_with_no_galaxies.begin(), rows_with_no_galaxies.end(),
                  i) != rows_with_no_galaxies.end()) {
      result.push_back(grid.at(i));
    }
    result.push_back(grid.at(i));
  }

  result = rotate(result);
  std::vector<std::vector<char>> new_result{};
  for (int i = 0; i < result.size(); i++) {
    bool no_galaxies = true;
    for (int j = 0; j < result.at(0).size(); j++) {
      if (result.at(i).at(j) != '.') {
        no_galaxies = false;
      }
    }
    if (no_galaxies) {
      new_result.push_back(result.at(i));
    }
    new_result.push_back(result.at(i));
  }
  return rotate(rotate(rotate(new_result)));
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

std::vector<std::pair<std::uint32_t, std::uint32_t>> get_nbrs(
    std::pair<std::uint32_t, std::uint32_t> curr,
    std::vector<std::vector<bool>> const& visited) {
  std::vector<std::pair<std::uint32_t, std::uint32_t>> result{};
  std::uint32_t i = curr.first;
  std::uint32_t j = curr.second;

  // if (i > 0) {
  //   std::uint32_t new_i = i - 1;
  //   std::uint32_t new_j = j;
  //   if (!visited.at(new_i).at(new_j)) {
  //     result.push_back({new_i, new_j});
  //   }
  // }

  if (j > 0) {
    std::uint32_t new_i = i;
    std::uint32_t new_j = j - 1;
    if (!visited.at(new_i).at(new_j)) {
      result.push_back({new_i, new_j});
    }
  }

  if (i < visited.size() - 1) {
    std::uint32_t new_i = i + 1;
    std::uint32_t new_j = j;
    if (!visited.at(new_i).at(new_j)) {
      result.push_back({new_i, new_j});
    }
  }

  if (j < visited.at(0).size() - 1) {
    std::uint32_t new_i = i;
    std::uint32_t new_j = j + 1;
    if (!visited.at(new_i).at(new_j)) {
      result.push_back({new_i, new_j});
    }
  }

  return result;
}

int bfs(std::pair<std::uint32_t, std::uint32_t> start,
        std::pair<std::uint32_t, std::uint32_t> end,
        std::vector<std::vector<char>>& grid,
        std::vector<std::vector<bool>>& visited) {
  std::queue<std::pair<std::uint32_t, std::uint32_t>> queue{};
  queue.push(start);
  visited.at(start.first).at(start.second) = true;
  int dist = 0;

  while (!queue.empty()) {
    int num_nbrs = queue.size();
    for (int i = 0; i < num_nbrs; i++) {
      std::pair<std::uint32_t, std::uint32_t> curr = queue.front();
      if (curr == end) {
        return dist;
      }
      queue.pop();
      for (auto const& nbr : get_nbrs(curr, visited)) {
        queue.push(nbr);
        visited.at(nbr.first).at(nbr.second) = true;
      }
    }
    dist++;
  }
  std::cout << "bad!\n";
  throw std::exception{};
}

int main() {
  std::vector<std::vector<char>> image = get_expanded_image();
  std::vector<std::pair<std::uint32_t, std::uint32_t>> galaxy_coords =
      get_galaxy_coords(image);
  std::uint32_t node_count = galaxy_coords.size();
  std::vector<std::pair<std::uint32_t, std::uint32_t>> pairs =
      get_pairs(node_count);

  std::uint64_t total = 0;
  for (auto const& pair : pairs) {
    auto const from = galaxy_coords.at(pair.first);
    auto const to = galaxy_coords.at(pair.second);
    std::int32_t a = from.first - to.first;
    std::int32_t b = from.second - to.second;
    auto manhattan_dist = std::abs(a) + std::abs(b);
    total += manhattan_dist;
  }
  std::cout << total << '\n';
}