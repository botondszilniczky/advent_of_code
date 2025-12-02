#include <fstream>
#include <iostream>
#include <vector>

struct Code
{
    char direction;
    int value;

    friend std::istream &operator>>(std::istream &is, Code &c)
    {
        is >> c.direction >> c.value;
        return is;
    }
};

void sol1(const std::vector<Code> &codes)
{
    int counter = 0;
    int sum = 50;
    for (auto c : codes)
    {
        switch (c.direction)
        {
        case 'L':
            sum -= c.value;
            sum %= 100;
            break;

        case 'R':
            sum += c.value;
            sum %= 100;
            break;

        default:
            break;
        }
        if (sum == 0)
        {
            counter++;
        }
    }
    std::cout << "Solution 1: " << counter << std::endl;
}

void sol2(const std::vector<Code> &codes)
{
    int counter = 0;
    int sum = 50;
    for (auto c : codes)
    {
        int prevSum = sum;
        switch (c.direction)
        {
        case 'L':
            counter += std::abs(c.value / 100);
            sum -= (c.value % 100);
            sum = ((sum % 100) + 100) % 100;
            counter += prevSum < sum && sum != 0 && prevSum != 0 ? 1 : 0;
            break;

        case 'R':
            counter += std::abs(c.value / 100);
            sum += (c.value % 100);
            sum = ((sum % 100) + 100) % 100;
            counter += prevSum > sum && sum != 0 && prevSum != 0 ? 1 : 0;
            break;

        default:
            break;
        }
        if (sum == 0)
        {
            counter++;
        }
    }
    std::cout << "Solution 2: " << counter << std::endl;
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
    std::vector<Code> codes;
    Code c;
    while (file >> c)
    {
        codes.push_back(c);
    }

    sol1(codes);
    sol2(codes);

    return 0;
}