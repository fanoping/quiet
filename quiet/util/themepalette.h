#ifndef THEME_H
#define THEME_H

#include <QColor>
#include <QDebug>

#include "util/constants.h"


class ThemePalette
{
public:
    ThemePalette();
    ThemePalette(Theme theme);

    // Theme settings
    void setTheme(Theme theme);
    Theme getTheme() { return m_theme; }


    // For individual widget background color (widget background, slider  etc.)
    QColor primaryBackground;
    QColor secondaryBackground;
    QColor tertiaryBackground;


    // For Text, Icons,  Foreground Items
    QColor primaryLabel;
    QColor secondaryLabel;
    QColor tertiaryLabel;
    QColor quaternaryLabel;

    // For Text Field Text
    QColor placeholderLabel;

    // Main Theme Color (Tint)
    QColor themeColor;

    // ShadowColor (Gray)
    QColor shadowColor;

private:
    Theme m_theme;

    void setupColor();
};

#endif // THEME_H
