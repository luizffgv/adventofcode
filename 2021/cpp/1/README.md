# Advent of Code 2021&mdash;Day 1

- The count is calculated as we read the values using `istream_iterator`.
- No loops were manually written.

## Part one

Here we use a stateful lambda that stores the previous reading so we can compare
to the most recent one.

## Part two

Here we keep track of the last 3 depth readings in a `deque` (a `queue` has no
`back_inserter`). At each iteration we check if the current reading is greater
than the reading that is going to be removed, because that's enough to know if
we went up or down.
