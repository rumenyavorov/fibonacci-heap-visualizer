#include "FibonacciHeapWrapper.h"

FibonacciHeapWrapper::FibonacciHeapWrapper(QObject *parent) : QObject(parent) {
    // Initialization, if needed
}

void FibonacciHeapWrapper::insert(int value) {
    fibHeap.insert(value);
    emit nodesChanged();
}

void FibonacciHeapWrapper::removeSmallest() {
    fibHeap.extract_min();
    emit nodesChanged();
}

void FibonacciHeapWrapper::clearHeap() {
    fibHeap.clear();
    emit nodesChanged();
}

void FibonacciHeapWrapper::decreaseKey(int from, int to) {
    //TODO: Implement logic to decrease key
    emit nodesChanged();
}

void FibonacciHeapWrapper::deleteNode(int value) {
    //TODO: Implement logic to delete node
    emit nodesChanged();
}

QString FibonacciHeapWrapper::getCurrentNodes() const {
    return QString::fromStdString(fibHeap.getNodeKeys());
}

QList<QObject*> FibonacciHeapWrapper::getNodes() const {
    auto nodes = fibHeap.getVisualNodes();
    QList<QObject*> qNodes;
    for (VisualNode* node : nodes) {
        qNodes.append(node);
    }
    return qNodes;
}
