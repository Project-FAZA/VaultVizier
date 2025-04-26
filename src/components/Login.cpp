#include "components.hpp"
#include "../classes/AuthUser.hpp"

using namespace std;

void Login(ScreenInteractive &screen, ScreenStatus *status)
{
    string username;
    string password;
    string msg = "Welcome";

    // Input fields
    auto usernameInput = Input(&username, "Username", inputOption());
    auto passwordInput = Input(&password, "Password", inputOption(true));

    // Button to trigger login
    auto loginButton = Button("Log In", [&]
                              {
        if (!username.empty() && !password.empty()) {
            if (!AuthUser::alreadyExists(username)) msg = "User does not exist";
            else if (AuthUser::verifyPassword(username, password))
            {
                *status = DASHBOARD;
                screen.Exit();
            }
            else msg = "Invalid Password";
        } });

    auto createAccountButton = Button("Create An Account", [&] {});

    // Container for input and button
    auto container = Container::Vertical({
        usernameInput,
        passwordInput,
        Container::Horizontal({loginButton, createAccountButton}),
    });

    // Final UI layout
    auto app = Renderer(container, [&]
                        { return vbox({
                                     text(msg) | bold | center,
                                     separator(),
                                     hbox(text("Username: "), usernameInput->Render()),
                                     hbox(text("Password: "), passwordInput->Render()),
                                     separator(),
                                     hbox(loginButton->Render(), filler(), createAccountButton->Render()) | flex | center,
                                 }) |
                                 flex |
                                 borderRounded |
                                 size(WIDTH, EQUAL, 50) |
                                 hcenter; });

    screen.Loop(app);
}