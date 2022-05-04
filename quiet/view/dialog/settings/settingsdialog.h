#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QStyleOption>
#include <QCloseEvent>
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
    // a main layout with nested two layout
    QVBoxLayout m_layout;

    // Buttons
    QHBoxLayout m_buttonLayout;
    QPushButton* m_buttonOK;
    QPushButton* m_buttonApply;
    QPushButton* m_buttonCancel;

    // Tabbar (QTabWidget)
    std::unique_ptr<QTabWidget> m_tabbar;
    std::unique_ptr<AppearanceTab> m_apperanceTab;

    void initAttributes();
    void initLayout();    
    void initConnect();

protected:
    void closeEvent(QCloseEvent* event) override;

signals:
    void settingsDialogClosed();

};


#endif // SETTINGSDIALOG_H
