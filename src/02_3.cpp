#include "openedu.hpp"
using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n; input >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = i + 1;

    for (int i = 2; i < n; i++)
    {
        int t = a[i / 2];
        a[i / 2] = a[i];
        a[i] = t;
    }

    output.print(a, a+n);
}
