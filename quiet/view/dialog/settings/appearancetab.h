#ifndef APPEARANCETAB_H
#define APPEARANCETAB_H

#include <QObject>
#include <QTableWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

class AppearanceTab : public QWidget
{
    Q_OBJECT
public:
    explicit AppearanceTab(QWidget *parent = 0);
    ~AppearanceTab();

private:
    QFormLayout m_layout;

    QLineEdit* lineEdit;
    QLineEdit* lineEdit2;

    void initAttributes();
    void initLayout();

signals:

public slots:
};

#endif // APPEARANCETAB_H
