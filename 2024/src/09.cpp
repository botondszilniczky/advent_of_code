#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int findLastNonNegative(const std::vector<int>& input) {
    for (int i = input.size() - 1; i >= 0; --i) {
        if (input[i] != -1) {
            return i;
        }
    }
    return -1; // Return -1 if all elements are -1
}

int findContinuousSequence(const std::vector<int>& input, int A, int N) {
    for (int i = 0; i <= input.size() - N; ++i) {
        bool found = true;
        for (int j = 0; j < N; ++j) {
            if (input[i + j] != A) {
                found = false;
                break;
            }
        }
        if (found) {
            return i; // Return the starting position of the sequence
        }
    }
    return -1; // Return -1 if no such sequence is found
}

int sol1(string data)
{
    vector<int> compact;
    for (int i = 0; i < data.size(); i++)
    {
        int num = data[i] - '0';
        if (i%2 == 0)
        {
            for (int j = 0; j < num; j++)
            {
                compact.push_back(i/2);
            }
        }
        else
        {
            for (int j = 0; j < num; j++)
            {
                compact.push_back(-1);
            }
        }
    }
    
    int dotCount = count(compact.begin(), compact.end(), -1);
    for (int i = 0; i < compact.size() - dotCount; i++)
    {
        if (compact[i] < 0)
        {
            int pos = findLastNonNegative(compact);
            if (pos != -1)
            {
                swap(compact[i], compact[pos]);
            }
        }
    }
    
    double sum = 0;
    for (int i = 0; i < compact.size()-dotCount; i++)
    {
        sum += i * compact[i];
    }
    cout << fixed << setprecision(0) << sum << endl;
    return 0;
}

int sol2(string data)
{
    vector<int> compact;
    for (int i = 0; i < data.size(); i++)
    {
        int num = data[i] - '0';
        if (i%2 == 0)
        {
            for (int j = 0; j < num; j++)
            {
                compact.push_back(i/2);
            }
        }
        else
        {
            for (int j = 0; j < num; j++)
            {
                compact.push_back(-1);
            }
        }
    }
    
    int pos = findLastNonNegative(compact);
    for (int num = compact[pos]; num >= 0; num--)
    {
        int start = find(compact.begin(), compact.end(), num) - compact.begin();
        int numCount = count(compact.begin(), compact.end(), num);
        int availableSpace = findContinuousSequence(compact, -1, numCount);
        if (availableSpace != -1 && availableSpace < start)
        {
            for (int i = 0; i < numCount; i++)
            {
                swap(compact[start + i], compact[availableSpace + i]);
            }
        }
    }

    double sum = 0;
    for (int i = 0; i < compact.size(); i++)
    {
        if (compact[i] > 0)
        {
            sum += i * compact[i];
        }
    }
    cout << fixed << setprecision(0) << sum << endl;
    return 0;
}

int main(int argc, char const *argv[])
{
    ifstream file("./build/2024/09_input.txt");
    vector<string> data;
    string line;
    while(getline(file, line))
    {
        data.push_back(line);
    }
    sol1(data[0]);
    sol2(data[0]);

    return 0;
}
