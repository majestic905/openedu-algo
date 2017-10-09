#include "openedu.hpp"
#include <vector>

using namespace std;

void quickSort(vector<int>& A, int l, int r, int k1, int k2) {
    // да, нужно было всего лишь вставить эту пару строчек
    if (k2 < l || r < k1)
        return;

    int key = A[(l+r) / 2], i = l, j = r;
    do {
        while (A[i] < key) ++i;
        while (A[j] > key) --j;
        if (i <= j) {
            int t = A[j];
            A[j] = A[i];
            A[i] = t;
            ++i;
            --j;
        }
    } while (i <= j);

    if (l < j)
        quickSort(A, l, j, k1, k2);
    if (i < r)
        quickSort(A, i, r, k1, k2);
}


int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n, k1, k2; input >> n >> k1 >> k2;
    int a, b, c, a1, a2; input >> a >> b >> c >> a1 >> a2;
    vector<int> A(n); A[0] = a1; A[1] = a2;

    for (int i = 2; i < n; ++i) {
        int a3 = a*a1 + b*a2 + c;
        A[i] = a3;
        a1 = a2;
        a2 = a3;
    }

    quickSort(A, 0, n-1, k1-1, k2-1);
    output.println(A.begin()+k1-1, A.begin()+k2);
}
