#include "contextmenuitem.h"

ContextMenuItem::ContextMenuItem(QWidget *parent) : QWidget(parent)
{
    _layout.setContentsMargins(6, 0, 9, 0);
    // layout settings

    _actionLabel.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    _shortcutLabel.setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    _layout.addWidget(&_actionLabel);
    _layout.addWidget(&_shortcutLabel);

    setLayout(&_layout);

    // connect with action
    connectAction();
}


void ContextMenuItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        qDebug() << "action name" << _actionName << "pressed";
        QWidget::mousePressEvent(event);
        if(!_actionName.isEmpty()){
            emit onPressed(_actionName);
        }
    }
}




void ContextMenuItem::connectAction()
{
     connect(this, &ContextMenuItem::onPressed, g_actionManager, &ActionManager::actionReceived);
}
