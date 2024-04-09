#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

void solve(std::string filename)
{
    std::string reg1 = "^.*[aeiou].*[aeiou].*[aeiou].*$";
    std::string reg2 = "^.*(.)\\1.*$";
    std::string reg3 = "^(?:(?!ab|cd|pq|xy).)+$";

    std::ifstream file(filename);
    std::vector<std::string> data;
    while(file)
    {
        std::string line;
        file >> line;
        // std::cout << line << std::endl;
        if (std::regex_match(line,std::regex(reg1)) &&
            std::regex_match(line,std::regex(reg2)) &&
            std::regex_match(line,std::regex(reg3)))
        {
            data.push_back(line);
        }
    }

    std::cout << "Result 1:\t" << data.size() << std::endl;
}

void solve2(std::string filename)
{
    std::string reg1 = "^.*(..).*\\1.*$";
    std::string reg2 = "^.*(.).\\1.*$";

    std::ifstream file(filename);
    std::vector<std::string> data;
    while(file)
    {
        std::string line;
        file >> line;
        // std::cout << line << std::endl;
        if (std::regex_match(line,std::regex(reg1)) &&
            std::regex_match(line,std::regex(reg2)))
        {
            data.push_back(line);
        }
    }

    std::cout << "Result 2:\t" << data.size() << std::endl;
}

int main(int argc, char const *argv[])
{
    solve("input.txt");
    solve2("input.txt");
    return 0;
}
