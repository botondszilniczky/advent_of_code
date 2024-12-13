#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <vector>

using namespace std;

pair<double, double> solveEquation(double A, double B, double C, double D, double E, double F)
{
    double x = (C*E-B*F) / (A*E-B*D);
    double y = (A*F-C*D) / (A*E-B*D);
    return make_pair(x,y);
}

int sol1(vector<string> data)
{
    double A, B, C;
    double D, E, F;
    regex reg1("A: X\\+(\\d+), Y\\+(\\d+)");
    regex reg2("B: X\\+(\\d+), Y\\+(\\d+)");
    regex reg3("X=(\\d+), Y=(\\d+)");

    int sum = 0;
    for (string line : data)
    {
        smatch m;
        if (regex_search(line, m, reg1))
        {
            A = stod(m[1]);
            D = stod(m[2]);
        }
        if (regex_search(line, m, reg2))
        {
            B = stod(m[1]);
            E = stod(m[2]);
        }
        if (regex_search(line, m, reg3))
        {
            C = stod(m[1]);
            F = stod(m[2]);
            pair<double, double> res = solveEquation(A, B, C, D, E, F);
            if (0 <= res.first && res.first <= 100 && floor(res.first) == res.first
                && 0 <= res.second && res.second <= 100 && floor(res.second) == res.second)
            {
                // cout << A << ", " << B << ", " << C << endl;
                // cout << D << ", " << E << ", " << F << endl;
                // cout << res.first << ", " << res.second << endl << endl;
                sum += 3*res.first + res.second;
            }
        }
    }
    cout << sum << endl;
    return 0;
}

int sol2(vector<string> data)
{
    double A, B, C;
    double D, E, F;
    regex reg1("A: X\\+(\\d+), Y\\+(\\d+)");
    regex reg2("B: X\\+(\\d+), Y\\+(\\d+)");
    regex reg3("X=(\\d+), Y=(\\d+)");
    double correction = 10000000000000;

    double sum = 0;
    for (string line : data)
    {
        smatch m;
        if (regex_search(line, m, reg1))
        {
            A = stod(m[1]);
            D = stod(m[2]);
        }
        if (regex_search(line, m, reg2))
        {
            B = stod(m[1]);
            E = stod(m[2]);
        }
        if (regex_search(line, m, reg3))
        {
            C = stod(m[1]) + correction;
            F = stod(m[2]) + correction;
            pair<double, double> res = solveEquation(A, B, C, D, E, F);
            if (0 <= res.first && floor(res.first) == res.first
                && 0 <= res.second && floor(res.second) == res.second)
            {
                // cout << A << ", " << B << ", " << C << endl;
                // cout << D << ", " << E << ", " << F << endl;
                // cout << res.first << ", " << res.second << endl << endl;
                sum += 3*res.first + res.second;
            }
        }
    }
    cout << fixed << setprecision(0) << sum << endl;
    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/13_input.txt");
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
