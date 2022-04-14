#ifndef NODE_H
#define NODE_H

#include <QList>
#include <QMap>
#include <QFileInfo>
#include <QDebug>
#include "stdint.h"
#include <iomanip>
#include <iostream>
#include <sstream>

#include "util/utils.h"

class Node
{
public:
    Node();
    ~Node();

    // Tree Structure Related
    // node getters / setters
    void setParent(Node* node) { parent = node; }
    Node* getParent() const { return parent; }

    // clear child
    void clear();

    QList<QString> traverse(); //preorder output
    bool search(QString& fileStr, Node*& queryNode);

    Node* insertChild(const uint8_t childChar);



    // for debug
    void print(int level=1);

    // Content Related
    // Flags from m_value
    bool isValid();
    bool isCached();
    void setValid();
    void setCached();

    // HashKey getter
    HashKey getHashKey() const;
    QFileInfo getFileInfo() const;

    void setHashKey(HashKey key);
    void setFileInfo(const QFileInfo& fileInfo);


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
    QFileInfo m_fileInfo;

};

#endif // NODE_H
