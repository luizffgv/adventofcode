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

    const map<char, function<void(int)>> movements{
      {'f', [&](int delta) { x += delta; }},
      {'d', [&](int delta) { y += delta; }},
      {'u', [&](int delta) { y -= delta; }}};

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