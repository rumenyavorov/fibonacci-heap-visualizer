#include "FibonacciHeap.h"

namespace fib_heap
{

const int FibonacciHeap::m_minimumKey = 0x80000000; // the minimum int value

FibonacciHeapNode* FibonacciHeap::insert(int newKey)
{
    FibonacciHeapNode* newNode = _create_node(newKey);
    _insert_node(newNode);
    return newNode;
}

void FibonacciHeap::merge(FibonacciHeap &another)
{
    m_minNode = _merge(m_minNode, another.m_minNode);
    m_numOfNodes += another.m_numOfNodes;
    another.m_minNode = nullptr; // so that another
    another.m_numOfNodes = 0;
}

int FibonacciHeap::extract_min()
{
    FibonacciHeapNode* minNode = _extract_min_node();
    int ret = minNode->key;
    delete minNode;
    return ret;
}

void FibonacciHeap::decrease_key(FibonacciHeapNode* x, int newKey)
{
    _decrease_key(x, newKey);
}

void FibonacciHeap::delete_node(FibonacciHeapNode* x)
{
    _decrease_key(x, m_minimumKey);
    extract_min();
}

string FibonacciHeap::getNodeKeys() const
{
    string result;
    if (m_minNode != nullptr) {
        _traverseNodes(m_minNode, result);
    }
    return result;
}

void FibonacciHeap::clear()
{
    _clear(m_minNode);
    m_minNode = nullptr;
    m_numOfNodes = 0;
}

FibonacciHeapNode* FibonacciHeap::_create_node(int newKey)
{
    FibonacciHeapNode* newNode = new FibonacciHeapNode;
    newNode->key = newKey;
    newNode->left = newNode;
    newNode->right = newNode;
    newNode->parent = nullptr;
    newNode->child = nullptr;
    newNode->degree = 0;
    newNode->mark = false;
    return newNode;
}


void FibonacciHeap::_insert_node(FibonacciHeapNode* newNode)
{
    m_minNode = _merge( m_minNode, newNode);
    m_numOfNodes++;
}


/*******************************************************************
* Remove x from its circular list
* Without changing the content of x
* Without freeing x's memory space
*******************************************************************/
void FibonacciHeap::_remove_from_circular_list(FibonacciHeapNode* x)
{
    if (x->right == x)
        return;
    FibonacciHeapNode* leftSib = x->left;
    FibonacciHeapNode* rightSib = x->right;
    leftSib->right = rightSib;
    rightSib->left = leftSib;
    x->left = x->right = x;
}


FibonacciHeapNode* FibonacciHeap::_merge(FibonacciHeapNode* a, FibonacciHeapNode* b)
{
    if(a == nullptr)
        return b;
    if(b == nullptr)
        return a;
    if( a->key > b->key ) // swap node
    {
        FibonacciHeapNode* temp = a;
        a = b;
        b = temp;
    }
    FibonacciHeapNode* aRight = a->right;
    FibonacciHeapNode* bLeft	= b->left;
    a->right = b;
    b->left = a;
    aRight->left = bLeft;
    bLeft->right = aRight;
    return a;
}


/***********************************************************
 * Rearrange the heap
 * Update the m_minNode
 * Return the current minimum node
***********************************************************/
FibonacciHeapNode* FibonacciHeap::_extract_min_node()
{
    FibonacciHeapNode* mn = m_minNode;
    if (mn == nullptr){
        return nullptr;
    }
    _unparent_all(mn->child);
    _merge(mn, mn->child);
    if (mn == mn->right){
        m_minNode = nullptr;
    }else{
        m_minNode = mn->right;
    }
    _remove_from_circular_list(mn);
    if (m_minNode != nullptr){
        _consolidate();
    }
    m_numOfNodes--;
    return mn;
}

/*make all nodes' parent nullptr in a circular list*/
void FibonacciHeap::_unparent_all(FibonacciHeapNode* x)
{
    if(x == nullptr)
        return;
    FibonacciHeapNode* y = x;
    do {
        y->parent = nullptr;
        y = y->right;
    }while(y != x);
}


void FibonacciHeap::_consolidate()
{
    int Dn = (int)(log2(m_numOfNodes) / log2(1.618));
    FibonacciHeapNode** A = new FibonacciHeapNode*[Dn + 1];
    for(int i = 0; i < Dn + 1; i++){
        A[i] = nullptr;
    }
    vector<FibonacciHeapNode*> nodeList;
    auto node = m_minNode;
    do{
        nodeList.emplace_back(node);
        node = node->right;
    } while (node != m_minNode);
    for (auto e: nodeList){
        int d = e->degree;
        _remove_from_circular_list(e);
        while(A[d] != nullptr){
            auto tmp = A[d];
            if (e->key > tmp->key){
                swap(e, tmp);
            }
            _make_child(tmp, e);
            A[d++] = nullptr;
        }
        A[e->degree] = e;
        m_minNode = e;
    }
    for (int i = 0; i < Dn + 1; i++){
        if (A[i] != nullptr && A[i] != m_minNode){
            _merge(m_minNode, A[i]);
        }
    }
    FibonacciHeapNode* flag = m_minNode;
    FibonacciHeapNode* iter = flag;
    do{
        if (iter->key < m_minNode->key){
            m_minNode = iter;
        }
        iter = iter->right;
    } while (iter != flag);
    delete []A;
}


void FibonacciHeap::_make_child(FibonacciHeapNode *child, FibonacciHeapNode *parent)
{
    child->parent = parent;
    parent->child = _merge(parent->child, child);
    parent->degree++;
    child->mark = false;
}

void FibonacciHeap::_decrease_key(FibonacciHeapNode* x, int newKey)
{
    x->key = newKey;
    FibonacciHeapNode* y = x->parent;
    if ( y != nullptr && x->key < y->key )
    {
        _cut(x, y);
        _cascading_cut(y);
    }
    if (x->key < m_minNode->key)
        m_minNode = x;
}

void FibonacciHeap::_traverseNodes(FibonacciHeapNode* start, std::string& result) const
{
    FibonacciHeapNode* current = start;
    do {
        if (!result.empty()) {
            result += ", ";
        }
        result += std::to_string(current->key);
        if (current->child != nullptr) {
            _traverseNodes(current->child, result);  // Recursive call for children
        }
        current = current->right;
    } while (current != start);
}

/***********************************************************************
* Remove x from the child list of y, decrement y->degree
* Add x to the root list, make its parent NULL
* And clear the mark of x
***********************************************************************/
void FibonacciHeap::_cut(FibonacciHeapNode* x, FibonacciHeapNode* y)
{
    y->child = (x == x->right ? nullptr : x->right);
    _remove_from_circular_list(x);
    y->degree--;
    _merge(m_minNode, x);
    x->parent = nullptr;
    x->mark = false;
}

/***********************************************************************
* Continue cutting on the path from the decreased node to the root
    Until meet one node, which is a root or is unmarked
***********************************************************************/
void FibonacciHeap::_cascading_cut(FibonacciHeapNode* y)
{
    FibonacciHeapNode* z = y->parent;
    if ( z != nullptr)
    {
        if( y->mark == false)
            y->mark = true;
        else
        {
            _cut(y,z);
            _cascading_cut(z);
        }
    }
}


/*********************************************************************
* t1 is used to traversal the circular list.
  When t1 == x for the second time (the first time is at t1's initialization),
  t1 has completed the traversal.
**********************************************************************/
void FibonacciHeap::_clear(FibonacciHeapNode* x)
{
    if (x != nullptr) {
        FibonacciHeapNode* curr = x;
        do {
            FibonacciHeapNode* delNode = curr;
            curr = curr->right;
            if (delNode->child != nullptr) {
                _clear(delNode->child);
            }
            delete delNode;
        } while (curr != x);
    }
}

void FibonacciHeap::addChildren(FibonacciHeapNode* current, VisualNode* parentVisualNode, std::vector<VisualNode*>& result) const
{
    if (!current) return;

    FibonacciHeapNode* startNode = current;
    do {
        VisualNode* visualNode = new VisualNode(current->key, current->degree, current->id);
        if (parentVisualNode) {
            parentVisualNode->addChild(visualNode);
        } else {
            result.push_back(visualNode);
        }

        if (current->child) {
            addChildren(current->child, visualNode, result);
        }

        current = current->right;
    } while (current != startNode);
}

FibonacciHeapNode* FibonacciHeap::findNode(int key) const
{
    return _findNode(m_minNode, key);
}

FibonacciHeapNode* FibonacciHeap::_findNode(FibonacciHeapNode* start, int key) const
{
    if (start == nullptr) {
        return nullptr;
    }

    FibonacciHeapNode* current = start;
    do {
        if (current->key == key) {
            return current;
        }
        if (current->child != nullptr) {
            FibonacciHeapNode* found = _findNode(current->child, key);
            if (found != nullptr) {
                return found;
            }
        }
        current = current->right;
    } while (current != start);

    return nullptr;
}


std::vector<VisualNode*> FibonacciHeap::getVisualNodes() const
{
    std::vector<VisualNode*> result;
    if (!m_minNode) return result;

    //start with the minimum node and iterate over the root list
    FibonacciHeapNode* current = m_minNode;
    do {
        VisualNode* visualNode = new VisualNode(current->key, current->degree, current->id);
        result.push_back(visualNode);

        if (current->child) {
            addChildren(current->child, visualNode, result);
        }

        current = current->right;
    } while (current != m_minNode);

    //mark the min node
    for (VisualNode* node : result) {
        if (node->key() == m_minNode->key) {
            node->setIsMin(true);
        }
    }

    return result;
}
}
