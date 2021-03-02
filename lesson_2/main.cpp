#include <iostream>
#include <cstdlib>
#include "JSArray.hpp"

// TODO
// Add benchmarks
auto hash1 = [] (const int& n) { return 101*((n >> 24) + 101 * ((n >> 16) + 101 * (n >> 8))) + n ; } ;
auto hash2 = [] (const int& n) { return ((n >> 16) ^ n) * 0x45d9f3b ; };
auto hash3 = [] (const int& n) { return n ; };


int main() {
    JSArray<int> contigiusArray;
    for (int i = 0; i < 1000000; ++i) {
        contigiusArray.addElement(i, rand());
    }

    JSArray<int,decltype(hash1)> gapArray1(hash1);
    for (int i = 0; i < 100000; ++i) {
        if (i > 100) {
            i += rand()%i;
        }
        gapArray1.addElement(i, rand());
    }

    JSArray<int,decltype(hash2)> gapArray2(hash2);
    for (int i = 0; i < 100000; ++i) {
        if (i > 100) {
            i += rand()%i;
        }
        gapArray2.addElement(i, rand());
    }

    JSArray<int,decltype(hash3)> gapArray3(hash3);
    for (int i = 0; i < 100000; ++i) {
        if (i > 100) {
            i += rand()%i;
        }
        gapArray3.addElement(i, rand());
    }

    return 0;
}