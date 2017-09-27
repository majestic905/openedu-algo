#include "openedu.hpp"
#include <stack>

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    stack<int> s;

    int n, a, b; input >> n;
    for (int i = 0; i < n; ++i) {
        string str; input >> str;
        if (str == "+") {
            a = s.top(); s.pop();
            b = s.top(); s.pop();
            s.push(a + b);
        } else if (str == "-") {
            a = s.top(); s.pop();
            b = s.top(); s.pop();
            s.push(b - a);
        } else if (str == "*") {
            a = s.top(); s.pop();
            b = s.top(); s.pop();
            s.push(a * b);
        } else
            s.push(stoi(str));
    }

    output << s.top();
}
