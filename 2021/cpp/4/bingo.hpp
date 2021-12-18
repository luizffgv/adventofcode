#ifndef BINGO_HPP
#define BINGO_HPP

#include <algorithm>   // all_of
#include <concepts>    // equality_comparable
#include <cstddef>     // size_t
#include <functional>  // identity
#include <iterator>    // input_iterator
#include <type_traits> // remove_reference_t
#include <vector>      // vector

/**
 * @brief A bingo card.
 *
 * @tparam T Type for the card values.
 */
template <std::equality_comparable T>
class Bingo
{
    /// Values.
    std::vector<std::vector<T>> grid;
    /// Values that have been marked.
    std::vector<std::vector<bool>> marked;
    /// Flag for whether the card has won.
    bool won{};

public:
    /**
     * @brief Constructs a bingo card from a pair of iterators.
     *
     * @tparam It Iterator type.
     * @param cols Number of columns of the board.
     * @param begin Iterator to the beginning of the values.
     * @param end Iterator to the end of the values.
     */
    template <std::input_iterator It>
    Bingo(std::size_t cols, It begin, It const &end)
    {
        while (distance(begin, end) >= cols)
        {
            grid.emplace_back(begin, next(begin, cols));
            marked.emplace_back(grid.back().size(), false);
            advance(begin, cols);
        }
    }

    /**
     * @brief Marks a value in the board.
     *
     * @param val Value to be marked.
     */
    void Mark(T const &val)
    {
        typename decltype(grid)::difference_type y{0};
        for (typename decltype(grid)::const_reference row : as_const(grid))
        {
            if (typename std::remove_reference_t<decltype(row)>::const_iterator
                  found{find(row.cbegin(), row.cend(), val)};
                found != row.cend())
            {
                auto const x{distance(row.cbegin(), found)};

                marked[y][x] = true;

                if (std::all_of(
                      marked[y].cbegin(), marked[y].cend(), std::identity{})
                    || std::all_of(
                      marked.cbegin(),
                      marked.cend(),
                      [&x](typename decltype(marked)::const_reference row)
                      { return row[x]; }))
                    won = true;

                break;
            }

            ++y;
        }
    }

    /**
     * @brief Check the board for a win.
     *
     * @return true Board has won.
     * @return false Board has not yet won.
     */
    bool Won() const { return won; }

    /**
     * @brief Returns the list of unmarked values.
     *
     * @return vector<T> List of unmarked values.
     */
    std::vector<T> unmarked() const
    {
        std::vector<T> res;

        for (typename decltype(grid)::size_type y{0}; y < grid.size(); ++y)
            for (typename decltype(grid)::value_type::size_type x{0};
                 x < grid[y].size();
                 ++x)

                if (!marked[y][x])
                    res.push_back(grid[y][x]);

        return res;
    }
};

#endif // #ifndef BINGO_HPP
