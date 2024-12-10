#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void combinations(const string& s, vector<int>& pos, vector<string>& res, int n, int l) {
    cout << n << ": " << pos.size() << " " << res.size() << endl;
    if (n == l) {
        string line = "";
        for (int i = 0 ; i != n ; i++) {
            line += s[pos[i]];
        }
        res.push_back(line);
        return;
    }
    for (int i = 0 ; i != s.size(); i++) {
        pos[n] = i;
        combinations(s, pos, res, n+1, l);
    }
}
vector<string> combinations(const string& s, int l) {
    vector<int> pos(l, 0); // To store the current combination
    vector<string> combs;
    while (true) {
        // Print the current combination
        string comb = "";
        for (int i = 0; i < l; i++) {
            comb += s[pos[i]];
        }
        combs.push_back(comb);

        // Generate the next combination
        int index = l - 1;
        while (index >= 0 && pos[index] == s.size() - 1) {
            pos[index] = 0; // Reset this position and carry over
            index--;
        }

        // If index is negative, all combinations are generated
        if (index < 0) {
            break;
        }

        // Increment the current position
        pos[index]++;
    }
    return combs;
}

double sol1(vector<string> data)
{
    string s = "*+";
    double sum = 0;
    for (string line : data)
    {
        stringstream ss;
        ss << line;
        double result = 0; // result to be checked
        char trash;
        ss >> result >> trash;
        vector<double> nums; // numbers to add or multiply
        double num = 0;
        while (ss >> num)
        {
            nums.push_back(num);
        }
        if (nums.size() == 0)
        {
            continue;
        }

        vector<string> combs = combinations(s, nums.size()-1);
        bool equal = false;
        
        for(int i = 0; i < combs.size() && !equal; i++)
        {
            double res = nums[0];
            bool overflow = false;
            for (int j = 0; j < combs[i].size() && !overflow; j++)
            {
                if (combs[i][j] == '+')
                {
                    res += nums[j+1];
                }
                if (combs[i][j] == '*')
                {
                    res *= nums[j+1];
                }
                overflow = result < res;
            }
            if (result == res)
            {
                equal = true;
                sum += result;
            }
        }
    }
    cout << fixed << setprecision(0) << sum << endl;
    return 0;
}

double sol2(vector<string> data)
{
    string s = "*+|";
    double sum = 0;
    for (string line : data)
    {
        stringstream ss;
        ss << line;
        double result = 0; // result to be checked
        char trash;
        ss >> result >> trash;
        vector<double> nums; // numbers to add or multiply
        double num = 0;
        while (ss >> num)
        {
            nums.push_back(num);
        }
        if (nums.size() == 0)
        {
            continue;
        }

        vector<string> combs = combinations(s, nums.size()-1);
        bool equal = false;
        for(int i = 0; i < combs.size() && !equal; i++)
        {
            double res = nums[0];
            bool overflow = false;
            for (int j = 0; j < combs[i].size() && !overflow; j++)
            {
                if (combs[i][j] == '+')
                {
                    res += nums[j+1];
                }
                if (combs[i][j] == '*')
                {
                    res *= nums[j+1];
                }
                if (combs[i][j] == '|')
                {
                    stringstream concat;
                    concat << fixed << setprecision(0) << res << nums[j+1];
                    concat >> res;
                }
                overflow = result < res;
            }
            if (result == res)
            {
                equal = true;
                sum += result;
            }
        }
    }
    cout << fixed << setprecision(0) << sum << endl;
    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/07_input.txt");
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
