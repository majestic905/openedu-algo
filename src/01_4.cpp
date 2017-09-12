#include "openedu.hpp"

using namespace std;

struct Node {
    double value;
    int index;
    bool operator<(const Node& t) { return this->value < t.value; }
    bool operator>(const Node& t) { return this->value > t.value; }
};

void selectionSort(Node* a, int n) {
    for (int j = 1; j < n; ++j) {
        Node key = a[j];
        int i = j - 1;
        while (i > -1 && a[i] > key) {
            a[i+1] = a[i];
            --i;
        }
        a[i+1] = key;
    }
}

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    Node *a = new Node[n];
    for (int i = 0; i < n; ++i) {
        input >> a[i].value;
        a[i].index = i+1;
    }

    selectionSort(a, n);
    output << a[0].index << " " << a[n/2].index << " " << a[n-1].index;
}
