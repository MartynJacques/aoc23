#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
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
  // std::string_view instructions = "LR";
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

  std::vector<std::string> keys{};
  for (auto const& [key, value] : map) {
    if (key.at(2) == 'A') {
      keys.push_back(key);
    }
  }

  // For each key ending with A, store the steps it takes to get to a node
  // ending with Z
  // Find the lcm of all of the stored steps
  std::vector<std::uint64_t> steps_per_key{};
  for (std::string& key : keys) {
    int i = 0;
    int steps = 0;
    while (key.at(2) != 'Z') {
      auto next_pair = map.at(key);
      if (instructions.at(i) == 'L') {
        key = next_pair.first;
      } else {
        key = next_pair.second;
      }
      i = (i + 1) % instructions.size();
      steps++;
    }
    steps_per_key.push_back(steps);
  }

  std::uint64_t result = steps_per_key.at(0);
  for (int i = 1; i < steps_per_key.size(); i++) {
    result = std::lcm(steps_per_key.at(i), result);
  }

  std::cout << result << '\n';
}