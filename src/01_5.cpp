#include "openedu.hpp"

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

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
    int *a = new int[n];
    int *b = new int[n];
    for (int i = 0; i < n; ++i) {
        input >> a[i];
        b[i] = i+1;
    }

    selectionSort(a, b, n);
    for (int i = 1; i < n; ++i)
        if (b[i] != i+1)
            output << "Swap elements at indices " << MIN(b[i], i+1) << " and " << MAX(b[i], i+1) << "." << "\n";
    output.println("No more swaps needed.");
    output.println(a, a+n);
}
