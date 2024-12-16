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

struct pos
{
    int x, y;
};

bool operator==(const pos& a,const pos& b){ return tuple(a.x,a.y) == tuple(b.x,b.y); }
pos operator+(const pos& a, const pos& b){ return { a.x + b.x, a.y + b.y }; }
pos operator*(const pos& a, const pos& b){ return { a.x * b.x, a.y * b.y }; }
pos operator%(const pos& a, const pos& b){ return { a.x % b.x, a.y % b.y }; }

struct robot
{
    pos p, v;
};

pos mod(const pos& a, const pos& b)
{
    return ((a % b) + b) % b;
}

int sol1(vector<string> data)
{
    int H = 11;
    int W = 7;
    int seconds = 100;
    vector<vector<int>> safetyFactor(H, vector<int>(W, 0));
    vector<robot> robots;
    for (string line : data) 
    {
        regex reg("p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)");
        smatch m;
        if (regex_search(line, m, reg))
        {
            int p1 = stoi(m[1]);
            int p2 = stoi(m[2]);
            int v1 = stoi(m[3]);
            int v2 = stoi(m[4]);
            robots.push_back(robot{{p1,p2}, {v1,v2}});
            p1 = p1 < 0 ? W - p1 : p1;
            p2 = p2 < 0 ? H - p2 : p2;
            v1 = v1 < 0 ? W - v1 : v1;
            v2 = v2 < 0 ? H - v2 : v2;

            //                  <>  ^v
            pair<int, int> p = {p1, p2};
            pair<int, int> v = {v1, v2};

            int y = (p.first + seconds * v.first) % W;
            int x = (p.second + seconds * v.second) % H;
            safetyFactor[x][y] += 1;
        }
    }
    
    int res = 0;
    int act = 0;
    for (int i = 0; i < safetyFactor.size()/2; i++)
    {
        for ( int j = 0; j < safetyFactor[i].size()/2; j++)
        {
            act += safetyFactor[i][j];
        }
    }
    res = act;
    act = 0;
    for (int i = 0; i < safetyFactor.size()/2; i++)
    {
        for ( int j = safetyFactor[i].size()/2+1; j < safetyFactor[i].size(); j++)
        {
            act += safetyFactor[i][j];
        }
    }
    res *= act;
    act = 0;
    for (int i = safetyFactor.size()/2+1; i < safetyFactor.size(); i++)
    {
        for ( int j = 0; j < safetyFactor[i].size()/2; j++)
        {
            act += safetyFactor[i][j];
        }
    }
    res *= act;
    act = 0;
    for (int i = safetyFactor.size()/2+1; i < safetyFactor.size(); i++)
    {
        for ( int j = safetyFactor[i].size()/2+1; j < safetyFactor[i].size(); j++)
        {
            act += safetyFactor[i][j];
        }
    }
    res *= act;

    // for (size_t i = 0; i < safetyFactor.size(); i++)
    // {
    //     for (size_t j = 0; j < safetyFactor[i].size(); j++)
    //     {
    //         if (i == H/2 || j == W/2)
    //         {
    //             cout << "# ";
    //             continue;
    //         }
            
    //         cout << safetyFactor[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    

    cout << res << endl;

    pos size{W, H};
    int quads[4] = {0, 0, 0, 0};
    for (auto& [position, velocity] : robots)
    {
        position = mod(position + velocity * pos{100, 100}, size);
        if (position.x != size.x/2 && position.y != size.y/2)
        {
            int ix = position.y < (size.y/2);
            int iy = position.x < (size.x/2);
            quads[iy*2 + ix]++;
        }
    }
    cout << "new: " << quads[0] * quads[1] * quads[2] * quads[3] << endl;

    return 0;
}

int sol2(vector<string> data)
{
    double safetyFactor = 0;
    
    cout << fixed << setprecision(0) << safetyFactor << endl;
    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/14_test_input.txt");
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
