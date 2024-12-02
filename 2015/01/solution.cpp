#include <iostream>
#include <fstream>
#include <regex>


std::string readFile(std::string filename)
{
    std::ifstream file(filename);
    std::string data;
    file >> data;
    return data;
}

void solve(std::string data)
{
    int result = 0;
    for(char c : data)
    {
        switch (c)
        {
        case '(':
            result++;
            break;
        
        case ')':
            result--;
            break;
        
        default:
            break;
        }
    }
    std::cout << "Result 1:\t" << result << std::endl;
}

void solve2(std::string data)
{
    int floor = 0;
    for(size_t i = 0; i < data.size(); i++)
    {
        switch (data[i])
        {
        case '(':
            floor++;
            break;
        
        case ')':
            floor--;
            break;

        default:
            break;
        }
        if (floor < 0)
        {
            std::cout << "Result 2:\t" << i+1 << std::endl;
            return;
        }
        
    }
}

int main(int argc, char const *argv[])
{
    std::string exePath = argv[0];
    std::string inputPath;
    std::regex fileReg("(.*[\\/\\\\]).*$");
    std::smatch match;
    if(std::regex_search(exePath, match, fileReg))
    {
        for(auto m : match)
        {
            std::cout << m << std::endl;
            inputPath = m;
        }
    }
    std::string data = readFile(inputPath + "input01.txt");
    
    solve(data);
    solve2(data);
    return 0;
}
