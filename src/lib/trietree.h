#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>


class TrieNode{

    public:
        
        TrieNode* child_[67];
        bool endFlag_;
        std::vector<std::string> endId_;

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

#endif
