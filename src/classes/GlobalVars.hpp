#ifndef GV_HPP
#define GV_HPP

#include <ftxui/screen/color.hpp>

// 161 235 255 border for dark mode
class GlobalVar
{
public:
    static inline ftxui::Color getColor() { return darkMode ? ftxui::Color::RGB(161, 235, 255) : ftxui::Color::RGB(0, 0, 0); }
    static inline ftxui::Color getBg() { return darkMode ? ftxui::Color::RGB(10, 10, 29) : ftxui::Color::RGB(230, 230, 230); }

    static inline bool darkMode = true;
};

#endif