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

int main() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::vector<condition_record> records{};
  std::string line{};

  std::vector<std::vector<std::vector<char>>> grids{};
  {
    std::vector<std::vector<char>> grid{};
    while (std::getline(infile, line)) {
      if (line.empty()) {
        grids.push_back(grid);
        grid.clear();
        continue;
      }

      std::vector<char> char_line{};
      for (int i = 0; i < line.size(); i++) {
        char_line.push_back(line.at(i));
      }
      grid.push_back(char_line);
    }
    grids.push_back(grid);
  }

  int total = 0;

  for (auto const& grid : grids) {
    for (int i = 0; i < grid.size() - 1; i++) {
      std::uint32_t rows_above = i + 1;
      std::uint32_t rows_below = grid.size() - i - 1;
      std::uint32_t min = std::min(rows_above, rows_below);

      int count = 0;
      int a = i;
      int b = i + 1;
      bool is_mirror = true;
      while (count < min) {
        if (grid.at(a) != grid.at(b)) {
          is_mirror = false;
          break;
        }
        a--;
        b++;
        count++;
      }

      if (is_mirror) {
        std::cout << i << '\n';
        total += (100 * rows_above);
        break;
      }
    }

    auto rotated_grid = rotate(grid);
    for (int i = 0; i < rotated_grid.size() - 1; i++) {
      std::uint32_t rows_above = i + 1;
      std::uint32_t rows_below = rotated_grid.size() - i - 1;
      std::uint32_t min = std::min(rows_above, rows_below);

      int count = 0;
      int a = i;
      int b = i + 1;
      bool is_mirror = true;
      while (count < min) {
        if (rotated_grid.at(a) != rotated_grid.at(b)) {
          is_mirror = false;
          break;
        }
        a--;
        b++;
        count++;
      }

      if (is_mirror) {
        std::cout << i << '\n';
        total += (rows_above);
        break;
      }
    }
  }
  std::cout << total << '\n';
}