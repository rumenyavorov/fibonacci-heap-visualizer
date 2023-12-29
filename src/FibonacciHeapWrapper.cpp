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

QString FibonacciHeapWrapper::getCurrentNodes() const {
    return QString::fromStdString(fibHeap.getNodeKeys());
}
