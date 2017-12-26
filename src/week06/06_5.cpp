#include "openedu.hpp"
#include <set>
#include <vector>
#include <climits>

using namespace std;

struct Node {
    int key, min, max;
    Node *parent, *left, *right;
    Node() { key = min = max = 0; parent = left = right = NULL; }
    Node(int min, int max) : min(min), max(max) {
        parent = left = right = NULL;
    }
};

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    vector<Node> nodes(n);

    set<int> keys;
    bool isCorrect = true;

    for (int i = 0; i < n && isCorrect; ++i) {
        int key, left, right;
        input >> key >> left >> right;

        if (nodes[i].min == 0 && nodes[i].max == 0) {
            nodes[i].min = INT_MIN;
            nodes[i].max = INT_MAX;
        }
        nodes[i].key = key;

        if (left != 0) {
            nodes[left-1].min = nodes[i].min;
            nodes[left-1].max = key;
            nodes[left-1].parent = &nodes[i];
            nodes[i].left = &nodes[left-1];
        }

        if (right != 0) {
            nodes[right-1].min = key;
            nodes[right-1].max = nodes[i].max;
            nodes[right-1].parent = &nodes[i];
            nodes[i].right = &nodes[right-1];
        }

        if (nodes[i].parent != NULL)
            if (nodes[i].parent->key > nodes[i].key) {
                if (nodes[i].parent->right == &nodes[i] || nodes[i].key > nodes[i].parent->max || nodes[i].key < nodes[i].parent->min)
                    isCorrect = false;
            } else {
                if (nodes[i].parent->left == &nodes[i] || nodes[i].key > nodes[i].parent->max || nodes[i].key < nodes[i].parent->min)
                    isCorrect = false;
            }

        if (keys.find(key) != keys.end())
            isCorrect = false;
        keys.insert(key);
    }

    if (isCorrect)
        output << "YES";
    else
        output << "NO";
}
