#include "node.h"

Node::Node():
    parent(nullptr),
    m_value(0x0)
{

}

Node::~Node()
{

}

/*
 * Public Methods
 */

bool Node::isValid()
{
    return (0x1 << 6) & m_value;
}

bool Node::isCached()
{
    return (0x1 << 7) & m_value;
}

void Node::setValid()
{
    if(isValid()) {
        qDebug() << "File Exists Error";
        return;
    }

    m_value = m_value | (0x1 << 6);
}

void Node::setCached()
{
    if(isCached()) {
        qDebug() << "File Cached";
        return;
    }

    m_value = m_value | (0x1 << 7);
}

uint8_t Node::key()
{
    // return last 6 bits (key)
    return m_value & (0x3F);
}

void Node::clear()
{
    QMap<uint8_t, Node*>::iterator iter;
    for (iter = children.begin(); iter != children.end(); ++iter) {
         iter.value()->clear();
         delete iter.value();
    }
    children.clear();
}

void Node::insert(QString str)
{
    if(str.isEmpty()) {

        return;
    }
    uint8_t firstChar = str[0].toLatin1();

    if (!children.contains(firstChar)) {
        Node* newChild = new Node();
        children[firstChar] = newChild;
        newChild->setParent(this);
    }

    str.remove(0, 1);
     if(str.isEmpty()) {
         children[firstChar]->setValid();
     }
    children[firstChar]->insert(str);
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

bool Node::search(QString& queryString, Node *&queryNode)
{
     uint8_t firstChar = queryString[0].toLatin1();
     if (!children.contains(firstChar)) {
          return false;
     } else {
          queryString.remove(0, 1);
          if(queryString.isEmpty()) {
              queryNode = children[firstChar];
              return true;
          } else {
              return children[firstChar]->search(queryString, queryNode);
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


