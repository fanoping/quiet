#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QObject>
#include <QtWidgets>

class ImageViewer : public QObject
{
    Q_OBJECT
public:
    explicit ImageViewer(QObject *parent = 0);

signals:


};

#endif // IMAGEVIEWER_H
