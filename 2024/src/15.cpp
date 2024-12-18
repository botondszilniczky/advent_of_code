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

map<char, pair<int, int>> directions = {
    {'^', {-1, 0}},
    {'v', {1, 0}},
    {'<', {0, -1}},
    {'>', {0, 1}}
};

pair<int, int> operator+(pair<int, int> a, pair<int, int> b)
{
    return make_pair(a.first+b.first, a.second+b.second);
}

ostream& operator<<(ostream& os, vector<string> v)
{
    for (auto a : v)
    {
        os << a << endl;
    }
    return os;
}

void moveDirection(vector<string>& grid, pair<int, int>& pos, char me, char direction)
{
    pair<int, int> dir = directions[direction];
    pair<int, int> newPos = pos + dir;

    if (grid[newPos.first][newPos.second] == '#')
    {
        return;
    }

    if (grid[newPos.first][newPos.second] == 'O')
    {
        pair<int, int> p = newPos;
        moveDirection(grid, p, 'O', direction);
    }
    
    if (grid[newPos.first][newPos.second] == '[')
    {
        pair<int, int> p = newPos;
        moveDirection(grid, p, '[', direction);
    }

    if (grid[newPos.first][newPos.second] == ']')
    {
        pair<int, int> p = newPos;
        moveDirection(grid, p, ']', direction);
    }

    if ((me != '[' && me != ']') || (direction == '<') || (direction == '>'))
    {
        if (grid[newPos.first][newPos.second] == '.')
        {
            grid[pos.first][pos.second] = '.';
            grid[newPos.first][newPos.second] = me;
            pos = newPos;
        }
    }
    else
    {
        if (me == '[')
        {
            pair<int, int> pos2 = newPos + directions['>'];
            if (grid[newPos.first][newPos.second] == '.'
                && grid[pos2.first][pos2.second] == '.')
            {
                pair<int, int> p = pos + directions['>'];
                grid[pos.first][pos.second] = '.';
                grid[p.first][p.second] = '.';
                grid[newPos.first][newPos.second] = me;
                grid[pos2.first][pos2.second] = ']';
            }
        }
        if (me == ']')
        {
            pair<int, int> pos2 = newPos + directions['<'];
            if (grid[newPos.first][newPos.second] == '.'
                && grid[pos2.first][pos2.second] == '.')
            {
                pair<int, int> p = pos + directions['<'];
                grid[pos.first][pos.second] = '.';
                grid[p.first][p.second] = '.';
                grid[newPos.first][newPos.second] = me;
                grid[pos2.first][pos2.second] = '[';
            }
        }
    }
}

bool canMove(vector<string>& grid, set<pair<int, int>>& visited, pair<int, int>& pos, char direction)
{
    if (!visited.insert(pos).second)
    {
        return true;
    }

    pair<int, int> dir = directions[direction];
    pair<int, int> nextPos = pos + dir;

    if (grid[nextPos.first][nextPos.second] == '#')
    {
        return false;
    }
    if (grid[nextPos.first][nextPos.second] == '[')
    {
        pair<int, int> boxHalf = nextPos + directions['>'];
        return canMove(grid, visited, nextPos, direction) 
                && canMove(grid, visited, boxHalf, direction);
    }
    if (grid[nextPos.first][nextPos.second] == ']')
    {
        pair<int, int> boxHalf = nextPos + directions['<'];
        return canMove(grid, visited, boxHalf, direction) 
                && canMove(grid, visited, nextPos, direction);
    }
    if (grid[nextPos.first][nextPos.second] == '.')
    {
        return true;
    }
    return false;
}

void stepForward(vector<string>& grid, set<pair<int, int>>& visited, pair<int, int> pos, char direction)
{
    if (visited.find(pos) != visited.end())
    {
        pair<int, int> nextPos = pos + directions[direction];
        if (grid[nextPos.first][nextPos.second] != '.')
        {
            if (grid[nextPos.first][nextPos.second] == '[')
            {
                pair<int, int> boxPos = nextPos + directions['>'];
                stepForward(grid, visited, boxPos, direction);
            }
            if (grid[nextPos.first][nextPos.second] == ']')
            {
                pair<int, int> boxPos = nextPos + directions['<'];
                stepForward(grid, visited, boxPos, direction);
            }
            stepForward(grid, visited, nextPos, direction);
        }
        swap(
            grid[pos.first][pos.second],
            grid[nextPos.first][nextPos.second]
        );
        visited.erase(pos);
    }
}

int sol1(vector<string> data)
{
    int W = data[0].size();
    int H = 0;

    vector<string> grid;
    int i = 0;
    while (data[i].size() != 0)
    {
        grid.push_back(data[i]);
        H = i;
        i++;
    }
    // for (auto a : grid)
    // {
    //     cout << a << endl;
    // }
    string command = "";
    for (int j = i+1; j < data.size(); j++)
    {
        command += data[j];
    }
    // cout << endl << command << endl;
    pair<int, int> robot;
    for (int x = 0; x < grid.size(); x++)
    {
        for (int y = 0; y < grid[x].size(); y++)
        {
            if (grid[x][y] == '@')
            {
                robot = make_pair(x, y);
            }
        }
    }
    
    for (char c : command)
    {
        moveDirection(grid, robot, '@', c);
        // cout << grid << endl;
    }
    int sum = 0;
    for (int x = 0; x < grid.size(); x++)
    {
        for (int y = 0; y < grid[x].size(); y++)
        {
            if (grid[x][y] == 'O')
            {
                sum += x*100+y;
            }   
        }
    }
    cout << sum << endl;

    return 0;
}

int sol2(vector<string> data)
{
    vector<string> grid;
    int i = 0;
    while (data[i].size() != 0)
    {
        grid.push_back(data[i]);
        i++;
    }
    // for (auto a : grid)
    // {
    //     cout << a << endl;
    // }
    string command = "";
    for (int j = i+1; j < data.size(); j++)
    {
        command += data[j];
    }
    // cout << endl << command << endl;

    for (auto& s : grid)
    {
        string ss = "";
        for (int j = 0; j < s.size(); j++)
        {
            if (s[j] == '#')
            {
                ss += "##";
            }
            else if (s[j] == '.')
            {
                ss += "..";
            }
            else if (s[j] == 'O')
            {
                ss += "[]";
            }
            else if (s[j] == '@')
            {
                ss += "@.";
            }
        }
        s = ss;
    }

    pair<int, int> robot;
    for (int x = 0; x < grid.size(); x++)
    {
        for (int y = 0; y < grid[x].size(); y++)
        {
            if (grid[x][y] == '@')
            {
                robot = make_pair(x, y);
            }
        }
    }

    for (char c : command)
    {
        if (c == '<' || c == '>')
        {
            moveDirection(grid, robot, '@', c);
        }
        else
        {
            set<pair<int, int>> visited;
            if (canMove(grid, visited, robot, c))
            {
                stepForward(grid, visited, robot, c);
                robot = robot + directions[c];
            }
        }
        // cout << c << endl;
        // cout << grid << endl;
    }

    int sum = 0;
    for (int x = 0; x < grid.size(); x++)
    {
        for (int y = 0; y < grid[x].size(); y++)
        {
            if (grid[x][y] == '[')
            {
                sum += x*100+y;
            }   
        }
    }
    cout << sum << endl;

    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/15_input.txt");
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
