#include "openedu.hpp"
#include <climits>
using namespace std;

long long inversions = 0;

void merge(int* A, int l, int m, int r) {
    int nl = m - l + 1, nr = r - m;
    int i, j;
    int *L = new int[nl + 1], *R = new int[nr + 1];
    for (i = 0; i < nl; ++i)
        L[i] = A[l + i];
    for (j = 0; j < nr; ++j)
        R[j] = A[m + 1 + j];
    L[nl] = R[nr] = INT_MAX;
    i = j = 0;
    for (int k = l; k < r + 1; ++k)
        if (L[i] <= R[j]) {
            A[k] = L[i];
            ++i;
        } else {
            inversions += nl - i;
            A[k] = R[j];
            ++j;
        }
   delete L, R;
}

void mergeSort(int* a, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    int *a = new int[n];
    for (int i = 0; i < n; ++i)
        input >> a[i];

    mergeSort(a, 0, n-1);
    output << inversions;
}
