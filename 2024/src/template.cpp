#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <vector>

using namespace std;

int sol1(vector<string> data)
{
    return 0;
}

int sol2(vector<string> data)
{
    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/<DAY>_input.txt");
    vector<string> data;
    string line;
    while(getline(file, line))
    {
        data.push_back(line);
    }
    sol1(data);
    sol2(data);

    return 0;
}
