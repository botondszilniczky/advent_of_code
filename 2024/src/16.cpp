#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <vector>
#include <queue>

using namespace std;

enum Dir
{
    NORTH, EAST, SOUTH, WEST
};

int step = 1;
int turn = 1000;
const int INF = INT32_MAX;

pair<int, int> neigbours[4] = {
//   NORTH    EAST    SOUTH   WEST
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

map<pair<int, int>, int> revNeigbours = {
    {{-1, 0}, 0}, {{0, 1}, 1}, {{1, 0}, 2}, {{0, -1}, 3}
};

struct cell
{
    pair<int, int> pos;
    int distance;
    int direction;
    cell(pair<int, int> p, int dis, int dir) : pos(p), distance(dis), direction(dir){};
};

pair<int, int> operator+(pair<int, int> a, pair<int, int> b)
{
    return make_pair(a.first+b.first, a.second+b.second);
}

pair<int, int> operator-(pair<int, int> a, pair<int, int> b)
{
    return make_pair(a.first-b.first, a.second-b.second);
}

bool operator<(const pair<int, int>& a, const pair<int, int>& b)
{
    if (a.first == b.first)
    {
        return a.second < b.second;
    }
    return a.first < b.first;
}

bool operator<(const cell &a, const cell &b)
{
    if (a.distance == b.distance)
    {
        if (a.pos == b.pos)
        {
            return a.direction < b.direction;
        }
        
        return a.pos < b.pos;
    }
    return (a.distance < b.distance);
}

bool operator==(const cell &a, const cell &b)
{
    return a.pos == b.pos && a.distance == b.distance;
}

ostream& operator<<(ostream& os, pair<int, int> p)
{
    
    return os << "[" << p.first << ", " << p.second << "]";
}

ostream& operator<<(ostream& os, set<cell> st)
{
    os << "{";
    for (auto [pos, dis, dir] : st)
    {
        os << pos << dis << ", ";
    }
    return os << "}" << endl;
}

int calculateEndPrize(vector<string>& grid, pair<int, int> s, pair<int, int> e)
{
    int ROW = grid.size();
    int COL = grid[0].size();
    int dis[ROW][COL];
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            dis[i][j] = INF;
        }
    }

    set<cell> st;
    set<pair<int, int>> processed;

    st.insert(cell(s, 0, 1));
    dis[s.first][s.second] = 0;

    while (!st.empty())
    {
        cell c = *st.begin();
        st.erase(st.begin());
        if (c.pos == e)
        {
            break;
        }
        
        processed.insert(c.pos);

        for (int i = 0; i < 4; i++)
        {
            // neigbour pos
            pair<int, int> n = c.pos + neigbours[i];
            // if Wall --> continue
            if (grid[n.first][n.second] == '#')
            {
                continue;
            }
            // relative direction to actual node
            pair<int, int> nRelativeDir = n - c.pos;
            // turn needed
            int turnCount = (abs(revNeigbours[nRelativeDir] - c.direction) % 3);
            // cost of reaching neigbour node from actual node
            int cost = dis[c.pos.first][c.pos.second] + turnCount * turn + step;

            if (processed.find(n) != processed.end())
            {
                continue;
            }

            if (dis[n.first][n.second] > cost)
            {
                dis[n.first][n.second] = cost;
                st.insert(cell(n, dis[n.first][n.second], revNeigbours[nRelativeDir]));
            }
        }
    }
    // for (int i = 0; i < ROW; i++)
    // {
    //     for (int j = 0; j < COL; j++)
    //     {
    //         cout << dis[i][j] << "\t";
    //     }
    //     cout << endl;
    // }
    
    // cout << e << endl;
    return dis[e.first][e.second];
}

int sol1(vector<string> data)
{
    pair<int, int> start;
    pair<int, int> end;
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            if (data[i][j] == 'S')
            {
                start = make_pair(i, j);
            }
            if (data[i][j] == 'E')
            {
                end = make_pair(i, j);
            }
        }
    }
    int shortest = calculateEndPrize(data, start, end);

    cout << shortest << endl;
    
    return 0;
}

int sol2(vector<string> data)
{
    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/16_input.txt");
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
