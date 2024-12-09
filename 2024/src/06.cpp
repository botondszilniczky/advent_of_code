#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <regex>

using namespace std;

enum Element
{
    OBSTACKLE, GUARD, VISITED, FREE
};

ostream& operator<<(ostream& os, const pair<int, int>& d)
{
    return os << "<" << d.first << ", " << d.second << ">";
}

ostream& operator<<(ostream& os, vector<pair<pair<int, int>, pair<int, int>>>& d)
{
    for (auto p : d)
    {
        os << "<" << p.first << ", " << p.second << ">; ";
    }
    return os;
}

vector<vector<Element>> createMap(vector<string> data, pair<int, int> &gPos)
{
    vector<vector<Element>> grid;
    int i = 0;
    for (string line : data) {
        vector<Element> tmp;
        int j = 0;
        for (char c : line)
        {
            switch (c)
            {
            case '.':
                tmp.push_back(Element::FREE);
                break;
            
            case '#':
                tmp.push_back(Element::OBSTACKLE);
                break;

            case '^':
                tmp.push_back(Element::GUARD);
                gPos = {i, j};
                break;
            
            default:
                break;
            }
            j++;
        }
        grid.push_back(tmp);
        i++;
    }
    return grid;
}

template<class T, class U>
bool operator==(pair<T,U> p1, pair<T,U> p2)
{
    return (p1.first == p2.first && p1.second == p2.second);
}

int sol1(vector<string> data)
{
    pair<int, int> guardPos = {0, 0};
    vector<vector<Element>> grid = createMap(data, guardPos);
    pair<int, int> direction = {-1, 0};
    bool leave = false;
    while (!leave)
    {
        pair<int, int> newPos = {guardPos.first + direction.first, guardPos.second + direction.second};
        if ((newPos.first) < 0 || (newPos.first) >= grid.size()
            || (newPos.second) < 0 || (newPos.second) >= grid[newPos.first].size()
        )
        {
            leave = true;
            grid[guardPos.first][guardPos.second] = Element::VISITED;
            continue;
        }
        if (grid[newPos.first][newPos.second] == Element::OBSTACKLE) // TURN RIGHT
        {
            if (direction.first == -1 && direction.second == 0) // UP
            {
                direction = {0, 1};
            }
            else if (direction.first == 0 && direction.second == 1) // RIGHT
            {
                direction = {1, 0};
            }
            else if (direction.first == 1 && direction.second == 0) // DOWN
            {
                direction = {0, -1};
            }
            else if (direction.first == 0 && direction.second == -1) // LEFT
            {
                direction = {-1, 0};
            }
        }
        if (grid[newPos.first][newPos.second] == Element::VISITED || grid[newPos.first][newPos.second] == Element::FREE) // STEP FORWARD
        {
            grid[guardPos.first][guardPos.second] = Element::VISITED;
            grid[newPos.first][newPos.second] = Element::GUARD;
            guardPos = newPos;
        }
    }
    int counter = 0;
    for (auto row : grid)
    {
        for (auto cell : row)
        {
            if (cell == Element::VISITED)
            {
                counter++;
            }
            
        }
    }
    
    cout << counter << endl;
    return counter;
}

