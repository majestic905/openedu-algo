#include "openedu.hpp"
#include <queue>
#include <string>

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    queue<string> s;
    string token, content;
    for (int i = 0; i < n; ++i) {
        input >> token;
        if (token == "+") {
            string content; input >> content;
            s.push(content);
        }
        else {
            output << s.front() << "\n";
            s.pop();
        }
    }
}



//struct Queue {
//    string container[1000000];
//    long long head;
//    long long tail;

//    Queue() { head = 0; tail = 0; }
//    string pop() { return container[head++]; }
//    void push(string s) { container[tail++] = s; }
//};

//int main() {
//    openedu_in input = openedu_in();
//    openedu_out output = openedu_out();

//    int n; input >> n;
//    Queue s;
//    string token, content;
//    for (int i = 0; i < n; ++i) {
//        input >> token >> content;
//        if (token == "+")
//            s.push(content);
//        else
//            output << s.pop() << "\n";
//    }
//}
