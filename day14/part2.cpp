#include <fstream>
#include <iostream>
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

void print_grid(std::vector<std::vector<char>> const& grid) {
  for (auto const& row : grid) {
    for (auto const& c : row) {
      std::cout << c;
    }
    std::cout << '\n';
  }
}

int main() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::string input_line{};
  std::vector<std::vector<char>> grid{};
  while (std::getline(infile, input_line)) {
    std::vector<char> grid_row{};
    for (int i = 0; i < input_line.size(); i++) {
      grid_row.push_back(input_line.at(i));
    }
    grid.push_back(grid_row);
  }

  grid = rotate(grid);
  auto original_grid = grid;

  int num_cycles = 1000;
  for (int cycle = 0; cycle < num_cycles; cycle++) {
    for (int a = 0; a < 4; a++) {
      for (int i = 0; i < grid.size(); i++) {
        for (int j = grid.at(0).size() - 1; j >= 0; j--) {
          if (grid.at(i).at(j) == 'O') {
            // bubble this as far right as possible
            int k = j;
            while (k < grid.at(0).size() - 1 && grid.at(i).at(k + 1) != '#') {
              // swap k and k + 1
              char tmp = grid.at(i).at(k + 1);
              grid[i][k + 1] = grid[i][k];
              grid[i][k] = tmp;
              k++;
            }
          }
        }
      }
      grid = rotate(grid);
    }
    if (grid == original_grid) {
      std::cout << "Repeat\n";
      break;
    }
  }

  int total_load = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid.at(0).size(); j++) {
      if (grid.at(i).at(j) == 'O') {
        total_load += j + 1;
      }
    }
  }

  std::cout << total_load << '\n';
}