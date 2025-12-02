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
        os << pos << dis << "; ";
    }
    return os << "}" << endl;
}

ostream& operator<<(ostream& os, cell c)
{
    return os << c.pos << "\t" << c.distance;
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
        // cout << c.pos+make_pair(1,1) << " " << c.distance << " " << c.direction << endl;
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
            int dir = revNeigbours[nRelativeDir] - c.direction;
            dir = abs(dir) > 2 ? abs(dir) - 2 : dir;
            // turn needed
            int turnCount = (abs(dir) % 3);
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

int calculateEndPrize(vector<string>& grid, vector<vector<int>>& prizeMap, pair<int, int> s, pair<int, int> e)
{
    int ROW = grid.size();
    int COL = grid[0].size();
    prizeMap = vector<vector<int>>(ROW, vector<int>(COL, INF));

    set<cell> st;
    set<pair<int, int>> processed;

    st.insert(cell(s, 0, 1));
    prizeMap[s.first][s.second] = 0;

    while (!st.empty())
    {
        cell c = *st.begin();
        // cout << c.pos+make_pair(1,1) << " " << c.distance << " " << c.direction << endl;
        st.erase(st.begin());
        
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
            int dir = revNeigbours[nRelativeDir] - c.direction;
            dir = abs(dir) > 2 ? abs(dir) - 2 : dir;
            // turn needed
            int turnCount = (abs(dir) % 3);
            // cost of reaching neigbour node from actual node
            int cost = prizeMap[c.pos.first][c.pos.second] + turnCount * turn + step;

            if (processed.find(n) != processed.end())
            {
                continue;
            }

            if (prizeMap[n.first][n.second] > cost && cost <= prizeMap[e.first][e.second])
            {
                prizeMap[n.first][n.second] = cost;
                st.insert(cell(n, prizeMap[n.first][n.second], revNeigbours[nRelativeDir]));
            }
        }
    }
    cout << "######################" << endl;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            cout << prizeMap[i][j] << "\t";
        }
        cout << endl;
    }
    
    // cout << e << endl;
    return prizeMap[e.first][e.second];
}

int calculateEndPrize(vector<string>& grid, vector<vector<int>>& prizeMap, set<pair<int, int>>& visited, cell c, pair<int, int> e)
{
    if (c.pos == e)
    {
        return c.distance;
    }

    visited.insert(c.pos);
    int path = 0;
    for (int i = 0; i < 4; i++)
    {
        pair<int, int> n = c.pos + neigbours[i];

        // if (c.pos == make_pair(10,3))
        // {
        //     cout << "########### NEIGBOUR ############" << endl;
        //     cout << n << endl;
        //     cout << "#################################" << endl;
        // }
        

        if (grid[n.first][n.second] == '#') // If WALL --> Continue
        {
            continue;
        }        

        if (visited.find(n) != visited.end()) // If visited --> Continue
        {
            continue;
        }

        // relative direction to actual node
        pair<int, int> nRelativeDir = n - c.pos;
        int dir = revNeigbours[nRelativeDir] - c.direction;
        dir = abs(dir) > 2 ? abs(dir) - 2 : dir;
        // turn needed
        int turnCount = (abs(dir) % 3);
        // cost of reaching neigbour node from actual node
        int pmc = prizeMap[c.pos.first][c.pos.second];
        int pmn = prizeMap[n.first][n.second];
        int pmnc = pmn - pmc;
        int cost = pmc + turnCount * turn + step;
        int cost2 = c.distance + turnCount * turn + step;
        int pmncost = pmn - cost;

        int dif = pmnc - pmncost;
        cout << "dif = " << pmnc - pmncost << endl;
        if (dif == 1 || dif == 1001)
        {
            int p = calculateEndPrize(grid, prizeMap, visited, cell(n, cost, revNeigbours[nRelativeDir]), e);
            path += p == -1 ? 0 : 1;
        }

        // if (c.pos == make_pair(10,3))
        // {
        //     cout << "########## COST + PATH ##########" << endl;
        //     cout << cost << "\t" << path << "\t" << (abs(prizeMap[n.first][n.second] - cost) < 1002) << endl;
        //     cout << "#################################" << endl;
        // }
    }
    cout << c << "\t" << path << endl;
    if (0 < path)
    {
        prizeMap[c.pos.first][c.pos.second] = c.distance;    
        visited.erase(c.pos);
        return c.distance;
    }
    c.distance = -1*INF;
    prizeMap[c.pos.first][c.pos.second] = -1*INF;
    visited.erase(c.pos);
    return c.distance;
}

void dfs(vector<vector<int>>& prizeMap, set<pair<int, int>>& best, set<cell>& visited, cell current, pair<int, int> e)
{
    if (prizeMap[current.pos.first][current.pos.second] == INF)
    {
        return;
    }
    if (visited.find(current) != visited.end())
    {
        return;
    }
    if (current.pos == e)
    {
        if (current.distance == prizeMap[e.first][e.second])
        {
            for (auto c : visited)
            {
                best.insert(c.pos);
            }
            best.insert(current.pos);
        }
        return;
    }
    cout << current << endl;
    
    visited.insert(current);
    for (auto neigbour : neigbours)
    {
        // neigbour pos
        pair<int, int> n = current.pos + neigbour;
        // relative direction to actual node
        pair<int, int> nRelativeDir = n - current.pos;
        int dir = revNeigbours[nRelativeDir] - current.direction;
        dir = abs(dir) > 2 ? abs(dir) - 2 : dir;
        // turn needed
        int turnCount = (abs(dir) % 3);
        // cost of reaching neigbour node from actual node
        int cost = current.distance + turnCount * turn + step;
        
        if (cost <= prizeMap[e.first][e.second])
        {
            dfs(prizeMap, best, visited, cell(n, cost, revNeigbours[nRelativeDir]), e);
        }
        
    }

    visited.erase(current);
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
    int ROW = data.size();
    int COL = data[0].size();
    vector<vector<int>> prizeMap = vector<vector<int>>(ROW, vector<int>(COL, INF));
    set<pair<int, int>> v;
    int prize = calculateEndPrize(data, prizeMap, start, end);
    prize = calculateEndPrize(data, prizeMap, v, cell(start, 0, 1), end);
    cout << prize << endl;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            cout << prizeMap[i][j] << "\t";
        }
        cout << endl;
    }
    set<pair<int, int>> st;
    set<cell> visited;
    // dfs(prizeMap, st, visited, cell(start,0,1), end);
    
    // cout << st << endl << endl;

    cout << st.size() << endl;

    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/16_test_input.txt");
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
