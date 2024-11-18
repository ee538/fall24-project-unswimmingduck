#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

#include <unordered_set>
#include <cmath>
const double kTolerance = 1e-5;

TEST(AutoComplete, Test1) {
    
    std::unordered_set<std::string> set = {
    "Vermont Elementary School",
    "Vermont Square United Methodist Church",
    "Vernon Branch Los Angeles Public Library",
    "Vernon",
    "Vernon 1",
    "Venice & Broadway",
    "Venice & Olive",
    "Vernon Adult Day Program",
    "Vermont & 24th",
    "Vermont & 24th 1",
    "Vermont & Adams",
    "Vermont & Adams 1",
    "Vermont & 29th",
    "Vermont & 29th 1",
    "Vermont & Jefferson",
    "Vermont & 35th",
    "Vermont & 35th 1",
    "Vermont & Jefferson 1",
    "Vermont & Jefferson 2",
    "Vermont & 36th",
    "Vermont & 36th 1",
    "Vermont & Exposition",
    "Vermont & Exposition 1",
    "Vermont & Leighton (Metro 204 Northbound)(#05637)",
    "Vermont & Leighton (Metro 204 Southbound)(#14018)",
    "Vermont & 39th (Metro 204 Southbound)(#14041)",
    "Vermont & 39th (Metro 204 Northbound) (#05658)",
    "Vermont & Martin Luther King Jr (Metro 204 754 Southbound)(#15431)",
    "Vermont & Martin Luther King Jr (Metro 204 754 Northbound)(#11247)",
    "Vermont & 42nd (Metro 204 Southbound)(#14043)",
    "Vermont & 42nd (Metro 204 Northbound)(#05660)",
    "Vermont & Vernon (Metro 204 Southbound)(#14087)",
    "Vermont & Vernon (Metro 204 Northbound)(#05700)",
    "Vermont & 46th (Metro 204 Northbound)(#05661)",
    "Vermont & 46th (Metro 204 Southbound)(#14044)",
    "Vermont Square",
    "Vermont & Washington",
    "Vermont & Jefferson 3",
    "Vermont Auto Center - Complete Auto Repair",
    "Venice & Oak",
    "Venice & Oak 1",
    "Venice & Figueroa",
    "Venice & Figueroa 1",
    "Venice & Flower",
    "Venice & Hope",
    "Venice & Grand",
    "Venice & Grand 1",
    "Venice & Hill"
};
    
    TrojanMap map;
    
    std::vector<std::string> result = map.Autocomplete("Ve");

    for(std::string search: result){
        EXPECT_EQ(set.find(search) != set.end(), true);
        set.erase(search);
    }
    EXPECT_EQ(set.size(), 0);
}


TEST(AutoComplete, Test2) {
    
    std::unordered_set<std::string> set = {
      "Pilgrim Congregational Church",
      "Pico",
      "Pico 1",
      "Pico & Flower",
      "Pico & Maple",
      "Pizza King",
      "Pico & Hill",
      "Pico & Hill 1",
      "Pico & Grand",
      "Pico & Grand 1"
};
    
    TrojanMap map;
    
    std::vector<std::string> result = map.Autocomplete("Pi");

    for(std::string search: result){
        EXPECT_EQ(set.find(search) != set.end(), true);
        set.erase(search);
    }
    EXPECT_EQ(set.size(), 0);
}


TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  
  
  auto position = m.GetPosition("Venice & Grand");
  std::pair<double, double> gt1(34.035743, -118.266548); 
    EXPECT_NEAR(position.first, gt1.first, kTolerance);
    EXPECT_NEAR(position.second, gt1.second, kTolerance);
  
  position = m.GetPosition("Pico & Grand 1");
  std::pair<double, double> gt2(34.0388531, -118.2641173); 
  EXPECT_NEAR(position.first, gt2.first, kTolerance);
  EXPECT_NEAR(position.second, gt2.second, kTolerance);
  
  // Test Unknown
  position = m.GetPosition("XXX");
  std::pair<double, double> gt4(-1, -1);
  EXPECT_EQ(position, gt4);
}



// Phase 2: Item3
TEST(TrojanMapTest, GetAllCategories) {
  TrojanMap m;
  
  auto output = m.GetAllCategories();
  std::set<std::string> expected = {
    "artwork", "attraction", "bakery", "bank", "bar", "beauty", "beverages", "bicycle", "bicycle_rental",
    "bus_station", "cafe", "car", "car_repair", "car_wash", "charging_station", "childcare", "clinic",
    "clothes", "confectionery", "convenience", "copyshop", "dentist", "department_store", "driving_school",
    "fabric", "fast_food", "food_court", "fountain", "fuel", "gallery", "hairdresser", "hospital", "hotel",
    "library", "marketplace", "mobile_phone", "museum", "music", "optician", "parcel_locker", "parking",
    "parking_entrance", "pharmacy", "place_of_worship", "police", "post_box", "post_office", "restaurant",
    "school", "shoe_repair", "shoes", "skate", "social_facility", "supermarket", "theatre", "tobacco",
    "yoga", "yes"
  };
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, expected);
}


