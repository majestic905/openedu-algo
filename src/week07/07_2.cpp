#include "openedu.hpp"
#include <queue>

using namespace std;

struct Node {
    int key, height;
    Node *parent, *left, *right;

    Node() {
        parent = left = right = NULL; height = 0;
    }
    static Node* getRoot(Node *node) {
        while (node->parent != NULL)
            node = node->parent;
        return node;
    }

    static Node* next(Node *node) {
        return (node->right == NULL ? node : minimum(node->right));
    }

    static Node* previous(Node *node) {
        return (node->left == NULL ? node : maximum(node->left));
    }

    static Node* maximum(Node *node) {
        while (node->right != NULL)
            node = node->right;
        return node;
    }

    static Node* minimum(Node *node) {
        while (node->left != NULL)
            node = node->left;
        return node;
    }

    static Node* remove(Node *item) {
        Node *parent = item->parent;

        if (item->left == NULL && item->right == NULL) {
            if (parent == NULL)
                return NULL;
            if (parent->left == item)
                parent->left = NULL;
            else
                parent->right = NULL;

            updateHeight(parent);
            return balance(parent);
        }

        if ((item->left == NULL) ^ (item->right == NULL))
            if (item->left != NULL) {
                if (parent != NULL) {
                    if (parent->left == item)
                        parent->left = item->left;
                    else
                        parent->right = item->left;

                    updateHeight(parent);
                }

                item->left->parent = parent;
                return balance(item->left);
            }
            else {
                if (parent != NULL) {
                    if (parent->left == item)
                        parent->left = item->right;
                    else
                        parent->right = item->right;

                    updateHeight(parent);
                }

                item->right->parent = parent;
                return balance(item->right);
            }


        if ((item->left != NULL) && (item->right != NULL)) {
            Node *prev = previous(item);
            remove(prev);
            item->key = prev->key;
        }

        return balance(item);
    }

    static Node* insert(Node *root, Node *node) {
        if (root == NULL)
            return node;
        Node *current = root;
        while (true) {
            if (current->key == node->key)
                return current;
            if (current->key < node->key) {
                if (current->right != NULL)
                    current = current->right;
                else {
                    current->right = node;
                    node->parent = current;
                    updateHeight(node);
                    return balance(node);
                }
            }
            else {
                if (current->left != NULL)
                    current = current->left;
                else {
                    current->left = node;
                    node->parent = current;
                    updateHeight(node);
                    return balance(node);
                }
            }
        }
    }

    static void updateHeight(Node *node) {
        while (node != NULL) {
            long rH = node->right != NULL ? node->right->height : -1;
            long lH = node->left != NULL ? node->left->height : -1;
            long currentH = node->height;
            node->height = (rH > lH ? rH + 1 : lH + 1);
            node = node->parent;
        }
    }

    static Node* search(Node *root, int key) {
        while (root != NULL && root->key != key)
            root = (root->key > key ? root->left : root->right);
        return root;
    }

    static Node* balance(Node *current) {
        if (current == NULL)
            return NULL;
        while (true) {
            int balance = getBalance(current);
            if (balance > 1)
                current = (getBalance(current->right) == -1 ? bigLeftTurn(current) : smallLeftTurn(current));
            if (balance < -1)
                current = (getBalance(current->left) == 1 ? bigRightTurn(current) : smallRightTurn(current));
            if (current->parent == NULL)
                return current;
            else
                current = current->parent;
        }
    }

    static void printTree(Node *root, openedu_out output) {
        if (root == NULL)
            return;
        queue<Node*> bfsQueue;
        int counter = 1;
        bfsQueue.push(root);
        while (bfsQueue.size() != 0) {
            Node* current = bfsQueue.front();
            bfsQueue.pop();
            output << current->key;

            if (current->left != NULL) {
                bfsQueue.push(current->left);
                output << " " << ++counter;
            }
            else
                output << " " << 0;

            if (current->right != NULL) {
                bfsQueue.push(current->right);
                output << " " << ++counter << "\n";
            } else
                output << " " << "0\n";
        }
    }

    static int getBalance(Node *tree) {
        if (tree == NULL)
            return 0;

        if (tree->left != NULL && tree->right != NULL)
            return tree->right->height - tree->left->height;
        if (tree->left == NULL && tree->right != NULL)
            return tree->right->height + 1;
        if (tree->left != NULL && tree->right == NULL)
            return -1 - tree->left->height;
        else
            return 0;
    }

