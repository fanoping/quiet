#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDebug>

#include "util/themepalette.h"

class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings* getInstance();
    ~Settings();

    const ThemePalette& themePalette() const;

private:
    explicit Settings(QObject *parent = 0);

    ThemePalette m_themePalette;

signals:

public slots:
};

extern Settings* g_settingsManager;

#endif // SETTINGS_H
