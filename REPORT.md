

## Item 1: Autocomplete The Location Name
### Function Description
```c++
std::vector<std::string> Autocomplete(std::string name);
```

In this function, we can type the partial name of the location and return a list of possible locations with the partial name as the prefix. 

Example:

Input: "Chi" \
Output: ["Chick-fil-A", "Chipotle", "Chinese Street Food"]

### Implimentation
We use Trie Tree to implement this function. The data structure of Trie Tree is below. 

#### Trie-Tree Data Structure
```c++
class TrieNode{
    public:
        TrieNode* child_[67];	// to store the child node
        bool endFlag_;			// to flag if this node has end flag
        std::vector<std::string> endId_;	// to store which id end in this level node
        TrieNode(): endFlag_(false){
            for(int i=0; i<67; i++){
                child_[i] = nullptr;
            }
        };

};

class TrieTree{

    public:

        // TrieNode pointer
        TrieNode* node_ = nullptr;
        
        // this unorder_map is used to store the char and the unique id of the char
        // so that we can store the input name into the TrieTree
        std::unordered_map<char, int> charId_;

        TrieTree(std::unordered_map<char, int> charId): charId_(charId){
            node_ = new TrieNode();
        };

        ~TrieTree();

        // the helper function of ~TrieTree()
        void destroy(TrieNode* root);

        // insert the data of name into TrieTree
        void insert(std::string name, std::string id);

        // return all the id of the possible name that are similar to the input name
        std::vector<std::string> find(std::string name);

        // the helper function of find()
        void bfs_find(TrieNode* node, std::vector<std::string>* result);
};
```
#### Implimentation
In the Trie Node, the index of  ``child_[]`` represents a special word or letter. So we need a map to record the relationship between every index and the letter, just as the below example.
Example:    { {"a",  0},  {"b",  1}, {"c", 2} .... }. The belowing picture can explain clearly how Tire-Tree work.

