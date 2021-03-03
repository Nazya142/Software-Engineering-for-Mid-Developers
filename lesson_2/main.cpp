#include <iostream>
#include <cstdlib>
#include "JSArray.hpp"
#include "../benchmark/include/benchmark/benchmark.h"

// TODO
// Add benchmarks
auto hash1 = [] (const int& n) { return 101*((n >> 24) + 101 * ((n >> 16) + 101 * (n >> 8))) + n ; } ;
auto hash2 = [] (const int& n) { return ((n >> 16) ^ n) * 0x45d9f3b ; };
auto hash3 = [] (const int& n) { return n ; };



static void BM_ContigiusArray(benchmark::State& state) {
    JSArray<int> contigiusArray;
    for (int i = 0; i < 1000000; ++i) {
        contigiusArray.addElement(i, rand());
    }
}
BENCHMARK(BM_ContigiusArray);

static void BM_GapArrayHash1(benchmark::State& state){
    JSArray<int,decltype(hash1)> gapArray(hash1);
    for (int i = 0; i < 100000; ++i) {
        if (i > 100) {
            i += rand()%i;
        }
        gapArray.addElement(i, rand());
    }
}
BENCHMARK(BM_GapArrayHash1);

static void BM_GapArrayHash2(benchmark::State& state){
    JSArray<int,decltype(hash2)> gapArray(hash2);
    for (int i = 0; i < 100000; ++i) {
        if (i > 100) {
            i += rand()%i;
        }
        gapArray.addElement(i, rand());
    }
}
BENCHMARK(BM_GapArrayHash2);

static void BM_GapArrayHash3(benchmark::State& state){
    JSArray<int,decltype(hash3)> gapArray(hash3);
    for (int i = 0; i < 100000; ++i) {
        if (i > 100) {
            i += rand()%i;
        }
        gapArray.addElement(i, rand());
    }
}
BENCHMARK(BM_GapArrayHash3);

BENCHMARK_MAIN();