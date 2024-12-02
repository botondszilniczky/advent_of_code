#include <fstream>
#include <iostream>
#include <list>
#include <math.h>

using namespace std;

int sol1(list<int> &first, list<int> &second)
{
    auto x = first.begin();
    auto y = second.begin();
    int sum = 0;
    while (x != first.end() && y != second.end())
    {
        // cout << *x << "\t" << *y << "\t" << abs(*x-*y) << endl;
        sum += abs(*x-*y);
        x++;
        y++;
    }
    cout << sum << endl;
    return sum;
}

int sol2(list<int> &first, list<int> &second)
{
    int sum = 0;
    for (auto x = first.begin(); x != first.end(); x++)
    {
        int numOfOccurances = 0;
        for (auto y = second.begin(); y != second.end() && *y <= *x; y++)
        {
            if (*y == *x)
            {
                numOfOccurances++;
            }
        }
        sum += numOfOccurances * (*x);
    }
    cout << sum << endl;
    return sum;
}

int main(int argc, char const *argv[])
{
    list<int> first;
    list<int> second;

    ifstream f("./build/2024/01_input.txt");
    int a,b;
    while (f >> a >> b)
    {
        // cout << a << "\t" << b << endl;
        first.push_back(a);
        second.push_back(b);
    }

    first.sort();
    second.sort();
    
    sol1(first, second);
    sol2(first, second);
    
    return 0;
}
