#include "unionfind_gas.h"


unionfind_gas::unionfind_gas(int size){
    size_ = size;
    root_ = new int[size_];
    for(int i=0; i<size_; i++){
        root_[i] = i;
    }
    childSize_ = new int[size_] {1};
}


// using recursion to find the root 
int unionfind_gas::find(int p){
    if(root_[p] == p){
        return p;
    }
    return find(root_[p]);
}


// define the unit function
void unionfind_gas::unit(int p, int q){
    // find their roots respectively
    int p_root = find(p);
    int q_root = find(q);

    // assert their roots
    // if two nodes has the same root, it means that the two node can be achieved respecetively under current condition
    // and the fucntion of unit is to flag that the two nodes can be connected. So, if they have same node, we donot need any operation
    if(p_root != q_root){
        // then we should use size of the child to determine how to unit
        // nomarlly, we always unit the node which has smaller child into the node has larger child, becasue it can reduces the runtime
        if(childSize_[p_root] >= childSize_[q_root]){
            // update the childSize_
            childSize_[p_root] += childSize_[q_root];
            childSize_[q_root] = 0;
            // update the root
            root_[q_root] = p_root;
        }
        else{
            // update the childSize_
            childSize_[q_root] += childSize_[p_root];
            childSize_[p_root] = 0;
            // update the root
            root_[p_root] = q_root;
        }
    }

}


bool unionfind_gas::same_union(int p, int q){
    std::cout << "The root of " << p << " is " << find(p) << " the root of " << q << " is " << find(q) << std::endl;
    return find(p) == find(q);
}