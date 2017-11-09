#include <iostream>
#include "openedu.hpp"
#include <map>

using namespace std;

struct Node {
    Node *prev, *next;
    string value;
    Node(string value) : value(value), prev(NULL), next(NULL) {}
};

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    map<string, Node*> m;
    Node *last = NULL;

    int n; input >> n;
    for (int i = 0; i < n; ++i) {
        string action; input >> action;
        if (action == "get") {
            string key; input >> key;
            map<string, Node*>::iterator it = m.find(key);
            output << (it == m.end() ? "<none>" : it->second->value) << "\n";
        } else if (action == "put") {
            string key, value; input >> key >> value;
            map<string, Node*>::iterator it = m.find(key);
            if (it != m.end()) {
                it->second->value = value;
            } else {
                Node *node = new Node(value);
                node->prev = last;
                if (last != NULL)
                    last->next = node;
                m[key] = node;
                last = node;
            }
        } else if (action == "delete") {
            string key; input >> key;
            map<string, Node*>::iterator it = m.find(key);
            if (it != m.end()) {
                Node *node = it->second;
                if (node->prev != NULL)
                    node->prev->next = node->next;
                if (node->next != NULL)
                    node->next->prev = node->prev;
                if (node == last)
                    last = last->prev;
                m.erase(key);
                delete node;
            }
        } else if (action == "prev") {
            string key; input >> key;
            map<string, Node*>::iterator it = m.find(key);
            output << (it == m.end() || it->second->prev == NULL ? "<none>" : it->second->prev->value) << "\n";
        } else if (action == "next") {
            string key; input >> key;
            map<string, Node*>::iterator it = m.find(key);
            output << (it == m.end() || it->second->next == NULL ? "<none>" : it->second->next->value) << "\n";
        }
    }
}
