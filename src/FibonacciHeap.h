#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include <cmath>
#include <string>
#include <vector>
using namespace std;

namespace fib_heap{

struct FibonacciHeapNode {
    int key;
    FibonacciHeapNode* left;
    FibonacciHeapNode* right;
    FibonacciHeapNode* parent;
    FibonacciHeapNode* child;
    int degree;
    bool mark;
    int id;
};

class FibonacciHeap {
public:
    FibonacciHeapNode* m_minNode;
    int m_numOfNodes;

    FibonacciHeap(){  // initialize a new and empty Fib Heap
        m_minNode = nullptr;
        m_numOfNodes = 0;
    }

    ~FibonacciHeap() {
        _clear(m_minNode);
    }

    /* Insert a node with key value new_key
       and return the inserted node*/
    FibonacciHeapNode* insert(int newKey);

    /* Merge current heap with another*/
    void merge(FibonacciHeap &another);

    /* Return the key of the minimum node*/
    int  extract_min();

    /* Decrease the key of node x to newKey*/
    void decrease_key(FibonacciHeapNode* x, int newKey);

    /*Delete a specified node*/
    void delete_node(FibonacciHeapNode* x);

    string getNodeKeys() const;

    void clear(); // Method to clear the heap


    // private:
    static const int m_minimumKey;
    FibonacciHeapNode* _create_node(int newKey);
    void _insert_node(FibonacciHeapNode* newNode);
    void _remove_from_circular_list(FibonacciHeapNode* x);
    FibonacciHeapNode* _merge(FibonacciHeapNode* a, FibonacciHeapNode* b);
    void _make_child(FibonacciHeapNode *child, FibonacciHeapNode *parent);
    void _consolidate();
    void _unparent_all(FibonacciHeapNode* x);
    FibonacciHeapNode* _extract_min_node();
    void _decrease_key(FibonacciHeapNode* x, int newKey);
    void _cut(FibonacciHeapNode* x, FibonacciHeapNode* y);
    void _cascading_cut(FibonacciHeapNode* y);
    void _clear(FibonacciHeapNode* x);
    void _traverseNodes(FibonacciHeapNode* start, string& result) const;

};

}

#endif // FIBONACCIHEAP_H
