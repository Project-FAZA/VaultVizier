#ifndef GV_HPP
#define GV_HPP

#include <ftxui/screen/color.hpp>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// 161 235 255 border for dark mode
class GlobalVar
{
public:
    static inline ftxui::Color getColor() { return darkMode ? ftxui::Color::RGBA(161, 235, 255, 0) : ftxui::Color::RGB(0, 0, 0); }
    static inline ftxui::Color getBg() { return darkMode ? ftxui::Color::RGBA(10, 10, 29, 0) : ftxui::Color::RGB(230, 230, 230); }

    static inline bool darkMode = true;
    static inline string selectedSSN = "";
    static inline string currAuthUsername = "";
    static inline bool editMode = false;

    static void createIfDoesNotExist(const string &filename, const string &content);
    static void assignEditValues(
        string *ssn,
        string *firstName, string *lastName,
        string *dobDay, string *dobMonth, string *dobYear,
        string *street, string *city, string *state, string *zipCode, string *country,
        string *phoneNumber, string *weight, string *height, int *genderSelected, int *married, bool *medicare, bool *medicaid);
};

#endif