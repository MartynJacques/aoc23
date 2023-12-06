#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string_view>

int main() {
  std::array<std::string_view, 9> digit_words{
      "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

  std::map<std::string_view, char> map{
      {"one", '1'},   {"two", '2'},   {"three", '3'},
      {"four", '4'},  {"five", '5'},  {"six", '6'},
      {"seven", '7'}, {"eight", '8'}, {"nine", '9'},
  };

  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::string line{};
  int res = 0;
  while (std::getline(infile, line)) {
    std::stringstream sstream{};
    int i = 0;
    while (i < line.size()) {
      if (std::isdigit(line[i])) {
        sstream << line.at(i);
      } else {
        for (std::string_view sv : digit_words) {
          if (line.substr(i).rfind(sv, 0) == 0) {
            sstream << map[sv];
            break;
          }
        }
      }
      i++;
    }
    std::string s{};
    sstream >> s;
    std::string sss{s[0], s[s.size() - 1]};
    std::cout << std::stoi(sss) << '\n';
    res += std::stoi(sss);
  }
  std::cout << res << '\n';
}
