#include "themepalette.h"

ThemePalette::ThemePalette():
    m_theme(THEME_DARK)
{
    setupColor();
}

ThemePalette::ThemePalette(Theme theme):
    m_theme(theme)
{
    qDebug() << "theme check" <<(m_theme == THEME_DARK);
    setupColor();
}

void ThemePalette::setTheme(Theme theme)
{
    m_theme = theme;
    setupColor();
}

void ThemePalette::setupColor()
{
    // Ref: https://sarunw.com/posts/dark-color-cheat-sheet/
    // Using Grouped ones

    // Note - it is in ARGB not RGBA

    switch(m_theme) {
    case THEME_DARK:
        primaryBackground      = "#FF000000";
        secondaryBackground = "#FF1C1E1E";
        tertiaryBackground       = "#FF2C2C2E";

        primaryLabel                   = "#FFFFFFFFF";
        secondaryLabel              = "#99EBEBF5";
        tertiaryLabel                    = "#4DEBEBF5";
        quaternaryLabel             = "#2EEBEBF5";

        placeholderLabel            = "#4DEBEBF5";

        themeColor                      = "#FF30D158";

        shadowColor                   = "#990D0D0D";
        break;
    case THEME_LIGHT:
        primaryBackground      = "#FFF2F2F7";
        secondaryBackground = "#FFFFFFFF";
        tertiaryBackground       = "#FFF2F2F7";

        primaryLabel                   = "#FF000000";
        secondaryLabel              = "#993C3C43";
        tertiaryLabel                    = "#4D3C3C43";
        quaternaryLabel             = "#2E3C3C43";

        placeholderLabel            = "#EBEBF54D";

        themeColor                      = "#FF34C759";

        shadowColor                   = "#EBDBDFDF";
        break;
    }
}
