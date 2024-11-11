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