#include "openedu.hpp"
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    int key;
    Node *parent, *left, *right;

    Node() {key = 0; parent = left = right = NULL;}

    static int count(Node* node) {
        if (node == NULL) return 0;
        return Node::count(node->left) + 1 + Node::count(node->right);
    }

    static Node* search(Node* node, int value) {
        while (value != node->key) {
            if (value < node->key && node->left != NULL)
                node = node->left;
            else if (value > node->key & node->right != NULL)
                node = node->right;
            else
                break;
        }

        return (value == node->key ? node : NULL);
    }
};

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    vector<Node> nodes(n);

    for (int i = 0; i < n; ++i) {
        int key, left, right;
        input >> key >> left >> right;

        nodes[i].key = key;

        if (left != 0) {
            nodes[i].left = &nodes[left-1];
            nodes[left-1].parent = &nodes[i];
        }
        if (right != 0) {
            nodes[i].right = &nodes[right-1];
            nodes[right-1].parent = &nodes[i];
        }
    }

    int m; input >> m;
    vector<int> requests(m);
    for (int i = 0; i < m; ++i)
        input >> requests[i];

    Node* root = &nodes[0];
    while (root->parent != NULL)
        root = root->parent;

    for (int i = 0; i < m; ++i) {
        if (root != NULL) {
            Node* node = Node::search(root, requests[i]);
            if (node != NULL) {
                if (node == root) {
                    root = NULL;
                    output << 0;
                } else {
                    if (node->parent->right == node)
                        node->parent->right = NULL;
                    else
                        node->parent->left = NULL;
                }
                n -= Node::count(node);
            }
            output << n << "\n";
        } else {
            output << 0;
        }
    }
}
