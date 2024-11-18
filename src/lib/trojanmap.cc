#include "trojanmap.h"

//-----------------------------------------------------
// TODO: Students should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return
 * -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string &id) { 
  return 0;
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist,
 * return -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string &id) {
  return 0;
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return
 * "NULL".
 *
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string &id) {
  return "";
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return
 * an empty vector.
 *
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string &id) {
  return {};
}

/**
 * GetID: Given a location name, return the id.
 * If the node does not exist, return an empty string.
 * The location name must be unique, which means there is only one node with the name.
 *
 * @param  {std::string} name          : location name
 * @return {std::string}               : id
 */
std::string TrojanMap::GetID(const std::string &name) {
  std::string res = "";
  return res;
}

/**
 * GetPosition: Given a location name, return the position. If id does not
 * exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);
  if(name_id_map.find(name) != name_id_map.end()){
    std::string id = name_id_map[name];
    results.first = data[id].lat;
    results.second = data[id].lon;
  }
  return results;
}

/**
 * CalculateEditDistance: Calculate edit distance between two location names
 * @param  {std::string} a          : first string
 * @param  {std::string} b          : second string
 * @return {int}                    : edit distance between two strings
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b) {    
  // common cases
  if(a.size() == 0){
    return b.size();
  }
  else if(b.size() == 0){
    return a.size();
  }

  int len_a = a.size();
  int len_b = b.size();

  // construct a matrix that can be used in DP algorithm
  std::vector<std::vector<int>> result(len_b+1, std::vector<int>(len_a+1));
  // result matrix:    0 a0 a1 a2 a3 .. an
  //                 b0
  //                 b1
  //                 .
  //                 .
  //                 bm  

  // initialization the result matrix
  for(int j=0; j<= len_a; j++){
    result[0][j] = j;
  }
  for(int i=0; i<=len_b; i++){
    result[i][0] = i;
  }

  // using dynamic programming to solve the editdistance between a and b
  for(int i=1; i<=len_b; i++){
    for(int j=1; j<=len_a; j++){
      if(a[j] == b[i]){
        result[i][j] = result[i-1][j-1];
      }
      else{
        result[i][j] = std::min(result[i-1][j]+1, std::min(result[i][j-1]+1, result[i-1][j-1]+1));
      }
    }
  }

  return result[len_b][len_a];
}

/**
 * FindClosestName: Given a location name, return the name with the smallest edit
 * distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : the closest name
 */
std::string TrojanMap::FindClosestName(std::string name) {
  std::string tmp = ""; // Start with a dummy word
  int distance = std::numeric_limits<int>::max();

  // iterate all the name and find the smallest edit-distance one
  for(const auto& pair: name_id_map){
    int cur_distance = CalculateEditDistance(name, pair.first);
    if(cur_distance<distance){
      std::cout << " the pair.first is " << pair.first << ", the pair.second is: " << pair.second << std::endl;
      tmp = pair.first;
      distance = cur_distance;
    }
  }

  return tmp;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name) {
  std::vector<std::string> results;

  std::cout<< "the autocomplete is called" << std::endl;

  // get the all target id
  std::vector<std::string> targetId = tree->find(name);

  // using id to get the correct name
  for(std::string id: targetId){
      results.push_back(data[id].name); 
  }

  return results;
}

/**
 * GetAllCategories: Return all the possible unique location categories, i.e.
 * there should be no duplicates in the output.
 *
 * @return {std::vector<std::string>}  : all unique location categories
 */
std::vector<std::string> TrojanMap::GetAllCategories() {
  // 11-13
    // Test OK, but student_test is lack !!!!
    std::vector<std::string> res;

    if(categorySet_.size() == 0){
      construct_categorySet();
    }

    for(std::string attribute: categorySet_){
      res.push_back(attribute);
    }

  return res;
}

