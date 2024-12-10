#include <iostream>
#include <string>
#include <vector>
using namespace std;

void combinations(const string& s, vector<int>& pos, int n, int l) {
    if (n == l) {
        for (int i = 0 ; i != n ; i++) {
            cout << s[pos[i]];
        }
        cout << endl;
        return;
    }
    for (int i = 0 ; i != s.size(); i++) {
        pos[n] = i;
        combinations(s, pos, n+1, l);
    }
}

int main() {
	string s("+*");
	vector<int> pos(s.size(), 0);
    combinations(s, pos, 0, 10);
	return 0;
}