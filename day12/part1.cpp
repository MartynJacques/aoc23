#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class condition_record {
 public:
  std::string record{};
  std::vector<int> groups{};
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

void print_record(condition_record const& record) {
  std::cout << record.record << " (";
  for (int i = 0; i < record.groups.size() - 1; i++) {
    std::cout << record.groups.at(i) << ", ";
  }
  std::cout << record.groups.at(record.groups.size() - 1) << ")";
}

int get_num_of_arrangements(std::string const& record,
                            std::vector<int> const& groups);

int hash(std::string const& record, std::vector<int> const& groups, int group) {
  std::string this_group = record.substr(0, group);
  std::replace(this_group.begin(), this_group.end(), '?', '#');

  if (this_group != std::string(group, '#')) {
    return 0;
  }

  if (record.size() == group) {
    if (groups.size() == 1) {
      return 1;
    } else {
      return 0;
    }
  }

  if (record.at(group) == '?' || record.at(group) == '.') {
    return get_num_of_arrangements(record.substr(group + 1),
                                   {groups.begin() + 1, groups.end()});
  }

  return 0;
}

int dot(std::string const& record, std::vector<int> const& groups) {
  return get_num_of_arrangements(record.substr(1), groups);
}

int get_num_of_arrangements(std::string const& record,
                            std::vector<int> const& groups) {
  if (groups.size() == 0) {
    if (record.find('#') != std::string::npos) {
      return 1;
    } else {
      return 0;
    }
  }

  if (record.size() == 0) {
    return 0;
  }

  char c = record.at(0);
  int group = groups.at(0);
  int total = 0;

  if (c == '#') {
    total = hash(record, groups, group);
  } else if (c == '.') {
    total = dot(record, groups);
  } else if (c == '?') {
    total = hash(record, groups, group) + dot(record, groups);
  } else {
    throw std::exception{};
  }
  print_record({record, groups});
  std::cout << " -> " << total << '\n';
  return total;
}

int main() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::vector<condition_record> records{};
  std::string line{};
  while (std::getline(infile, line)) {
    std::vector<std::string> space_split = split(line, ' ');
    std::string record = space_split[0];

    std::vector<std::string> nums_split = split(space_split[1], ',');
    std::vector<int> groups{};
    for (auto const& num : nums_split) {
      groups.push_back(std::stoi(num));
    }

    records.push_back(condition_record{record, groups});
  }

  int total = 0;
  for (auto const& record : records) {
    total += get_num_of_arrangements(record.record, record.groups);
    std::cout << "------------------------\n";
  }
  std::cout << "Total: " << total << '\n';
}