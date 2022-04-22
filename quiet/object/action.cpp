#include "action.h"


Action::Action(const QString &name, const QIcon &icon, const QString &text, QObject *parent):
    QAction(icon, text, parent),
    m_name(name)
{

}

Action::Action(const QString &name, const QString &text, QObject *parent):
    QAction(text, parent),
    m_name(name)
{

}

Action::Action(const QString &name, QObject *parent):
    QAction(name, parent),
    m_name(name)
{

}

Action::Action(QObject *parent):
    QAction(parent)
{

}

Action::~Action()
{

}
