#include "openedu.hpp"
#include <vector>

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    string p, t; input >> p >> t;
    vector<int> inclusions;

    for (int i = 0, ilen = t.size()-p.size()+1; i < ilen; ++i) {
        bool ok = true;
        for (int j = 0, jlen = p.size(); j < jlen; ++j)
            if (t[i+j] != p[j]) {
                ok = false;
                break;
            }
       if (ok)
           inclusions.push_back(i+1);
    }

    output << int(inclusions.size()) << "\n";
    output.println(inclusions.begin(), inclusions.end());
}