    static Node* smallLeftTurn(Node *root) {
        Node *child = root->right;
        Node *parent = root->parent;
        Node *x = root->left;
        Node *y = root->right->left;
        Node *z = root->right->right;

        child->parent = parent;
        root->parent = child;
        if (x != NULL)
            x->parent = root;
        if (y != NULL)
            y->parent = root;
        if (z != NULL)
            z->parent = child;

        root->left = x;
        root->right = y;
        child->left = root;
        child->right = z;
        if (parent != NULL)
            if (parent->right == root)
                parent->right = child;
            else
                parent->left = child;

        int xH = x != NULL ? x->height : -1;
        int yH = y != NULL ? y->height : -1;
        int zH = z != NULL ? z->height : -1;

        root->height = (xH > yH ? xH + 1 : yH + 1);
        child->height = (root->height > zH ? root->height + 1 : zH + 1);

        updateHeight(child);
        return child;
    }

    static Node* smallRightTurn(Node *root) {
        Node *child = root->left;
        Node *parent = root->parent;
        Node *x = root->right;
        Node *y = root->left->left;
        Node *z = root->left->right;

        child->parent = parent;
        root->parent = child;
        if (x != NULL)
            x->parent = root;
        if (y != NULL)
            y->parent = child;
        if (z != NULL)
            z->parent = root;

        root->left = z;
        root->right = x;
        child->left = y;
        child->right = root;
        if (parent != NULL)
            if (parent->right == root)
                parent->right = child;
            else
                parent->left = child;

        int xH = x != NULL ? x->height : -1;
        int yH = y != NULL ? y->height : -1;
        int zH = z != NULL ? z->height : -1;

        root->height = (zH > xH ? zH + 1 : xH + 1);
        child->height = (y->height > root->height ? yH + 1 : root->height + 1);

        updateHeight(child);
        return child;
    }

    static Node* bigRightTurn(Node *root) {
        Node *w = root->right;
        Node *parent = root->parent;
        Node *b = root->left;
        Node *c = root->left->right;
        Node *z = b->left;
        Node *x = c->left;
        Node *y = c->right;

        c->parent = parent;
        b->parent = c;
        root->parent = c;
        if (w != NULL)
            w->parent = root;
        if (z != NULL)
            z->parent = b;
        if (y != NULL)
            y->parent = root;
        if (x != NULL)
            x->parent = b;

        if (parent != NULL)
            if (parent->right == root)
                parent->right = c;
            else
                parent->left = c;
        c->left = b;
        c->right = root;
        b->left = z;
        b->right = x;
        root->left = y;
        root->right = w;

        int xH = (x != NULL ? x->height : -1);
        int yH = (y != NULL ? y->height : -1);
        int zH = (z != NULL ? z->height : -1);
        int wH = (w != NULL ? w->height : -1);

        b->height = (zH > xH ? zH + 1 : xH + 1);
        root->height = (yH > wH ? yH + 1 : wH + 1);
        c->height = (b->height > root->height ? b->height + 1 : root->height + 1);

        updateHeight(c);
        return c;
    }

    static Node* bigLeftTurn(Node *root) {
        Node *w = root->left;
        Node *parent = root->parent;
        Node *b = root->right;
        Node *c = root->right->left;
        Node *z = b->right;
        Node *x = c->left;
        Node *y = c->right;

        c->parent = parent;
        b->parent = c;
        root->parent = c;
        if (w != NULL)
            w->parent = root;
        if (z != NULL)
            z->parent = b;
        if (y != NULL)
            y->parent = b;
        if (x != NULL)
            x->parent = root;

        if (parent != NULL)
            if (parent->right == root)
                parent->right = c;
            else
                parent->left = c;
        c->left = root;
        c->right = b;
        b->left = y;
        b->right = z;
        root->left = w;
        root->right = x;

        int xH = (x != NULL ? x->height : -1);
        int yH = (y != NULL ? y->height : -1);
        int zH = (z != NULL ? z->height : -1);
        int wH = (w != NULL ? w->height : -1);

        root->height = (wH > xH ? root->height = wH + 1 : root->height = xH + 1);
        b->height = (yH > zH ? b->height = yH + 1 : b->height = zH + 1);
        c->height = (b->height > root->height ? b->height + 1 : root->height + 1);

        updateHeight(c);
        return c;
    }
};

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    vector<Node*> nodes(n);
    vector<int> leafs;

    for (int i = 0; i < n; ++i)
        nodes[i] = new Node();

    for (int i = 0; i < n; ++i) {
        int key, left, right; input >> key >> left >> right;

        nodes[i]->key = key;

        if (left != 0) {
            nodes[left-1]->parent = nodes[i];
            nodes[i]->left = nodes[left-1];
        }

        if (right != 0) {
            nodes[right-1]->parent = nodes[i];
            nodes[i]->right = nodes[right-1];
        }

        if (right == 0 && left == 0)
            leafs.push_back(i);
    }

    for (int i = 0, ilen = leafs.size(); i < ilen; ++i)
        Node::updateHeight(nodes[leafs[i]]);

    Node *root = Node::getRoot(nodes[0]);
    root = Node::balance(root);
    output << n << "\n";
    Node::printTree(root, output);

    for (int i = 0; i < n; ++i)
        delete nodes[i];
}
