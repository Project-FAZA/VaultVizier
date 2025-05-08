// CreateAcc.cpp
#include "components.hpp"
#include "../classes/AuthUser.hpp"

using namespace std;

void CreateAcc(ScreenInteractive &screen, ScreenStatus *status)
{
    string username;
    string password;
    string confirmPassword;
    string msg = "Create New Account";

    vector<string> roleOptions = {"User", "Doctor"};
    int roleIndex = 0;

    // Input fields
    auto usernameInput = Input(&username, "Username", inputOption());
    auto passwordInput = Input(&password, "Password", inputOption(true));
    auto confirmPasswordInput = Input(&confirmPassword, "Confirm Password", inputOption(true));

    auto roleSelector = Radiobox(&roleOptions, &roleIndex);

    // Button to trigger account creation
    auto createButton = Button("Create Account", [&]
                               {
        if (username.empty() || password.empty() || confirmPassword.empty()) {
            msg = "All fields are required";
        } else if (AuthUser::alreadyExists(username)) {
            msg = "User already exists";
        } else if (password != confirmPassword) {
            msg = "Passwords do not match";
        } else {
            AuthUser::create(username, password, roleIndex);
            // msg = "Account created successfully!";
            
            screen.Exit();
        } });

    auto backButton = Button("Back", [&]
                             {
        *status = LOGIN;
        screen.Exit(); });

    // Container for inputs and buttons
    auto container = Container::Vertical({
        usernameInput,
        passwordInput,
        confirmPasswordInput,
        roleSelector,
        Container::Horizontal({createButton, backButton}),
    });

    // UI Layout
    auto app = Renderer(container, [&]
                        { return vbox({
                                     text(msg) | bold | center,
                                     separator(),
                                     hbox(text("Username: "), usernameInput->Render()),
                                     hbox(text("Password: "), passwordInput->Render()),
                                     hbox(text("Confirm:  "), confirmPasswordInput->Render()),
                                     hbox(text("Role:     "), roleSelector->Render()),
                                     separator(),
                                     hbox(createButton->Render(), filler(), backButton->Render()) | flex | center,
                                 }) |
                                 flex |
                                 borderRounded |
                                 size(WIDTH, EQUAL, 50) |
                                 hcenter; });

    screen.Loop(app);
}
