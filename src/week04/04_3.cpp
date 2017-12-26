#include "openedu.hpp"
#include <stack>
#include <map>

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    map<char,char> m = {{']', '['}, {'}', '{'}, {')', '('}};

    int n; input >> n;
    for (int i = 0; i < n; ++i) {
        string seq; input >> seq;
        stack<char> s;
        string r = "YES";

        for (char c: seq) {
            if (m.find(c) != m.end()) {
                if (s.empty() || (!s.empty() && m[c] != s.top())) {
                    r = "NO";
                    break;
                } else
                    s.pop();
            } else
                s.push(c);
        }

        if (s.empty())
            output << r << "\n";
        else
            output << "NO" << "\n";
    }
}
