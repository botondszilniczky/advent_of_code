#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

int sol1(vector<string> data)
{
    regex reg("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    int sum = 0;
    for (string element : data)
    {
        smatch match;
        string s = element;
        while (regex_search(s, match, reg))
        {
            sum += stoi(match[1]) * stoi(match[2]);
            s = match.suffix().str();
        }
        
    }
    cout << sum << endl;
    return sum;
}

int sol2(vector<string> data)
{
    regex reg("mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don\\'t\\(\\)");
    int sum = 0;
    bool enabled = true;
    for (string element : data)
    {
        smatch match;
        string s = element;
        while (regex_search(s, match, reg))
        {
            if (match.str().find("do()") != string::npos)
            {
                enabled = true;
                s = match.suffix().str();
                continue;
            }
            if (match.str().find("don't()") != string::npos)
            {
                enabled = false;
                s = match.suffix().str();
                continue;
            }
            if (enabled)
            {
                sum += stoi(match[1]) * stoi(match[2]);
            }
            s = match.suffix().str();
        }
    }
    cout << sum << endl;
    return sum;
}

int main(int argc, char const *argv[])
{
    ifstream f("./build/2024/03_input.txt");
    vector<string> data;

    string line;
    while (getline(f, line))
    {
        data.push_back(line);
    }

    sol1(data);
    sol2(data);
    
    return 0;
}
