#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <string>

using namespace std;

int main()
{
    ifstream in{"input.in"};

    map<string::size_type, pair<size_t, size_t>> counts;
    for_each(
      istream_iterator<string>(in),
      {},
      [&counts](string const& line)
      {
          for (auto const& index : ranges::views::iota(
                 remove_reference_t<decltype(line)>::size_type{0}, line.size()))
          {
              if (line[index] == '1')
                  ++counts[index].first;
              ++counts[index].second;
          }
      });

    int gamma{};
    int epsilon{};
    for_each(counts.cbegin(),
             counts.cend(),
             [&gamma, &epsilon](decltype(counts)::const_reference key_val_pair)
             {
                 auto const& ones{key_val_pair.second.first};
                 auto const& total{key_val_pair.second.second};

                 gamma <<= 1;
                 epsilon <<= 1;

                 (ones > total / 2 ? gamma : epsilon) |= 0b1;
             });

    cout << gamma * epsilon << endl;
}