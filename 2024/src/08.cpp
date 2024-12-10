#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

void searchAntinodes(vector<string>& data, set<pair<int, int>>& antinodes, int row, int col, char freq)
{
    for (int r = 0; r < data.size(); r++)
    {
        for (int c = 0; c < data[r].size(); c++)
        {
            if (row == r && col == c)
            {
                continue;
            }
            if (data[r][c] == freq)
            {
                pair<int, int> dist = {(r-row), (c-col)};
                pair<int, int> a1 = {(row - dist.first), (col - dist.second)};
                pair<int, int> a2 = {(r + dist.first), (c + dist.second)};
                
                if (0 <= a1.first && a1.first < data.size() && 0 <= a1.second && a1.second < data[a1.first].size())
                {
                    antinodes.insert(a1);
                }
                if (0 <= a2.first && a2.first < data.size() && 0 <= a2.second && a2.second < data[a2.first].size())
                {
                    antinodes.insert(a2);
                }
            }
        }
    }
}

void searchExtraAntinodes(vector<string>& data, set<pair<int, int>>& antinodes, int row, int col, char freq)
{
    for (int r = 0; r < data.size(); r++)
    {
        for (int c = 0; c < data[r].size(); c++)
        {
            if (row == r && col == c)
            {
                continue;
            }
            if (data[r][c] == freq)
            {
                pair<int, int> dist = {(r-row), (c-col)};
                
                bool out1 = false;
                bool out2 = false;
                int i = 0;
                while (!out1 || !out2)
                {
                    pair<int, int> a1 = {(row - (i * dist.first)), (col - (i * dist.second))};
                    pair<int, int> a2 = {(r + (i * dist.first)), (c + (i * dist.second))};
                    
                    if (0 <= a1.first && a1.first < data.size() && 0 <= a1.second && a1.second < data[a1.first].size())
                    {
                        antinodes.insert(a1);
                    }
                    else
                    {
                        out1 = true;
                    }
                    if (0 <= a2.first && a2.first < data.size() && 0 <= a2.second && a2.second < data[a2.first].size())
                    {
                        antinodes.insert(a2);
                    }
                    else
                    {
                        out2 = true;
                    }

                    i++;
                }
            }
        }
    }
}

int sol1(vector<string> data)
{
    set<char> frequences;
    for (string line : data)
    {
        for (char c : line)
        {
            if (c != '.')
            {
                frequences.insert(c);
            }
        }
    }
    
    set<pair<int, int>> antinodes;
    for (char c : frequences)
    {
        for (int row = 0; row < data.size(); row++)
        {
            for (int col = 0; col < data[row].size(); col++)
            {
                if (data[row][col] == c)
                {
                    searchAntinodes(data, antinodes, row, col, c);
                }
            }
        }
    }

    cout << antinodes.size() << endl;
    return 0;
}

int sol2(vector<string> data)
{
    set<char> frequences;
    for (string line : data)
    {
        for (char c : line)
        {
            if (c != '.')
            {
                frequences.insert(c);
            }
        }
    }
    
    set<pair<int, int>> antinodes;
    for (char c : frequences)
    {
        for (int row = 0; row < data.size(); row++)
        {
            for (int col = 0; col < data[row].size(); col++)
            {
                if (data[row][col] == c)
                {
                    searchExtraAntinodes(data, antinodes, row, col, c);
                }
            }
        }
    }

    cout << antinodes.size() << endl;
    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/08_input.txt");
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
