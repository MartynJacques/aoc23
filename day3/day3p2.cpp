#include <fstream>
#include <iostream>
#include <map>
#include <set>
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
  std::map<std::pair<int, int>, std::set<int>> map{};
  std::vector<std::pair<int, int>> astericks{};
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (isdigit(grid[i].at(j))) {
        this_int += grid[i].at(j);
        for (auto nbr : get_nbrs(i, j, grid.size() - 1, grid[0].size() - 1)) {
          char nbr_val = grid[nbr.first].at(nbr.second);
          if (nbr_val == '*') {
            astericks.push_back({nbr.first, nbr.second});
          }
        }
      } else {
        if (this_int != "") {
          for (auto asterick : astericks) {
            if (map.find(asterick) == map.end()) {
              map.insert(std::pair<std::pair<int, int>, std::set<int>>{
                  asterick, {std::stoi(this_int)}});
            } else {
              map[asterick].insert(std::stoi(this_int));
            }
          }
        }
        this_int = "";
        astericks.clear();
      }
    }
  }

  int total = 0;
  for (auto const& [key, value] : map) {
    if (value.size() == 2) {
      int tmp = 1;
      for (auto const& val : value) {
        tmp *= val;
      }
      total += tmp;
    }

    // std::cout << key.first << ", " << key.second << ": ";
    // for (auto const& val : value) {
    //   std::cout << val << ", ";
    // }
    // std::cout << '\n';
  }
  std::cout << total << '\n';
}
