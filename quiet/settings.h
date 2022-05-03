#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDebug>
#include <QImageReader>
#include <QSettings>
#include <memory>

#include "util/themepalette.h"
#include "util/constants.h"

// TODO: - move all modifiable params to QSettings for saving the state of the settings

class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings* getInstance();
    ~Settings();

    // Getters
    const ThemePalette& themePalette() const;
    const QString supportedFormatStr() const;
    const QString supportedFormatRegex() const;


private:
    explicit Settings(QObject *parent = 0);

    // TODO: - migrate this Section to Config
    ///////////////////////////////////////////////
    // Theme Palette, defines color etc...
    ThemePalette m_themePalette;
    ///////////////////////////////////////////////
    // Overall QSettings Config
    std::unique_ptr<QSettings> m_settingsConfig;

    // Supported Formats
    QList<QByteArray> m_supportedFormats;

    // Initialization
    void initAttributes();
    void initDefaults();

signals:
    // emit signals whenever any settings changed (i.e. received signals in slots)
    void settingsChanged();

public slots:
    // Settings From Settings Dialog
    // Setters
    void setThemePalette(int theme);

};

extern Settings* g_settingsManager;

#endif // SETTINGS_H
