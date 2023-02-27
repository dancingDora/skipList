#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

//class skipNode : key, value(T), next(vector<skipNode *>)
template<class T>
struct skipNode{
    int key;
    T val;
    vector <skipNode *> next;
    skipNode(int k, T v, int level) : key(k), val(v) {
        for(int i = 0; i < level; i++)
            next.push_back(nullptr);
    }
};

