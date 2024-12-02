#include "benchmark/benchmark.h"

#include <iostream>
#include <string>
#include "src/lib/trojanmap.h"
#include <random>



static void BM_Item7(benchmark::State& state) {
  // Perform setup here
  TrojanMap map;
  // input letter
  std::vector<std::vector<double>> selectPool_ = {{-118.310, -118.260, 34.030, 34.010}, {-118.310, -118.265, 34.035, 34.010}, {-118.315, -118.270, 34.035, 34.005}, {-118.317, -118.255, 34.030, 34.005}};
  std::vector<int> random_number = {2, 3, 2, 0, 3, 3, 0, 0, 3, 1, 0, 0, 0, 2, 2, 3, 0, 3, 1, 3, 1, 0, 3, 2, 0, 2, 1, 0, 2, 3, 2, 0, 2, 3, 3, 0, 3, 3, 1, 3, 3, 0, 3, 3, 0, 0, 3, 0, 3, 3, 3, 2, 3, 2, 2, 2, 2, 2, 3, 3, 1, 1, 0, 1, 1, 1, 1, 3, 0, 2, 0, 1, 0, 1, 2, 2, 3, 3, 2, 2, 3, 0, 2, 1, 1, 2, 1, 2, 1, 0, 2, 2, 0, 1, 1, 1, 1, 0, 1, 1, 3, 2, 2, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 2, 3, 3, 0, 1, 1, 0, 3, 1, 2, 3, 0, 3, 2, 1, 2, 2, 2, 3, 0, 3, 2, 0, 3, 0, 3, 1, 1, 1, 2, 0, 0, 0, 0, 1, 2, 2, 1, 2, 3, 2, 0, 0, 3, 0, 0, 3, 3, 2, 2, 3, 1, 3, 3, 0, 1, 3, 1, 3, 2, 0, 2, 3, 0, 2, 2, 3, 1, 2, 0, 3, 1, 2, 2, 0, 1, 3, 0, 0, 1, 1, 3, 0, 2, 3, 2, 0, 2, 0, 0, 1, 0, 1, 2, 2, 0, 1, 1, 3, 1, 3, 2, 1, 1, 3, 3, 1, 2, 2, 3, 3, 1, 3, 3, 2, 1, 3, 0, 2, 3, 2, 1, 0, 2, 0, 1, 1, 1, 1, 2, 1, 3, 3, 2, 1, 3, 0, 3, 1, 3, 3, 1, 1};
  for (auto _ : state) {
    // This code gets timed
    for(int i=0; i<state.range(0); i++){
        auto subgraph = map.GetSubgraph(selectPool_[random_number[i]]);
        map.CycleDetection(subgraph, selectPool_[random_number[i]]);
    }   
  }
}


// Register the function as a benchmark
BENCHMARK(BM_Item7)->RangeMultiplier(2)->Range(1, 1<<8);

// Run the benchmark
BENCHMARK_MAIN();