/**
 * GetAllLocationsFromCategory: Return all the locations of the input category (i.e.
 * 'attributes' in data.csv). If there is no location of that category, return
 * (-1, -1). The function should be case-insensitive.
 *
 * @param  {std::string} category         : category name (attribute)
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetAllLocationsFromCategory(
    std::string category) {
  std::vector<std::string> res;
  construct_categoryLocation_map();
  if(categoryLocations_.find(category) != categoryLocations_.end()){
    res = categoryLocations_[category];
  }
  return res;
}

/**
 * GetLocationRegex: Given the regular expression of a location's name, your
 * program should first check whether the regular expression is valid, and if so
 * it returns all locations that match that regular expression.
 *
 * @param  {std::regex} location name      : the regular expression of location
 * names
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetLocationRegex(std::regex location) {
  std::vector<std::string> result;
  for(const auto& pair: data){
    if (std::regex_match(pair.second.name, location)) {
      result.push_back(pair.second.id);
    }
  }
  return result;
}

/**
 * CalculateDistance: Get the distance between 2 nodes.
 * We have provided the code for you. Please do not need to change this function.
 * You can use this function to calculate the distance between 2 nodes.
 * The distance is in mile.
 * The distance is calculated using the Haversine formula.
 * https://en.wikipedia.org/wiki/Haversine_formula
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id,
                                    const std::string &b_id) {
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2), 2.0) + cos(a.lat * M_PI / 180.0) *
                                           cos(b.lat * M_PI / 180.0) *
                                           pow(sin(dlon / 2), 2.0);
  double c = 2 * asin(std::min(1.0, sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations
 * inside the vector.
 * We have provided the code for you. Please do not need to change this function.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0; i < int(path.size()) - 1; i++) {
    sum += CalculateDistance(path[i], path[i + 1]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path
 * which is a list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
  std::vector<std::string> path;

  if(name_id_map.size() == 0){
    construct_name_id_map();
  }

  // get the both location ids
  std::string location1_id = name_id_map[location1_name];
  std::string location2_id = name_id_map[location2_name];

  // priority queue
  std::priority_queue<std::pair<double, std::string>, 
                      std::vector<std::pair<double, std::string>>, 
                      std::greater<>> pq;
  // Init priority queue
  pq.push({0.0, location1_id});

  // init the distance map
  std::unordered_map<std::string, double> distances;
  for (const auto &pair : data) {
    distances[pair.first] = std::numeric_limits<double>::max();
  }
  distances[location1_id] = 0.0;

  // root map to track back the shortest path
  std::unordered_map<std::string, std::string> root;

  while (!pq.empty()) {
    std::pair<double,std::string> cur_pair = pq.top(); 
    std::string cur_id = cur_pair.second;
    // std::cout << "The cur_id is: " << cur_id << std::endl;
    double prefix_distance = cur_pair.first;
    pq.pop();

    if(cur_id == location2_id){
      break;
    } 
    
    for(const auto& neighbor_id: data[cur_id].neighbors){
      double neighbor_distance = prefix_distance + CalculateDistance(neighbor_id, cur_id);
       if (neighbor_distance < distances[neighbor_id]) {
        distances[neighbor_id] = neighbor_distance;
        root[neighbor_id] = cur_id;
        pq.push({neighbor_distance, neighbor_id});
      }
    }
  }

  std::cout << " ---- the while loop stop ----- " << std::endl;

  // track back the shortest path
  for (std::string at = location2_id; at != location1_id; at = root[at]) {
    // std::cout << "The at id is: " << at << std::endl;
    path.push_back(at);
  }
  path.push_back(location1_id);
  // reverse the path
  std::reverse(path.begin(), path.end());

  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest
 * path which is a list of id. Hint: Do the early termination when there is no
 * change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name) {
  std::vector<std::string> path;

  // if(name_id_map.size() == 0){
  //   construct_name_id_map();
  // }

  // get the both location ids
  std::string location1_id = name_id_map[location1_name];
  std::string location2_id = name_id_map[location2_name];

  // init the distance map
  std::unordered_map<std::string, double> distances;
  for (const auto &pair : data) {
    distances[pair.first] = std::numeric_limits<double>::max();
  }
  distances[location1_id] = 0.0;

  // std::cout << "The location1_id distance is " << distances[location1_id] << std::endl;

  // root map to track back the shortest path
  std::unordered_map<std::string, std::string> root;

  // std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> vertices;
  // construct_vertice_edge(vertices, location1_id);

  // std::cout << "The size of the vertices is: " << vertices.size() << std::endl;

  for(int i=0; i<data.size(); i++){
    // std::cout << "The " << i <<"-th iteration" << std::endl;
    for(const auto& data_pair: data){
      double prefix_distance = distances[data_pair.first];
      for(const auto& neighbor_id: data_pair.second.neighbors){
        double neighbor_distance = CalculateDistance(neighbor_id, data_pair.first);
        if(neighbor_distance+prefix_distance < distances[neighbor_id]){
          distances[neighbor_id] = neighbor_distance+prefix_distance;
          root[neighbor_id] = data_pair.first;
        }
      }
    }
  }


  // for(int i=0; i<vertices.size()-1; i++){
  //   // std::cout << "The " << i << "-th" << " iteration " << std::endl;
  //   for(const auto& vertice: vertices){
  //     double prefix_distance = distances[vertice.first];
  //     if(vertice.first == location1_id){
  //       std::cout << "The prefix distance is " << prefix_distance << std::endl;
  //     }
  //     for(const auto& neighbor_pair: vertice.second){
  //       if(vertice.first == location1_id){
  //         std::cout << "The distance is " << prefix_distance+neighbor_pair.second <<  " the former distance is " << distances[neighbor_pair.first] << std::endl;
  //       }
        
  //       // std::cout << "The neighbour distance is " << neighbor_pair.second << ", the prefix distance is " << prefix_distance << std::endl;  
  //       if(prefix_distance != std::numeric_limits<double>::max() && prefix_distance+neighbor_pair.second < distances[neighbor_pair.first]){
  //         std::cout << "Update " << vertice.first << " to " << neighbor_pair.first;
  //         distances[neighbor_pair.first] = prefix_distance + neighbor_pair.second;
  //         root[neighbor_pair.first] = vertice.first;
  //       }
  //     }
  //   }

  // }

  // std::cout<<"The for loop stop" << std::endl;

  // track back the shortest path
  for (std::string at = location2_id; at != location1_id; at = root[at]) {
    // std::cout << "The at id is: " << at << std::endl;
    path.push_back(at);
  }
  path.push_back(location1_id);
  // reverse the path
  std::reverse(path.begin(), path.end());

  

  return path;
}

/**
 * Traveling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path, 
 *                                                                      for example: {10.3, {{0, 1, 2, 3, 4, 0}, {0, 1, 2, 3, 4, 0}, {0, 4, 3, 2, 1, 0}}},
 *                                                                      where 10.3 is the total distance, 
 *                                                                      and the first vector is the path from 0 and travse all the nodes and back to 0,
 *                                                                      and the second vector is the path shorter than the first one,
 *                                                                      and the last vector is the shortest path.
 */
