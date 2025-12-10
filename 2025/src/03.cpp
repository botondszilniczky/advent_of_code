#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

void sol1(const std::vector<std::vector<int>> &batteryCells)
{
    int sumCharge = 0;
    for (const auto &cells : batteryCells)
    {
        int totalCharge = 0;
        int max = 0;
        size_t maxIndex = 0;
        for (size_t i = 0; i < cells.size() - 1; ++i)
        {
            if (cells[i] > max)
            {
                max = cells[i];
                maxIndex = i;
            }
        }
        totalCharge += max * 10;
        max = 0;
        maxIndex++;
        for (size_t i = maxIndex; i < cells.size(); ++i)
        {
            if (cells[i] > max)
            {
                max = cells[i];
                maxIndex = i;
            }
        }
        totalCharge += max;
        sumCharge += totalCharge;
    }
    std::cout << "Solution 1: " << sumCharge << std::endl;
}

void sol2(const std::vector<std::vector<int>> &batteryCells)
{
    long sumCharge = 0;
    for (const auto &cells : batteryCells)
    {
        long totalCharge = 0;
        size_t maxIndex = 0;
        for (size_t j = 0; j < 12; ++j)
        {
            long max = 0;
            for (size_t i = maxIndex; i < cells.size() - 11 + j; ++i)
            {
                if (cells[i] > max)
                {
                    max = cells[i];
                    maxIndex = i;
                }
            }
            maxIndex++;
            totalCharge += max * std::pow(10, 11 - j);
        }
        sumCharge += totalCharge;
    }
    std::cout << "Solution 2: " << sumCharge << std::endl;
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
    std::vector<std::vector<int>> batteryCells;

    for (std::string line; std::getline(file, line);)
    {
        std::vector<int> cells;
        for (char ch : line)
        {
            if (std::isdigit(ch))
            {
                cells.push_back(ch - '0');
            }
        }
        batteryCells.push_back(cells);
    }

    sol1(batteryCells);
    sol2(batteryCells);

    return 0;
}