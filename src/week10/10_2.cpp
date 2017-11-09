#include "openedu.hpp"
#include <iostream>
#include <vector>
#include <algorithm> // for microsoft compiler

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    string s; input >> s;
    int n = s.size();
    vector<int> z(n, 0);
    for (int i=1, l=0, r=0; i<n; ++i) {
        if (i <= r)
            z[i] = min(r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i, r = i+z[i]-1;
    }

    output.print(z.begin()+1, z.end());
}