// Please use brute force to implement this function, ie. find all the permutations.
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Brute_force(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

// Please use backtracking to implement this function
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

// Hint: https://en.wikipedia.org/wiki/2-opt
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_2opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

// This is optional
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_3opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 * We have provided the code for you. Please do not need to change this function.
 * Example: 
 *   Input: "topologicalsort_locations.csv"
 *   File content:
 *    Name
 *    Ralphs
 *    KFC
 *    Chick-fil-A
 *   Output: ['Ralphs', 'KFC', 'Chick-fil-A']
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(
    std::string locations_filename) {
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, word)) {
    location_names_from_csv.push_back(word);
  }
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 * We have provided the code for you. Please do not need to change this function.
 * Example: 
 *   Input: "topologicalsort_dependencies.csv"
 *   File content:
 *     Source,Destination
 *     Ralphs,Chick-fil-A
 *     Ralphs,KFC
 *     Chick-fil-A,KFC
 *   Output: [['Ralphs', 'Chick-fil-A'], ['Ralphs', 'KFC'], ['Chick-fil-A', 'KFC']]
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(
    std::string dependencies_filename) {
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);
    std::vector<std::string> dependency;
    while (getline(s, word, ',')) {
      dependency.push_back(word);
    }
    dependencies_from_csv.push_back(dependency);
  }
  fin.close();
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a
 * sorting of nodes that satisfies the given dependencies. If there is no way to
 * do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(
    std::vector<std::string> &locations,
    std::vector<std::vector<std::string>> &dependencies) {
  std::vector<std::string> result;

  std::unordered_map<std::string, std::unordered_set<std::string>> relations;

  for(std::string location: locations){
    std::unordered_set<std::string> child;
    relations[location] = child;
  }

  for(std::vector<std::string> dependency: dependencies){
    std::string name = dependency[0];
    relations[dependency[0]].insert(dependency[1]);
  }

  // // cout test to chechk the child set.
  // // the test result is correct
  // for(std::string location: locations){
  //   std::cout << " The " << location << "'s child has: ";
  //   for(const auto& chid: relations[location]){
  //     std::cout << chid <<" ";
  //   }
  //   std::cout << std::endl;
  // }


  for(const auto& location: locations){
    std::vector<std::string> tmp;
    find_relationship(location, relations, tmp, result);
  }

  return result;
}

