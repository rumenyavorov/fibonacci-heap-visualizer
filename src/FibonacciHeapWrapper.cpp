#include "FibonacciHeapWrapper.h"
#include <algorithm>

FibonacciHeapWrapper::FibonacciHeapWrapper(QObject *parent) : QObject(parent){}

void FibonacciHeapWrapper::insert(int value)
{
    fibHeap.insert(value);
    emit nodesChanged();
}

void FibonacciHeapWrapper::removeSmallest()
{
    fibHeap.extract_min();
    emit nodesChanged();
}

void FibonacciHeapWrapper::clearHeap()
{
    fibHeap.clear();
    emit nodesChanged();
}

void FibonacciHeapWrapper::decreaseKey(int from, int to)
{
    fib_heap::FibonacciHeapNode* node = fibHeap.findNode(from);
    if (node != nullptr) {
        fibHeap.decrease_key(node, to);
        emit nodesChanged();
    }
}

void FibonacciHeapWrapper::deleteNode(int value)
{
    fib_heap::FibonacciHeapNode* node = fibHeap.findNode(value);
    if (node != nullptr) {
        fibHeap.delete_node(node);
        emit nodesChanged();
    }
}

QString FibonacciHeapWrapper::getCurrentNodes() const
{
    return QString::fromStdString(fibHeap.getNodeKeys());
}

QList<QObject*> FibonacciHeapWrapper::getNodes() const
{
    auto nodes = fibHeap.getVisualNodes();
    QList<QObject*> qNodes;
    for (VisualNode* node : nodes) {
        qNodes.append(node);
    }
    reverse(qNodes.begin(), qNodes.end()); // Reverse the QList

    return qNodes;
}
