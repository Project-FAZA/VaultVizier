#include "components.hpp"

using namespace std;

void Login(ScreenInteractive &screen, ScreenStatus *status)
{
    string username;
    string password;

    // Input fields
    auto username_input = Input(&username, "Username", inputOption());
    auto password_input = Input(&password, "Password", inputOption(true));

    // Button to trigger login
    auto login_button = Button("Log In", [&]
                               {
        if (!username.empty() && !password.empty()) {
            *status = DASHBOARD;
            screen.Exit();
        } });

    // Container for input and button
    auto container = Container::Vertical({
        username_input,
        password_input,
        login_button,
    });

    // Final UI layout
    auto app = Renderer(container, [&]
                        { return vbox({
                                     text("Welcome") | bold | center,
                                     separator(),
                                     hbox(text("Username: "), username_input->Render()),
                                     hbox(text("Password: "), password_input->Render()),
                                     separator(),
                                     login_button->Render() | center,
                                 }) |
                                 flex |
                                 borderRounded |
                                 size(WIDTH, EQUAL, 50) |
                                 hcenter; });

    screen.Loop(app);
}