![a4cebf1a243cb41f29aa94dfb660ae2](https://github.com/user-attachments/assets/a972d47c-2a18-4c2a-9a00-47141a8036a7)

In this way, I construct a funtion called ```CharDataProcess()```. In this function, I iterate all the name of location and using an ``unordered_map`` to store the relationship.

### RunTime Complexity
Then we iterate all the location name and insert all the name into the Trie-Tree. The **runtime complexity is O(n)**. 
When we want to find the word, we firstly iterate all the input letter and arrive to the correct level node and then using **BFS** to search all the result. **The runtime complexity is O(1), but if we consider the construction of Trie-Tree as a part of find function runtime complexity is O(n).** 
  
### Test the Validation of Output
To test if the output is correct or not, I also use Python and Pandas to accomplish same function and test the correction of ouput.
```python
import  pandas  as  pd
import  re

# read the data and get the list of the name
df  =  pd.read_csv('data.csv')
name_list  =  df[df["name"].notna()]["name"].tolist()

# regex expression
input  =  "Pico"
regex_expression  =  r'\b'+  input  +  '\w*'

# get the all name that math the regex expression
result  = []
for  name  in  name_list:
	if(re.match(regex_expression, name)):
		result.append(name)

print(result)
```

### Google Benchmark
I also using **Google Benchmark**  and python to draw a diagram of how the runtime grows based on the input size.
![runtime_item1](https://github.com/user-attachments/assets/5970588f-b14e-491d-b90b-45919f70f0af)

## Item 2-1: Find the place's coordinates in the Map 
### Function Description
```c++
std::pair<double, double> GetPosition(std::string name);
```

Given a location name, return the latitude and longitude. 

Example:

Input: "Target" \
Output: (34.0257016, -118.2843512)

### Implementation
We iterate all the data and construct an ``unordered_map`` to store the location name and its id. In the ``unordered_map``, key is the location name and the value is the location id. In this way, we can get the id by the location name quickly. **The Runtime Complexity of unordered_map construction is O(n), the Runtime Complexity of find coordination is O(1).**

### Runtime Complexity
Assume the number of location is n. **The Runtime Complexity is O(n)**. This is because we need to construct the unordered_map to store the location name and location id, then we can use location name to get the location id and get the coordination of the location.

### Google Benchmark
![runtime_item2_correct](https://github.com/user-attachments/assets/92ee62cf-55d5-4f44-adc0-229596637141)


## Item 2-2: Check Edit Distance Between Two Location Names 
### Function Description
```c++
int CalculateEditDistance(std::string name1, std::string name2);
```

When entering a location name that does not exist in the map, your program should determine whether the input can be replaced with a "similar name" or not. By "similar names" we mean the names that exist in the map with a *smallest distance* from the original input. 

The distance between two names A and B is the minimum number of operations required to convert A to B. There are 3 operations:
+ Insert a character
+ Delete a character
+ Replace a character
```c++
std::string FindClosestName(std::string name);
```
### Implementation
I use **Dynamic Programming** to implement this function. The detail of the location can be explain in the belowing pircture.
![image](https://github.com/user-attachments/assets/bef5a3c1-9c2c-4c31-a389-8a24a6886978)


### Runtime Complexity
if the length of the name1 is n and the length of the name2 is m, **the Runtime Complexity is O(n*m).**



## Item 3: Get All Categories (Phase 2)
### Function Description
```c++
std::vector<std::string> GetAllCategories();
```

In this section, your program should print all available categories among all existing categories in the map. There should be no duplicates in the output.

### Implementation
In order to print all the categories and we also need to avoid the duplication, we using ``unordered_set`` to accomplish the goal. The function will iterate all the data and insert every attribute that can't be found in set. In this way, we can collect all the attribute without duplication.

### Runtime Complexity
Assume the number of data is n, **the Runtime Complexity is O(n).** This is because we should iterate all the data to collect all attirbute.

### Result output
```
**************************************************************
3

**************************************************************
* 3. Find all location categories                             
**************************************************************

"parcel_locker", "car_wash", "childcare", "yes", "driving_school", "dentist", "police", "charging_station", "copyshop", "theatre", "bicycle", "museum", "post_office", "library", "fuel", "hotel", "bank", "convenience", "parking", "clothes", "fast_food", "hairdresser", "restaurant", "yoga", "cafe", "clinic", "parking_entrance", "optician", "bakery", "shoes", "hospital", "beverages", "car_repair", "post_box", "tobacco", "attraction", "fountain", "confectionery", "school", "car", "shoe_repair", "food_court", "artwork", "fabric", "gallery", "social_facility", "supermarket", "pharmacy", "department_store", "mobile_phone", "bar", "skate", "marketplace", "music", "place_of_worship", "beauty", "bicycle_rental", "bus_station", 
TrojanMap Menu
**************************************************************
```

### Validation of Output
In order to verify the correct of the output, I also using write a program by Python to test if the output is correct or not.
```python
import pandas as pd
import json

df = pd.read_csv('data.csv')

attributes = df[df["attributes"].notna()]["attributes"].unique().tolist()
category = []
for attribute in attributes:
    print(attribute)

```

## Item 4: Get All Locations In A Category (Phase 2)
### Function Description
```c++
std::vector<std::string> GetAllLocationsFromCategory(std::string category);
```

In this section if the user entries a category, the program prints all locations that match that category. For example, if there is a category called "bank", your program should print all location ids that match the "bank" category. 

### Implementation
In order to get the location by the category, we should construct a ``unordered_map`` to store the category and the relative locations. The function will iterate all the data and insert the location to relative attribute vector in the ``unordered_set``.

### RumTime Complexity
**The Runtime Complexity of construct the map is O(n), after the construction is done the the Runtime Complexity of find is O(1).**

### Result Output
```
**************************************************************
4

**************************************************************
* 4. Get all locations in a category                           
**************************************************************

Please input the category:bank
"9591449441", "9591449465", "5237417651", TrojanMap Menu
**************************************************************
```

### Ouput Validation
In order to verify the correct of the output, I also using write a program by Python to test if the output is correct or not.
```
import pandas as pd
import json

df = pd.read_csv('data.csv')
attributes= "bank"
locations = df[df["attributes"].str.contains(attributes, na=False)]["id"].astype(str).tolist()

for location in locations:
    print(location)
```


## Item 5: Get Locations Using A Regular Expression (Phase 2)
### Function Description
```c++
std::vector<std::string> GetLocationRegex(std::regex location);
```

Your program should also verify if the input regular expression was correct. Return an empty vector if the regex is not valid or matches no items.

### Implementation
In this function, one of the most important part is that we should assert if the input regular expression is correct or not. So I use ``try{...} catch{...}`` synax to print the error if the regular expression is wrong. What's more, if the regular expression is correct, we iterate all the location name and use ``std::regex_match`` to find the similar location name.

### RunTime Complexity
Assume that the number of the data is n, **the Runtime Complexity is O(n).** This is because we have to iterate all the data and using ``std::regex_match`` to assert if the location name match the regular expression.

### Output Example
![image](https://github.com/user-attachments/assets/4665d292-58a9-4e95-b585-40295eb08771)
![image](https://github.com/user-attachments/assets/95b4d476-a914-462b-a227-0b51304f65d5)
![image](https://github.com/user-attachments/assets/a7ca4973-9386-4301-9579-fda46d1ab3d1)




## Item 6: CalculateShortestPath between two places 
### Function Description
```c++
std::vector<std::string> CalculateShortestPath_Dijkstra(std::string &location1_name,
                                               std::string &location2_name);
std::vector<std::string> CalculateShortestPath_Bellman_Ford(std::string &location1_name,
                                               std::string &location2_name);
```

Given 2 locations A and B, find the best route from A to B. The distance between 2 points is the euclidean distance using latitude and longitude. You should use both Dijkstra algorithm and Bellman-Ford algorithm. Compare the time for the different methods. Show the routes on the map. If there is no path, please return empty vector.

### Implementation
**In Dijkstra,**  we should using a Priority Queue to store node and extract the node with the smallest distance from the priority queue. For each neighbor of the current node, Calculate the potential distance to that neighbor via the current node. If the calculated distance is shorter than the currently recorded distance for the neighbor, update the distance in the priority queue and the predecessor of the neighbor. The algorithm stops when all nodes have been visited, or the shortest path to the target node has been found.

### RunTime Complexity
**In Dijkstra,**  assume that the number of vertice is ``V`` and the number of edges is ``E``. **The RunTime Complexity is O((V+E)log(V))**

**In BellmanFord**,   assume that the number of vertice is ``V`` and the number of edges is ``E``. **The RunTime Complexity is O(V*E)**


### Result
![image](https://github.com/user-attachments/assets/bd5b1760-ca20-4dc8-bb11-076bcae85f14)
There are some output on map picture belowing.
![4c98717f31b3f174776bed42a22f82f](https://github.com/user-attachments/assets/53067998-7e12-4504-9920-e9b885150f12)
![8bb852a6e51f24a93314a19ab7ea729](https://github.com/user-attachments/assets/20c2b8b3-21aa-48ca-b89b-997839147083)





## Item 7: Cycle Detection (Phase 2)
### Function Description
```c++
bool CycleDetection(std::vector<double> &square);
```

In this section, we use a square-shaped subgraph of the original graph by using four coordinates stored in ```std::vector<double> square```, which follows the order of left, right, upper, and lower bounds. 

Then try to determine if there is a cycle path in the that subgraph.
If it does, return true and report the path of the cycle on the map. Otherwise return false.



### Implementation Detail
I use ``unionFind`` to solve this problem. UnionFind can solve this problem very efficiently. If there exists a cycle path it means that one node have the same root node. The mehcanism of the unionfind to solve this problem can be explained by the follow picture.
 
The detail of ``unionFind`` data structure is below.
```c++
class unionFind{
    public:
        int size_;	// The size of unionfind
        int* root_;	// The root of the union
        std::unordered_set<int> flags;	// The node that has been set 
        
        unionFind(){
            root_ = nullptr;
        };
        unionFind(int size);
        ~unionFind(){
            delete root_;
            root_ = nullptr;
        }
        int find(int id);
        void unit(int p, int q);
};
```

Firstly, iterating all nodes in the region and insert the node and its neighbor into the unionfind data structure. In the iteration, we can check if there has two neighbor nodes that has same root. If it has it means that there has cycle path.
![image](https://github.com/user-attachments/assets/e9fc00d0-4d16-4317-a75c-24c3006e6e51)

### Runtime Complexity
Assume that the number of data is n. **The Runtime Complexity is O(n). This is because we using unionfind and in worst case the function need to iterate all nodes in the region to get the result.**

### My Result
#### Example 1
```shell
Input: square = {-118.310, -118.290, 34.020, 34.005}
Output: true
```

#### Example 2
```shell
Input: square = {-118.300, -118.250, 34.030, 34.010}
Output: true
```

#### Example 3
```shell
Input: square = {-118.305, -118.295, 34.010, 34.005}
Output: true
```

#### Example 4
```shell
Input: square = {-118.310, -118.275, 34.015, 34.005}
Output: true
```


## Item 8: Topological Sort (Phase 2)
### Function Description
```c++
std::vector<std::string> DeliveringTrojan(std::vector<std::string> &location_names,
                                            std::vector<std::vector<std::string>> &dependencies);
```

For example, 

```shell
Input: 
location_names = {"Ralphs", "Chick-fil-A", "KFC"}
dependencies = {{"Ralphs","KFC"}, {"Ralphs","Chick-fil-A"}, {"Chick-fil-A", "KFC"}}
```
### Implementation
To solve this problem, I use DFS to search the correct topological order. It is easy to know that if we select one of node in the dependencies as the start node and keep searching the next node, we can get a temporary topological order. Assume that the length of the temporary order is x, the number of the all locations is n. The temporary order just have two cases: one of the case is that the result order is the sub-order of the correct topological order and in this case **x is smaller than n**, the other case is that the temporary order is the correct order and in this case **x equals to the n**. **So, in this way, we can use DFS to iterate all possible topological orders and use the length of the order to assert if the output order is the correct topological order.**
The following picture shows how this function word.
![image](https://github.com/user-attachments/assets/07cb3b96-3dad-467f-8c04-6761bd3c222b)

### My Result output

#### Example 1
input:
```
locations name: {Ralphs, KFC, Chick-fil-A, Arco, Chase}
dependencies: {{Ralphs,Chick-fil-A},{Ralphs,KFC},{KFC,Chick-fil-A},{Chick-fil-A,Arco},{Chick-fil-A,Chase},{Arco,Chase}}
```
result:
```
**************************************************************
* 8. Topological Sort                                         
**************************************************************

Please input the locations filename:/home/bonanza/EE538/fall24-project-unswimmingduck/input/topologicalsort_locations.csv
Please input the dependencies filename:/home/bonanza/EE538/fall24-project-unswimmingduck/input/topologicalsort_dependencies.csv
*************************Results******************************
Topological Sorting Results:
Ralphs
KFC
Chick-fil-A
Arco
Chase
Ross
**************************************************************
Time taken by function: 0 ms
```
#### Exmaple 2
input 
```
locations name: {Ralphs,KFC,Chick-fil-A,Arco,Chase,Ross}
dependencies" {{Ralphs,Chick-fil-A},{Ralphs,KFC},{KFC,Chick-fil-A},{Chick-fil-A,Arco},{Chick-fil-A,Chase},{Arco,Chase},{Chick-fil-A,Ross},{Ralphs,Ross},{Chase,Ross}}
```

result
```
**************************************************************
* 8. Topological Sort                                         
**************************************************************

Please input the locations filename:/home/bonanza/EE538/fall24-project-unswimmingduck/input/topologicalsort_locations.csv
Please input the dependencies filename:/home/bonanza/EE538/fall24-project-unswimmingduck/input/topologicalsort_dependencies.csv
*************************Results******************************
Topological Sorting Results:
Ralphs
KFC
Chick-fil-A
Arco
Chase
Ross
**************************************************************
Time taken by function: 0 ms
```

#### Example 3
input
```
locations name: {Ralphs,KFC,Chick-fil-A,Arco,Chase,Ross,Target,Trader Joes}
dependencies" {{Ralphs,Chick-fil-A},{Ralphs,KFC},{KFC,Chick-fil-A},{Chick-fil-A,Arco},{Chick-fil-A,Chase},{Arco,Chase},{Chick-fil-A,Ross},{Ralphs,Ross},{Chase,Ross},{Ralphs,Target},{KFC,Target},{Ross,Target},{Ross,Trader Joes},{Chase,Trader Joes},{Target,Trader Joes}}
```
Result
```
**************************************************************
* 8. Topological Sort                                         
**************************************************************

Please input the locations filename:/home/bonanza/EE538/fall24-project-unswimmingduck/input/topologicalsort_locations.csv
Please input the dependencies filename:/home/bonanza/EE538/fall24-project-unswimmingduck/input/topologicalsort_dependencies.csv
*************************Results******************************
Topological Sorting Results:
Ralphs
KFC
Chick-fil-A
Arco
Chase
Ross
Target
Trader Joes
**************************************************************
Time taken by function: 0 ms
```

#### Example 4
input
```
locations name: {Ralphs,KFC,Chick-fil-A,Arco,Chase,Ross,Target,Trader Joes,Chipotle}
dependencies" {{Ralphs,Chick-fil-A},{Ralphs,KFC},{KFC,Chick-fil-A},{Chick-fil-A,Arco},{Chick-fil-A,Chase},{Arco,Chase},{Chick-fil-A,Ross},{Ralphs,Ross},{Chase,Ross},{Ralphs,Target},{KFC,Target},{Ross,Target},{Ross,Trader Joes},{Chase,Trader Joes},{Target,Trader Joes},{Trader Joes,Chipotle}}
```
Result
```
**************************************************************
* 8. Topological Sort                                         
**************************************************************

Please input the locations filename:/home/bonanza/EE538/fall24-project-unswimmingduck/input/topologicalsort_locations.csv
Please input the dependencies filename:/home/bonanza/EE538/fall24-project-unswimmingduck/input/topologicalsort_dependencies.csv
*************************Results******************************
Topological Sorting Results:
Ralphs
KFC
Chick-fil-A
Arco
Chase
Ross
Target
Trader Joes
Chipotle
**************************************************************
Time taken by function: 1 ms
```

#### Example 5
input
```
locations name: {Ralphs,KFC,Chick-fil-A,Arco,Chase,Ross,Target,Trader Joes,Chipotle,Pico}
dependencies" {{Ralphs,Chick-fil-A},{Ralphs,KFC},{KFC,Chick-fil-A},{Chick-fil-A,Arco},{Chick-fil-A,Chase},{Arco,Chase},{Chick-fil-A,Ross},{Ralphs,Ross},{Chase,Ross},{Ralphs,Target},{KFC,Target},{Ross,Target},{Ross,Trader Joes},{Chase,Trader Joes},{Target,Trader Joes},{Trader Joes,Chipotle}, {Chipotle,Pico}}
```
Result
```
**************************************************************
* 8. Topological Sort                                         
**************************************************************

Please input the locations filename:/home/bonanza/EE538/fall24-project-unswimmingduck/input/topologicalsort_locations.csv
Please input the dependencies filename:/home/bonanza/EE538/fall24-project-unswimmingduck/input/topologicalsort_dependencies.csv
*************************Results******************************
Topological Sorting Results:
Ralphs
KFC
Chick-fil-A
Arco
Chase
Ross
Target
Trader Joes
Chipotle
Pico
**************************************************************
Time taken by function: 6 ms
```
### Runtime Complexity
Due to this function using DFS to iterate all the possible topological order, **assume the number of input locations is n and the RunTime Complexity is O(n).**


## Item 9: The Traveling Trojan Problem (AKA Traveling Salesman!) 
### Function Description
In this section, we assume that we are using a UAV which means we can fly directly from 1 point to another point. Given a vector of location ids, assume every location can reach all other locations in the vector (i.e. assume that the vector of location ids is a complete graph).
Find the shortest route that covers all the locations exactly once and goes back to the start point. 

```c++
std::pair<double, std::vector<std::vector<std::string>>> TravelingTrojan_Brute_force(
      std::vector<std::string> location_ids);
```
```c++
std::pair<double, std::vector<std::vector<std::string>>> TravelingTrojan_Backtracking(
      std::vector<std::string> location_ids);
```

### Implementation
#### BruteForce Method
In BruteForce Method, I use DFS algorithm and recursion to implement this function. The DFS iterate all the possible cycle path and find the minimum distance. The detail of how the DFS works is showed in the belowing picture.
![image](https://github.com/user-attachments/assets/97637064-e8b4-4aa9-8ef7-7e30dc4826c7)

#### BruteForce with Backtracing Method
With backtracing, I add one more comparing condition in recursion base case. In DFS algorithm, I will compare current path distances with the current minimum distance. If the current path distance is larger thant the current minimum distance, it is unecessary to iterate more path. The working detail of this method is shown in the belowing picture.
![image](https://github.com/user-attachments/assets/c1c2e58a-f8fc-4d4f-abff-e24d3052eefa)

#### 2-opt Method
The core of 2-opt method is changing the edge. In every iteration, we will change two edges and see if the distance of the path will be shrinked or not. If the distance will decrease, we make the change and still do the operation of changing edge until the distance dosen't decreas anymore. The mechanism detail of this method is shown in the belowing picture.
![image](https://github.com/user-attachments/assets/76ffe923-6aed-4687-85f1-3602dd89cbf3)

### Result

| Number of node      | BruteForce | BruteForce with Backtracing| 2-opt|
| -------------------- | ----------- |-------|-----|
|    7| 	13 ms	| 	11 ms	   |   0 ms  |
|8|51 ms| 21 ms| 1ms
|9| 369 ms| 90 ms | 1 ms
|10|3277 ms| 935 ms| 1 ms
|11|34878 ms|1806 ms| 4 ms

## Item 10: Find Nearby
### Function Description
Given an attribute name `C`, a location name `L` and a number `r` and `k`, find at most `k` locations in attribute `C` on the map near `L`(do not include `L`) with the range of `r` and return a vector of string ids. 

The order of locations should be from
nearest to farthest, and you should not include the current location. 

```c++
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k);
```

### Implementation
In order to get the location that has same attribute with input c, we should has a map that stores the attribute and its relative location. Then, iterating all nodes that has the same attribute with input ``c`` and caculating the distance between the node and ``c``. If the distance smaller than ``r``, inserting the node into a priority queue and output the node at the last of the function.

### RunTime Complexity
**The RunTime Complexity is O(n), n is the number of the data.** This is because we need iterate all locations to get the target locations that share same attribute with ``c``.

### Result
![image](https://github.com/user-attachments/assets/5ae87354-51bc-4ac7-8053-9e8d7121fb28)




## Item 11: Find the Shortest Path to Visit All locations (Phase 3)
### Function Description
Given an vector of locations, you need to find the shortest path to visit all the locations.

```c++
std::vector<std::string> TrojanMap::TrojanPath(std::vector<std::string> &location_names)
```

### Implementation
In order to finding the shortest path, I using DFS algorithm to achieve this goal. Using recurrsion to finding all possible paths and finding the shortest distance path. What's more, I also apply backtracing to cutting branches and shrink the runtime.

### Runtime Report
![image](https://github.com/user-attachments/assets/0c081f38-ddce-49a6-bbd2-ada8e9948d06)


### Result 
![c71fac6f1b89ae9994778c5d3fb9c38](https://github.com/user-attachments/assets/ba333066-22be-4b50-837e-a7d61227e419)
![10d2c59a12ee443f94e7a6426f6298c](https://github.com/user-attachments/assets/67b63b91-6cd5-4d39-8fd9-6b8d9bd08a10)
![7abb2f082de4a7fa2dcd515ef8609e9](https://github.com/user-attachments/assets/f6ec3039-5afc-40f3-8121-48d3342a0d49)


## Item 12: Check the existence of the path with a constrained gas 
### Function Description
Given a map of nodes, you need to determine if it is possible to travel from a given starting point to a destination point with a car that has a certain size of gas tank. You can refuel at any nodes. If the distance between any two nodes on the path is larger than the size of the gas tank, you cannot travel between those nodes. Assume 1 gallon of gas can travel 1 mile.

### Implementation
I using **unionFind** to accomplish this function. The detail of unionfnd is below.
```c++
class unionfind_gas{
    public:
        int* root_;			// root array
        int* childSize_;	// store the size of childnode for current node
        int size_;			// the total node in unionfind
        
        unionfind_gas(int size);
        unionfind_gas(){
            root_ = nullptr;
            childSize_ = nullptr;
        }

        ~unionfind_gas(){
            // delete the pointers
            delete root_;
            root_ = nullptr;
            delete childSize_;
            childSize_ = nullptr;
        }

        void unit(int p, int q);

        int find(int p);

        bool same_union(int p, int q);
};
```
In the function, we will iterate all the location and caculate the distance between the node and all its neighbors' nodes. If the distance is smaller than the gas volum, we put two nodes in the same unit. After iterating all nodes, we find if the start node and destination node has the same root. If the two nodes has same root, it means that the two node is accessible using the gas volum. The more detail explain is shown on belowing picture.
![image](https://github.com/user-attachments/assets/f81d6c7a-666a-4e17-86cc-c61b2792c227)

### RunTime Complexity
Assume that the number of data is n, **the Runtime Complexity is O(n)**. This is because the function should iterate all nodes and use unionfind to store their relationship

### RunTime Report
![image](https://github.com/user-attachments/assets/de7b8ecb-65dc-4b7f-8baa-942a1cbc8ef0)

