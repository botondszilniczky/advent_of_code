#ifndef INPUT_PARSER
#define INPUT_PARSER

#include <regex>
#include <fstream>
#include <list>

class InputParser
{
private:
    std::ifstream file;

public:
    void parseInput(std::list<std::smatch>& matches, std::regex regex);

    InputParser(std::string filename);
    ~InputParser();
};

#endif