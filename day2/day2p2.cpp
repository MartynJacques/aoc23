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

int main() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::string line{};
  int total = 0;
  while (std::getline(infile, line)) {
    std::map<std::string, int> maxs = {{"red", 0}, {"blue", 0}, {"green", 0}};
    std::vector<std::string> lines_split = split(line, ':');

    auto game_num_split = split(lines_split[0], ' ');
    auto game_num = game_num_split[1];

    std::vector<std::string> shown_split = split(lines_split[1], ';');

    bool possible = true;
    for (auto s : shown_split) {
      auto colours_split = split(s, ',');
      for (auto ss : colours_split) {
        auto pair_split = split(ss, ' ');
        auto i = std::stoi(pair_split[1]);
        auto colour = pair_split[2];
        if (i > maxs[colour]) {
          maxs[colour] = i;
        }
      }
    }

    int power = 1;
    for (auto const& [key, value] : maxs) {
      power *= value;
    }
    total += power;
  }

  std::cout << total << '\n';
}
