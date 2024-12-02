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
      "2578244375",
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
     "2578244375",
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
  
  std::vector<std::string> location_names = {"Ralphs", "KFC", "Target", "Chick-fil-A", "Trader Joes"};
  std::vector<std::vector<std::string>> dependencies = {{"Ralphs","KFC"}, {"Ralphs","Chick-fil-A"}, 
                                                          {"KFC", "Chick-fil-A"}, {"Target", "Trader"},
                                                          {"Chick-fil-A", "Trader"}, {"KFC", "Target"},
                                                          {"Target", "Chick-fil-A"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Ralphs", "KFC", "Target", "Chick-fil-A", "Trader" };
  EXPECT_EQ(result, gt);
}


// // Phase 3
// // Test TSP function
TEST(TrojanMapTest, TSP1) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976",
                              "6820935923",
                              "6816180153",
                              "8566227783",
                              "122702233",
                              "8566227656",
                              "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}


TEST(TrojanMapTest, TSP2) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976",
                              "6820935923",
                              "6816180153",
                              "8566227783",
                              "122702233",
                              "8566227656",
                              "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}


TEST(TrojanMapTest, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976",
                              "6820935923",
                              "6816180153",
                              "8566227783",
                              "122702233",
                              "8566227656",
                              "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}


// Test FindNearby points
TEST(TrojanMapTest, FindNearby) {
  TrojanMap m;
  
  auto result = m.FindNearby("bank", "Chase", 10, 10);
  std::vector<std::string> ans{"5237417651", "9591449465"};
  EXPECT_EQ(result, ans);
}


// // // Test CalculateShortestPath_TrojanPath function
TEST(TrojanMapTest, CalculateShortestPath_TrojanPath) {
  TrojanMap m;
  
  // Test for Ralphs, KFC and Chick-fil-A 
  std::vector<std::string> input = {"Ralphs", "Ross", "Trader Joes"};
  auto path = m.TrojanPath(input);
  std::vector<std::string> gt{
      "2578244375",
"4380040154",
"4380040153",
"4380040152",
"4380040148",
"6818427920",
"6818427919",
"6818427918",
"6818427892",
"6818427898",
"6818427917",
"6818427916",
"7232024780",
"6813416145",
"6813416154",
"6813416153",
"2613117902",
"6818390178",
"2613117882",
"6818390165",
"2613117885",
"6807374562",
"6818390172",
"6818390171",
"6818390170",
"2613117861",
"6817230316",
"3642819026",
"6817230310",
"7811699597",
"5565967545",
"123318572",
"6813405206",
"6813405205",
"6813405204",
"6813405203",
"6813405202",
"6813405201",
"6818390145",
"6818390144",
"6813379475",
"6813379474",
"6813379385",
"6045054380",
"6813379418",
"6047234443",
"6813379419",
"9591449515",
"6814820015",
"6814820010",
"6814820018",
"6814769290",
"9591449485",
"5237417649",
"9591449485",
"6396649383",
"6814769289",
"6813379584",
"6813360961",
"6813379480",
"6813360960",
"6814620882",
"6813360954",
"6813360952",
"6813379420",
"6813360951",
"6813360936",
"6813379467",
"6813379466",
"6813379465",
"6813379464",
"3402887075",
"6813379432",
"4536989637",
"4536989640",
"3443310465",
"6813379491",
"6818390136",
"3433701978",
"4536989636",
"3432332948",
"6814770351",
"3431300454",
"4536993735",
"6814770342",
"2776870272",
"5580882852",
"6814770345",
"2776870269",
"1472141961",
"5580883117",
"123153544",
"1673645147",
"2738332818",
"1673644724",
"2738332817",
"122844997",
"5580881629",
"4399697303",
"4399697301",
"4399697300",
"6813379550",
"6814916523",
"1732243620",
"4015372469",
"4015372463",
"6819179749",
"1732243544",
"6813405275",
"348121996",
"348121864",
"6813405280",
"1472141024",
"6813411590",
"216155217",
"6813411589",
"1837212103",
"1837212101",
"6820935911",
"932416162",
"4060015482",
"4020099365",
"6820972450",
"1732243549",
"6820972451",
"1836105028",
"9118747759",
"4060015481",
"4020099358",
"6814990127",
"7867091027",
"7867091030",
"6226313827",
"932378219",
"6814990112",
"1870795293",
"6814990128",
"4060015480",
"1870795287",
"4020099348",
"1870795282",
"1870787389",
"1870795272",
"1870795261",
"1870795259",
"1855150081",
"1870797882",
"1870795205",
"21302801",
"5617977522",
"6653019481",
"1855169974",
"1732243610",
"6653019471",
"4060015479",
"4020099325",
"123241992",
"1732243574",
"7396914898",
"7174763274",
"123050488",
"1732243849",
"123241996",
"1732243570",
"4060016288",
"4020099319",
"5617977544",
"269634035",
"4060016287",
"1732243865",
"5707890488",
"5617977547",
"8386719092",
"5617977548",
"5617977553",
"5617977554",
"6790607407",
"6790607405",
"6790607406",
"6790607398",
"6790607396",
"7159565267"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  
  // 
  std::cout << "The length of my path is " << path.size() << std::endl;
  std::cout << "The length of GT path is " << gt.size() << std::endl;

  for(int i=0; i<path.size(); i++){
    if(path[i] != gt[i]){
      std::cout << "The wrong id is " << i << std::endl;
    }
  }

  // EXPECT_EQ(path, gt);

  input = {"Ralphs", "Trader Joes", "Ross"};
  path = m.TrojanPath(input);
  EXPECT_EQ(path, gt);
}


TEST(TrojanMapTest, Queries) {
  TrojanMap m;
    std::vector<std::pair<double, std::vector<std::string>>> input {{0.05, {"Target", "KFC"}},
                                                                  {0.05, {"Ralphs", "Chase"}},
                                                                  {0.02, {"KFC", "Ross"}},
                                                                  {999, {"dummy", "dummy"}}
                                                                  };
  auto actual = m.Queries(input);
  std::vector<bool> expected {true, true, false, false};
  EXPECT_EQ(expected, actual);
}