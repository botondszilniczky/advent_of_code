#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void sol1(std::vector<std::string> lines)
{
    long long result = 0;

    for (int i = 1; i < lines.size(); ++i)
    {
        for (int j = 0; j < lines[i].size(); ++j)
        {
            if (lines[i - 1][j] == 'S' || lines[i - 1][j] == '|')
            {
                if (lines[i][j] == '^')
                {
                    result++;
                    if (lines[i][j - 1] == '.')
                    {
                        lines[i][j - 1] = '|';
                    }
                    if (lines[i][j + 1] == '.')
                    {
                        lines[i][j + 1] = '|';
                    }
                }
                if (lines[i][j] == '.')
                {
                    lines[i][j] = '|';
                }
            }
        }
    }
    std::cout << "Solution 1: " << result << std::endl;
}

struct PairHash
{
    size_t operator()(const std::pair<int, int> &p) const noexcept
    {
        return ((size_t)p.first << 32) ^ (unsigned)p.second;
    }
};

std::vector<std::string> G;
int H, W;

// memo[r][c] = number of timelines starting from (r,c)
std::unordered_map<std::pair<int, int>, long long, PairHash> memo;

long long dfs(int r, int c)
{
    auto key = std::make_pair(r, c);
    if (memo.count(key))
        return memo[key];

    // fall down until hitting '^' or exiting
    int rr = r + 1;
    while (rr < H && G[rr][c] != '^')
        rr++;

    if (rr == H)
    {
        // exited the manifold → one timeline
        return memo[key] = 1;
    }

    // splitter at (rr, c)
    long long total = 0;

    // left branch
    int lc = c - 1;
    if (lc < 0)
    {
        total += 1; // left branch exits immediately
    }
    else
    {
        total += dfs(rr, lc);
    }

    // right branch
    int rc = c + 1;
    if (rc >= W)
    {
        total += 1; // exits immediately
    }
    else
    {
        total += dfs(rr, rc);
    }

    return memo[key] = total;
}

void sol2(const std::vector<std::string> &lines)
{
    G = lines;
    H = G.size();
    W = G[0].size();
    memo.clear();

    int sr = -1, sc = -1;
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
            if (G[r][c] == "S"[0])
            {
                sr = r;
                sc = c;
            }

    long long result = dfs(sr, sc);

    std::cout << "Solution 2: " << result << "\n";
}

int main(int argc, char **argv)
{
    std::string input = argc > 1 ? argv[1] : "input.txt";

    std::ifstream file(input);
    if (!file)
    {
        std::cerr << "Error opening file: " << input << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    for (std::string line; std::getline(file, line);)
    {
        if (line.empty())
        {
            continue;
        }
        lines.push_back(line);
    }

    sol1(lines);
    sol2(lines);

    return 0;
}