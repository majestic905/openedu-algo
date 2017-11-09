#include "openedu.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    string s; input >> s;
    int i = 1, j = 0, n = s.size();
    vector<int> p(n+1);
    while (i < n) {
        if (s[i] == s[j]) {
            p[i+1] = j + 1;
            ++i; ++j;
        } else {
            if (j > 0)
                j = p[j];
            else {
                p[i+1] = 0;
                ++i;
            }
        }
    }

    output.print(p.begin()+1, p.end());
}
