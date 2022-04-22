#include "node.h"

Node::Node():
    parent(nullptr),
    m_value(0x0)
{

}

Node::~Node()
{
    for (QMap<uint8_t, Node*>::iterator iter = children.begin(); iter != children.end(); ++iter) {
         delete iter.value();
    }
}

/*
 * Public Methods
 */

void Node::clear()
{
    for (QMap<uint8_t, Node*>::iterator iter = children.begin(); iter != children.end(); ++iter) {
         iter.value()->clear();
         delete iter.value();
    }
    children.clear();
}

Node* Node::insertChild(const uint8_t childChar)
{
    Node* child;
    if(!children.contains(childChar)) {
        child = new Node();
        children[childChar] = child;
    } else {
        child = children[childChar];
    }
    return child;
}

QList<QString> Node::traverse()
{
     QMap<uint8_t, Node*>::iterator iter;
     QList<QString> result, tmp;

     for (iter = children.begin(); iter != children.end(); ++iter){
         tmp = iter.value()->traverse();

         for( int i=0; i< tmp.count(); ++i ) {
             tmp[i] = QString(QChar(iter.key())) + tmp[i];
         }
         if(iter.value()->isValid()) {
             tmp.insert(0, QString(QChar(iter.key())));
         }
         result.append(tmp);
     }
     return result;
}

bool Node::search(QString& str, Node *&queryNode)
{
     uint8_t firstChar = str[0].toLatin1();
     if (!children.contains(firstChar)) {
          return false;
     } else {
          str.remove(0, 1);
          if(str.isEmpty()) {
              queryNode = children[firstChar];
              return true;
          } else {
              return children[firstChar]->search(str, queryNode);
          }
     }

}

void Node::print(int level)
{
    QMap<uint8_t, Node*>::iterator iter;
    std::ostringstream oss;

    for (iter = children.begin(); iter != children.end(); ++iter){
        oss.str(""); oss.clear();
        oss << std::setw(3*level - 2) << std::setfill(' ') <<  (char) iter.key();
        if(iter.value()->isValid()) oss<< "*";
        qDebug() << oss.str().c_str();
        iter.value()->print(level+1);
    }
}

// Content Related

bool Node::isValid()
{
    return NODE_VALID & m_value;
}

bool Node::isCached()
{
    return NODE_CACHE & m_value;
}

void Node::setValid()
{
    if(isValid()) {
        qDebug() << "File Exists Error";
        return;
    }

    m_value = m_value | NODE_VALID;
}

void Node::setCached()
{
    if(isCached()) {
        qDebug() << "File Cached";
        return;
    }

    m_value = m_value | NODE_CACHE;
}

HashKey Node::getHashKey() const
{
    // return last 6 bits (key)
    return m_value & NODE_HASHKEY;
}

QFileInfo Node::getFileInfo() const
{
    return m_fileInfo;
}

void Node::setHashKey(HashKey key)
{
    m_value = (key & NODE_HASHKEY) | (m_value & 0xC0);
}

void Node::setFileInfo(const QFileInfo& fileInfo)
{
    m_fileInfo = fileInfo;
}




