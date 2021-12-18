#include "bingo.hpp"
#include "input_helpers.hpp"

#include <fstream>  // ifstream
#include <iostream> // cout, endl
#include <numeric>  // accumulate
#include <utility>  // as_const
#include <vector>   // vector

using std::accumulate;
using std::as_const;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

int main()
{
    ifstream in{"input.in"};

    auto draws{line_to_ints(in)};
    auto bingos{istream_to_bingos<vector>(in)};

    for (decltype(draws)::const_reference draw : as_const(draws))
        for (decltype(bingos)::reference bingo : bingos)
        {
            bingo.Mark(draw);
            if (bingo.Won())
            {
                auto const unmarked{bingo.unmarked()};
                cout << accumulate(unmarked.cbegin(),
                                   unmarked.cend(),
                                   decltype(unmarked)::value_type{})
                          * draw
                     << endl;
                ;
                return 0;
            }
        }

    return 1;
}
