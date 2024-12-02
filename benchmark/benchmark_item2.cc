#include "benchmark/benchmark.h"

#include <iostream>
#include <string>
#include "src/lib/trojanmap.h"
#include <random>


// // the name of location are all correct
// static void BM_Item2(benchmark::State& state) {
//   // Perform setup here
//   TrojanMap trojanmap;
//   std::vector<std::string> namePool_ = {"Crosswalk","Jefferson Park","Saint James Park","Foshay Learning Center","Holy Name School","National Schools","Normandie Elementary School",
//                                         "Saint Agnes Elementary School","Saint Cecilia School","Saint Patrick School","Santa Barbara Avenue School","Trinity Elementary School","Twenty-Eight Street Elementary School","Twenty-Fourth Street Elementary School",
//                                         "Vermont Elementary School","Wadsworth Elementary School","Washington Boulevard School","West Vernon Elementary School","Jefferson Senior High School","KGFJ-AM (Los Angeles)","Dockweller Station Los Angeles Post Office","Saint Marks Lutheran Church", "Saint Patricks Catholic Church"};
//   std::vector<int> random_number = {12, 5, 0, 15, 20, 14, 3, 10, 8, 5, 2, 1, 11, 6, 19, 20, 7, 10, 3, 2, 12, 15, 1, 4, 17, 9, 11, 0, 21, 8, 20, 4, 13, 2, 5, 6, 18, 7, 16, 10, 4, 15, 13, 14, 3, 12, 1, 9, 21, 0, 8, 11, 13, 16, 6, 7, 17, 18, 2, 10, 4, 15, 11, 20, 19, 3, 9, 21, 12, 0, 1, 8, 19, 16, 6, 14, 5, 2, 20, 17, 7, 12, 18, 9, 11, 4, 14, 13, 10, 5, 3, 21, 8, 1, 15, 19, 6, 14, 20, 13, 11, 7, 3, 10, 16, 18, 2, 0, 5, 15, 21, 12, 9, 8, 20, 6, 13, 14, 18, 7, 17, 10, 4, 19, 0, 21, 2, 1, 15, 11, 3, 12, 8, 19, 16, 9, 14, 4, 5, 18, 6, 10, 17, 7, 13, 20, 3, 2, 21, 0, 15, 9, 12, 8, 19, 18, 1, 6, 14, 11, 5, 17, 2, 4, 10, 7, 20, 13, 8, 15, 3, 12, 6, 19, 9, 11, 21, 16, 14, 7, 0, 5, 17, 1, 10, 2, 8, 4, 18, 13, 15, 19, 3, 20, 14, 6, 9, 17, 0, 12, 7, 10, 11, 21, 2, 18, 16, 13, 19, 3, 8, 6, 1, 15, 4, 12, 14, 10, 5, 17, 7, 13, 21, 20, 11, 18, 9, 2, 19, 8, 0, 15, 14, 4, 10, 6, 13, 7, 3, 1, 5, 17, 12, 11, 8, 19, 14, 18, 16, 9, 2, 10, 6, 21, 7, 0, 20, 13, 8, 15, 3, 12, 17, 9, 1, 10, 11, 21, 18, 2, 16, 4, 14, 5, 20, 7, 0, 13, 15, 9, 8, 11, 19, 14, 3, 1, 2, 6};
//   for(auto _: state ){
//     for(int i=0; i<state.range(0); i++){
//         trojanmap.GetPosition(namePool_[random_number[i]]);
//     }
//   }
// }


// the name of location are all correct
static void BM_Item2(benchmark::State& state) {
  // Perform setup here
  TrojanMap trojanmap;
  std::vector<std::string> namePool_ = {"Crosswalk","Jefferson Park","Saint James Park","Foshay Learning Center","Holy Name School","National Schools","Normandie Elementary School",
                                        "Saint Agnes Elementary School","Saint Cecilia School","Saint Patrick School","Santa Barbara Avenue School","Trinity Elementary School","Twenty-Eight Street Elementary School","Twenty-Fourth Street Elementary School",
                                        "Vermont Elementary School","Wadsworth Elementary School","Washington Boulevard School","West Vernon Elementary School","Jefferson Senior High School","KGFJ-AM (Los Angeles)","Dockweller Station Los Angeles Post Office","Saint Marks Lutheran Church", "Saint Patricks Catholic Church"};
  std::vector<std::string> random_letters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "J", "L", "M", "N", "O", "P", "R", "S", "T", "U", "V", "W"};
  std::vector<int> random_number = {12, 5, 0, 15, 20, 14, 3, 10, 8, 5, 2, 1, 11, 6, 19, 20, 7, 10, 3, 2, 12, 15, 1, 4, 17, 9, 11, 0, 21, 8, 20, 4, 13, 2, 5, 6, 18, 7, 16, 10, 4, 15, 13, 14, 3, 12, 1, 9, 21, 0, 8, 11, 13, 16, 6, 7, 17, 18, 2, 10, 4, 15, 11, 20, 19, 3, 9, 21, 12, 0, 1, 8, 19, 16, 6, 14, 5, 2, 20, 17, 7, 12, 18, 9, 11, 4, 14, 13, 10, 5, 3, 21, 8, 1, 15, 19, 6, 14, 20, 13, 11, 7, 3, 10, 16, 18, 2, 0, 5, 15, 21, 12, 9, 8, 20, 6, 13, 14, 18, 7, 17, 10, 4, 19, 0, 21, 2, 1, 15, 11, 3, 12, 8, 19, 16, 9, 14, 4, 5, 18, 6, 10, 17, 7, 13, 20, 3, 2, 21, 0, 15, 9, 12, 8, 19, 18, 1, 6, 14, 11, 5, 17, 2, 4, 10, 7, 20, 13, 8, 15, 3, 12, 6, 19, 9, 11, 21, 16, 14, 7, 0, 5, 17, 1, 10, 2, 8, 4, 18, 13, 15, 19, 3, 20, 14, 6, 9, 17, 0, 12, 7, 10, 11, 21, 2, 18, 16, 13, 19, 3, 8, 6, 1, 15, 4, 12, 14, 10, 5, 17, 7, 13, 21, 20, 11, 18, 9, 2, 19, 8, 0, 15, 14, 4, 10, 6, 13, 7, 3, 1, 5, 17, 12, 11, 8, 19, 14, 18, 16, 9, 2, 10, 6, 21, 7, 0, 20, 13, 8, 15, 3, 12, 17, 9, 1, 10, 11, 21, 18, 2, 16, 4, 14, 5, 20, 7, 0, 13, 15, 9, 8, 11, 19, 14, 3, 1, 2, 6};
  for(auto _: state ){
    // if (state.range(0) > MAX_ALLOWED_SIZE) {
    //   throw std::runtime_error("Input size too large");
    // }
    // std::cout << "--- the range is " << state.range(0) << std::endl;
    for(int i=0; i<state.range(0); i++){
      
        // std::string input = namePool_[random_number[i]] + random_letters[i];
        std::string input = trojanmap.FindClosestName(namePool_[random_number[i]] + random_letters[i]);
        // std::cout << "The closest location name is " << input << std::endl;
        // trojanmap.GetPosition(input);
    }
  }

}


// Register the function as a benchmark
BENCHMARK(BM_Item2)->RangeMultiplier(2)->Range(1, 1<<8);

// Run the benchmark
BENCHMARK_MAIN();