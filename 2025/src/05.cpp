#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <vector>

struct FreshRange
{
    long start;
    long end;
};

struct Ingredient
{
    long id;
};

void sol1(const std::vector<FreshRange> &ranges, const std::vector<Ingredient> &ingredients)
{
    long count = 0;
    for (const auto &ingredient : ingredients)
    {
        for (const auto &range : ranges)
        {
            if (ingredient.id >= range.start && ingredient.id <= range.end)
            {
                count++;
                break;
            }
        }
    }
    std::cout << "Solution 1: " << count << std::endl;
}

std::vector<FreshRange> mergeRanges(const std::vector<FreshRange> &ranges)
{
    if (ranges.empty())
    {
        return {};
    }

    std::vector<FreshRange> sortedRanges = ranges;
    std::sort(sortedRanges.begin(), sortedRanges.end(),
              [](const FreshRange &a, const FreshRange &b)
              { return a.start < b.start; });

    std::vector<FreshRange> merged;
    merged.push_back(sortedRanges[0]);

    for (size_t i = 1; i < sortedRanges.size(); ++i)
    {
        FreshRange &last = merged.back();
        if (sortedRanges[i].start <= last.end)
        {
            last.end = std::max(last.end, sortedRanges[i].end);
        }
        else
        {
            merged.push_back(sortedRanges[i]);
        }
    }

    return merged;
}

void sol2(const std::vector<FreshRange> &ranges, const std::vector<Ingredient> &ingredients)
{
    std::vector<FreshRange> mergedRanges = mergeRanges(ranges);
    long count = 0;
    for (const auto &range : mergedRanges)
    {
        count += (range.end - range.start + 1);
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
    std::vector<FreshRange> ranges;
    std::vector<Ingredient> ingredients;

    for (std::string line; std::getline(file, line);)
    {
        if (line.empty())
        {
            continue;
        }
        size_t pos = line.find('-');
        if (pos != std::string::npos)
        {
            FreshRange range;
            range.start = std::stol(line.substr(0, pos));
            range.end = std::stol(line.substr(pos + 1));
            ranges.push_back(range);
        }
        else
        {
            Ingredient ingredient;
            ingredient.id = std::stol(line);
            ingredients.push_back(ingredient);
        }
    }

    sol1(ranges, ingredients);
    sol2(ranges, ingredients);

    return 0;
}