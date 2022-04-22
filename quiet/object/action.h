#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QAction>


class Action : public QAction
{
    Q_OBJECT
public:
    Action(const QString &name, const QIcon &icon, const QString &text, QObject *parent = nullptr);
    Action(const QString &name, const QString &text, QObject *parent = nullptr);
    Action(const QString &name, QObject *parent = nullptr);
    Action(QObject *parent = nullptr);
    ~Action();

    QString name() const { return m_name; }
    void setName(const QString& name) { m_name = name; }

private:
    QString m_name;
};

#endif // ACTION_H
