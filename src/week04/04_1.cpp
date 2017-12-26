#include "openedu.hpp"
#include <stack>
#include <string>

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    stack<string> s;
    string token, content;
    for (int i = 0; i < n; ++i) {
        input >> token;
        if (token == "+") {
            string content; input >> content;
            s.push(content);
        }
        else {
            output << s.top() << "\n";
            s.pop();
        }
    }
}
