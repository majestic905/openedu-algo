#include "openedu.hpp"
#include <algorithm>
#include <vector>

using namespace std;

void countSort(vector<int>& a, int n, int maxVal) {
	vector<int> b(maxVal+1, 0);
	for (int i = 0; i < n; ++i)
		++b[a[i]];
	int k = 0;
	for (int i = 0; i < maxVal+1; ++i)
		for (int j = 0; j < b[i]; ++j)
			a[k++] = i;
}

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    int n, m; input >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i)
        input >> a[i];
    for (int i = 0; i < m; ++i)
        input >> b[i];

    countSort(a, n, 40000);
    countSort(b, m, 40000);

    vector<int> r(n*m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            r[i*m+j] = a[i]*b[j];
    sort(r.begin(), r.end());

    int sum = 0;
    for (int i = 0; i < n*m; i += 10)
        sum += r[i];
    output << sum;
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
