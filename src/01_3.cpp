#include "openedu.hpp"

using namespace std;

void selectionSort(int* a, int *indices, int n) {
    indices[0] = 1;
    for (int j = 1; j < n; ++j) {
        int key = a[j];
        int i = j - 1;
        while (i > -1 && a[i] > key) {
            a[i+1] = a[i];
            --i;
        }
        a[i+1] = key;
        indices[j] = i+2;
    }
}

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    int *a = new int[n], *indices = new int[n];
    for (int i = 0; i < n; ++i)
        input >> a[i];

    selectionSort(a, indices, n);

    output.println(indices, indices+n);
    output.print(a, a+n);
}

