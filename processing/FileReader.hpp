#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <list>
#include <sstream>
#include <fstream>

class FileReader
{
private:
    std::ifstream file;
    std::list<std::string> lines;

    void readFile();
public:
    std::list<std::string> getLines();
    FileReader(std::string filename);
    ~FileReader();
};




#endif // FILEREADER_HPP
