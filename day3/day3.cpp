#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
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

std::vector<std::pair<int, int>> get_nbrs(int i, int j, int max_i, int max_j) {
  std::vector<std::pair<int, int>> nbrs{};
  if (i > 0 && j > 0) {
    nbrs.push_back({i - 1, j - 1});
  }

  if (i > 0) {
    nbrs.push_back({i - 1, j});
  }

  if (i > 0 && j < max_j) {
    nbrs.push_back({i - 1, j + 1});
  }

  if (j > 0) {
    nbrs.push_back({i, j - 1});
  }

  if (j < max_j) {
    nbrs.push_back({i, j + 1});
  }

  if (i < max_i && j > 0) {
    nbrs.push_back({i + 1, j - 1});
  }

  if (i < max_i) {
    nbrs.push_back({i + 1, j});
  }

  if (i < max_i && j < max_j) {
    nbrs.push_back({i + 1, j + 1});
  }

  return nbrs;
}

int main() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::string line{};
  std::vector<std::string> grid{};
  while (std::getline(infile, line)) {
    grid.push_back(line);
  }

  std::string this_int{};
  bool has_symbol_neighbour = false;
  std::vector<std::pair<int, std::pair<int, int>>> nums{};
  int total = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (isdigit(grid[i].at(j))) {
        this_int += grid[i].at(j);
        for (auto nbr : get_nbrs(i, j, grid.size() - 1, grid[0].size() - 1)) {
          char nbr_val = grid[nbr.first].at(nbr.second);
          if (!isalnum(nbr_val) && nbr_val != '.') {
            has_symbol_neighbour = true;
          }
        }
      } else {
        if (this_int != "") {
          if (has_symbol_neighbour) {
            total += std::stoi(this_int);
          }
        }
        this_int = "";
        has_symbol_neighbour = false;
      }
    }
  }

  std::cout << total << '\n';
}
