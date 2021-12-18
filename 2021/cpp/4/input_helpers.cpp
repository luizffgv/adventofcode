#include "input_helpers.hpp"

#include "bingo.hpp"
#include "globals.hpp"

#include <istream> // istream
#include <sstream> // istringstream
#include <string>  // string, getline, stoi
#include <utility> // move
#include <vector>  // vector

// Takes a line from an istream and returns it as an isstream.
std::function<std::istringstream(std::istream &)> const line_to_isstream{
  [](std::istream &is)
  {
      std::string str;
      std::getline(is, str);
      return std::istringstream{std::move(str)};
  }};

// Takes an istream with comma-separated ints and puts them in a vector.
std::function<std::vector<int>(std::istream &&)> const istream_to_ints{
  [](std::istream &&is)
  {
      std::vector<int> v;
      std::string      tmp;
      while (getline(is, tmp, ','))
          v.emplace_back(std::stoi(tmp));
      return v;
  }};

// Composition of line_to_isstream and istream_to_ints.
std::function<std::vector<int>(std::istream &)> const line_to_ints{
  [](std::istream &is) { return istream_to_ints(line_to_isstream(is)); }};
