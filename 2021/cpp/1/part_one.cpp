#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

int main()
{
    ifstream in{"input.in"};

    int count{};
    for_each(istream_iterator<int>(in),
             {},
             [&, prev{*istream_iterator<int>(in)}](int cur) mutable
             {
                 if (prev < cur)
                     ++count;
                 prev = cur;
             });
    cout << count << endl;
}