#include <iostream>

class unionfind_gas{
    public:
        int* root_;
        int* childSize_;
        int size_;
        
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