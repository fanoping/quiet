#include "settings.h"

Settings* g_settingsManager = nullptr;

Settings::Settings(QObject *parent) : QObject(parent)
{
    initAttributes();
    initDefaults();

//    m_themePalette = ThemePalette(THEME_DARK);
    m_themePalette = ThemePalette(THEME_LIGHT);

    m_supportedFormats = QImageReader::supportedImageFormats();
    m_supportedFormats.removeAll("pdf");
}

Settings::~Settings()
{
    m_settingsConfig.reset();
}

Settings* Settings::getInstance()
{
    if(!g_settingsManager) {
        g_settingsManager = new Settings();
    }
    return g_settingsManager;
}

void Settings::initAttributes()
{
   QSettings::setDefaultFormat(QSettings::NativeFormat);
}

void Settings::initDefaults()
{
    m_settingsConfig.reset(new QSettings());

    // Default Setups
    // Theme
    m_settingsConfig.get()->beginGroup("theme");
    int theme = m_settingsConfig.get()->value("theme", QVariant::fromValue(Theme::THEME_LIGHT)).toInt();
    m_settingsConfig.get()->endGroup();

    setThemePalette(theme);
}


const ThemePalette& Settings::themePalette() const
{
    return m_themePalette;
}

const QString Settings::supportedFormatStr() const
{
    QString filter;

    filter.append("Image Formats (");
    for(int idx=0; idx < m_supportedFormats.count(); ++idx) {

        filter.append("*." + QString::fromUtf8(m_supportedFormats.at(idx)) + ";");
    }
    filter.chop(1);
    filter.append(")");
    return filter;
}

const QString Settings::supportedFormatRegex() const
{
    QString filter;

    filter.append(".*\\.(");
    for(int idx=0; idx < m_supportedFormats.count(); ++idx) {
        filter.append(QString::fromUtf8(m_supportedFormats.at(idx)) + "|");
    }
    filter.chop(1);
    filter.append(")$");
    return filter;
}

void Settings::setThemePalette(int theme)
{

    switch (theme) {
    case THEME_LIGHT:
        m_themePalette.setTheme(THEME_LIGHT);
    case THEME_DARK:
        m_themePalette.setTheme(THEME_DARK);
    }

    emit settingsChanged();
}
