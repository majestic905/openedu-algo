#include <iostream>
using namespace std;

int main() {
    cout << '0';
  for (unsigned long i = 0; i < 100000; i++) {
    cout << __builtin_popcountl(i)%2;
  }
}
