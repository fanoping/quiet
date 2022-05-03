#ifndef CONSTANTS
#define CONSTANTS

enum ViewLayer {
    VIEW_IMAGE,
    VIEW_DIRECTORY
};

enum Edges {
    ALL,
    TOP,
    BOTTOM,
    LEADING,
    TRAILING,
    VERTICAL,
    HORIZONTAL
};

enum ScrollDirection {
    SCROLL_INWARDS,        // angle -120
    SCROLL_OUTWARDS    // angle +120
};

enum Theme {
    THEME_LIGHT,
    THEME_DARK
};

Q_DECLARE_METATYPE(Theme);

#endif // CONSTANTS