/**
 * inSquare: Give a id retunr whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) {
  return true;
}


/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location
 * ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square
 * area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the
 * square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square) {
  std::vector<std::string> subgraph;

  // ##################### written by Yiheng Zhou (Nov-14)

  // iterate all the data
  for(const auto& pair: data){
    Node node = pair.second;
    // if the id is in the square, we add the id into the vector
    if(node.lon>square[0] && node.lon<square[1] && node.lat<square[2] && node.lat>square[3]){
      subgraph.push_back(pair.first);
    }
  }

  return subgraph;
}
/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true
 * if there is a cycle path inside the square, false otherwise.
 *
 * @param {std::vector<std::string>} subgraph: list of location ids in the
 * square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square) {
  std::unordered_map<std::string, int> subgraph_id;
  int i=0; 
  for(const std::string& graph: subgraph){
    subgraph_id[graph] = i;
    i++;
  }


  // init the unionFind
  unionFind uf = unionFind(subgraph_id.size());
  // iterate all subgraph
  for(const std::string& graph: subgraph){
    // ######### written by Nov-15

    int curNode_id = subgraph_id[graph];
    // using a map to store the root id and the location id of the neighbour
    std::unordered_map<int, std::string> neighbors_ids;
    // get all the neighbor
    for(const auto& neighbor: data[graph].neighbors){

      // filter the location that not in the subgrapgh
      if(subgraph_id.find(neighbor) != subgraph_id.end()){
        int special_id = subgraph_id[neighbor];
        int root_id = uf.find(special_id);
        // the two neighbour has some root, it will return true
        if(neighbors_ids.find(root_id) != neighbors_ids.end()){
          // std::cout<< "two node ids is: " << neighbor << ", " << neighbors_ids[special_id] << std::endl; 
          return true;
        }
        else{ // if not just put the special id and the location id into the neighbors_ids
          neighbors_ids[root_id] = neighbor;
        }
      }
    }

    for(const auto& pair: neighbors_ids){
      // std::cout << "THe location id and specical id of curNode is: " << curNode_id << ", " << graph << "THe location id and specical id of subgrapgh is: " << pair.first << ", " << pair.second << std::endl; 
      uf.unit(curNode_id, subgraph_id[pair.second]);
    }
  }
  return false;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r,
 * find all locations in class C on the map near L with the range of r and
 * return a vector of string ids
 *
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {double} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k) {
  std::vector<std::string> res;
  return res;
}

/**
 * Shortest Path to Visit All Nodes: Given a list of locations, return the shortest
 * path which visit all the places and no need to go back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::vector<std::string> }      : the shortest path
 */
