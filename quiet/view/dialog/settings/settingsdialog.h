#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <memory>


#include "view/dialog/settings/appearancetab.h"


class SettingsDialog: public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    int exec() override;

private:
    QVBoxLayout m_layout;

    // Tabbar (QTabWidget)
    std::unique_ptr<QTabWidget> m_tabbar;
    std::unique_ptr<AppearanceTab> m_apperanceTab;

    void initAttributes();
    void initLayout();
};


#endif // SETTINGSDIALOG_H
