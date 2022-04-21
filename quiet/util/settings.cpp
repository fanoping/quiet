#include "settings.h"

Settings* g_settingsManager = nullptr;

Settings::Settings(QObject *parent) : QObject(parent)
{
    m_themePalette = ThemePalette(THEME_DARK);
//    m_themePalette = ThemePalette(THEME_LIGHT);
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
