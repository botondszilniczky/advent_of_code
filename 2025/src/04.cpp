#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

void sol1(const std::vector<std::vector<char>> &map)
{
    long count = 0;
    for (int i = 0; i < map.size(); ++i)
    {
        const auto &row = map[i];
        for (int j = 0; j < row.size(); ++j)
        {
            char ch = row[j];
            if (ch == '@')
            {
                int paperRollCount = 0;
                for (int k = std::max(0, i - 1); k <= std::min(static_cast<int>(map.size()) - 1, i + 1); ++k)
                {
                    for (int l = std::max(0, j - 1); l <= std::min(static_cast<int>(row.size()) - 1, j + 1); ++l)
                    {
                        if (k == i && l == j)
                        {
                            continue;
                        }
                        if (map[k][l] == '@')
                        {
                            paperRollCount++;
                        }
                    }
                }
                if (paperRollCount < 4)
                {
                    count++;
                }
            }
        }
    }
    std::cout << "Solution 1: " << count << std::endl;
}

void sol2(std::vector<std::vector<char>> &map)
{
    long totalCount = 0;
    long count = 0;
    do
    {
        count = 0;
        for (int i = 0; i < map.size(); ++i)
        {
            const auto &row = map[i];
            for (int j = 0; j < row.size(); ++j)
            {
                char ch = row[j];
                if (ch == '@')
                {
                    int paperRollCount = 0;
                    for (int k = std::max(0, i - 1); k <= std::min(static_cast<int>(map.size()) - 1, i + 1); ++k)
                    {
                        for (int l = std::max(0, j - 1); l <= std::min(static_cast<int>(row.size()) - 1, j + 1); ++l)
                        {
                            if (k == i && l == j)
                            {
                                continue;
                            }
                            if (map[k][l] == '@')
                            {
                                paperRollCount++;
                            }
                        }
                    }
                    if (paperRollCount < 4)
                    {
                        count++;
                        map[i][j] = 'X';
                    }
                }
            }
        }
        totalCount += count;
    } while (count != 0);

    std::cout << "Solution 2: " << totalCount << std::endl;
}

int main(int argc, char **argv)
{
    std::string input = argc > 1 ? argv[1] : "input.txt";

    std::ifstream file(input);
    if (!file)
    {
        std::cerr << "Error opening file: " << input << std::endl;
        return 1;
    }
    std::vector<std::vector<char>> map;

    for (std::string line; std::getline(file, line);)
    {
        std::vector<char> row;
        for (char ch : line)
        {
            row.push_back(ch);
        }
        map.push_back(row);
    }

    sol1(map);
    sol2(map);

    return 0;
}