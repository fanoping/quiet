#ifndef NODE_H
#define NODE_H

#include <QList>
#include <QMap>
#include <QDebug>
#include "stdint.h"
#include <iomanip>
#include <iostream>
#include <sstream>

class Node
{
public:
    Node();
    ~Node();

    // flags
    bool isValid();
    bool isCached();
    void setValid();
    void setCached();


    // hash key getter
    uint8_t key();

    // node getters / setters
    void setParent(Node* node) { parent = node; }
    Node* getParent() { return parent; }

    // clear child
    void clear();

    void insert(QString str);
    QList<QString> traverse(); //preorder output
    bool search(QString& queryString, Node*& queryNode);


    // for debug
    void print(int level=1);

private:
    Node* parent;
    QMap<uint8_t, Node*> children;

    // contents
    /*
     * Content storage format (m_value):
     *
     *       bit                   7           6         5-0
     *       usage         cache   valid   hashKey
     *
     */
    uint8_t  m_value;

};

#endif // NODE_H
