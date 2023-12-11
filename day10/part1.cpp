#include <fstream>
#include <iostream>
#include <map>
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

std::pair<int, int> get_next(std::pair<int, int> prev, std::pair<int, int> curr,
                             std::vector<std::vector<char>> const& grid) {
  char curr_char = grid.at(curr.first).at(curr.second);
  if (curr_char == '|') {
    if (prev.first == curr.first - 1) {
      return {curr.first + 1, curr.second};
    }
    if (prev.first == curr.first + 1) {
      return {curr.first - 1, curr.second};
    }
  }

  if (curr_char == '-') {
    if (prev.second == curr.second - 1) {
      return {curr.first, curr.second + 1};
    }
    if (prev.second == curr.second + 1) {
      return {curr.first, curr.second - 1};
    }
  }

  if (curr_char == 'L') {
    if (prev.second == curr.second + 1) {
      return {curr.first - 1, curr.second};
    }
    if (prev.first == curr.first - 1) {
      return {curr.first, curr.second + 1};
    }
  }

  if (curr_char == 'J') {
    if (prev.second == curr.second - 1) {
      return {curr.first - 1, curr.second};
    }
    if (prev.first == curr.first - 1) {
      return {curr.first, curr.second - 1};
    }
  }

  if (curr_char == '7') {
    if (prev.second == curr.second - 1) {
      return {curr.first + 1, curr.second};
    }
    if (prev.first == curr.first + 1) {
      return {curr.first, curr.second - 1};
    }
  }

  if (curr_char == 'F') {
    if (prev.second == curr.second + 1) {
      return {curr.first + 1, curr.second};
    }
    if (prev.first == curr.first + 1) {
      return {curr.first, curr.second + 1};
    }
  }

  if (curr_char == '.') {
    throw std::exception{};
  }

  if (curr_char == 'S') {
    throw std::exception{};
  }

  throw std::exception{};
}

int main() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::vector<std::vector<char>> grid{};
  std::string line{};
  std::pair<int, int> s{};
  while (std::getline(infile, line)) {
    std::vector<char> grid_line{};
    for (int i = 0; i < line.size(); i++) {
      if (line.at(i) == 'S') {
        s = {grid.size(), grid_line.size()};
      }
      grid_line.push_back(line.at(i));
    }
    grid.push_back(grid_line);
  }

  std::pair<int, int> prev = s;

  // Can start one up or one down from S
  std::pair<int, int> curr = {s.first + 1, s.second};

  int dist = 0;
  while (curr != s) {
    dist++;
    auto tmp = curr;
    curr = get_next(prev, curr, grid);
    prev = tmp;
  }
  std::cout << dist / 2.0 << '\n';
}