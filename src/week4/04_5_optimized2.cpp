
#include "openedu.hpp"
#include <queue>
#include <map>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    unsigned short registers[26];
    map<string, int> labels;
    queue<unsigned short> q;

    list<string> instructions;
    for (int i = 0;; ++i) {
        string temp; input >> temp;
        if (temp.size() == 0)
            break;
        if (temp[0] == ':')
            labels[temp.substr(1)] = i;
        instructions.push_back(temp);
    }

    // JZEG><PC+-*/%:Q?
    vector<int> type(instructions.size(), 0);
    vector<int> gotos(instructions.size(), 10e6);
    vector<unsigned short> numbers(instructions.size(), 0);
    vector<int> register1(instructions.size(), 0);
    vector<int> register2(instructions.size(), 0);
    int i = 0;
    for (list<string>::iterator it = instructions.begin(); it != instructions.end(); ++it, ++i) {
        string instruction = *it;
        switch (instruction[0]) {
            case 'J':
                gotos[i] = labels[instruction.substr(1)];
                type[i] = 1;
                break;
            case 'Z':
                gotos[i] = labels[instruction.substr(2)];
                register1[i] = instruction[1] - 'a';
                type[i] = 2;
                break;
            case 'E':
                gotos[i] = labels[instruction.substr(3)];
                register1[i] = instruction[1] - 'a';
                register2[i] = instruction[2] - 'a';
                type[i] = 3;
                break;
            case 'G':
                gotos[i] = labels[instruction.substr(3)];
                register1[i] = instruction[1] - 'a';
                register2[i] = instruction[2] - 'a';
                type[i] = 4;
                break;
            case '>':
                register1[i] = instruction[1] - 'a';
                type[i] = 5;
                break;
            case '<':
                register1[i] = instruction[1] - 'a';
                type[i] = 6;
                break;
            case 'P':
                if (instruction.size() > 1)
                    type[i] = 7;
                else
                    type[i] = 17;
                break;
            case 'C':
                if (instruction.size() > 1) {
                    register1[i] = instruction[1]-'a';
                    type[i] = 8;
                } else
                    type[i] = 18;
                break;
            case '+':
                type[i] = 9;
                break;
            case '-':
                type[i] = 10;
                break;
            case '*':
                type[i] = 11;
                break;
            case '/':
                type[i] = 12;
                break;
            case '%':
                type[i] = 13;
                break;
            case ':':
                type[i] = 14;
                break;
            case 'Q':
                type[i] = 15;
                break;
            default:
                numbers[i] = (unsigned short) stoi(instruction);
                type[i] = 16;
                break;
        }
    }


    int current = 0;
    for (int ilen = instructions.size(); current < ilen; ++current) {
        switch (type[current]) {
            case 1:
                current = gotos[current];
                break;
            case 2:
                if (registers[register1[current]] == 0)
                    current = gotos[current];
                break;
            case 3:
                if (registers[register1[current]] == registers[register2[current]])
                    current = gotos[current];
                break;
            case 4:
                if (registers[register1[current]] > registers[register2[current]])
                    current = gotos[current];
                break;
            case 5: {
                unsigned short a = q.front(); q.pop();
                registers[register1[current]] = a;
                break;
            }
            case 6: {
                q.push(registers[register1[current]]);
                break;
            }
            case 7: {
                output << registers[register1[current]] << "\n";
                break;
            }
            case 8: {
                output << char(registers[register1[current]] % 256);
                break;
            }
            case 9: {
                unsigned short a = q.front(); q.pop();
                unsigned short b = q.front(); q.pop();
                q.push((a + b) % 65536);
                break;
            }
            case 10: {
                unsigned short a = q.front(); q.pop();
                unsigned short b = q.front(); q.pop();
                q.push((a - b) % 65536);
                break;
            }
            case 11: {
                unsigned short a = q.front(); q.pop();
                unsigned short b = q.front(); q.pop();
                q.push((a * b) % 65536);
                break;
            }
            case 12: {
                unsigned short a = q.front(); q.pop();
                unsigned short b = q.front(); q.pop();
                q.push(b == 0 ? 0 : a/b);
                break;
            }
            case 13: {
                unsigned short a = q.front(); q.pop();
                unsigned short b = q.front(); q.pop();
                q.push(b == 0 ? 0 : a%b);
                break;
            }
            case 14:
                break;
            case 15:
                current = 10e6;
                break;
            case 16:
                q.push(numbers[current]);
                break;
            case 17:
                output << q.front()<< "\n";
                q.pop();
                break;
            case 18:
                output << char(q.front() % 256);
                q.pop();
                break;
        }
    }
}
