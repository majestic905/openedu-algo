#include "openedu.hpp"

using namespace std;

void selectionSort(double* a, int* b, int n) {
    for (int j = 1; j < n; ++j) {
        int key = a[j];
        int bkey = b[j];
        int i = j - 1;
        while (i > -1 && a[i] > key) {
            a[i+1] = a[i];
            b[i+1] = b[i];
            --i;
        }
        a[i+1] = key;
        b[i+1] = bkey;
    }
}

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    double *a = new double[n];
    int *b = new int[n];
    for (int i = 0; i < n; ++i) {
        input >> a[i];
        b[i] = i+1;
    }

    selectionSort(a, b, n);
    output << b[0] << " " << b[n/2] << " " << b[n-1];
}
