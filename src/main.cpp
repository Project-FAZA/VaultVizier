#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include "classes/Patient.hpp"
#include "components/components.hpp"

using namespace ftxui;

int main()
{
    auto status = ScreenStatus::LOGIN;
    auto screen = ScreenInteractive::TerminalOutput();

    while (true)
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        if (status == ScreenStatus::DASHBOARD)
            Dashboard(screen, &status);
        else if (status == ScreenStatus::DOCTOR_DASHBOARD)
            DoctorDashboard(screen, &status);
        else if (status == ScreenStatus::LOGIN)
            Login(screen, &status);
        else if (status == ScreenStatus::CREATE_ACC)
            CreateAcc(screen, &status);

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
}
