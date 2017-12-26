#include <iostream>
#include "openedu.hpp"
#include <set>

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    set<long long> s;
    int n; input >> n;
    for (int i = 0; i < n; ++i) {
        string action; input >> action;
        switch (action[0]) {
            case 'A':
                long long a; input >> a;
                s.insert(a);
                break;
            case 'D':
                long long b; input >> b;
                s.erase(b);
                break;
            case '?':
                long long c; input >> c;
                output << (s.find(c) == s.end() ? 'N' : 'Y') << "\n";
                break;
        }
    }
}
