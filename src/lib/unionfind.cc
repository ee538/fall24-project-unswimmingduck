#include "unionfind.h"

unionFind::unionFind(int size){
    size_ = size;
    root_ = new int [size_];
    for(int i=0; i<size_; i++){
        root_[i] = i;
    }
}

int unionFind::find(int id){
    if(id<0 || id>=size_){
        return -1;
    }

    if(root_[id] == id){
        return id;
    }

    return find(root_[id]);
}


void unionFind::unit(int p, int q){
    // std::cout<< "set p: " << p <<" be the root of q: " << q << std::endl;
    if(flags.find(p) == flags.end()){
        flags.insert(p);
    }else{
        // std::cout << "The p: " << p << " has been set so we don't change it" << std::endl;
    }


    if(flags.find(q) == flags.end()){
        root_[q] = p;
        flags.insert(q);
        // std::cout<< "!!! we succssfully set p: " << p <<" be the root of q: " << q << std::endl;
    }
    else{
        //  std::cout << "The q: " << q << " has been set so we don't change it" << std::endl;
    }
    
    
}