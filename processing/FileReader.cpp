#include "FileReader.hpp"

void FileReader::readFile()
{
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    
}

std::list<std::string> FileReader::getLines()
{
    return lines;
}

FileReader::FileReader(std::string filename)
{
    file.open(filename);
    readFile();
}

FileReader::~FileReader()
{
    file.close();
}