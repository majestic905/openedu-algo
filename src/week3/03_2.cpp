#include "openedu.hpp"
#include <vector>

using namespace std;

void countingSort(vector<string>& array, vector<int>& indices, int n, int m, int p) {
    int k = m - p - 1;

    vector<int> newIndices(n+1);
    vector<int> counts(123);

    for (int i = 0; i < n; ++i)
        ++counts[array[k][i]];
    for (int i = 98; i <= 122; ++i)
        counts[i] += counts[i-1];
    for (int i = n; i > 0; --i) {
        int symbol = array[k][indices[i]-1];
        int newIndex = counts[symbol];
        newIndices[newIndex] = indices[i];
        --counts[symbol];
    }

    indices = newIndices;
}

void radixSort(vector<string>& array, vector<int>& indices, int n, int m, int k) {
    for (int i = 0; i < k; ++i)
        countingSort(array, indices, n, m, i);
}

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n, m, k; input >> n >> m >> k;
    vector<string> array(m);
    for (int i = 0; i < m; ++i)
        input >> array[i];

    vector<int> indices(n+1);
    for (int i = 0; i < n+1; ++i)
        indices[i] = i;

    radixSort(array, indices, n, m, k);

    output.print(indices.begin()+1, indices.end());
}
