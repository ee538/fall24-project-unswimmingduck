#include <iostream>
#include "src/lib/trojanmap.h"
#include "src/lib/mapui.h"
// #define NCURSES

int main() {
  MapUI x;
  #ifdef NCURSES
    x.PlotMap();
    x.DynamicPrintMenu();
  #else
    x.PlotMap();
    x.PrintMenu();
  #endif
  return 0;
}

// int main(){
//   TrojanMap trojanmap;

//   std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
//   auto result = trojanmap.TravelingTrojan_2opt(input);
//   std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
//   std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
//   std::cout << "GT path length: "  << trojanmap.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
// }

//   // ################# Test The shortestPath function
//   // auto path = trojanmap.CalculateShortestPath_Dijkstra("Ralphs", "Target");
//   // std::cout << "the size of the path is " << path.size() << std::endl; 
//   // std::vector<std::string> gt{2}
//   //     "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920","6818427919",
//   //     "6818427918","6818427892","6818427898","6818427917","6818427916","7232024780","6813416145",
//   //     "6813416154","6813416153","6813416152","6813416151","6813416155","6808069740","6816193785",
//   //     "6816193786","123152294","4015203136","4015203134","4015203133","21098539","6389467809",
//   //     "4015203132","3195897587","4015203129","4015203127","6352865690","6813379589","6813379483",
//   //     "3402887081","6814958394","3402887080","602606656","4872897515","4399697589","6814958391",
//   //     "123209598","6787673296","122728406","6807762271","4399697304","4399697302","5231967015",
//   //     "1862347583","3233702827","4540763379","6819179753","6820935900","6820935901","6813379556",
//   //     "6820935898","1781230450","1781230449","4015405542","4015405543","1837212104","1837212107",
//   //     "2753199985","6820935907","1837212100","4015372458","6813411588","1837212101","6814916516",
//   //     "6814916515","6820935910","4547476733"};
//   // for(int i=0; i<path.size(); i++){
//   //   std::cout << path[i] << std::endl;
//   // }


//   //// Test FindNearby() function
//   // auto result = trojanmap.FindNearby("supermarket", "Ralphs", 10, 10);
//   // std::vector<std::string> ans{"5237417649", "6045067406", "7158034317"};
//   // for(const auto& res: result){
//   //   std::cout << res << " ";
//   // }


//   // // Test the TrojanPath() function
// //   std::vector<std::string> input = {"KFC", "Ralphs", "Chick-fil-A"};
// //   auto path = trojanmap.TrojanPath(input);
// //   std::cout << "The size of the output path is " << path.size() << std::endl;
// //   std::vector<std::string> gt{
// //         "2578244375","4380040154","4380040158","4380040167","6805802087","8410938469","6813416131",
// //         "7645318201","6813416130","6813416129","123318563","452688940","6816193777","123408705",
// //         "6816193774","452688933","452688931","123230412","6816193770","6787470576","4015442011",
// //         "6816193692","6816193693","6816193694","3398621886","3398621887","6816193695","5690152756",
// //         "6804883324","3398621888","6813416123","6813416171","6807536647","6807320427","6807536642",
// //         "6813416166","7882624618","7200139036","122814440","6813416163","7477947679","7298150111",
// //         "6787803640","6807554573","2613117890","4835551096","4835551101","4835551097","4835551100",
// //         "3088547686","4835551100","4835551099","4835551098","6813565307","6813565306","6813565305",
// //         "6813565295","6813565296","3402814832","4835551107","6813379403","6813379533","3402814831",
// //         "6813379501","3402810298","6813565327","3398574883","6813379494","6813379495","6813379544",
// //         "6813379545","6813379536","6813379546","6813379547","6814916522","6814916523","1732243620",
// //         "4015372469","4015372463","6819179749","1732243544","6813405275","348121996","348121864",
// //         "6813405280","1472141024","6813411590","216155217","6813411589","1837212103","1837212101",
// //         "6814916516","6814916515","6820935910","4547476733"};
// //   std::cout << "The size of the gt is " << gt.size() << std::endl;

//     // // #################################
//     // // Test the Query function
//     // std::vector<std::pair<double, std::vector<std::string>>> input {{0.05, {"Target", "Ralphs"}},
//     //                                                             {0.01, {"Ralphs", "Target"}},
//     //                                                             {0.02, {"KFC", "Target"}},
//     //                                                             {999, {"dummy", "dummy"}}
//     //                                                             };
//     // auto actual = trojanmap.Queries(input);
//     // std::cout << " the result is ";
//     // for(const auto& result: actual){
//     //     std::cout << result << " ";
//     // }
//     // std::cout << std::endl;

// //     // // ## Test the GA algorithm
//     std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
//     auto result = trojanmap.TravelingTrojan_Genetic_Algorithm(input);
//     std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
//     // std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
//     // std::cout << "GT path length: "  << trojanmap.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
//     // // result.second = result.second.push_back(result.second[0]);

//     // std::cout << "My path is ";
//     // for(const auto& location: result.second.back()){
//     //   std::cout << location << " ";
//     // }
//     // std::cout<< std::endl;

