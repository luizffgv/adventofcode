#ifndef INPUT_HELPERS
#define INPUT_HELPERS

#include "bingo.hpp"
#include "globals.hpp"

#include <functional> // function
#include <istream>    // istream
#include <optional>   // optional
#include <sstream>    // istringstream
#include <vector>     // vector

// Takes a line from an istream and returns it as an isstream.
std::function<std::istringstream(std::istream &)> extern const line_to_isstream;

// Takes an istream with comma-separated ints and puts them in a vector.
std::function<std::vector<int>(std::istream &&)> extern const istream_to_ints;

// Composition of line_to_isstream and istream_to_ints.
std::function<std::vector<int>(std::istream &)> extern const line_to_ints;

// Scans the entire istream for bingo cards.
template <template <typename...> class Container>
auto constexpr istream_to_bingos{
  [](std::istream &is)
  {
      Container<Bingo<int>> bingos;

      std::optional<std::vector<int>> bingo_nums;
      while (is)
      {
          auto line{line_to_isstream(is)};
          if (!line.str().size())
          {
              if (bingo_nums)
                  bingos.emplace_back(
                    cols, bingo_nums->cbegin(), bingo_nums->cend());
              bingo_nums.emplace();
          }
          else
          {
              int num;
              while (line >> num)
                  bingo_nums->emplace_back(num);
          }
      }

      return bingos;
  }};

#endif // #ifndef INPUT_HELPERS
