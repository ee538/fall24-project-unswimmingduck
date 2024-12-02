#include "benchmark/benchmark.h"

#include <iostream>
#include <string>
#include "src/lib/trojanmap.h"
#include <random>



static void BM_Item9(benchmark::State& state) {
  // Perform setup here
  TrojanMap trojanmap;
  // input letter
//   std::vector<std::string> selectPool_ = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "J", "L", "M", "N", "O", "P", "R", "S", "T", "U", "V", "W"};
//   std::vector<int> random_number = {12, 5, 0, 15, 20, 14, 3, 10, 8, 5, 2, 1, 11, 6, 19, 20, 7, 10, 3, 2, 12, 15, 1, 4, 17, 9, 11, 0, 21, 8, 20, 4, 13, 2, 5, 6, 18, 7, 16, 10, 4, 15, 13, 14, 3, 12, 1, 9, 21, 0, 8, 11, 13, 16, 6, 7, 17, 18, 2, 10, 4, 15, 11, 20, 19, 3, 9, 21, 12, 0, 1, 8, 19, 16, 6, 14, 5, 2, 20, 17, 7, 12, 18, 9, 11, 4, 14, 13, 10, 5, 3, 21, 8, 1, 15, 19, 6, 14, 20, 13, 11, 7, 3, 10, 16, 18, 2, 0, 5, 15, 21, 12, 9, 8, 20, 6, 13, 14, 18, 7, 17, 10, 4, 19, 0, 21, 2, 1, 15, 11, 3, 12, 8, 19, 16, 9, 14, 4, 5, 18, 6, 10, 17, 7, 13, 20, 3, 2, 21, 0, 15, 9, 12, 8, 19, 18, 1, 6, 14, 11, 5, 17, 2, 4, 10, 7, 20, 13, 8, 15, 3, 12, 6, 19, 9, 11, 21, 16, 14, 7, 0, 5, 17, 1, 10, 2, 8, 4, 18, 13, 15, 19, 3, 20, 14, 6, 9, 17, 0, 12, 7, 10, 11, 21, 2, 18, 16, 13, 19, 3, 8, 6, 1, 15, 4, 12, 14, 10, 5, 17, 7, 13, 21, 20, 11, 18, 9, 2, 19, 8, 0, 15, 14, 4, 10, 6, 13, 7, 3, 1, 5, 17, 12, 11, 8, 19, 14, 18, 16, 9, 2, 10, 6, 21, 7, 0, 20, 13, 8, 15, 3, 12, 17, 9, 1, 10, 11, 21, 18, 2, 16, 4, 14, 5, 20, 7, 0, 13, 15, 9, 8, 11, 19, 14, 3, 1, 2, 6};
  std::vector<std::vector<std::string>> selectPool_;
  srand(time(NULL));
  std::vector<std::string> location_ids;
  for(auto& pair: trojanmap.data){
    location_ids.push_back(pair.first);
  }

  for(int i=0; i<=8; i++){
    std::vector<std::string> sub_vector;
    for(int j=0; j<std::pow(2, i); j++){
        sub_vector.push_back(location_ids[rand()%location_ids.size()]);
    }
    selectPool_.push_back()
  }

  for (auto _ : state) {
    // This code gets timed
    for(int i=0; i<state.range(0); i++){
        trojanmap.Autocomplete(selectPool_[random_number[i]]);
    }
  }
}


// Register the function as a benchmark
BENCHMARK(BM_Item9)->RangeMultiplier(2)->Range(1, 1<<8);

// Run the benchmark
BENCHMARK_MAIN();