std::vector<std::string> TrojanMap::TrojanPath(
      std::vector<std::string> &location_names) {
    std::vector<std::string> res;
    return res;
}

/**
 * Given a vector of queries, find whether there is a path between the two locations with the constraint of the gas tank.
 *
 * @param  {std::vector<std::pair<double, std::vector<std::string>>>} Q : a list of queries
 * @return {std::vector<bool> }      : existence of the path
 */
std::vector<bool> TrojanMap::Queries(const std::vector<std::pair<double, std::vector<std::string>>>& q) {
    std::vector<bool> ans(q.size());
    return ans;
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * We have provided the code for you. Please do not need to change this function.
 */
void TrojanMap::CreateGraphFromCSVFile() {
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0])) n.attributes.insert(word);
        if (isdigit(word[0])) n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}


// ######################################################################################################
// ----------------------- Implementation of new defined function by Yiheng ZHou ------------------------

/**
 * CharDataProcess() : to iterate all the char in data of name and constructor a map that store the char and its unique id
 */
void TrojanMap::CharDataProcess(){
  int id = 0;

  for(const auto& pair: data){
    
    Node cur_node = pair.second;
  
    for(char c: cur_node.name){
      c = std::tolower(c);
      
      if(char_id.find(c) == char_id.end()){
        char_id[c] = id;
        id++;
      }
    }

  }
}

/**
 * loadName(): loading all the data of name into TrieTree 
 */
void TrojanMap::loadName(){
  for(const auto& pair: data){
    
    Node cur_node = pair.second;
    
    tree->insert(cur_node.name, pair.first);

  }
}

void TrojanMap::construct_name_id_map(){
    for(const auto& pair: data){  
      name_id_map[pair.second.name] = pair.first;
  }
}


// the helper function of GetAllCategories() 
void TrojanMap::construct_categorySet(){
  for(const auto& pair: data){
      for(std::string attribute: pair.second.attributes){
        if(categorySet_.find(attribute) == categorySet_.end()){
          categorySet_.insert(attribute);
        }
      }
    }
}


void TrojanMap::construct_categoryLocation_map(){
  // first we should check if the category set is empty or not
  if(categorySet_.size() == 0){
    construct_categorySet();
  }

  // iterate all the data
  for(const auto& pair: data){
    
    Node node = pair.second;

    // iterate all the attributes of the single date and find if the attribute is in the map key
    // if it is in the key, new a vector and push name of the location into the vector
    for(std::string attribute : node.attributes){
      if(categoryLocations_.find(attribute) != categoryLocations_.end()){
        categoryLocations_[attribute].push_back(node.id);
      }
      else{
        std::vector<std::string> locationNames;
        locationNames.push_back(node.id);
        categoryLocations_[attribute] = locationNames;
      }
    }
  }
}


void TrojanMap::find_relationship(std::string location, 
                                  std::unordered_map<std::string, std::unordered_set<std::string>> relations,
                                  std::vector<std::string> tmp, std::vector<std::string>& result){
  // base case
  if(relations[location].size() == 0){

    // push the tail node into the tmp vector
    tmp.push_back(location);
    // assert if the tmp vector is the final result
    if(tmp.size() > result.size()){
      result = tmp;
    }

    // we also should remember to pop the last vector out to avoid influencing other vector
    tmp.pop_back();
    return;
  }

  // push current node to the vector
  tmp.push_back(location);
  for(const auto& child: relations[location]){
    find_relationship(child, relations, tmp, result);
  }
  // after we have iterate this level, we should pop the node back, so that it will not make any mistakes
  tmp.pop_back();

}