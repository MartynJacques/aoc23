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

int main() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::string line{};
  int total = 0;
  while (std::getline(infile, line)) {
    std::vector<std::string> colon_split = split(line, ':');
    std::vector<std::string> line_split = split(colon_split[1], '|');

    std::vector<std::string> actual_nums_split = split(line_split[0], ' ');
    std::set<int> lottery_nums{};
    for (auto const& a : actual_nums_split) {
      try {
        lottery_nums.insert(std::stoi(a));
      } catch (std::exception& e) {
        // do nothing
      }
    }

    std::vector<std::string> my_nums_split = split(line_split[1], ' ');
    int score = 0;
    for (auto const& a : my_nums_split) {
      try {
        int b = std::stoi(a);
        if (lottery_nums.find(b) != lottery_nums.end()) {
          if (score == 0) {
            score = 1;
          } else {
            score *= 2;
          }
        }
      } catch (std::exception& e) {
      }
    }
    total += score;
  }

  std::cout << total << '\n';
}