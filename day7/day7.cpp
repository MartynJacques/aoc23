#include <array>
#include <iostream>

int main() {
  std::uint64_t result = 1;

  std::uint64_t game_duration = 49877895;
  std::uint64_t record_distance = 356137815021882;

  std::uint64_t count = 0;
  for (std::uint64_t hold_time = 0; hold_time <= game_duration; hold_time++) {
    std::uint64_t travel_time = game_duration - hold_time;
    std::uint64_t travel_distance =
        travel_time * hold_time;  // hold_time = speed
    if (travel_distance > record_distance) {
      count++;
    }
  }
  result = result * count;

  std::cout << result << '\n';
}