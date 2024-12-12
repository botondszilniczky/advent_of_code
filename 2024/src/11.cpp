#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<pair<double, int>, double> cache;

double calculateRocks(double stone, int blinks)
{
    if (blinks == 0)
    {
        return 1;
    }
    if (cache.find(make_pair(stone, blinks)) != cache.end())
    {
        return cache[make_pair(stone, blinks)];
    }
    if (stone == 0)
    {
        double res = calculateRocks(1, blinks-1);
        cache.insert({make_pair(stone, blinks), res});
        return res;
    }
    stringstream ss;
    ss << fixed << setprecision(0) << stone;
    string s;
    ss >> s;
    int length = s.size();
    if (length % 2 == 0)
    {
        double res = calculateRocks(stod(s.substr(0, length/2)), blinks-1) + calculateRocks(stod(s.substr(length/2, length/2)), blinks-1);
        cache.insert({make_pair(stone, blinks), res});
        return res;
    }
    double res = calculateRocks((stone * 2024), blinks-1);
    cache.insert({make_pair(stone, blinks), res});
    return res;
}

int sol1(string data)
{
    int blinks = 25;
    stringstream ss;
    ss << data;
    double num = 0;
    double sum = 0;
    while (ss >> num)
    {
        sum += calculateRocks(num, blinks);
    }

    cout << fixed << setprecision(0) << sum << endl;
    return 0;
}

int sol2(string data)
{
    int blinks = 75;
    stringstream ss;
    ss << data;
    double num = 0;
    double sum = 0;
    while (ss >> num)
    {
        sum += calculateRocks(num, blinks);
    }

    cout << fixed << setprecision(0) << sum << endl;
    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/11_input.txt");
    vector<string> data;
    string line;
    while(getline(file, line))
    {
        data.push_back(line);
    }
    sol1(data[0]);
    sol2(data[0]);

    return 0;
}
