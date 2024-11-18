#include <iostream>
#include <unordered_set>

class unionFind{
    public:
        int size_;
        int* root_;
        std::unordered_set<int> flags;
        
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