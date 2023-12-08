#include <algorithm>
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

int main() {
  // std::string_view instructions = "LLR";
  std::string_view instructions =
      "LLRRRLLRLRRRLLRLRLRLRLRRRLRRLRRLRLLLRRLLRRLRRLRRLRRRLLLRRLRLRRRLRRRLRLRR"
      "LRRRLRLRRRLRLRLLLRLRRLRLRRLRRRLRLRRRLRRRLRRRLRRRLRLRRRLRRRLRLLRRLRLRLRRR"
      "LRRLRRRLRRRLRRRLRRRLLLLRRLLRLRRLRRLRRRLRRRLLLRRLRRLRLRRLRRRLRRLRLRRRLRLR"
      "RLLRLLRRLRLRRRLRRLRRLRLRRLLLRRRLRLRRRLRLRLLRLRLRRRLRLRLRRRLRRLRRLRRRLRRL"
      "LRRRR";

  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::string line{};
  std::map<std::string, std::pair<std::string, std::string>> map{};
  while (std::getline(infile, line)) {
    std::string key = std::string() + line.at(0) + line.at(1) + line.at(2);
    std::string left = std::string() + line.at(7) + line.at(8) + line.at(9);
    std::string right = std::string() + line.at(12) + line.at(13) + line.at(14);

    map.emplace(key, std::pair{left, right});
  }

  std::string key = "AAA";
  int i = 0;
  int steps = 0;
  while (key != "ZZZ") {
    auto next_pair = map.at(key);
    if (instructions.at(i) == 'L') {
      key = next_pair.first;
    } else {
      key = next_pair.second;
    }
    i = (i + 1) % instructions.size();
    steps++;
  }

  std::cout << steps << '\n';
}