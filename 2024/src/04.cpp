#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool checkCharAtPos(vector<string> data, size_t posX, size_t posY, char c)
{
    return posX >= 0 && posX < data.size() && posY >= 0 && posY < data[posX].size() && data[posX][posY] == c;
}

int sol1(vector<string> data)
{
    vector<pair<int,int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1},
    };
    int counter = 0;
    for (size_t x = 0; x < data.size(); x++)
    {
        for (size_t y = 0; y < data[x].size(); y++)
        {
            if (data[x][y] == 'X')
            {
                for (auto dir : directions)
                {
                    size_t posX = x;
                    size_t posY = y;
                    posX += dir.first;
                    posY += dir.second;
                    if (checkCharAtPos(data, posX, posY, 'M'))
                    {
                        posX += dir.first;
                        posY += dir.second;
                        if (checkCharAtPos(data, posX, posY, 'A'))
                        {
                            posX += dir.first;
                            posY += dir.second;
                            if (checkCharAtPos(data, posX, posY, 'S'))
                            {
                                counter++;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << counter << endl;
    return counter;
}

int sol2(vector<string> data)
{
    vector<pair<int,int>> directions = {
        {-1, -1}, {-1, 1},
        {1, -1}, {1, 1},
    };
    int counter = 0;
    for (size_t x = 0; x < data.size(); x++)
    {
        for (size_t y = 0; y < data[x].size(); y++)
        {
            if (data[x][y] == 'A')
            {
                if (checkCharAtPos(data, (x-1), (y-1), 'M') && checkCharAtPos(data, (x+1), (y+1), 'S')
                    || checkCharAtPos(data, (x-1), (y-1), 'S') && checkCharAtPos(data, (x+1), (y+1), 'M'))
                {
                    if (checkCharAtPos(data, (x-1), (y+1), 'M') && checkCharAtPos(data, (x+1), (y-1), 'S')
                        || checkCharAtPos(data, (x-1), (y+1), 'S') && checkCharAtPos(data, (x+1), (y-1), 'M'))
                    {
                        counter++;
                    }
                }
            }
        }
    }
    cout << counter << endl;
    return counter;}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/04_input.txt");
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
