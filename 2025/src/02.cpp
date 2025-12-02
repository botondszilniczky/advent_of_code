#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

struct IDRange
{
    std::string from, to;
};

void sol1(const std::vector<IDRange> &ranges)
{
    long count = 0;
    int num = 0;
    for (const auto &range : ranges)
    {
        for (long i = std::stol(range.from); i <= std::stol(range.to); ++i)
        {
            std::stringstream ss;
            ss << i;
            std::string id = ss.str();
            if (id.size() % 2 != 0)
                continue;
            if (id.substr(0, id.size() / 2) == id.substr(id.size() / 2, id.size() - id.size() / 2))
            {
                count += i;
                num++;
            }
        }
    }
    std::cout << "Solution 1: " << count << std::endl;
}

void sol2(const std::vector<IDRange> &ranges)
{
    long count = 0;
    for (const auto &range : ranges)
    {
        for (long i = std::stol(range.from); i <= std::stol(range.to); ++i)
        {
            std::stringstream ss;
            ss << i;
            std::string id = ss.str();
            std::regex re("(\\d+?)\\1+");
            std::smatch match;
            if (std::regex_match(id, match, re))
            {
                count += i;
            }
        }
    }
    std::cout << "Solution 2: " << count << std::endl;
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
    std::vector<IDRange> ranges;

    for (std::string line; std::getline(file, line, ',');)
    {
        IDRange range;
        size_t dashPos = line.find('-');
        range.from = line.substr(0, dashPos);
        range.to = line.substr(dashPos + 1);
        ranges.push_back(range);
    }

    sol1(ranges);
    sol2(ranges);

    return 0;
}