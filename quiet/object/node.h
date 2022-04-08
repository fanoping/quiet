#ifndef NODE_H
#define NODE_H

#include <QList>

class Node
{
public:
    Node();

    Node* next();
    Node* prev();

private:
    Node* parent;
    QList<Node*> children;

    // contents
    char m_value;

};

#endif // NODE_H
