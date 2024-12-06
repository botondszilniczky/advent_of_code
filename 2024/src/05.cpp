#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

int sol1(vector<string> data)
{
    vector<pair<int,int>> rules;
    bool isOrder = false;
    int counter = 0;

    for (string line : data)
    {
        if (isOrder)
        {
            vector<int> order;
            regex reg("(\\d+)\\,*");
            smatch m;
            string s = line;
            bool ok = true;
            while (ok && regex_search(s, m, reg))
            {
                int act = stoi(m[1].str());
                for (int element : order)
                {
                    for (auto rule : rules)
                    {
                        if (rule.first == act && rule.second == element)
                        {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok)
                    {
                        break;
                    }
                }
                order.push_back(act);
                s = m.suffix();
            }
            if (ok)
            {
                int mid = order.size()/2;
                counter += order[mid];
            }
            continue;
        }
        
        if (line == "")
        {
            isOrder = true;
            continue;
        }
        regex reg("(\\d+)\\|(\\d+)");
        smatch m;
        regex_search(line, m, reg);
        rules.push_back({stoi(m[1].str()), stoi(m[2].str())});
    }
    cout << counter << endl;
    return counter;
}

int sol2(vector<string> data)
{
    vector<pair<int,int>> rules;
    bool isOrder = false;
    int counter = 0;

    for (string line : data)
    {
        if (isOrder)
        {
            vector<int> order;
            regex reg("(\\d+)\\,*");
            smatch m;
            string s = line;
            bool ok = true;
            while (regex_search(s, m, reg))
            {
                int act = stoi(m[1].str());
                if (ok)
                {
                    for (int element : order)
                    {
                        for (auto rule : rules)
                        {
                            if (rule.first == act && rule.second == element)
                            {
                                ok = false;
                                break;
                            }
                        }
                    }
                }
                
                order.push_back(act);
                s = m.suffix();
            }
            if (!ok)
            {
                vector<int> correct;
                for (int o : order)
                {
                    auto pos = correct.begin();
                    for (auto rule : rules)
                    {
                        if (rule.second == o)
                        {
                            auto it = find(pos, correct.end(), rule.first);
                            if (it != correct.end())
                            {
                                pos = it + 1;
                            }
                        }
                    }
                    correct.insert(pos, o);
                }
                int mid = correct.size()/2;
                counter += correct[mid];
            }
            continue;
        }
        
        if (line == "")
        {
            isOrder = true;
            continue;
        }
        regex reg("(\\d+)\\|(\\d+)");
        smatch m;
        regex_search(line, m, reg);
        rules.push_back({stoi(m[1].str()), stoi(m[2].str())});
    }
    cout << counter << endl;
    return counter;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/05_input.txt");
    vector<string> data;
    string line;
    while(getline(file, line))
    {
        data.push_back(line);
    }
    sol1(data);
    sol2(data);

    return 0;
}
