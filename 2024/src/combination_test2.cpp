#include <iostream>
#include <string>
#include <vector>
using namespace std;

void combinations(const string& s, int l) {
    vector<int> pos(l, 0); // To store the current combination
    while (true) {
        // Print the current combination
        for (int i = 0; i < l; i++) {
            cout << s[pos[i]];
        }
        cout << endl;

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
}

int main() {
    string s("+*");
    int length = 4; // Length of the combinations
    combinations(s, length);
    return 0;
}
