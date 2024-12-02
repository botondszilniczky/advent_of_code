#include <iostream>
#include "../../processing/InputParser.hpp"
#include "../../processing/FileReader.hpp"
#include <list>

enum Instruction
{
    TURN_ON,
    TOGGLE,
    TURN_OFF
};

struct data
{
    Instruction instruction;
    size_t start_x, start_y, end_x, end_y;

    data(std::string instr, size_t s_x, size_t s_y, size_t e_x, size_t e_y)
    : start_x(s_x), start_y(s_y), end_x(e_x), end_y(e_y)
    {
        if(instr == "turn on")
            instruction = Instruction::TURN_ON;
        else if(instr == "toggle")
            instruction = Instruction::TOGGLE;
        else if(instr == "turn off")
            instruction = Instruction::TURN_OFF;
    }
};

void solve(std::list<std::string>& lines)
{
    bool lights[1000][1000] = {false};
    std::regex rgx("^([a-zA-Z ]*) (\\d*+)\\,(\\d*+) .*? (\\d*+)\\,(\\d*+)$");
    size_t count = 0;
    std::cout << "count = " << count << std::endl;
    for(std::string line : lines)
    {
        std::smatch match;
        if(std::regex_search(line, match, rgx))
        {
            data instruction(match[1].str(), std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4]), std::stoi(match[5]));
            // std::cout   << instruction.instruction << "\t"
            //             << instruction.start_x << "\t"
            //             << instruction.end_x << "\t"
            //             << instruction.start_y << "\t"
            //             << instruction.end_y << "\t"
            //             << std::endl;
            for(size_t x = instruction.start_x; x <= instruction.end_x; x++)
            {
                for (size_t y = instruction.start_y; y <= instruction.end_y; y++)
                {
                    std::cout << "light\t"<< x << "\t" << y << "\t" << lights[x][y] << "\t";
                    switch (instruction.instruction)
                    {
                    case Instruction::TURN_ON:
                        count += lights[x][y]?0:1;
                        lights[x][y] = true;
                        break;

                    case Instruction::TURN_OFF:
                        count += lights[x][y]?-1:0;
                        lights[x][y] = true;
                        break;

                    case Instruction::TOGGLE:
                        count += lights[x][y]?-1:1;
                        lights[x][y] = !lights[x][y];
                        break;

                    default:
                        break;
                    }
                    // std::cout << count << std::endl;
                }
            }
            // std::cout << "current res:\t" << count << std::endl
            // << "#############################" << std::endl;
        }
    }
    std::cout << "Result 1:\t" << count << std::endl;
}

int main(int argc, char const *argv[])
{
    std::string exePath = argv[0];
    std::string inputPath;
    std::regex fileReg("(.*[\\/\\\\]).*+$");
    std::smatch match;
    if(std::regex_search(exePath, match, fileReg))
    {
        if(match.size() < 2)
        {
            std::cout << "[ERROR]: Input file is not available!" << std::endl;
        }
        else
        {
            inputPath = match[1];
        }
    }
    FileReader fileReader(inputPath + "input06.txt");
    std::list<std::string> lines = fileReader.getLines();
    // for(std::string line : lines)
    // {
    //     std::cout << line << std::endl;
    // }
    std::cout   << "###############################" << std::endl
                << "#                             #" << std::endl
                << "###############################" << std::endl;
    solve(lines);
    
    

    return 0;
}
