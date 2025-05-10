#ifndef COMP_HPP
#define COMP_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include "Request.hpp"
#include "../classes/Equipment.hpp"
#include <ftxui/dom/table.hpp>

using namespace ftxui;

enum ScreenStatus
{
    LOGIN,
    CREATE_ACC,
    DASHBOARD,
    DOCTOR_DASHBOARD
};

InputOption inputOption(bool password = false);
void updateList(const vector<Request> &requests, vector<string> &displayList);
void updateRequestTable(Table *table, vector<Request> req);

void Login(ScreenInteractive &screen, ScreenStatus *status);
void Dashboard(ScreenInteractive &screen, ScreenStatus *status);
void DoctorDashboard(ScreenInteractive &screen, ScreenStatus *status);
void CreateAcc(ScreenInteractive &screen, ScreenStatus *status);

#endif
