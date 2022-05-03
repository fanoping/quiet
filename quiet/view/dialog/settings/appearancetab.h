#ifndef APPEARANCETAB_H
#define APPEARANCETAB_H

#include <QObject>
#include <QTableWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDebug>

#include "settings.h"

class AppearanceTab : public QWidget
{
    Q_OBJECT
public:
    explicit AppearanceTab(QWidget *parent = 0);
    ~AppearanceTab();

private:
    QFormLayout m_layout;

    QComboBox* m_appearanceSelection;

    void initAttributes();
    void initLayout();
    void initConnect();

signals:

public slots:

};

#endif // APPEARANCETAB_H
