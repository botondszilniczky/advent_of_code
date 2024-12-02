#include "InputParser.hpp"
#include <iostream>

void InputParser::parseInput(std::list<std::smatch>& matches, std::regex regex)
{
    while(file)
    {
        std::smatch match;
        std::string line;
        
        std::getline(file, line);
        if (line.length() == 0)
        {
            continue;
        }

        if (std::regex_search(line, match, regex))
        {
            std::cout << match.str() << std::endl;
            matches.push_back(std::move(match));
        }
    }
    for(auto a : matches)
    {
        std::cout << a[0] << std::endl;
    }
}

InputParser::InputParser(std::string filename)
{
    file.open(filename, std::ifstream::in);
}

InputParser::~InputParser()
{
    file.close();
}
