#include "openedu.hpp"

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    long long a, b; input >> a >> b;
    output << a+b*b;
}
