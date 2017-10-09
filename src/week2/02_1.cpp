#include "openedu.hpp"
#include <climits>

using namespace std;

void merge(int *a, int l, int m, int r, openedu_out& os) {
    int nl = m - l + 1, nr = r - m;
    int i, j;
    int *L = new int[nl + 1], *R = new int[nr + 1];
    for (i = 0; i < nl; ++i)
        L[i] = a[l + i];
    for (j = 0; j < nr; ++j)
        R[j] = a[m + 1 + j];
    L[nl] = R[nr] = INT_MAX;
    i = j = 0;
    for (int k = l; k < r + 1; ++k)
        if (L[i] <= R[j]) {
            a[k] = L[i];
            ++i;
        } else {
            a[k] = R[j];
            ++j;
        }
    delete L, R;
    os << l + 1 << " " << r + 1 << " " << a[l] << " " << a[r] << "\n";
}

void mergeSort(int *a, int l, int r, openedu_out& os) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m, os);
        mergeSort(a, m + 1, r, os);
        merge(a, l, m, r, os);
    } else /* if (l == r) */
        os << l + 1 << " " << r + 1 << " " << a[l] << " " << a[r] << "\n";
}

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    int *a = new int[n];
    for (int i = 0; i < n; ++i)
        input >> a[i];

    mergeSort(a, 0, n-1, output);
    output.print(a, a+n);
}
