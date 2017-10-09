#include "openedu.hpp"
#include <queue>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    unsigned short registers[26];
    map<string, int> labels;
    queue<unsigned short> q;

    vector<string> instructions;
    for (int i = 0;; ++i) {
        string temp; input >> temp;
        if (temp == "")
            break;
        if (temp[0] == ':')
            labels[temp.substr(1)] = i;
        instructions.push_back(temp);
    }

    vector<int> gotosAndInts(instructions.size(), 10e6);
    for (int i = 0, ilen = instructions.size(); i < ilen; ++i) {
        switch (instructions[i][0]) {
            case 'J':
                gotosAndInts[i] = labels[instructions[i].substr(1)];
                break;
            case 'Z':
                gotosAndInts[i] = labels[instructions[i].substr(2)];
                break;
            case 'E':
            case 'G':
                gotosAndInts[i] = labels[instructions[i].substr(3)];
                break;
        }
        if (instructions[i][0] >= 'a' && instructions[i][0] <= 'z')
            gotosAndInts[i] = stoi(instructions[i]);
    }

    int current = 0;
    for (int ilen = instructions.size(); current < ilen; ++current) {
        switch (instructions[current][0]) {
            case '+': {
                unsigned short a = q.front(); q.pop();
                unsigned short b = q.front(); q.pop();
                q.push((a + b) % 65536);
                break;
            }
            case '-': {
                unsigned short a = q.front(); q.pop();
                unsigned short b = q.front(); q.pop();
                q.push((a - b) % 65536);
                break;
            }
            case '*': {
                unsigned short a = q.front(); q.pop();
                unsigned short b = q.front(); q.pop();
                q.push((a * b) % 65536);
                break;
            }
            case '/': {
                unsigned short a = q.front(); q.pop();
                unsigned short b = q.front(); q.pop();
                q.push(b == 0 ? 0 : a/b);
                break;
            }
            case '%': {
                unsigned short a = q.front(); q.pop();
                unsigned short b = q.front(); q.pop();
                q.push(b == 0 ? 0 : a%b);
                break;
            }
            case '>': {
                unsigned short a = q.front(); q.pop();
                registers[instructions[current][1]-'a'] = a;
                break;
            }
            case '<': {
                q.push(registers[instructions[current][1]-'a']);
                break;
            }
            case 'P': {
                if (instructions[current].size() == 1) {
                    unsigned short a = q.front(); q.pop();
                    output << a << "\n";
                } else {
                    unsigned short a = registers[instructions[current][1]-'a'];
                    output << a << "\n";
                }
                break;
            }
            case 'C': {
                if (instructions[current].size() == 1) {
                    int a = q.front(); q.pop();
                    output << char(a % 256);
                } else {
                    int a = registers[instructions[current][1]-'a'];
                    output << char(registers[instructions[current][1]-'a'] % 256);
                }
                break;
            }
            case ':':
                break;
            case 'J':
                current = gotosAndInts[current];
                break;
            case 'Z':
                if (registers[instructions[current][1] - 'a'] == 0)
                    current = gotosAndInts[current];
                break;
            case 'E':
                if (registers[instructions[current][1] - 'a'] == registers[instructions[current][2] - 'a'])
                    current = gotosAndInts[current];
                break;
            case 'G':
                if (registers[instructions[current][1] - 'a'] > registers[instructions[current][2] - 'a'])
                    current = gotosAndInts[current];
                break;
            case 'Q':
                current = 10e6;
                break;
            default:
                q.push((unsigned short) gotosAndInts[current]);
                break;
        }
    }
}
