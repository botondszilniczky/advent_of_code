#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<char> nums = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int searchRout(vector<string> &data, set<pair<int, int>>& peaks, int x, int y, int n)
{
    if (n == 9)
    {
        if (data[x][y] == nums[9])
        {
            peaks.insert(make_pair(x,y));
            return 1;
        }
        else
        {
            return 0;
        }
    }
    pair<int, int> up       = {x-1, y};
    pair<int, int> down     = {x+1, y};
    pair<int, int> left     = {x, y-1};
    pair<int, int> right    = {x, y+1};
    int sum = 0;
    if (0 <= up.first && up.first < data.size() && 0 <= up.second && up.second < data[up.first].size() 
        && data[up.first][up.second] == nums[n+1])
    {
        sum += searchRout(data, peaks, up.first, up.second, n+1);

    }
    if (0 <= down.first && down.first < data.size() && 0 <= down.second && down.second < data[down.first].size() 
        && data[down.first][down.second] == nums[n+1])
    {
        sum += searchRout(data, peaks, down.first, down.second, n+1);
    }
    if (0 <= left.first && left.first < data.size() && 0 <= left.second && left.second < data[left.first].size() 
        && data[left.first][left.second] == nums[n+1])
    {
        sum += searchRout(data, peaks, left.first, left.second, n+1);
    }
    if (0 <= right.first && right.first < data.size() && 0 <= right.second && right.second < data[right.first].size() 
        && data[right.first][right.second] == nums[n+1])
    {
        sum += searchRout(data, peaks, right.first, right.second, n+1);
    }
    return sum;
}

int sol1(vector<string> data)
{
    int sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            if (data[i][j] == nums[0])
            {
                set<pair<int, int>> peaks;
                searchRout(data, peaks, i, j, 0);
                sum += peaks.size();
            }
        }
    }
    cout << sum << endl;
    return 0;
}

int sol2(vector<string> data)
{
    int sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            if (data[i][j] == nums[0])
            {
                set<pair<int, int>> peaks;
                sum += searchRout(data, peaks, i, j, 0);
            }
        }
    }
    cout << sum << endl;
    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/10_input.txt");
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
