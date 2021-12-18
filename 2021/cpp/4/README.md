# Advent of Code 2021&mdash;Day 4

- We have a `Bingo` class to represent our cards.
- We use reusable and composable lambdas for common operations.

## Part one

Here we simply play the game until the first card has won, then we accumulate
its score.

## Part two

Works similarly, we need to remove the bingos that have won. We keep track of
the last removed bingo until all numbers have been drawn.
