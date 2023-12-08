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

enum HandType {
  high_card = 0,
  one_pair,
  two_pair,
  three_of_a_kind,
  full_house,
  four_of_a_kind,
  five_of_a_kind
};

std::map<char, int> card_ranks{
    {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3},  {'6', 4},  {'7', 5}, {'8', 6},
    {'9', 7}, {'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12}};

HandType get_type(std::string& hand) {
  std::map<char, int> char_counts{};
  for (int i = 0; i < hand.size(); i++) {
    if (char_counts.find(hand.at(i)) == char_counts.end()) {
      char_counts.emplace(hand.at(i), 1);
    } else {
      char_counts[hand.at(i)] = char_counts[hand.at(i)] + 1;
    }
  }

  if (char_counts.size() == 1) {
    return five_of_a_kind;
  }

  if (char_counts.size() == 5) {
    return high_card;
  }

  std::vector<int> counts{};
  for (auto const& [card, count] : char_counts) {
    counts.push_back(count);
  }
  std::sort(counts.begin(), counts.end());

  if (counts == std::vector{1, 4}) {
    return four_of_a_kind;
  }

  if (counts == std::vector{2, 3}) {
    return full_house;
  }

  if (counts == std::vector{1, 1, 3}) {
    return three_of_a_kind;
  }

  if (counts == std::vector{1, 2, 2}) {
    return two_pair;
  }

  // if (counts == std::vector{1, 1, 1, 2}) {
  return one_pair;
  // }
}

int main() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
  }

  std::string line{};
  std::vector<std::pair<std::string, int>> hands_and_bids{};
  while (std::getline(infile, line)) {
    auto line_split = split(line, ' ');
    std::pair<std::string, int> hand_and_bid = {line_split[0],
                                                std::stoi(line_split[1])};
    hands_and_bids.push_back(hand_and_bid);
  }

  std::sort(
      hands_and_bids.begin(), hands_and_bids.end(),
      [](std::pair<std::string, int> a, std::pair<std::string, int> b) {
        auto a_type = get_type(a.first);
        auto b_type = get_type(b.first);

        if (a_type == b_type) {
          // sort per card
          for (int i = 0; i < a.first.size(); i++) {
            if (a.first.at(i) == b.first.at(i)) {
              continue;
            } else if (card_ranks[a.first.at(i)] > card_ranks[b.first.at(i)]) {
              return false;
            } else {
              return true;
            }
          }
          throw std::exception{};
        } else if (a_type > b_type) {
          return false;
        } else {
          return true;
        }
        throw std::exception{};
      });

  std::uint64_t total = 0;
  int count = 1;
  for (auto const& [hand, bid] : hands_and_bids) {
    std::cout << hand << '\n';
    total += (bid * count);
    count++;
  }
  std::cout << total << '\n';
}