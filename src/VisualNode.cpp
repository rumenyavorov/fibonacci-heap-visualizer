#include "VisualNode.h"

VisualNode::VisualNode(int key, int degree, int id, QObject *parent)
    : QObject(parent), m_key(key), m_degree(degree), m_id(id), m_isMin(false) {}

int VisualNode::key() const {
    return m_key;
}

int VisualNode::degree() const {
    return m_degree;
}

int VisualNode::id() const {
    return m_id;
}

bool VisualNode::isMin() const {
    return m_isMin;
}

QList<QObject*> VisualNode::children() const {
    return m_children;
}

void VisualNode::setIsMin(bool value) {
    if (m_isMin != value) {
        m_isMin = value;
        emit isMinChanged();
    }
}

void VisualNode::addChild(VisualNode* child) {
    if (child) {
        m_children.append(child);
        emit childrenChanged();
    }
}
