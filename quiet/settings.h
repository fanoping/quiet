#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDebug>
#include <QImageReader>

#include "util/themepalette.h"

class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings* getInstance();
    ~Settings();

    const ThemePalette& themePalette() const;
    const QString supportedFormatStr() const;
    const QString supportedFormatRegex() const;


private:
    explicit Settings(QObject *parent = 0);
    
    // Theme Palette, defines color etc...
    ThemePalette m_themePalette;

    // Supported Formats
    QList<QByteArray> m_supportedFormats;


signals:

public slots:
};

extern Settings* g_settingsManager;

#endif // SETTINGS_H
