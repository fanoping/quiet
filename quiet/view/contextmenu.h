#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QWidget>
#include <QMenu>
#include <QDebug>
#include <QPainter>
#include <QAction>

namespace Ui {
class ContextMenu;
}

class ContextMenu : public QMenu
{
    Q_OBJECT

public:
    explicit ContextMenu(QWidget *parent = 0);
    ~ContextMenu();

private:
    Ui::ContextMenu *ui;

public slots:
    void showAt(QPoint pos);
    void setGeometry(QRect geo);

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // CONTEXTMENU_H
