#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <set>
#include <sstream>
#include <vector>

void sol1(const std::vector<std::vector<long long>> &numbers, const std::vector<char> &operators)
{
    std::vector<long long> results(numbers[0].size(), 0);
    for (int i = 0; i < numbers.size(); ++i)
    {
        const auto &nums = numbers[i];
        for (int j = 0; j < nums.size(); ++j)
        {
            long num = nums[j];
            if (operators[j] == '+')
            {
                results[j] += num;
            }
            else if (operators[j] == '*')
            {
                results[j] == 0 ? results[j] = num : results[j] *= num;
            }
        }
    }

    std::cout << "Solution 1: " << std::reduce(results.begin(), results.end(), 0LL) << std::endl;
}

void sol2(const std::vector<std::string> &lines, const std::vector<char> &operators)
{
    size_t operatorIndex = 0;
    long long result = 0;
    long long partialSum = 0;
    long long count = 0;
    for (size_t i = 0; i < lines[0].size(); ++i)
    {
        std::stringstream ss;
        for (size_t j = 0; j < lines.size(); ++j)
        {
            if (!isspace(lines[j][i]))
            {
                ss << lines[j][i];
            }
        }
        if (ss.str().empty())
        {
            result += count;
            count = 0;
            operatorIndex++;
            continue;
        }
        if (operators[operatorIndex] == '+')
        {
            count += std::stoll(ss.str());
        }
        else if (operators[operatorIndex] == '*')
        {
            count == 0 ? count = std::stoll(ss.str()) : count *= std::stoll(ss.str());
        }
    }
    result += count;
    std::cout << "Solution 2: " << result << std::endl;
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
    std::vector<std::vector<long long>> numbers;
    std::vector<std::string> lines;
    std::vector<char> operators;

    for (std::string line; std::getline(file, line);)
    {
        if (line.empty())
        {
            continue;
        }
        if (line[0] != '*' && line[0] != '+')
        {
            lines.push_back(line);
        }
        while (line[0] == ' ')
        {
            line.erase(0, 1);
        }
        if (isdigit(line[0]))
        {
            std::istringstream iss(line);
            std::vector<long long> nums;
            long long num;
            while (iss >> num)
            {
                nums.push_back(num);
            }
            numbers.push_back(nums);
        }
        else
        {
            for (char ch : line)
            {
                if (!isspace(ch))
                {
                    operators.push_back(ch);
                }
            }
        }
    }

    sol1(numbers, operators);
    sol2(lines, operators);

    return 0;
}