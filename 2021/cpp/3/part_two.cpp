#include <algorithm>
#include <concepts>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <
  bidirectional_iterator                                                 It,
  predicate<typename It::value_type::size_type, typename It::value_type> Pred,
  integral Depth = typename It::value_type::size_type>
typename It::value_type
PartOxygen(It const &begin, It const &end, Pred const &pred, Depth depth)

{
    auto const &middle{partition(begin, end, bind_front(pred, depth))};
    auto const &ones{distance(begin, middle)};
    auto const &zeros{distance(middle, end)};

    if (ones >= zeros)
    {
        if (ones == 1)
            return *begin;
        return PartOxygen(begin, middle, pred, depth + 1);
    }
    else if (zeros == 1)
        return *prev(end);
    return PartOxygen(middle, end, pred, depth + 1);
}

template <
  bidirectional_iterator                                                 It,
  predicate<typename It::value_type::size_type, typename It::value_type> Pred,
  integral Depth = typename It::value_type::size_type>
typename It::value_type
PartCO2(It const &begin, It const &end, Pred const &pred, Depth depth)

{
    auto const &middle{partition(begin, end, bind_front(pred, depth))};
    auto const &ones{distance(begin, middle)};
    auto const &zeros{distance(middle, end)};

    if (ones >= zeros)
    {
        if (zeros == 1)
            return *prev(end);
        return PartCO2(middle, end, pred, depth + 1);
    }
    if (ones == 1)
        return *begin;
    return PartCO2(begin, middle, pred, depth + 1);
}

template <bidirectional_iterator It,
          integral               Depth = typename It::value_type::size_type>
pair<typename It::value_type, typename It::value_type> Part(It const &begin,
                                                            It const &end)
{
    auto constexpr pred{[](string::size_type const &index, const string &s)
                        { return s[index] == '1'; }};

    pair<typename It::value_type, typename It::value_type> result{};

    auto const &middle{partition(begin, end, bind_front(pred, 0))};
    auto const &ones{distance(begin, middle)};
    auto const &zeros{distance(middle, end)};

    if (ones >= zeros)
    {
        if (ones == 1)
            result.first = *begin;
        else
            result.first = PartOxygen(begin, middle, pred, 1);
        if (zeros == 1)
            result.second = *prev(end);
        else
            result.second = PartCO2(middle, end, pred, 1);
    }
    else
    {
        if (ones == 1)
            result.second = *begin;
        else
            PartCO2(begin, middle, pred, 1);
        if (zeros == 1)
            result.first = *prev(end);
        else
            PartOxygen(middle, end, pred, 1);
    }

    return result;
}

int main()
{
    ifstream in{"input.in"};

    vector<string> diagnostic{istream_iterator<string>(in), {}};

    auto res{Part(begin(diagnostic), end(diagnostic))};

    auto constexpr bin_stoi{[](string const &s)
                            {
                                int i{};
                                for (auto const &ch : s)
                                    i = i << 1 | (ch == '1');
                                return i;
                            }};

    cout << bin_stoi(res.first) * bin_stoi(res.second);
}