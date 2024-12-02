/*
    all the code is indepently written by Yiheng Zhou (https://github.com/unswimmingduck)
*/
#include "trietree.h"


TrieTree::~TrieTree(){
    destroy(node_);
}

/**
 * destory(): this function is the helper function of ~TrieTree
 * Implement: we using recursion and DFS to implement this function. 
 *            In this function, we can iterate all nullptr pointers and avoid memory leak
 */
void TrieTree::destroy(TrieNode* node){
    // base case
    if(node == nullptr){
        return ;
    }

    // iterate all child node
    for(int i=0; i<67; i++){
        destroy(node->child_[i]);
    }

    // release the memeory
    delete node;
    node = nullptr;

}

/**
 * insert() : this function is used to insert all the data of name to a multiple branches TrieTree
 * Implement: using for loop to iterate every char in the string and according the hashset chatId_ to get the unique id of the char 
 */
void TrieTree::insert(std::string name, std::string id){
    TrieNode* tmp = node_;

    for(char c: name){
        int id = charId_[std::tolower(c)];
        if(tmp->child_[id] == nullptr){
            tmp->child_[id] = new TrieNode();
        }
        tmp = tmp->child_[id];
    }

    tmp->endFlag_ = true;
    tmp->endId_.push_back(id);
}

/**
 * find(): This function is used to find the all string that similar to the input name
 * Implement: 1. It will iterate all the input name and find the correct node level
 *            2. Using BFS to get the all possible similar name 
 */
std::vector<std::string> TrieTree::find(std::string name){
    
    // std::cout<< "the find fucntion is called " << " the input name: " << name << std::endl;

    std::vector<std::string> res;

    // std::cout<< "the vectore res" << std::endl;

    TrieNode* tmp = node_;

    // std::cout<< "the tmp node" << std::endl;

    // std::cout << "the current level node is " << tmp <<std::endl; 

    // std::cout<< "the length of the name is: " << name.size() << std::endl;

    // std::cout<< "the id of e is " << charId_[std::tolower('e')] << std::endl;

    // using for loop to get the correct level node
    for(char c: name){
        // std::cout << "the split letter is " << c << std::endl;
        int id = charId_[std::tolower(c)];
        // std::cout << "the char id is " << id << std::endl;
        if(tmp->child_[id] ==nullptr){
            // std::cout << "the char " << c << " is not load in the charId";
            return res;
        }
        tmp = tmp->child_[id];
    }

    bfs_find(tmp, &res);
    
    return res;
}

/**
 * bfs_find(): This function is using BFS to get all the similar name
 * Implement:   1. it will iterate all the 67 nodes and push the not nullptr pointer in the queue
 *              2. pop() all the pointer in the queue and iterate all the possible pointer
 *              3. if the node pointer endFlag_ = True, we will add the vector endId_ to the result vector
 *              4. return the all targetId_ in the result vector
 */
void TrieTree::bfs_find(TrieNode* node, std::vector<std::string>* result){

    std::queue<TrieNode*> q;
    
    // initialize the queue
    for(int i=0; i<67; i++){
        if(node->child_[i] != nullptr){
            q.push(node->child_[i]);
        }
    }

    // BFS
    while(!q.empty()){
        // Get the first element
        TrieNode* curNode = q.front();
        q.pop();
        
        if(curNode->endFlag_ == true){
            result->insert(result->end(), curNode->endId_.begin(), curNode->endId_.end());
        }

        // broad search
        for(int i=0; i<67; i++){
            if(curNode->child_[i] != nullptr){
                q.push(curNode->child_[i]);
            }
        }
    }

}