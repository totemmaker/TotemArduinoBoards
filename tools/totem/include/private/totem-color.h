/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_COLOR
#define INCLUDE_TOTEM_COLOR

namespace Color {
enum {
    // Red HTML Color Names
    IndianRed = 0xFFCD5C5C,
    LightCoral = 0xFFF08080,
    Salmon = 0xFFFA8072,
    Crimson = 0xFFDC143C,
    Red = 0xFFFF0000,
    FireBrick = 0xFFB22222,
    DarkRed = 0xFF8B0000,
    // Pink HTML Color Names
    Pink = 0xFFFFC0CB,
    LightPink = 0xFFFFB6C1,
    HotPink = 0xFFFF69B4,
    DeepPink = 0xFFFF1493,
    MediumVioletRed = 0xFFC71585,
    PaleVioletRed = 0xFFDB7093,
    // Orange HTML Color Names
    DarkSalmon = 0xFFE9967A,
    LightSalmon = 0xFFFFA07A,
    Coral = 0xFFFF7F50,
    Tomato = 0xFFFF6347,
    OrangeRed = 0xFFFF4500,
    DarkOrange = 0xFFFF8C00,
    Orange = 0xFFFFA500,
    // Yellow HTML Color Names
    Gold = 0xFFFFD700,
    Yellow = 0xFFFFFF00,
    LightYellow = 0xFFFFFFE0,
    LemonChiffon = 0xFFFFFACD,
    LightGoldenrodYellow = 0xFFFAFAD2,
    PapayaWhip = 0xFFFFEFD5,
    Moccasin = 0xFFFFE4B5,
    PeachPuff = 0xFFFFDAB9,
    PaleGoldenrod = 0xFFEEE8AA,
    Khaki = 0xFFF0E68C,
    DarkKhaki = 0xFFBDB76B,
    // Purple HTML Color Names
    Lavender = 0xFFE6E6FA,
    Thistle = 0xFFD8BFD8,
    Plum = 0xFFDDA0DD,
    Violet = 0xFFEE82EE,
    Orchid = 0xFFDA70D6,
    Fuchsia = 0xFFFF00FF,
    Magenta = 0xFFFF00FF,
    MediumOrchid = 0xFFBA55D3,
    MediumPurple = 0xFF9370DB,
    RebeccaPurple = 0xFF663399,
    BlueViolet = 0xFF8A2BE2,
    DarkViolet = 0xFF9400D3,
    DarkOrchid = 0xFF9932CC,
    DarkMagenta = 0xFF8B008B,
    Purple = 0xFF800080,
    Indigo = 0xFF4B0082,
    SlateBlue = 0xFF6A5ACD,
    DarkSlateBlue = 0xFF483D8B,
    // Green HTML Color Names
    GreenYellow = 0xFFADFF2F,
    Chartreuse = 0xFF7FFF00,
    LawnGreen = 0xFF7CFC00,
    Lime = 0xFF00FF00,
    LimeGreen = 0xFF32CD32,
    PaleGreen = 0xFF98FB98,
    LightGreen = 0xFF90EE90,
    MediumSpringGreen = 0xFF00FA9A,
    SpringGreen = 0xFF00FF7F,
    MediumSeaGreen = 0xFF3CB371,
    SeaGreen = 0xFF2E8B57,
    ForestGreen = 0xFF228B22,
    Green = 0xFF008000,
    DarkGreen = 0xFF006400,
    YellowGreen = 0xFF9ACD32,
    OliveDrab = 0xFF6B8E23,
    Olive = 0xFF808000,
    DarkOliveGreen = 0xFF556B2F,
    MediumAquamarine = 0xFF66CDAA,
    DarkSeaGreen = 0xFF8FBC8B,
    LightSeaGreen = 0xFF20B2AA,
    DarkCyan = 0xFF008B8B,
    Teal = 0xFF008080,
    // Blue HTML Color Names
    Aqua = 0xFF00FFFF,
    Cyan = 0xFF00FFFF,
    LightCyan = 0xFFE0FFFF,
    PaleTurquoise = 0xFFAFEEEE,
    Aquamarine = 0xFF7FFFD4,
    Turquoise = 0xFF40E0D0,
    MediumTurquoise = 0xFF48D1CC,
    DarkTurquoise = 0xFF00CED1,
    CadetBlue = 0xFF5F9EA0,
    SteelBlue = 0xFF4682B4,
    LightSteelBlue = 0xFFB0C4DE,
    PowderBlue = 0xFFB0E0E6,
    LightBlue = 0xFFADD8E6,
    SkyBlue = 0xFF87CEEB,
    LightSkyBlue = 0xFF87CEFA,
    DeepSkyBlue = 0xFF00BFFF,
    DodgerBlue = 0xFF1E90FF,
    CornflowerBlue = 0xFF6495ED,
    MediumSlateBlue = 0xFF7B68EE,
    RoyalBlue = 0xFF4169E1,
    Blue = 0xFF0000FF,
    MediumBlue = 0xFF0000CD,
    DarkBlue = 0xFF00008B,
    Navy = 0xFF000080,
    MidnightBlue = 0xFF191970,
    // Brown HTML Color Names
    Cornsilk = 0xFFFFF8DC,
    BlanchedAlmond = 0xFFFFEBCD,
    Bisque = 0xFFFFE4C4,
    NavajoWhite = 0xFFFFDEAD,
    Wheat = 0xFFF5DEB3,
    BurlyWood = 0xFFDEB887,
    Tan = 0xFFD2B48C,
    RosyBrown = 0xFFBC8F8F,
    SandyBrown = 0xFFF4A460,
    Goldenrod = 0xFFDAA520,
    DarkGoldenrod = 0xFFB8860B,
    Peru = 0xFFCD853F,
    Chocolate = 0xFFD2691E,
    SaddleBrown = 0xFF8B4513,
    Sienna = 0xFFA0522D,
    Brown = 0xFFA52A2A,
    Maroon = 0xFF800000,
    // White HTML Color Names
    White = 0xFFFFFFFF,
    Snow = 0xFFFFFAFA,
    HoneyDew = 0xFFF0FFF0,
    MintCream = 0xFFF5FFFA,
    Azure = 0xFFF0FFFF,
    AliceBlue = 0xFFF0F8FF,
    GhostWhite = 0xFFF8F8FF,
    WhiteSmoke = 0xFFF5F5F5,
    SeaShell = 0xFFFFF5EE,
    Beige = 0xFFF5F5DC,
    OldLace = 0xFFFDF5E6,
    FloralWhite = 0xFFFFFAF0,
    Ivory = 0xFFFFFFF0,
    AntiqueWhite = 0xFFFAEBD7,
    Linen = 0xFFFAF0E6,
    LavenderBlush = 0xFFFFF0F5,
    MistyRose = 0xFFFFE4E1,
    // Gray HTML Color Names
    Gainsboro = 0xFFDCDCDC,
    LightGray = 0xFFD3D3D3,
    Silver = 0xFFC0C0C0,
    DarkGray = 0xFFA9A9A9,
    Gray = 0xFF808080,
    DimGray = 0xFF696969,
    LightSlateGray = 0xFF778899,
    SlateGray = 0xFF708090,
    DarkSlateGray = 0xFF2F4F4F,
    Black = 0xFF000000,
};
/// @brief Get HEX color code from RGB values
/// @param r [0:255] amount of Red color
/// @param g [0:255] amount of Green color
/// @param b [0:255] amount of Blue color
/// @return [0:0xFFFFFF] HEX color code
inline uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
    return r << 16 | g << 8 | b;
}
/// @brief Generate random color HEX code
/// @return [0:0xFFFFFF] HEX color code
inline uint32_t random() {
    return rgb(::random(256), ::random(256), ::random(256));
}
} // namespace Color

#endif /* INCLUDE_TOTEM_COLOR */
