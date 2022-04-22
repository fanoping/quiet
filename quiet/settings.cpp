#include "settings.h"

Settings* g_settingsManager = nullptr;

Settings::Settings(QObject *parent) : QObject(parent)
{
    m_themePalette = ThemePalette(THEME_DARK);
//    m_themePalette = ThemePalette(THEME_LIGHT);
    m_supportedFormats = QImageReader::supportedImageFormats();
    m_supportedFormats.removeAll("pdf");
    qDebug() << supportedFormatStr();
}

Settings::~Settings()
{

}

Settings* Settings::getInstance()
{
    if(!g_settingsManager) {
        g_settingsManager = new Settings();
    }
    return g_settingsManager;
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
