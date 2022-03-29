#ifndef CONTEXTMENUITEM_H
#define CONTEXTMENUITEM_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>

#include "model/actionmanager.h"

class ContextMenuItem : public QWidget
{
    Q_OBJECT
public:
    explicit ContextMenuItem(QWidget *parent = 0);

    void setAction(QString actionName) {_actionName = actionName;}
    void setText(QString actionDisplayName) { _actionLabel.setText(actionDisplayName); }
    void setShortCutText(QString actionName) { Q_UNUSED(actionName); /*TODO*/ }

private:
    QString _actionName;

    QLabel _actionLabel;
    QLabel _shortcutLabel;


//    QString _actionName;
//    QString _actionDisplayName;

    QHBoxLayout _layout;

    void connectAction();

signals:
    void onPressed(const QString&);

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent* event);
};

#endif // CONTEXTMENUITEM_H