//     // std::cout << "Caculation of My path length: "  << (trojanmap.CalculatePathLength(result.second.back())+trojanmap.CalculateDistance(result.second.back()[0], result.second.back()[7])) << "miles" << std::endl;


//     // std::vector<std::string> input = {"6819019976","6820935923","122702233","8566227783","8566227656","6816180153"};
//     // auto result = trojanmap.TravelingTrojan_2opt(input);
    
//     // std::cout << "The result distance is " << result.first << std::endl;
//     // std::cout << "The result path is: ";
//     // for(const auto& location: result.second.back()){
//     //   std::cout << location << " ";
//     // }
//     // std::cout << std::endl;

//     // // deteect the reverse path
//     // std::reverse(input.begin(), input.end());
//     // auto result1 = trojanmap.TravelingTrojan_2opt(input);
    
//     // std::cout << "The result distance is " << result1.first << std::endl;
//     // std::cout << "The result path is: ";
//     // for(const auto& location: result1.second.back()){
//     //   std::cout << location << " ";
//     // }
//     // std::cout << std::endl;


//     // auto result = trojanmap.CalculateShortestPath_Dijkstra("Ralphs", "Target");
//     // for(const auto& location: result){
//     //   std::cout << location << std::endl;
//     // }

//   // std::vector<std::string> input = {"Ralphs", "Ross", "Trader Joes"};
//   // auto result = trojanmap.TrojanPath(input);
//   // for(const auto& location: result){
//   //   std::cout << location << std::endl;
//   // }

//     std::vector<std::pair<double, std::vector<std::string>>> input {{0.05, {"Target", "KFC"}},
//                                                                   {0.05, {"Ralphs", "Chase"}},
//                                                                   {0.02, {"KFC", "Ross"}},
//                                                                   {999, {"dummy", "dummy"}}
//                                                                   };
//     auto actual = trojanmap.Queries(input);
//     for(const auto& res: actual){
//       std::cout << res << std::endl;
//     }
  
// }




// // #######################################
// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <algorithm>
// #include <limits>

// using namespace std;

// // Structure to represent a point (city)
// struct Point {
//     double x, y;
// };

// // Function to calculate the distance between two points
// double distance(const Point& a, const Point& b) {
//     return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
// }

// // Function to calculate the total distance of a tour
// double calculateTourDistance(const vector<Point>& points, const vector<int>& tour) {
//     double totalDistance = 0.0;
//     for (size_t i = 0; i < tour.size(); i++) {
//         int current = tour[i];
//         int next = tour[(i + 1) % tour.size()];
//         totalDistance += distance(points[current], points[next]);
//     }
//     return totalDistance;
// }

// // 2-OPT algorithm
// void twoOpt(vector<Point>& points, vector<int>& tour) {
//     bool improved = true;
//     int n = tour.size();

//     int iteration = 0;

//     while (improved) {
//         improved = false;
//         double bestDistance = calculateTourDistance(points, tour);

//         for (int i = 1; i < n - 1; i++) {
//             for (int j = i + 1; j < n; j++) {
//                 iteration++;
//                 std::cout << " --------------" <<  iteration << "-th " << "-------- " << std::endl;
//                 // Create a new tour by reversing a segment
//                 vector<int> newTour = tour;
//                 std::cout << "The path before swap is ";
//                 for(auto& path: newTour){
//                   std::cout << path << " ";
//                 }
//                 std::cout << std::endl;

//                 reverse(newTour.begin() + i, newTour.begin() + j + 1);

//                 // ######
//                 std::cout << "The path after swap is: "; 
//                 for(auto& path: newTour){
//                   std::cout << path << " ";
//                 }
//                 std::cout << std::endl;
//                 // ######


//                 double newDistance = calculateTourDistance(points, newTour);

//                 std::cout << "The new distance is " << newDistance << std::endl;
//                 std::cout << " ----------------------------- " <<std::endl;

//                 // If the new tour is better, accept the change
//                 if (newDistance < bestDistance) {
//                     tour = newTour;
//                     bestDistance = newDistance;
//                     improved = true;
//                 }
//             }
//         }
//     }
// }

// int main() {
//     // Example points (cities)
//     vector<Point> points = {
//         {0, 0},
//         {2, 3},
//         {5, 4},
//         {7, 1},
//         {3, 7},
//         {6, 8},
//     };

//     int n = points.size();

//     // Initial tour (0, 1, 2, ..., n-1)
//     vector<int> tour(n);
//     for (int i = 0; i < n; i++) {
//         tour[i] = i;
//     }

//     // Calculate initial distance
//     double initialDistance = calculateTourDistance(points, tour);
//     cout << "Initial tour distance: " << initialDistance << endl;

//     // Run 2-OPT algorithm
//     twoOpt(points, tour);

//     // Calculate optimized distance
//     double optimizedDistance = calculateTourDistance(points, tour);
//     cout << "Optimized tour distance: " << optimizedDistance << endl;

//     // Print the optimized tour
//     cout << "Optimized tour: ";
//     for (int city : tour) {
//         cout << city << " ";
//     }
//     cout << endl;

//     return 0;
// }

