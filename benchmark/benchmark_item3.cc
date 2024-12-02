#include "benchmark/benchmark.h"

#include <iostream>
#include <string>
#include "src/lib/trojanmap.h"
#include <random>



static void BM_Item3(benchmark::State& state) {
  // Perform setup here
  TrojanMap trojanmap;
  for (auto _ : state) {
    // This code gets timed
    trojanmap.GetAllCategories();
  }
}


// Register the function as a benchmark
BENCHMARK(BM_Item3);

// Run the benchmark
BENCHMARK_MAIN();