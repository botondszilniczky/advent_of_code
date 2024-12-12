#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

void countConnectedCropsAndFences(vector<string>& data, set<pair<int, int>>& visited, int x, int y, int& fences, int& crops)
{
    visited.insert(make_pair(x,y));
    crops++;
    pair<int, int> u = {x-1, y};
    pair<int, int> d = {x+1, y};
    pair<int, int> l = {x, y-1};
    pair<int, int> r = {x, y+1};

    if (0 <= u.first && u.first < data.size() && 0 <= u.second && u.second < data[u.first].size() 
        && data[x][y] == data[u.first][u.second])
    {
        if (!(visited.find(u) != visited.end()))
        {
            countConnectedCropsAndFences(data, visited, u.first, u.second, fences, crops);
        }
    }
    else
    {
        fences++;
    }
    if (0 <= d.first && d.first < data.size() && 0 <= d.second && d.second < data[d.first].size() 
        && data[x][y] == data[d.first][d.second])
    {
        if (!(visited.find(d) != visited.end()))
        {
            countConnectedCropsAndFences(data, visited, d.first, d.second, fences, crops);
        }
    }
    else
    {
        fences++;
    }
    if (0 <= l.first && l.first < data.size() && 0 <= l.second && l.second < data[l.first].size() 
        && data[x][y] == data[l.first][l.second])
    {
        if (!(visited.find(l) != visited.end()))
        {
            countConnectedCropsAndFences(data, visited, l.first, l.second, fences, crops);
        }
    }
    else
    {
        fences++;
    }
    if (0 <= r.first && r.first < data.size() && 0 <= r.second && r.second < data[r.first].size() 
        && data[x][y] == data[r.first][r.second])
    {
        if (!(visited.find(r) != visited.end()))
        {
            countConnectedCropsAndFences(data, visited, r.first, r.second, fences, crops);
        }
    }
    else
    {
        fences++;
    }   
}

void countConnectedCropsAndConnectedFences(vector<string>& data, set<pair<int, int>>& visited, int x, int y, int& fences, int& crops)
{
    visited.insert(make_pair(x,y));
    crops++;
    pair<int, int> u = {x-1, y};
    pair<int, int> d = {x+1, y};
    pair<int, int> l = {x, y-1};
    pair<int, int> r = {x, y+1};
    pair<int, int> ul = {x-1, y-1};
    pair<int, int> ur = {x-1, y+1};
    pair<int, int> dl = {x+1, y-1};
    pair<int, int> dr = {x+1, y+1};
    

    int neigbours = 0;
    bool neigboursPlus[4] = {};
    bool neigboursCross[4] = {};


    if (0 <= u.first && u.first < data.size() && 0 <= u.second && u.second < data[u.first].size() 
        && data[x][y] == data[u.first][u.second])
    {
        if (!(visited.find(u) != visited.end()))
        {
            countConnectedCropsAndConnectedFences(data, visited, u.first, u.second, fences, crops);
        }
        neigboursPlus[0] = true;
    }
    else
    {
        neigbours++;
    }
    if (0 <= d.first && d.first < data.size() && 0 <= d.second && d.second < data[d.first].size() 
        && data[x][y] == data[d.first][d.second])
    {
        if (!(visited.find(d) != visited.end()))
        {
            countConnectedCropsAndConnectedFences(data, visited, d.first, d.second, fences, crops);
        }
        neigboursPlus[1] = true;
    }
    else
    {
        neigbours++;
    }
    if (0 <= l.first && l.first < data.size() && 0 <= l.second && l.second < data[l.first].size() 
        && data[x][y] == data[l.first][l.second])
    {
        if (!(visited.find(l) != visited.end()))
        {
            countConnectedCropsAndConnectedFences(data, visited, l.first, l.second, fences, crops);
        }
        neigboursPlus[2] = true;
    }
    else
    {
        neigbours++;
    }
    if (0 <= r.first && r.first < data.size() && 0 <= r.second && r.second < data[r.first].size() 
        && data[x][y] == data[r.first][r.second])
    {
        if (!(visited.find(r) != visited.end()))
        {
            countConnectedCropsAndConnectedFences(data, visited, r.first, r.second, fences, crops);
        }
        neigboursPlus[3] = true;
    }
    else
    {
        neigbours++;
    }

    if (0 <= ul.first && ul.first < data.size() && 0 <= ul.second && ul.second < data[ul.first].size() 
        && data[x][y] != data[ul.first][ul.second])
    {
        neigboursCross[0] = true;
    }
    if (0 <= ur.first && ur.first < data.size() && 0 <= ur.second && ur.second < data[ur.first].size() 
        && data[x][y] != data[ur.first][ur.second])
    {
        neigboursCross[1] = true;
    }
    if (0 <= dl.first && dl.first < data.size() && 0 <= dl.second && dl.second < data[dl.first].size() 
        && data[x][y] != data[dl.first][dl.second])
    {
        neigboursCross[2] = true;
    }
    if (0 <= dr.first && dr.first < data.size() && 0 <= dr.second && dr.second < data[dr.first].size() 
        && data[x][y] != data[dr.first][dr.second])
    {
        neigboursCross[3] = true;
    }


    
    if (!neigboursPlus[0] && !neigboursPlus[2]) //UL L corner
    {
        // This is a up left corner
        fences++;
    }
    if (!neigboursPlus[0] && !neigboursPlus[3]) //UR L corner
    {
        // This is a up right corner
        fences++;
    }
    if (!neigboursPlus[1] && !neigboursPlus[2]) //DL L corner
    {
        // This is a down left corner
        fences++;
    }
    if (!neigboursPlus[1] && !neigboursPlus[3]) //DR L corner
    {
        // This is a down right corner
        fences++;
    }

    if (neigboursPlus[0] && neigboursPlus[2] && neigboursCross[0]) //UL V corner
    {
        // This is a up left corner
        fences++;
    }
    if (neigboursPlus[0] && neigboursPlus[3] && neigboursCross[1]) //UR V corner
    {
        // This is a up right corner
        fences++;
    }
    if (neigboursPlus[1] && neigboursPlus[2] && neigboursCross[2]) //DL V corner
    {
        // This is a down left corner
        fences++;
    }
    if (neigboursPlus[1] && neigboursPlus[3] && neigboursCross[3]) //DR V corner
    {
        // This is a down right corner
        fences++;
    }
}

int sol1(vector<string> data)
{
    set<pair<int, int>> visited;
    int sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            if (!(visited.find(make_pair(i,j)) != visited.end()))
            {
                int fences = 0;
                int crops = 0;
                countConnectedCropsAndFences(data, visited, i, j, fences, crops);
                sum += fences * crops;
            }
        }
    }
    cout << sum << endl;
    return 0;
}

int sol2(vector<string> data)
{
    set<pair<int, int>> visited;
    int sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            if (!(visited.find(make_pair(i,j)) != visited.end()))
            {
                int fences = 0;
                int crops = 0;
                countConnectedCropsAndConnectedFences(data, visited, i, j, fences, crops);
                sum += fences * crops;
            }
        }
    }
    cout << sum << endl;
    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/12_input.txt");
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
