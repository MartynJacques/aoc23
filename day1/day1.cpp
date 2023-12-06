#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::string line{};
  int res = 0;
  while (std::getline(infile, line)) {
    std::stringstream sstream{};
    for (char c : line) {
      if (isdigit(c)) {
        sstream << c;
      }
    }
    std::string s;
    sstream >> s;
    std::string sss{s[0], s[s.size() - 1]};
    res += std::stoi(sss);
  }
  std::cout << res << '\n';
}
