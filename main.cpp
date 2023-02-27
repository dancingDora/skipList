#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
//TODO::change the value of SKIP_LISTS_P & SKIP_LISTS_SIZE
const int SKIP_LISTS_SIZE = 1000;
const int SKIP_LISTS_P = 8;

using std::vector;
using std::cout;
using std::endl;
//class skipNode : key, value(T), next(vector<skipNode *>)
template<class T>
struct skipNode {
    int key;
    T val;
    vector<skipNode *> next;

    skipNode(int k, T v, int level) : key(k), val(v) {
        for (int i = 0; i < level; i++)
            next.push_back(nullptr);
    }
};

template<class T>
class skipList {
public:
    skipNode<T> *head;
    int maxLevel;
    const int minInt = std::numeric_limits<int>::min();
    const int maxInt = std::numeric_limits<int>::max();

public:
    skipList(int maxLevel, T initValue) : maxLevel(maxLevel) {
        head = new skipNode<T>(minInt, initValue, maxLevel);
        tail = new skipNode<T>(maxInt, initValue, maxLevel);

        for (int i = 0; i < maxLevel; i++)
            head->next[i] = tail;
    };

    ~skipList() {
        delete head;
        delete tail;
    };
    //p = 1/2
    int randomLevel() { // func random level
        int randomLevel = 1;
        double cal = randomLevel;
        while(random() % SKIP_LISTS_P == 0)
            randomLevel++;
        return (randomLevel < maxLevel) ? randomLevel : maxLevel;
    };




    skipNode<T> *insert(int k, T v) { // insert or update
        //get new node random level
        int x_level = randomLevel();
        skipNode<T> *newNode = nullptr;
        skipNode<T> *tmp = head;
        int tt;
        newNode = find(k, tt);
        // find() to judge the node exists, yep : update
        //                                  nope: insert
        if (newNode) {//then lets update
            newNode->val = v;
            return head;
        }
            //then lets insert
        newNode = new skipNode<T>(k, v, x_level);
        for (int i = x_level - 1; i > -1; i--) {
            //find the suit position to insert
            while (tmp->next[i] != nullptr && tmp->next[i]->key < k)
                tmp = tmp->next[i];
            newNode->next[i] = tmp->next[i];
            tmp->next[i] = newNode;
        }
        return head;
    };

    skipNode<T> *find(int k, int &cnt) {
        skipNode<T> * tmp = head;
        int currentLevel = nodeLevel(tmp->next);
        for(int i = (currentLevel - 1); i > -1 ;i--) {
            while (tmp->next[i] != nullptr && tmp->next[i]->key < k) {
                tmp = tmp->next[i];
                cnt++;
            }
        }
        tmp = tmp->next[0];
        if(tmp->key == k) return tmp;
        else return nullptr;
    };

    void printNode() {
        for(int i = 0; i < maxLevel; i++) {
            skipNode<T> * tmp = head;
            int lineLen = 1;
            if(tmp->next[i]->key != maxInt) {
                cout << "\n";
                cout << "This is level " << i << ":" << endl;
                cout << "{";

                while (tmp->next[i] != nullptr && tmp->next[i]->key != maxInt)
                {
                    cout << "(" << "Key: " << tmp->next[i]->key << ", ";
                    cout << "Value: " << tmp->next[i]->val << ")";

                    tmp = tmp->next[i];

                    if (tmp->next[i] != nullptr && tmp->next[i]->key != maxInt)
                    {
                        cout << ", ";
                    }

                    if (lineLen++ % 5 == 0) cout << "\n";
                }
                cout << "}" << "\n";
            }
        }
    };
private:
    skipNode<T> *tail;

    int nodeLevel(vector<skipNode<T> *> next) {
        int nodeLevel = 0;
        if (next[0]->key == maxInt)
            return 0;
        for (int i = 0; i < next.size(); i++)
            if (next[i] != nullptr && next[i]->key != maxInt)
                nodeLevel++;
            else break;
        return nodeLevel;
    }; // return max level
};
int main() {
    int maxLevel = 20;
    int search_time = 0;
    skipList<int> l(maxLevel, 0);
    for(size_t i = 0; i < SKIP_LISTS_SIZE; i++) {
        l.insert(i, i);
    }
    unsigned long search_time_storage = 0;
    for(int i = 0; i < 100000; i++) {
        int q = rand() % SKIP_LISTS_SIZE;
        l.find(q, search_time);
        search_time_storage += search_time;
//        cout << search_time_storage << endl;// cout debug
        search_time = 0;
    }
    double ans = double(double(search_time_storage) / 100000);
    cout << ans << endl;
//    int randomLevel = 1;
//    int ans[1000];
//    for(int i = 1; i < 1000; i++) {
//        ans[i] = rand() % 4;
//        cout << ans[i];
//    }
//    cout << endl;
//    int cnt = 1;
//    for(int i = 1; i < 100; i++) {
////        cout << ans[i];
//        while (ans[cnt++] == 0)
//            randomLevel++;
//        cout << randomLevel;
//        randomLevel = 1;
//    }
//    return 0;
}
