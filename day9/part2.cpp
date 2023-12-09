#include <algorithm>
#include <fstream>
#include <functional>
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

bool all_zeros(std::vector<int> const& nums) {
  for (auto const& num : nums) {
    if (num != 0) return false;
  }
  return true;
}

int find_next_val(std::vector<int> nums) {
  std::vector<std::vector<int>> expanded{};
  expanded.push_back(nums);
  while (!all_zeros(expanded.back())) {
    std::vector<int> diffs{};
    for (int i = 0; i < expanded.back().size() - 1; i++) {
      diffs.push_back(expanded.back().at(i + 1) - expanded.back().at(i));
    }
    expanded.push_back(diffs);
  }

  // for (auto const& e : expanded) {
  //   for (auto const& i : e) {
  //     std::cout << i << ' ';
  //   }
  //   std::cout << '\n';
  // }

  for (int i = expanded.size() - 2; i >= 0; i--) {
    int a = expanded.at(i + 1).back();
    int b = expanded.at(i).back();
    int res = a + b;
    expanded.at(i).push_back(res);
  }

  return expanded.at(0).back();
}

int main() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::string line{};
  std::vector<std::vector<int>> lines{};
  while (std::getline(infile, line)) {
    auto line_split = split(line, ' ');
    std::vector<int> nums{};
    for (auto const& st_int : line_split) {
      nums.push_back(std::stoi(st_int));
    }
    std::reverse(nums.begin(), nums.end());
    lines.push_back(nums);
  }

  std::uint64_t total = 0;
  for (auto const& line : lines) {
    int next_val = find_next_val(line);
    // std::cout << next_val << '\n';
    total += next_val;
  }
  std::cout << total << '\n';
}