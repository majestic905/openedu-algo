#include "openedu.hpp"
#include <vector>

using namespace std;

bool minHeapify(vector<int>& a, int i) {
    int right = i*2, left = i*2-1;
    if (left < a.size() && a[left] < a[i-1] || right < a.size() && a[right] < a[i-1])
        return false;
    return true;
}

bool isHeap(vector<int>& a) {
    bool r = true;
    for (int i = a.size() / 2 - 1; i >= 0 && r; --i)
        r = minHeapify(a, i+1);
    return r;
}

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        input >> a[i];
    output << (isHeap(a) ? "YES" : "NO");
}
