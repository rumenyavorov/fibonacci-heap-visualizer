#ifndef VISUALNODE_H
#define VISUALNODE_H

#include <QObject>
#include <QList>

class VisualNode : public QObject {
    Q_OBJECT
    Q_PROPERTY(int key READ key CONSTANT)
    Q_PROPERTY(int degree READ degree CONSTANT)
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QList<QObject*> children READ children NOTIFY childrenChanged)
    Q_PROPERTY(bool isMin READ isMin WRITE setIsMin NOTIFY isMinChanged)

public:
    VisualNode(int key, int degree, int id, QObject *parent = nullptr);

    int key() const;
    int degree() const;
    int id() const;
    bool isMin() const;
    QList<QObject*> children() const;

    void setIsMin(bool value);
    void addChild(VisualNode* child);

signals:
    void childrenChanged();
    void isMinChanged();

private:
    int m_key;
    int m_degree;
    int m_id;
    bool m_isMin;
    QList<QObject*> m_children;
};

#endif // VISUALNODE_H
