#include "benchmark/benchmark.h"

#include <iostream>
#include <string>
#include "src/lib/trojanmap.h"
#include <random>



static void BM_Item10(benchmark::State& state) {
  // Perform setup here
  TrojanMap map;
  // input letter
  std::vector<std::vector<double>> selectPool_ = {{"bank", "Chase", 1, 5}, {"supermarket", "Target", 1, 5}, {"supermarket", "Ralphs", 2, 5}, {"supermarket", "Trader Joes", 1, 6}};
  std::vector<int> random_number = {2, 3, 2, 0, 3, 3, 0, 0, 3, 1, 0, 0, 0, 2, 2, 3, 0, 3, 1, 3, 1, 0, 3, 2, 0, 2, 1, 0, 2, 3, 2, 0, 2, 3, 3, 0, 3, 3, 1, 3, 3, 0, 3, 3, 0, 0, 3, 0, 3, 3, 3, 2, 3, 2, 2, 2, 2, 2, 3, 3, 1, 1, 0, 1, 1, 1, 1, 3, 0, 2, 0, 1, 0, 1, 2, 2, 3, 3, 2, 2, 3, 0, 2, 1, 1, 2, 1, 2, 1, 0, 2, 2, 0, 1, 1, 1, 1, 0, 1, 1, 3, 2, 2, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 2, 3, 3, 0, 1, 1, 0, 3, 1, 2, 3, 0, 3, 2, 1, 2, 2, 2, 3, 0, 3, 2, 0, 3, 0, 3, 1, 1, 1, 2, 0, 0, 0, 0, 1, 2, 2, 1, 2, 3, 2, 0, 0, 3, 0, 0, 3, 3, 2, 2, 3, 1, 3, 3, 0, 1, 3, 1, 3, 2, 0, 2, 3, 0, 2, 2, 3, 1, 2, 0, 3, 1, 2, 2, 0, 1, 3, 0, 0, 1, 1, 3, 0, 2, 3, 2, 0, 2, 0, 0, 1, 0, 1, 2, 2, 0, 1, 1, 3, 1, 3, 2, 1, 1, 3, 3, 1, 2, 2, 3, 3, 1, 3, 3, 2, 1, 3, 0, 2, 3, 2, 1, 0, 2, 0, 1, 1, 1, 1, 2, 1, 3, 3, 2, 1, 3, 0, 3, 1, 3, 3, 1, 1};
  for (auto _ : state) {
    // This code gets timed
    for(int i=0; i<state.range(0); i++){
        map.FindNearby(selectPool_[i][0], selectPool_[i][1], (double)selectPool_[i][2], selectPool_[i][3]);
    }   
  }
}


// Register the function as a benchmark
BENCHMARK(BM_Item10)->RangeMultiplier(2)->Range(1, 1<<8);

// Run the benchmark
BENCHMARK_MAIN();