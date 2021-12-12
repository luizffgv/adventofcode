#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

int main()
{
    ifstream in{"input.in"};

    deque<int> q;
    copy_n(istream_iterator<int>(in), 3, back_inserter(q));

    int count{};
    for_each(istream_iterator<int>(in),
             {},
             [&](int cur)
             {
                 if (q.front() < cur)
                     ++count;
                 q.pop_front();
                 q.push_back(cur);
             });
    cout << count << endl;
}