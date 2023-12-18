#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <queue>
#include <sstream>
#include <unordered_set>
#include <vector>

using grid_t = std::vector<std::vector<char>>;
using coord_t = std::pair<int, int>;

struct coord_t_hash {
  std::size_t operator()(const coord_t& c) const {
    auto hash = c.first;
    hash *= 37;
    hash += c.second;
    hash *= 37;
    return hash;
  }
};

enum direction_t { north, east, south, west };

class position_t {
 public:
  coord_t coord;
  direction_t direction;

  bool operator==(position_t const& other) const {
    return coord == other.coord && direction == other.direction;
  }

  struct HashFunction {
    std::size_t operator()(const position_t& p) const {
      auto hash = p.coord.first;
      hash *= 37;
      hash += p.coord.second;
      hash *= 37;
      hash += p.direction;
      return hash;
    }
  };
};

std::optional<position_t> go_north(coord_t coord) {
  if (coord.first > 0) {
    return {{{coord.first - 1, coord.second}, north}};
  }
  return {};
}

std::optional<position_t> go_south(coord_t coord, grid_t grid) {
  if (coord.first < grid.size() - 1) {
    return {{{coord.first + 1, coord.second}, south}};
  }
  return {};
}

std::optional<position_t> go_west(coord_t coord) {
  if (coord.second > 0) {
    return {{{coord.first, coord.second - 1}, west}};
  }
  return {};
}

std::optional<position_t> go_east(coord_t coord, grid_t grid) {
  if (coord.second < grid.at(0).size() - 1) {
    return {{{coord.first, coord.second + 1}, east}};
  }
  return {};
}

std::vector<position_t> facing_north(position_t const& pos,
                                     grid_t const& grid) {
  char curr_char = grid.at(pos.coord.first).at(pos.coord.second);
  switch (curr_char) {
    case '.':
    case '|': {
      auto tmp = go_north(pos.coord);
      if (tmp.has_value()) {
        return {{*tmp}};
      }
      break;
    }
    case '/': {
      auto tmp = go_east(pos.coord, grid);
      if (tmp.has_value()) {
        return {{*tmp}};
      }
      break;
    }
    case '\\': {
      auto tmp = go_west(pos.coord);
      if (tmp.has_value()) {
        return {{*tmp}};
      }
      break;
    }
    case '-': {
      std::vector<position_t> res{};
      auto tmp = go_west(pos.coord);
      if (tmp.has_value()) {
        res.push_back(*tmp);
      }
      tmp = go_east(pos.coord, grid);
      if (tmp.has_value()) {
        res.push_back(*tmp);
      }
      return res;
      break;
    }
    default: {
      std::cout << "Oops, default in facing north\n";
      throw std::exception{};
    }
  }
  return {};
}

std::vector<position_t> facing_south(position_t const& pos,
                                     grid_t const& grid) {
  char curr_char = grid.at(pos.coord.first).at(pos.coord.second);
  switch (curr_char) {
    case '.':
    case '|': {
      auto tmp = go_south(pos.coord, grid);
      if (tmp.has_value()) {
        return {{*tmp}};
      }
      break;
    }
    case '/': {
      auto tmp = go_west(pos.coord);
      if (tmp.has_value()) {
        return {{*tmp}};
      }
      break;
    }
    case '\\': {
      auto tmp = go_east(pos.coord, grid);
      if (tmp.has_value()) {
        return {{*tmp}};
      }
      break;
    }
    case '-': {
      std::vector<position_t> res{};
      auto tmp = go_west(pos.coord);
      if (tmp.has_value()) {
        res.push_back(*tmp);
      }
      tmp = go_east(pos.coord, grid);
      if (tmp.has_value()) {
        res.push_back(*tmp);
      }
      return res;
      break;
    }
    default: {
      std::cout << "Oops, default in facing south\n";
      throw std::exception{};
    }
  }
  return {};
}

std::vector<position_t> facing_west(position_t const& pos, grid_t const& grid) {
  char curr_char = grid.at(pos.coord.first).at(pos.coord.second);
  switch (curr_char) {
    case '.':
    case '-': {
      auto tmp = go_west(pos.coord);
      if (tmp.has_value()) {
        return {{*tmp}};
      }
      break;
    }
    case '/': {
      auto tmp = go_south(pos.coord, grid);
      if (tmp.has_value()) {
        return {{*tmp}};
      }
      break;
    }
    case '\\': {
      auto tmp = go_north(pos.coord);
      if (tmp.has_value()) {
        return {{*tmp}};
      }
      break;
    }
    case '|': {
      std::vector<position_t> res{};
      auto tmp = go_north(pos.coord);
      if (tmp.has_value()) {
        res.push_back(*tmp);
      }
      tmp = go_south(pos.coord, grid);
      if (tmp.has_value()) {
        res.push_back(*tmp);
      }
      return res;
      break;
    }
    default: {
      std::cout << "Oops, default in facing west\n";
      throw std::exception{};
    }
  }
  return {};
}

