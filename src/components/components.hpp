#ifndef COMP_HPP
#define COMP_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

enum ScreenStatus
{
    LOGIN,
    CREATE_ACC,
    DASHBOARD
};

InputOption inputOption(bool password = false);

void Login(ScreenInteractive &screen, ScreenStatus *status);
void Dashboard(ScreenInteractive &screen, ScreenStatus *status);
void CreateAcc(ScreenInteractive &screen, ScreenStatus *status);

#endif
