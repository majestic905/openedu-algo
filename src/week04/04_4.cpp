#include "openedu.hpp"
#include <stack>
#include <utility>
#include <algorithm>

// http://e-maxx.ru/algo/stacks_for_minima

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    stack<pair<int, int>> s1, s2;
    int n; input >> n;
    for (int i = 0; i < n; ++i) {
        string c; input >> c;
        if (c == "+") {
            int t; input >> t;
            int m = (s1.size() == 0 ? t : min(t, s1.top().second));
            s1.push(pair<int, int>(t, m));
        } else if (c == "-") {
            if (s2.size() == 0)
                while (s1.size() != 0) {
                    int el = s1.top().first;
                    s1.pop();
                    int m = (s2.size() == 0 ? el : min(el, s2.top().second));
                    s2.push(pair<int, int>(el, m));
                }
            s2.pop();
        } else if (c == "?") {
            if (s1.size() == 0 || s2.size() == 0)
                output << (s1.size() == 0 ? s2.top().second : s1.top().second) << "\n";
            else
                output << min(s1.top().second, s2.top().second) << "\n";
        }
    }
}
