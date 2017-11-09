#include "openedu.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    string p, t; input >> p >> t;
    if (p.size() > t.size()) {
        output << 0;
        return 0;
    }

    string s = p + "#" + t;
    int n = (int) s.length();
    vector<int> z(n);
    for (int i=1, l=0, r=0; i<n; ++i) {
        if (i <= r)
            z[i] = min(r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i,  r = i+z[i]-1;
    }

    vector<int> inclusions;
    int psize = (int) p.length();
    for (int i = 0, ilen = t.size(); i < ilen; ++i) {
        if (z[i+psize+1] == psize)
            inclusions.push_back(i+1);
    }

    output << (int) inclusions.size() << "\n";
    output.print(inclusions.begin(), inclusions.end());
}


