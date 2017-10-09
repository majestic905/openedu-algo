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


//struct Stack {
//    string container[1000000];
//    long long top;

//    Stack() { top = 0; }
//    string pop() { return container[--top]; }
//    void push(string s) { container[top++] = s; }
//};

//int main() {
//    openedu_in input = openedu_in();
//    openedu_out output = openedu_out();

//    int n; input >> n;
//    Stack s;
//    string token, content;
//    for (int i = 0; i < n; ++i) {
//        input >> token >> content;
//        if (token == "+")
//            s.push(content);
//        else
//            output << s.pop() << "\n";
//    }
//}