int sol2(vector<string> data)
{
    pair<int, int> guardPos = {0, 0};
    vector<vector<Element>> grid = createMap(data, guardPos);
    vector<pair<pair<int, int>, pair<int, int>>> visitedGrid; // <POSITION, DIRECTION>
    vector<pair<int, int>> potentialObstackles;
    pair<int, int> guardStartPos = guardPos;
    // cout << guardStartPos << endl;
    int counter = 0;
    pair<int, int> direction = {-1, 0};
    bool leave = false;
    // cout << leave << endl;
    while (!leave)
    {
        pair<int, int> newPos = {guardPos.first + direction.first, guardPos.second + direction.second};
        if ((newPos.first) < 0 || (newPos.first) >= grid.size()
            || (newPos.second) < 0 || (newPos.second) >= grid[newPos.first].size()
        )
        {
            leave = true;
            grid[guardPos.first][guardPos.second] = Element::VISITED;
            continue;
        }
        if (grid[newPos.first][newPos.second] == Element::OBSTACKLE) // TURN RIGHT
        {
            visitedGrid.push_back({guardPos, direction});
            // cout << "TURN RIGHT" << endl;
            if (direction.first == -1 && direction.second == 0) // UP
            {
                direction = {0, 1};
            }
            else if (direction.first == 0 && direction.second == 1) // RIGHT
            {
                direction = {1, 0};
            }
            else if (direction.first == 1 && direction.second == 0) // DOWN
            {
                direction = {0, -1};
            }
            else if (direction.first == 0 && direction.second == -1) // LEFT
            {
                direction = {-1, 0};
            }
        }
        if (grid[newPos.first][newPos.second] == Element::VISITED || grid[newPos.first][newPos.second] == Element::FREE) // STEP FORWARD
        {
            // cout << "#################################" << endl;
            // cout << "Visited list: " << visitedGrid << endl;
            // cout << "Guard pos: " << guardPos << endl;
            // cout << "Direction: " << direction << endl;
            // cout << "New pos: " << newPos << endl;

            pair<int, int> nextDir;
            if (direction.first == -1 && direction.second == 0) // UP
            {
                nextDir = {0, 1};
            }
            else if (direction.first == 0 && direction.second == 1) // RIGHT
            {
                nextDir = {1, 0};
            }
            else if (direction.first == 1 && direction.second == 0) // DOWN
            {
                nextDir = {0, -1};
            }
            else if (direction.first == 0 && direction.second == -1) // LEFT
            {
                nextDir = {-1, 0};
            }
            // cout << "Next direction: " << nextDir << endl;
            if (newPos.first != guardStartPos.first || newPos.second != guardStartPos.second)
            {
                pair<int, int> pos = guardPos;
                while (pos.first >= 0 && pos.second < grid.size() && pos.second >= 0 && pos.second < grid[pos.first].size())
                {
                    if (grid[pos.first][pos.second] == Element::OBSTACKLE)
                    {
                        break;
                    }
                    pair<pair<int, int>, pair<int, int>> gandd = {pos, nextDir};
                    auto search = find(visitedGrid.begin(), visitedGrid.end(), gandd);
                    // cout << (search != visitedGrid.end() ? "Found!" : "NOT found!") << endl;
                    if (search != visitedGrid.end())
                    {
                        // cout << "potential obstackle" << endl;
                        potentialObstackles.push_back(newPos);
                        counter++;
                    }
                    pos.first += nextDir.first;
                    pos.second += nextDir.second;
                }
            }
            
            // cout << endl;
            grid[guardPos.first][guardPos.second] = Element::VISITED;
            grid[newPos.first][newPos.second] = Element::GUARD;
            guardPos = newPos;
        }
    }
    for (auto e : potentialObstackles)
    {
        cout << e << ", ";
    }
    cout << endl;
    cout << counter << endl;
    return counter;
}

int sol3(vector<string> data)
{
    pair<int, int> guardPos = {0, 0};
    int dir = 0;
    vector<vector<Element>> grid = createMap(data, guardPos);

    grid[guardPos.first][guardPos.second] = Element::FREE;
    pair<int, int> start = guardPos;
    
    vector<pair<int, int>> directions = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    
    auto solveCycle = [&]()
    {
        guardPos = start;
        dir = 0;
        set<vector<int>> visited;
        int turns = 0;
        while (true)
        {
            turns++;
            if (!visited.insert(vector<int>{guardPos.first, guardPos.second, dir}).second)
            {
                return true;
            }
            
            int r2 = guardPos.first + directions[dir].first;
            int c2 = guardPos.second + directions[dir].second;

            if (!(0 <= r2 && r2 < grid.size() && 0 <= c2 && c2 < grid[r2].size()))
            {
                return false;
            }
            if (grid[r2][c2] == Element::FREE)
            {
                guardPos = {r2, c2};
            }
            else
            {
                dir = (dir+1) % 4;
            }
        }
    };

    int answer = 0;
    for (int row = 0; row < grid.size(); row++)
    {
        for (int col = 0; col < grid[row].size(); col++)
        {
            if (grid[row][col] == Element::FREE && start != make_pair(row, col))
            {
                grid[row][col] = Element::OBSTACKLE;

                if (solveCycle())
                {
                    answer++;
                }
                
                grid[row][col] = Element::FREE;
            }
            
        }
    }

    cout << answer << endl;
    return answer;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/06_input.txt");
    vector<string> data;
    string line;
    while(getline(file, line))
    {
        data.push_back(line);
    }
    sol1(data);
    sol3(data);

    return 0;
}