std::vector<position_t> facing_east(position_t const& pos, grid_t const& grid) {
  char curr_char = grid.at(pos.coord.first).at(pos.coord.second);
  switch (curr_char) {
    case '.':
    case '-': {
      auto tmp = go_east(pos.coord, grid);
      if (tmp.has_value()) {
        return {{*tmp}};
      }
      break;
    }
    case '/': {
      auto tmp = go_north(pos.coord);
      if (tmp.has_value()) {
        return {{*tmp}};
      }
      break;
    }
    case '\\': {
      auto tmp = go_south(pos.coord, grid);
      if (tmp.has_value()) {
        return {{*tmp}};
      }
      break;
    }
    case '|': {
      std::vector<position_t> res{};
      auto tmp = go_north(pos.coord);
      if (tmp.has_value()) {
        res.push_back(*tmp);
      }
      tmp = go_south(pos.coord, grid);
      if (tmp.has_value()) {
        res.push_back(*tmp);
      }
      return res;
      break;
    }
    default: {
      std::cout << "Oops, default in facing east\n";
      throw std::exception{};
    }
  }
  return {};
}

std::vector<position_t> get_nbrs(position_t const& pos, grid_t const& grid) {
  direction_t dir = pos.direction;

  switch (dir) {
    case north: {
      return facing_north(pos, grid);
      break;
    }
    case south: {
      return facing_south(pos, grid);
      break;
    }
    case east: {
      return facing_east(pos, grid);
      break;
    }
    case west: {
      return facing_west(pos, grid);
      break;
    }
    default: {
      std::cout << "Oops, default in getnbrs\n";
      throw std::exception{};
      break;
    }
  }
  std::cout << "Oops, end of getnbrs\n";
  throw std::exception{};
}

int main() {
  std::ifstream infile("input.txt");
  if (infile.fail()) {
    std::cout << "Failed to open file\n";
    throw std::exception{};
  }

  grid_t grid{};
  {
    std::string input_line{};
    while (std::getline(infile, input_line)) {
      std::vector<char> grid_row{};
      for (auto const c : input_line) {
        grid_row.push_back(c);
      }
      grid.push_back(grid_row);
    }
  }

  int max = 0;
  for (int i = 0; i < grid.size(); i++) {
    {
      std::queue<position_t> positions{};
      std::unordered_set<position_t, position_t::HashFunction> visited{};
      std::unordered_set<coord_t, coord_t_hash> visited_coords{};
      positions.push({{i, 0}, east});
      while (!positions.empty()) {
        position_t curr_pos = positions.front();
        positions.pop();
        visited.insert(curr_pos);
        visited_coords.insert(curr_pos.coord);
        std::vector<position_t> nbrs = get_nbrs(curr_pos, grid);
        for (position_t const& nbr : nbrs) {
          if (visited.find(nbr) == visited.end()) {
            positions.push(nbr);
          }
        }
      }
      if (visited_coords.size() > max) {
        max = visited_coords.size();
      }
    }

    {
      std::queue<position_t> positions{};
      std::unordered_set<position_t, position_t::HashFunction> visited{};
      std::unordered_set<coord_t, coord_t_hash> visited_coords{};
      positions.push({{i, grid.at(0).size() - 1}, west});
      while (!positions.empty()) {
        position_t curr_pos = positions.front();
        positions.pop();
        visited.insert(curr_pos);
        visited_coords.insert(curr_pos.coord);
        std::vector<position_t> nbrs = get_nbrs(curr_pos, grid);
        for (position_t const& nbr : nbrs) {
          if (visited.find(nbr) == visited.end()) {
            positions.push(nbr);
          }
        }
      }
      if (visited_coords.size() > max) {
        max = visited_coords.size();
      }
    }
  }

  {
    for (int j = 0; j < grid.at(0).size() - 1; j++) {
      std::queue<position_t> positions{};
      std::unordered_set<position_t, position_t::HashFunction> visited{};
      std::unordered_set<coord_t, coord_t_hash> visited_coords{};
      positions.push({{0, j}, south});
      while (!positions.empty()) {
        position_t curr_pos = positions.front();
        positions.pop();
        visited.insert(curr_pos);
        visited_coords.insert(curr_pos.coord);
        std::vector<position_t> nbrs = get_nbrs(curr_pos, grid);
        for (position_t const& nbr : nbrs) {
          if (visited.find(nbr) == visited.end()) {
            positions.push(nbr);
          }
        }
      }
      if (visited_coords.size() > max) {
        max = visited_coords.size();
      }
    }
  }

  {
    for (int j = 0; j < grid.at(0).size() - 1; j++) {
      std::queue<position_t> positions{};
      std::unordered_set<position_t, position_t::HashFunction> visited{};
      std::unordered_set<coord_t, coord_t_hash> visited_coords{};
      positions.push({{grid.size() - 1, j}, north});
      while (!positions.empty()) {
        position_t curr_pos = positions.front();
        positions.pop();
        visited.insert(curr_pos);
        visited_coords.insert(curr_pos.coord);
        std::vector<position_t> nbrs = get_nbrs(curr_pos, grid);
        for (position_t const& nbr : nbrs) {
          if (visited.find(nbr) == visited.end()) {
            positions.push(nbr);
          }
        }
      }
      if (visited_coords.size() > max) {
        max = visited_coords.size();
      }
    }
  }

  std::cout << max << '\n';
}