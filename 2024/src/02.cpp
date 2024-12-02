#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int sol1(vector<string> &data)
{
    int sum = 0;
    for (string line : data)
    {
        stringstream ss;
        ss << line;
        int a;
        int b;
        ss >> a;
        char order = 'o'; // a: ascend, d: descend, o: N/A
        bool cool = true;
        while (ss >> b)
        {
            if (order == 'o')
            {
                if (a-b < 0)
                {
                    order = 'a';
                }
                else if (a-b > 0)
                {
                    order = 'd';
                }
                else
                {
                    cool = false;
                    break;
                }
            }
            if (order == 'a')
            {
                if (b-a <=3 && b-a >=1)
                {
                    a = b;
                }
                else
                {
                    cool = false;
                    break;
                }
            }
            if (order == 'd')
            {
                if (a-b <=3 && a-b >=1)
                {
                    a = b;
                }
                else
                {
                    cool = false;
                    break;
                }
            }   
        }
        if (cool)
        {
            sum++;
        }
    }
    cout << sum << endl;
    return 0;
}

int sol2(vector<string> data)
{
    int sum = 0;
    for (string line : data)
    {
        stringstream ss;
        ss << line;
        int a;
        int b;
        ss >> a;
        char order = 'o'; // a: ascend, d: descend, o: N/A
        bool cool = true;
        bool problemDampener = false;
        while (ss >> b)
        {
            if (order == 'o')
            {
                if (a-b < 0)
                {
                    order = 'a';
                }
                else if (a-b > 0)
                {
                    order = 'd';
                }
                else
                {
                    if (!problemDampener)
                    {
                        problemDampener = true;
                        a = b;
                        continue;
                    }
                    
                    cool = false;
                    break;
                }
            }
            if (order == 'a')
            {
                if (b-a <=3 && b-a >=1)
                {
                    a = b;
                }
                else
                {
                    if (!problemDampener)
                    {
                        problemDampener = true;
                        a = b;
                        continue;
                    }
                    cool = false;
                    break;
                }
            }
            if (order == 'd')
            {
                if (a-b <=3 && a-b >=1)
                {
                    a = b;
                }
                else
                {
                    if (!problemDampener)
                    {
                        problemDampener = true;
                        a = b;
                        continue;
                    }
                    cool = false;
                    break;
                }
            }   
        }
        if (cool)
        {
            sum++;
        }
    }
    cout << sum << endl;
    return 0;
}


int main(int argc, char const *argv[])
{
    ifstream f("./build/2024/02_input.txt");
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
