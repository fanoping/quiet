#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QStackedWidget>

#include <memory>  //TODO: handle include memory

#include "view/imagewidget.h"


class CentralWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0);

signals:

public slots:


private:
    std::shared_ptr<ImageWidget> imageWidget;
};

#endif // CENTRALWIDGET_H
