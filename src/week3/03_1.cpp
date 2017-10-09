#include <fstream>
#include <vector>

using namespace std;

void radixSort(unsigned *begin, unsigned *end) {
    unsigned *begin1 = new unsigned[end - begin];
    unsigned *end1 = begin1 + (end - begin);
    for (unsigned shift = 0; shift < 32; shift += 8) {
        size_t count[0x100] = {};
        for (unsigned *p = begin; p != end; p++)
            count[(*p >> shift) & 0xFF]++;
        unsigned *bucket[0x100], *q = begin1;
        for (int i = 0; i < 0x100; q += count[i++])
            bucket[i] = q;
        for (unsigned *p = begin; p != end; p++)
            *bucket[(*p >> shift) & 0xFF]++ = *p;
        std::swap(begin, begin1);
        std::swap(end, end1);
    }
    delete[] begin1;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n, m; input >> n >> m;
    unsigned *a = new unsigned[n], *b = new unsigned[m];
    for (int i = 0; i < n; ++i) {
        int t; input >> t;
        a[i] = unsigned(t);
    }
    for (int i = 0; i < m; ++i) {
        int t; input >> t;
        b[i] = unsigned(t);
    }

    unsigned *r = new unsigned[n*m];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            r[i*m+j] = a[i]*b[j];

    radixSort(r, r+n*m);

    unsigned long long sum = 0;
    for (int i = 0; i < n*m; i += 10)
        sum += r[i];
    output << sum;

    input.close();
    output.close();
}


//#include "openedu.hpp"
//#include <iostream>
//#include <algorithm>
//#include <vector>

//using namespace std;

//void radixSort(vector<int>& a) {
//   int maxi = *max_element(a.begin(), a.end()), n = a.size();
//   vector< vector<int> > buckets(256);

//   int q = 1;
//   while (maxi != 0) {
//       for (int i = 0; i < n; ++i) {
//          int num = a[i];
//          buckets[(num/q) % 256].push_back(num);
//       }

//       int k = 0;
//       for (int i = 0; i < 256; ++i) {
//           for (int j = 0; j < buckets[i].size(); ++j)
//              a[k++] = buckets[i][j];
//           buckets[i].clear();
//       }

//       maxi /= 256;
//       q *= 256;
//    }
//}

//int main() {
//    openedu_in input = openedu_in();
//    openedu_out output = openedu_out();

//    int n, m; input >> n >> m;
//    vector<int> a(n), b(m);
//    for (int i = 0; i < n; ++i)
//        input >> a[i];
//    for (int i = 0; i < m; ++i)
//        input >> b[i];

//    vector<int> r(n*m);
//    for (int i = 0; i < n; ++i)
//        for (int j = 0; j < m; ++j)
//            r[i*m+j] = a[i]*b[j];

//    radixSort(r);

//    long long sum = 0;
//    for (int i = 0; i < n*m; i += 10)
//        sum += r[i];
//    output << sum;
//}
