#include "openedu.hpp"

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

using namespace std;

struct Node {
    int value;
    int index;
    bool operator<(const Node& t) { return this->value < t.value; }
    bool operator>(const Node& t) { return this->value > t.value; }
    friend const openedu_out& operator<< (const openedu_out& stream, const Node& n) { return (stream << n.value); }
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
        a[i].index = i;
    }

    selectionSort(a, n);

    for (int i = 0; i < n; ++i) {
        if (a[i].index != i) {
            output << "Swap elements at indices " << MIN(a[i].index+1, i+1) << " and " << MAX(a[i].index+1, i+1) << "." << "\n";
            for (int j = 0; j < n; ++j)
                if (a[j].index == i) {
                    a[j].index = a[i].index;
                    break;
                }
            a[i].index = i;
        }
    }
    output.println("No more swaps needed.");
    output.println(a, a+n);
}
