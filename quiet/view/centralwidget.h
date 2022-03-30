#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QStackedWidget>
#include <QDebug>

#include <memory>  //TODO: handle include memory

#include "view/imagewidget.h"
#include "util/constants.h"


class CentralWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0);
    ~CentralWidget();

    void showImage(std::shared_ptr<QPixmap> image);


private:
    std::shared_ptr<ImageWidget> m_imageWidget;
    ViewLayer m_viewIndex;

signals:

public slots:
    void toggleWidget(ViewLayer viewIndex);

};

#endif // CENTRALWIDGET_H
