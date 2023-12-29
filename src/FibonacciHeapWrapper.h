#ifndef FIBONACCIHEAPWRAPPER_H
#define FIBONACCIHEAPWRAPPER_H

#include <QObject>
#include <QString>
#include "FibonacciHeap.h"

class FibonacciHeapWrapper : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentNodes READ getCurrentNodes NOTIFY nodesChanged)

public:
    explicit FibonacciHeapWrapper(QObject *parent = nullptr);

    Q_INVOKABLE void insert(int value);
    Q_INVOKABLE void removeSmallest();
    Q_INVOKABLE void clearHeap();
    Q_INVOKABLE QString getCurrentNodes() const;

signals:
    void nodesChanged();

private:
    fib_heap::FibonacciHeap fibHeap;
};

#endif // FIBONACCIHEAPWRAPPER_H
