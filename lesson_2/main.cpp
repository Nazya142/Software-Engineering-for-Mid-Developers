#include <iostream>
#include <cstdlib>
#include "JSArray.hpp"
#include "benchmark/benchmark.h"

constexpr auto hash1 = [] (const int& n) { return 101*((n >> 24) + 101 * ((n >> 16) + 101 * (n >> 8))) + n ; } ;
constexpr auto hash2 = [] (const int& n) { return ((n >> 16) ^ n) * 0x45d9f3b ; };
constexpr auto hash3 = [] (const int& n) { return n ; };

static void BM_ContigiusArray(benchmark::State& state) {
    for (auto _ : state) {
        JSArray<int> contigiusArray;
        for (int i = 0; i < 1000000; ++i) {
            contigiusArray.addElement(i, rand());
            auto temp = contigiusArray[i];
        }
    }
}
BENCHMARK(BM_ContigiusArray);

static void BM_GapArrayHash1(benchmark::State& state){
    for (auto _ : state) {
        JSArray<int,decltype(hash1)> gapArray(hash1);
        for (int i = 0; i < 20000000; i += 20) {
            gapArray.addElement(i, rand());
            auto temp = gapArray[i];
        }
    }
}
BENCHMARK(BM_GapArrayHash1);

static void BM_GapArrayHash2(benchmark::State& state){
    for (auto _ : state) {
        JSArray<int,decltype(hash2)> gapArray(hash2);
        for (int i = 0; i < 20000000; i += 20) {
            gapArray.addElement(i, rand());
            auto temp = gapArray[i];
        }
    }
}
BENCHMARK(BM_GapArrayHash2);

static void BM_GapArrayHash3(benchmark::State& state){
    for (auto _ : state) {
        JSArray<int,decltype(hash3)> gapArray(hash3);
        for (int i = 0; i < 20000000; i += 20) {
            gapArray.addElement(i, rand());
            auto temp = gapArray[i];
        }
    }
}
BENCHMARK(BM_GapArrayHash3);

BENCHMARK_MAIN();