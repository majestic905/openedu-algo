#include "openedu.hpp"
#include <map>
#include <climits>
#include <vector>

using namespace std;

struct Element {
    int currentIndex;
    int value;
    Element(int i, int v) : currentIndex(i), value(v) {}
};

struct QueueWithPriorities {
    map<int, Element*> ref;
    vector<Element*> array;
    int heapSize;
    openedu_out o;

    QueueWithPriorities(const openedu_out& output) {
        o = output;
        heapSize = 0;
        array = vector<Element*>(1000000, NULL);
    }

    void extract() {
        if (heapSize == 0)
            o << "*" << "\n";
        else {
            o << array[0]->value << "\n";
            --heapSize;
            swap(0, heapSize);
            delete array[heapSize];
            heapify(0);
        }
    }

    void decrease(int lineIndex, int value) {
        int index = ref[lineIndex]->currentIndex;
        array[index]->value = value;
        while (index > 0 && array[parent(index)]->value > array[index]->value) {
            swap(index, parent(index));
            index = parent(index);
        }
    }

    void insert(int lineIndex, int value) {
        array[heapSize] = new Element(heapSize, INT_MAX);
        ref[lineIndex] = array[heapSize];
        ++heapSize;
        decrease(lineIndex, value);
    }

    int parent(int i) { return (i + 1) / 2 - 1; }

    void heapify(int index) {
        int rightChildIndex = (index + 1) * 2;
        int leftChildIndex = rightChildIndex - 1;
        int lowestIndex = INT_MIN;

        if (leftChildIndex < heapSize && array[leftChildIndex]->value < array[index]->value)
            lowestIndex = leftChildIndex;
        else
            lowestIndex = index;

        if (rightChildIndex < heapSize && array[rightChildIndex]->value < array[lowestIndex]->value)
            lowestIndex = rightChildIndex;

        if (lowestIndex != index) {
            swap(lowestIndex, index);
            heapify(lowestIndex);
        }
    }

    void swap(int a, int b) {
        array[a]->currentIndex = b;
        array[b]->currentIndex = a;
        Element* temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }

    ~QueueWithPriorities() {
        for (int i = 0; i < heapSize; ++i)
            delete array[i];
    }
};

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    QueueWithPriorities q(output);
    for (int i = 0; i < n; ++i) {
        string action; input >> action;
        if (action == "A") {
            string value; input >> value;
            q.insert(i+1, stoi(value));
        } else if (action == "X") {
            q.extract();
        } else {
            string line, value; input >> line >> value;
            q.decrease(stoi(line), stoi(value));
        }
    }
}
