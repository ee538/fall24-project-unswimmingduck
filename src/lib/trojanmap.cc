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
  if(data.find(id) == data.end()){
    return -1;
  }
  return data[id].lat;
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist,
 * return -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string &id) {
  if(data.find(id) == data.end()){
    return -1;
  }
  return data[id].lon;
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return
 * "NULL".
 *
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string &id) {
  if(data.find(id) != data.end()){
    return data[id].name;
  }
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
  if(data.find(id) != data.end()){
    return data[id].neighbors;
  }
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
  // init the name_id_map
  if(name_id_map.size() == 0){
    construct_name_id_map();
  }
  // assert if the name exists or not
  if(name_id_map.find(name) != name_id_map.end()){
    res = name_id_map[name];
  }
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
  if(name_id_map.size() == 0){
    construct_name_id_map();
  }
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
int TrojanMap::CalculateEditDistance(std::string& a, std::string b) {    
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

  if(name_id_map.size() == 0){
    construct_name_id_map();
  }

  // iterate all the name and find the smallest edit-distance one
  for(const auto& pair: name_id_map){
    int cur_distance = CalculateEditDistance(name, pair.first);
    if(cur_distance<distance){
      // std::cout << " the pair.first is " << pair.first << ", the pair.second is: " << pair.second << std::endl;
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

  // std::cout<< "the autocomplete is called" << std::endl;

 
  

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

  // std::cout << " ---- the while loop stop ----- " << std::endl;

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

  std::unordered_map<std::string, int> flags;
  for(const auto& location: location_ids){
    flags[location] = 0;
  }

  double result_distance = std::numeric_limits<double>::max();
  std::vector<std::vector<std::string>> progress;

  for(int i=0; i<location_ids.size(); i++){
    std::vector<std::string> subPath;
    flags[location_ids[i]] = 1;
    TravelingTrojan_Brute_force_DFS(0, result_distance, 0, subPath, progress, location_ids[i], location_ids[i], flags);
  }

  records.first = result_distance;
  records.second = progress;

  return records;
}

// Please use backtracking to implement this function
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;

  std::unordered_map<std::string, int> flags;
  for(const auto& location: location_ids){
    flags[location] = 0;
  }

  double result_distance = std::numeric_limits<double>::max();
  std::vector<std::vector<std::string>> progress;

  for(int i=0; i<location_ids.size(); i++){
    std::vector<std::string> subPath;
    flags[location_ids[i]] = 1;
    TravelingTrojan_Brute_force_DFS_Backtracing(0, result_distance, 0, subPath, progress, location_ids[i], location_ids[i], flags);
  }

  records.first = result_distance;
  records.second = progress;

  return records;
}

// Hint: https://en.wikipedia.org/wiki/2-opt
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_2opt(
      std::vector<std::string> location_ids){
std::pair<double, std::vector<std::vector<std::string>>> records;
  
  // init the result_distance
  double result_distance = calculate_Route_Distance(location_ids);

  // create a vector to store the finding process
  std::vector<std::vector<std::string>> process;

  bool improved = true;
  while (improved) {
    improved = false;
    for(int i=1; i<location_ids.size()-1; i++){
      for(int j=i+1; j<location_ids.size(); j++){
        // std::vector<std::string> new_route = swap_function(location_ids, i+1, j);
        std::vector<std::string> new_route = location_ids;
        std::reverse(new_route.begin()+i, new_route.begin()+j+1);
        // process.push_back(new_route);
        double new_distance = calculate_Route_Distance(new_route);

        // #################
        // std::cout << "The distance is: " << new_distance << std::endl;
        // std::cout << "the path is ";
        // for(auto& location: new_route){
        //   std::cout << location << " "; 
        // }
        // std::cout << std::endl;
        // #################

        if(new_distance < result_distance){
          // std::cout << "The new distance is " << new_distance << std::endl;
          std::vector<std::string> save_route = std::vector<std::string>(new_route);
          save_route.push_back(new_route[0]);
          process.push_back(save_route);
          location_ids = new_route;
          result_distance = new_distance;
          improved = true;
        }
      }
    }
  }
  // update the records
  records.first = result_distance;
  records.second = process;

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

  if(result.size() != locations.size()){
    return {};
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

  // check if the name_id_map and categoryLocationSet_ exist or not
  if(name_id_map.size() == 0){
    construct_name_id_map();
    // std::cout << "The size of name_id_map is " << name_id_map.size() << std::endl;
  }
  if(categoryLocations_.size() == 0){
    construct_categoryLocation_map();
  }

  // build the customized comparetor
  struct Comapre{
    bool operator()(std::pair<double, std::string> a, std::pair<double, std::string> b){
      return a.first > b.first;
    }
  };
  // init the priority queue
  std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, Comapre> pq;
  std::string center_id = name_id_map[name];
  // ######################
  std::cout << "The size of the same attribute location is " << categoryLocations_[attributesName].size() << std::endl;
   std::cout << "The size of the same name_id_map is " << name_id_map.size() << std::endl;
  // // ######################

  for(const auto& location_id: categoryLocations_[attributesName]){
    double distance = CalculateDistance(location_id, center_id);
    std::cout << "The name is "<< location_id << " The distance is " << distance << " The r is " << r << ", Is the distance < r: "<< (distance<r) << std::endl;
    if(distance < r && location_id != center_id){
      pq.push(std::pair<double, std::string>{distance, location_id});
      std::cout << "The " << location_id << " has push into the pq" << std::endl;
    }
  }

  // iterate k times to get 0-th to k-th closest locations
  for(int i=0; i<k; i++){
    if(pq.size() != 0){
       // get the closet location
      std::pair<double, std::string> target_location = pq.top();
      pq.pop();
      res.push_back(target_location.second);
    }
    else{
      break;
    } 
  }

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
    std::vector<std::string> res={};

     // first using dijkstra alogrithm to get the shortest path between every locations
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> location_paths;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> locations_distance;
    for(int i=0; i<location_names.size(); i++){
      for(int j=i+1; j<location_names.size(); j++){
        // std::cout << " --- Calculate the date between " << location_names[i] << " and " << location_names[j] << std::endl;
        // get the shortest path
        std::vector<std::string> path = CalculateShortestPath_Dijkstra(location_names[i], location_names[j]);
        
        // update the path map
        location_paths[location_names[i]][location_names[j]] = std::vector<std::string>(path);
        std::reverse(path.begin(), path.end());
        location_paths[location_names[j]][location_names[i]] = path;
        // update the distance map
        double distance = CalculatePathLength(path);
        locations_distance[location_names[i]][location_names[j]] = distance;
        locations_distance[location_names[j]][location_names[i]] = distance;
        // std::cout << " --- The process done" << std::endl;
      }
    }

    // // ##############################
    // std::cout << "The size of the path is " << location_paths.size() << std::endl;
    // for(const auto& distances: locations_distance){
    //   for(const auto& dis: distances.second){
    //     std::cout << "The " << distances.first << " is " << dis.second << " to " << dis.first << std::endl;
    //   }
    // }
    // // ##############################


    std::unordered_map<std::string, int> locations_flag;
    for(const auto& location_name: location_names){
      locations_flag[location_name] = 0;
    }

    std::vector<std::string> reuslt;
    double distance = std::numeric_limits<double>::max();

    // using dfs to find the shortest path
    for(int i=0; i<location_names.size(); i++){
      std::vector<std::string> sub_result;
      // std::cout << "The start is " << location_names[i] << std::endl;
      find_shortestPath_Alllocations(reuslt, sub_result, location_names[i], 0, distance, 0, locations_flag, locations_distance);
    }
    
    // iterate all the result
    for(int i=1; i<reuslt.size(); i++){
      // get the sub_path  
      std::vector<std::string> sub_path = location_paths[reuslt[i-1]][reuslt[i]];
  
      if(i>1){
        // we should remove the repeat location in the middle
        res.insert(res.end(), sub_path.begin()+1, sub_path.end());
      }else{
        res.insert(res.end(), sub_path.begin(), sub_path.end());
      }
      
    }
    return res;
}

/**
 * Given a vector of queries, find whether there is a path between the two locations with the constraint of the gas tank.
 *
 * @param  {std::vector<std::pair<double, std::vector<std::string>>>} Q : a list of queries
 * @return {std::vector<bool> }      : existence of the path
 */
std::vector<bool> TrojanMap::Queries(const std::vector<std::pair<double, std::vector<std::string>>>& q) {

    std::vector<bool> ans;

    // construct the name_id map
    if(name_id_map.size() == 0){
      construct_name_id_map();
    }

    // we need to get a hashmap that store the location id and special id
    std::unordered_map<std::string, int> location_specialId_;
    int special_id = 0;
    for(const auto& data_pair: data){
      location_specialId_[data_pair.first] = special_id;
      special_id++;
    }
    
    // std::cout << "The size of the location_specailId is " << location_specialId_.size() << std::endl;

    // we need a hashset to store the visited node
    std::unordered_set<std::string> visited;
    // we need a vector to store all the distance
    std::vector<std::pair<double, std::pair<int, int>>> edges;
    // get all edge
    for(const auto& data_pair: data){
      // set the current node to visited
      visited.insert(data_pair.first);

      // if(data_pair.second.name == "Target"){
      //   std::cout << "The target node" << std::endl;
      // }

      // iterate all the neighbor
      for(const auto& neighbor_id: data_pair.second.neighbors){
        if(visited.find(neighbor_id) == visited.end()){ // we should affirm that the node we have not visisted before
          // calculate the distance and push the data pair into the vector
          if(location_specialId_[data_pair.first] == 16681 || location_specialId_[neighbor_id] == 16681){
            std::cout << "the id is " << location_specialId_[data_pair.first] << " The distance is " << CalculateDistance(data_pair.first, neighbor_id) << std::endl;
          }
          
          edges.push_back({CalculateDistance(data_pair.first, neighbor_id), {location_specialId_[data_pair.first], location_specialId_[neighbor_id]}});
        }
      }
    }


    // std::cout << "The speical id of Target is " << location_specialId_[name_id_map["Target"]] << std::endl;
    // // ########################
    // for(const auto& edge: edges){
    //   if(edge.second.first == 16681 || edge.second.second == 16681){
    //       std::cout << "The distance between " << edge.second.first << " and " << edge.second.second << " is " << edge.first << std::endl;
    //   }
    // }


    // we should iterate all the pair
    for(const auto& q_pair: q){
      // init the unionfind data
      unionfind_gas uf_gas = unionfind_gas(data.size());
      // iterata all the edges and update the unionfind_gas
      for(const auto& edge: edges){
        // if(edge.second.first == location_specialId_[name_id_map["Target"]] || edge.second.second == location_specialId_[name_id_map["Target"]]){
        //   std::cout << "The distance between " << edge.second.first << " and " << edge.second.second << " is " << edge.first << std::endl;
        // }
        // std::cout << "the node distance is " << edge.first << " the require distance is " << q_pair.first << std::endl;
        if(edge.first < q_pair.first){ // if the edge smaller than the required distance
          // std::cout << "Unit " << edge.second.first << " and " << edge.second.second << std::endl;
          uf_gas.unit(edge.second.first, edge.second.second);
        }
      }

      // we should assert if the input name is vaild or not
      if(name_id_map.find(q_pair.second[0]) != name_id_map.end() && name_id_map.find(q_pair.second[1]) != name_id_map.end()){
        // std::cout << "Using uf to assert " << location_specialId_[name_id_map[q_pair.second[0]]] << " and " << location_specialId_[name_id_map[q_pair.second[1]]] << std::endl;
        // std::cout << "The root of " << location_specialId_[name_id_map[q_pair.second[0]]] << " is " << uf_gas.find(location_specialId_[name_id_map[q_pair.second[0]]]) << " the root of " << location_specialId_[name_id_map[q_pair.second[1]]] << " is " << uf_gas.find(location_specialId_[name_id_map[q_pair.second[1]]]) << std::endl;
        ans.push_back(uf_gas.same_union(location_specialId_[name_id_map[q_pair.second[0]]], location_specialId_[name_id_map[q_pair.second[1]]]));
      }
      else{ // if the input name is invalid, just push false into the res
        ans.push_back(false);
      }
    }

    // std::cout << "The distance is " << CalculateDistance("6814769289", "5237417650") << std::endl;
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
      if(pair.second.name.size() != 0){
        name_id_map[pair.second.name] = pair.first;
      }
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


void TrojanMap::TravelingTrojan_Brute_force_DFS(int level, double& result_distance,double cur_distance, std::vector<std::string>& subPath, std::vector<std::vector<std::string>>& allpathSets,
                                                const std::string start_location, std::string cur_location, 
                                                std::unordered_map<std::string, int> flags
                                                ){
  if(level == flags.size()-1){
    // add the distance from the last node to the start node
    cur_distance += CalculateDistance(cur_location, start_location);
    
    if(cur_distance<result_distance){
      subPath.push_back(cur_location);
      subPath.push_back(start_location);
      allpathSets.push_back(std::vector<std::string>(subPath));
      subPath.pop_back();
      subPath.pop_back();
    }

    // update the distance
    result_distance = std::min(result_distance, cur_distance);
    
    return;
  }

  // visit cur_location
  flags[cur_location] = 1;
  subPath.push_back(cur_location);
  // iterate all the location that have not been visited
  for(const auto& pair: flags){
    if(pair.second == 0){
      TravelingTrojan_Brute_force_DFS(level+1,result_distance, cur_distance+CalculateDistance(pair.first, cur_location), 
                                      subPath, allpathSets, start_location, pair.first, flags);
    }
  }

  flags[cur_location] = 0;
  subPath.pop_back();

}


void TrojanMap::TravelingTrojan_Brute_force_DFS_Backtracing(int level, double& result_distance,double cur_distance, std::vector<std::string>& subPath, std::vector<std::vector<std::string>>& allpathSets,
                                                  const std::string start_location, std::string cur_location, 
                                                  std::unordered_map<std::string, int> flags
                                                  ){
  if(cur_distance>result_distance){
    // std::cout << "The result distance is " << result_distance << " the cur_distance is " << cur_distance << std::endl; 
    return;
  }
  else if(level == flags.size()-1){
    // add the distance from the last node to the start node
    cur_distance += CalculateDistance(cur_location, start_location);
    if(cur_distance<result_distance){
      subPath.push_back(cur_location);
      subPath.push_back(start_location);
      allpathSets.push_back(std::vector<std::string>(subPath));
      subPath.pop_back();
      subPath.pop_back();

      // update the distance
      result_distance = cur_distance;
    }
      
    return;
  }

  // visit cur_location
  flags[cur_location] = 1;
  subPath.push_back(cur_location);
  // iterate all the location that have not been visited
  for(const auto& pair: flags){
    if(pair.second == 0){
      TravelingTrojan_Brute_force_DFS_Backtracing(level+1, result_distance, cur_distance+CalculateDistance(pair.first, cur_location), 
                                      subPath, allpathSets, start_location, pair.first, flags);
    }
  }

  flags[cur_location] = 0;
  subPath.pop_back();
}


std::vector<std::string> TrojanMap::swap_function(const std::vector<std::string>& cur_path, int swap_start, int swap_end){
  std::vector<std::string> result = std::vector<std::string>(cur_path);
  while(swap_start < swap_end){
    // result.swap(swap_start, swap_end);
    std::string tmp = result[swap_start];
    result[swap_start] = result[swap_end];
    result[swap_end] = tmp;
    swap_start++;
    swap_end--;
  }
  return result;
}


double TrojanMap::calculate_Route_Distance(std::vector<std::string>& route){
  double result = 0;
  for(int i=1; i<route.size(); i++){
    result += CalculateDistance(route[i], route[i-1]);
  }
  result += CalculateDistance(route.at(0), route.at(route.size()-1));
  return result;
}


void TrojanMap::find_shortestPath_Alllocations(std::vector<std::string>& reuslt, std::vector<std::string> sub_reuslt, std::string cur_location,
                                               int level, double& result_distance, double cur_distance, 
                                               std::unordered_map<std::string, int>& locations_flags, 
                                               std::unordered_map<std::string, std::unordered_map<std::string, double>>& locations_distance){
  // pruning the branches
  if(cur_distance>result_distance){
    return;
  }
  // base case
  else if(level == locations_flags.size()-1 && cur_distance<result_distance){
    // update the sub_result
    sub_reuslt.push_back(cur_location);
    // update the result
    reuslt = sub_reuslt;
    // update the subresult
    sub_reuslt.pop_back();
    result_distance = cur_distance;
    
    return;
  }

  // arriving cur location
  // update the flags
  locations_flags[cur_location] = 1;
  //update the subresult
  sub_reuslt.push_back(cur_location);
  //iterate all the un-visisted locations
  for(const auto& next_location: locations_flags){
    if(next_location.second != 1){
      find_shortestPath_Alllocations(reuslt, sub_reuslt, next_location.first, level+1, 
                                   result_distance, cur_distance+locations_distance[cur_location][next_location.first], 
                                   locations_flags, locations_distance);
    }
  }
  // after iterate all the un-visited location, we should set the flag of cur_location to 0
  locations_flags[cur_location] = 0;
  // we also need to pop the cur_location back from the suv_result
  sub_reuslt.pop_back();
}


std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Genetic_Algorithm(std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> result;
  int population_size = location_ids.size()*10;
  
  int iteration  = location_ids.size()*10;
  int temperature = 100000;
  // std::cout << "The init temperature is " << temperature << std::endl;

  std::vector<std::pair<double, std::vector<std::string>>> populationPool_;

  // construct the special id, using map to store the locaiton id and special id
  std::unordered_map<std::string, int> location_specialId;
  for(int i=0; i<location_ids.size(); i++){
    location_specialId[location_ids[i]] = i;
  }

  std::vector<std::vector<double>> distanceMatrix(location_ids.size(), std::vector<double>(location_ids.size(), 0));
  // caculate all the distance between two nodes
  for(int i=0; i<location_ids.size(); i++){
    for(int j=i+1; j<location_ids.size(); j++){
      distanceMatrix[i][j] = CalculateDistance(location_ids[i], location_ids[j]);
      distanceMatrix[j][i] = distanceMatrix[i][j];
      // ####
      std::cout << "The distance between " << location_ids[i] << " and " << location_ids[j] << " is " << distanceMatrix[i][j] << std::endl;
    }
  }

  std::srand(std::time(0));
  // init the prelimminary generation
  for(int i=0; i<population_size; i++){
    // store the used id
    std::unordered_set<int> usedId;
    // store the single chrom
    std::vector<std::string> chrome;
    // generate single chrome
    for(int j=0; j<location_ids.size(); j++){
      while (true)
      {
        int random_num = std::rand() % location_ids.size();
        // if this random_num has not been used, we can use it
        if(usedId.find(random_num) == usedId.end()){
          usedId.insert(random_num);
          chrome.push_back(location_ids[random_num]);
          break;
        } 
      }
    }

    // after a chrom done, we should push it into the 
    populationPool_.push_back({calculate_Route_Distance_GA(chrome, location_specialId, distanceMatrix),chrome});
  }

  struct comparator_ga
  {
    bool operator()(std::pair<double, std::vector<std::string>> input1, std::pair<double, std::vector<std::string>> input2){
      return input1.first < input2.first;
    }
  };
  
  std::sort(populationPool_.begin(), populationPool_.end(), comparator_ga());

  
  int cur_iteration = 0;
  std::vector<std::vector<std::string>> processSet_;
  double result_distance = std::numeric_limits<double>::max();

  while( temperature>100 && cur_iteration<(iteration-1)){ // one-epoch iteration

    // #########################
    std::cout << " ---- " << cur_iteration << "-th " << " to " << iteration <<" iteration epochs ----- " << std::endl;
    std::cout << "the temperature is " << temperature << std::endl;
    // for(const auto& gnome_pair: populationPool_){
    //   std::cout << "The distance is " << gnome_pair.first << ", the path is: ";
    //   for(const auto& gnome: gnome_pair.second){
    //     std::cout << gnome << " ";
    //   }
    //   std::cout << std::endl;
    // }
    // #########################

    // new popultaionPool_
    std::vector<std::pair<double, std::vector<std::string>>> new_populationPool_;
    // iterate all the population_size 
    for(int i=0; i<populationPool_.size(); i++){
      // get the current gnome
      std::pair<double, std::vector<std::string>> cur_gnome = populationPool_[i];

      // #######################
      // std::cout << "The distance is " << cur_gnome.first << " the path is ";
      // for(const auto& gnome: cur_gnome.second){
      //   std::cout << gnome << " ";
      // }
      // std::cout << std::endl;
      // #######################

      // mutate this gnome
      while (true)
      { 
        // #####
        // std::cout << "THe mutatedGene function start" << std::endl;
        // #####

        // generate new gnome
        std::vector<std::string> new_gnome = mutatedGene(cur_gnome.second);

        // ###############
        // std::cout << "The mutatedGene end" << std::endl;
        // ###############

        // assert if the new_gnome has short length
        double new_distance = calculate_Route_Distance_GA(new_gnome, location_specialId, distanceMatrix);
        // std::cout << "The new distance is " << new_distance << std::endl;
        // ###########
        // std::cout << "the new gnome is ";
        // for(const auto& newG: new_gnome){
        //   std::cout << newG << " ";
        // }
        // std::cout << std::endl;
        // std::cout << "The new distance is " << new_distance << " and the cur_gnome distance is " << cur_gnome.first << std::endl;
        // ###########

        if(new_distance < cur_gnome.first){
          new_populationPool_.push_back({new_distance, new_gnome});
          break;
        }
        else{
          // Accepting the rejected children at
          // a possible probability above threshold.
          float prob = pow(2.7,
                          -1 * ((float)(new_distance - cur_gnome.first)/temperature));
          // ###############
          // std::cout << "The temperature is " << temperature << std::endl;
          // std::cout << "THe pro is " << prob << ", (float)(new_distance - cur_gnome.first)/temperature) is " << (float)(new_distance - cur_gnome.first)/temperature <<  std::endl;
          // ###############

          if (prob > 0.5) {
              new_populationPool_.push_back({new_distance, new_gnome});
              break;
          }
        }
      }
      // std::cout << "The while loop break" << std::endl;
    }



    // tmperature decreasing
    temperature = (int)(90*temperature)/100;
    // update the populationPool 
    populationPool_ = new_populationPool_;
    std::sort(populationPool_.begin(), populationPool_.end(), comparator_ga());
    // record the shortest path in every iteration
    if(populationPool_[0].first < result_distance){
      result_distance = populationPool_[0].first;
      processSet_.push_back(populationPool_[0].second);
    }
    
    std::cout << "The shortest distance is " << populationPool_[0].first << std::endl;
    std::cout<< " ----- " << cur_iteration << "-th epochs end ---- " << std::endl; 

    // update the iteration
    cur_iteration++;

    
  }
  result.first = result_distance;
  result.second = processSet_;
  return result;

}



double TrojanMap::calculate_Route_Distance_GA(std::vector<std::string>& route, std::unordered_map<std::string, int> location_specialId, std::vector<std::vector<double>> distanceMatrix){
  double result = 0;
  for(int i=1; i<route.size(); i++){
    result += distanceMatrix[location_specialId[route[i]]][location_specialId[route[i-1]]];
  }
  result += distanceMatrix[location_specialId[route[0]]][location_specialId[route[route.size()-1]]];
  return result;  
}


std::vector<std::string> TrojanMap::mutatedGene(std::vector<std::string> gnome){
  // std::srand(std::time(0));
  std::vector<std::string> new_gnome(gnome);
  // avoid random number is the same
  while (true) {
    int random_num1 = std::rand() % (gnome.size()-1);
    int random_num2 = std::rand() % (gnome.size()-1);
    // std::cout << "The size of the gnome is " << gnome.size() << std::endl;
    // std::cout << "The random num is " << random_num1 << " and " << random_num2 << std::endl;
    if (random_num1 != random_num2) {
      // std::cout << "go into the if condition function" << std::endl;
      std::string tmp = new_gnome[random_num1];
      new_gnome[random_num1] = new_gnome[random_num2];
      new_gnome[random_num2] = tmp;
      break;
    }
  }
  // std::cout << "The while loop break" << std::endl;
  return new_gnome;
}