// //Phase 2: Item4
TEST(TrojanMapTest, GetAllLocationsFromCategory1) {
  TrojanMap m;
  
  auto output = m.GetAllLocationsFromCategory("school");
  std::set<std::string> expected = { "358784231",
 "358786032",
 "358789632",
 "358789785",
 "358791507",
 "358791610",
 "358791878",
 "358792209",
 "358793609",
 "358793671",
 "358793678",
 "358794109",
 "358794278",
 "358794351",
 "358794547",
 "358801509",
 "358850043",
 "358851980",
 "358852034",
 "418030171",
 "4630579201"};
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, expected);
}


//Phase 2: Item5
TEST(TrojanMapTest, GetLocationRegex1) {
  TrojanMap m;
  std::set<std::string> expected_set;
  auto actual = m.GetLocationRegex(std::regex("dummy"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(actual_set, expected_set);
}

TEST(TrojanMapTest, GetLocationRegex2) {
  TrojanMap m;
  std::set<std::string> expected_set = { "1376467705",
                                        "1376467712",
                                        "4291117323",
                                        "4291117324",
                                        "6279600809",
                                        "6279600810",
                                        "9601938170",
                                        "9601938171"};
  auto actual = m.GetLocationRegex(std::regex("^Pico.*"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(expected_set, actual_set);
}


// Phase 2: Item-6
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Target");
  std::vector<std::string> gt{
      "578244375",
    "4380040154",
    "4380040158",
    "4380040167",
    "6805802087",
    "8410938469",
    "6813416131",
    "7645318201",
    "6813416130",
    "6813416129",
    "123318563",
    "452688940",
    "6816193777",
    "123408705",
    "6816193774",
    "452688933",
    "452688931",
    "123230412",
    "6816193770",
    "6787470576",
    "4015442011",
    "6816193692",
    "6816193693",
    "6816193694",
    "4015377691",
    "544693739",
    "6816193696",
    "6804883323",
    "6807937309",
    "6807937306",
    "6816193698",
    "4015377690",
    "4015377689",
    "122814447",
    "6813416159",
    "6813405266",
    "4015372488",
    "4015372487",
    "6813405229",
    "122719216",
    "6813405232",
    "4015372486",
    "7071032399",
    "4015372485",
    "6813379479",
    "6813379584",
    "6814769289",
    "5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Dijkstra("Target", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "Target");
  std::vector<std::string> gt{
      "578244375",
    "4380040154",
    "4380040158",
    "4380040167",
    "6805802087",
    "8410938469",
    "6813416131",
    "7645318201",
    "6813416130",
    "6813416129",
    "123318563",
    "452688940",
    "6816193777",
    "123408705",
    "6816193774",
    "452688933",
    "452688931",
    "123230412",
    "6816193770",
    "6787470576",
    "4015442011",
    "6816193692",
    "6816193693",
    "6816193694",
    "4015377691",
    "544693739",
    "6816193696",
    "6804883323",
    "6807937309",
    "6807937306",
    "6816193698",
    "4015377690",
    "4015377689",
    "122814447",
    "6813416159",
    "6813405266",
    "4015372488",
    "4015372487",
    "6813405229",
    "122719216",
    "6813405232",
    "4015372486",
    "7071032399",
    "4015372485",
    "6813379479",
    "6813379584",
    "6814769289",
    "5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path = m.CalculateShortestPath_Bellman_Ford("Target", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}


// // Phase 2: Item-7
TEST(TrojanMapTest, CycleDetection) {
  TrojanMap m;
  
  std::vector<double> square1 = {-118.299, -118.264, 34.032, 34.011};
  auto sub1 = m.GetSubgraph(square1);
  bool result1 = m.CycleDetection(sub1, square1);
  EXPECT_EQ(result1, true);
}


// Phase2: Item8
TEST(TrojanMapTest, TopologicalSort) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Ralphs", "KFC", "Target", "Chick-fil-A", "Trader"};
  std::vector<std::vector<std::string>> dependencies = {{"Ralphs","KFC"}, {"Ralphs","Chick-fil-A"}, 
                                                          {"KFC", "Chick-fil-A"}, {"Target", "Trader"},
                                                          {"Chick-fil-A", "Trader"}, {"KFC", "Target"},
                                                          {"Target", "Chick-fil-A"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Ralphs", "KFC", "Target", "Chick-fil-A", "Trader" };
  EXPECT_EQ(result, gt);
}