#include "openedu.hpp"
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    int key, parent, left, right;
    Node() { key = parent = left = right = 0; }
};

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    vector<int> leafs;
    int n; input >> n;

    if (n == 0) {
        output << 0;
        return 0;
    }

    vector<Node> array(n+1);
    for (int i = 1; i < n+1; ++i) {
        int key, left, right;
        input >> key >> left >> right;
        array[i].key = key;
        if (left != 0) {
            array[i].left = left;
            array[left].parent = i;
        }
        if (right != 0) {
            array[i].right = right;
            array[right].parent = i;
        }
        if (left == 0 && right == 0)
            leafs.push_back(i);
    }

    int height = 0;
    for (int i = 0, len = leafs.size(); i < len; i++)
    {
        int temp = 1;
        int current = leafs[i];
        while (array[current].parent != 0) {
            ++temp;
            current = array[current].parent;
        }
        if (temp > height)
            height = temp;
    }

    output << height;
}
