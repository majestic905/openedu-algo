#include "openedu.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void compute(vector<int>& z, string& s) {
    int n = s.size();
    for (int i=1, l=0, r=0; i<n; ++i) {
        if (i <= r)
            z[i] = min(r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i, r = i+z[i]-1;
    }
}

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    string s; input >> s;
    int n = s.size();
    if (n <= 2) {
        output << s;
        return 0;
    }
    vector<int> z(n, 0);
    compute(z, s);

    vector<string> m1;
    vector<int> m2;
    int i = 0;
    while (i < s.size()) {
        if (z[i] != 0 && z[i] % i == 0) {
            int m = z[i] / i + 1;
            m1.push_back(s.substr(0, i));
            m2.push_back(m);
            s = s.substr(i*m);
            compute(z, s);
            i = 0;
        } else
            ++i;
    }

    if (s.size() > 0) {
        m1.push_back(s);
        m2.push_back(1);
    }

    output << m1[0] << (m2[0] > 1 ? "*"+to_string(m2[0]) : "");
    for (int i = 1, ilen = m1.size(); i < ilen; ++i) {
        output << "+" << m1[i] << (m2[i] > 1 ? "*"+to_string(m2[i]) : "");
    }
}
