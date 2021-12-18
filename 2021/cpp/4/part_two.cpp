#include "input_helpers.hpp"

#include <fstream>  // ifstream
#include <iostream> // cout, endl
#include <list>     // list
#include <numeric>  // accumulate
#include <optional> // optional
#include <queue>    // queue
#include <utility>  // move

using std::accumulate;
using std::cout;
using std::endl;
using std::ifstream;
using std::list;
using std::move;
using std::optional;
using std::queue;

int main()
{
    ifstream in{"input.in"};

    auto const draws{line_to_ints(in)};
    auto       bingos{istream_to_bingos<list>(in)};
    // Bingos that will be removed
    queue<decltype(bingos)::const_iterator> won;
    optional<decltype(bingos)::value_type>  won_last;
    decltype(draws)::value_type             draw_last;

    for (auto draw_it{draws.cbegin()}; draw_it != draws.cend(); ++draw_it)
    {
        for (auto bingo_it{bingos.begin()}; bingo_it != bingos.end();
             ++bingo_it)
        {
            bingo_it->Mark(*draw_it);
            if (bingo_it->Won())
            {
                draw_last = *draw_it;
                won.emplace(bingo_it);
            }
        }

        while (won.size())
        {
            won_last = move(*won.front());
            bingos.erase(won.front());
            won.pop();
        }
    }

    auto const unmarked{won_last->unmarked()};
    cout << accumulate(unmarked.cbegin(),
                       unmarked.cend(),
                       decltype(unmarked)::value_type{})
              * draw_last
         << endl;

    return 0;
}
