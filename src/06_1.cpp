#include "openedu.hpp"
#include <vector>
#include <map>
#include <string>

using namespace std;

void binarySearch(vector<int>& array, int key, map<int, string>& results) {
    int l = -1, r = array.size();
    while (r > l+1) {
        if (r < array.size() && l >= 0 && array[l] == key && array[r] == key)
            break;
        int m = (l+r)/2;
        if (array[m] < key)
            l = m;
        else
            r = m;
    }

    if (r < array.size() && array[r] == key) {
        while (r < array.size() && array[r] == key)
            ++r;
        while (l >= 0 && array[l] == key)
            --l;
        l += 2;
        results[key] = to_string(l) + " " + to_string(r);
    } else {
        results[key] = "-1 -1";
    }
}

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    map<int, string> results;

    int n; input >> n;
    vector<int> array(n);
    for (int i = 0; i < n; ++i)
        input >> array[i];

    int m; input >> m;
    vector<int> requests(m);
    for (int i = 0; i < m; ++i)
        input >> requests[i];

    for (int i = 0; i < m; ++i) {
        if (results.find(requests[i]) == results.end())
            binarySearch(array, requests[i], results);
        output << results[requests[i]] << "\n";
    }
}
