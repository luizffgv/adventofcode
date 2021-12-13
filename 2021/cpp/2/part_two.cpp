#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

using namespace std;

int main()
{
    ifstream in{"input.in"};

    int x{};
    int y{};
    int aim{};

    const map<char, function<void(int)>> movements{
      {'f',
       [&](int delta)
       {
           x += delta;
           y += aim * delta;
       }},
      {'d', [&](int delta) { aim += delta; }},
      {'u', [&](int delta) { aim -= delta; }}};

    for_each(istream_iterator<string>(in),
             {},
             [&](string dir)
             {
                 int offset;
                 in >> offset;
                 movements.at(dir.front())(offset);
             });

    cout << x * y << endl;
}