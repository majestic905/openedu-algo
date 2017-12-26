#include "openedu.hpp"
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;

struct Node {
    int first, index; long long sum;
    Node() { first = -1; }
    Node(int first, int index, long long sum) : first(first), index(index), sum(sum) {}
};

int main() {
    ifstream ifl("input.txt");
    ofstream ofl("output.txt");

    string s; getline(ifl, s);
    for (int i = s.size()-1; i >= 0; --i)
       if (s[i] == ' ')
          s.erase(i, 1);

    unordered_map<char, Node> m;
    long long count = 0;
    for (int current = 0, len = s.size(); current < len; ++current) {
        char c = s[current];
        if (m[c].first == -1)
            m[c] = Node(current, 1, 0);
        else {
            int diff = current-m[c].first, index = m[c].index;
            count += (long long) diff*index - index - m[c].sum;
            m[c].sum += diff;
            ++m[c].index;
        }
    }

    ofl << count;
    ifl.close();
    ofl.close();
}
