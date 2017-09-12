#include "openedu.hpp"
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n, k; input >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        input >> a[i];
    }

    vector< vector<int> > A(k);
    for (int i = 0; i < k; ++i) {
        vector<int> t((n-i /* round up */ + k-1) / k);
        int m = 0;
        for (int j = i; j < n; j += k, ++m) {
            t[m] = a[j];
        }
        sort(t.begin(), t.end());
        A[i] = t;
    }

    a[0] = A[0][0];
    for (int i = 1; i < n; ++i) {
        int p = i % k, q = i / k;
        if (a[i-1] > A[p][q]) {
            output << "NO";
            return 0;
        } else
            a[i] = A[p][q];
    }

    output << "YES";
}
