#include "openedu.hpp"

using namespace std;

int main() {
    openedu_in input = openedu_in();
    openedu_out output = openedu_out();

    //Thread.CurrentThread.CurrentCulture = new CultureInfo("en-US"); //.NET Framework
    //CultureInfo.CurrentCulture = new CultureInfo("en-US"); //.NET Core

    int n; input >> n;
    double a; input >> a;
    double left = 0, right = a, last = -1;
    while ((right-left) > 0.0000001 / (n-1)) {
        double mid = (left + right) / 2;
        double prev = a;
        double cur = mid;
        bool aboveGround = cur > 0;
        for(int i = 3; i <= n; ++i) {
            double next = 2 * cur - prev + 2;
            aboveGround &= next > 0;
            prev = cur;
            cur = next;
        }
        if (aboveGround) {
            right = mid;
            last = cur;
        } else
            left = mid;
    }
    output << last;
}
