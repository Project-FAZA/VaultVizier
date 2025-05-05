#include "components.hpp"
#include "../classes/GlobalVars.hpp"

void DoctorDashboard(ScreenInteractive &screen, ScreenStatus *status)
{
    using namespace ftxui;

    std::vector<std::string> tabTitles = {"Sign Patient", "Settings", "Preferences"};
    int selectedTab = 0;

    /* ====================================================================================== */
    /* SIGN PATIENT (TODO Placeholder)                                                       */
    /* ====================================================================================== */
    Component signPatientTab = Renderer([]
                                        { return vbox({text("Sign Patient") | bold | center,
                                                       separator(),
                                                       text("TODO: Implement signing patient records.") | color(Color::Yellow) | center}) |
                                                 border | flex; });

    /* ====================================================================================== */
    /* SETTINGS TAB                                                                           */
    /* ====================================================================================== */
    std::string username;
    bool notifications = false;
    auto settingsTab = Container::Vertical({
        Input(&username, "Username", inputOption()),
        Checkbox("Enable notifications", &notifications),
    });

    Component settingsTabUI = Renderer(settingsTab, [&]
                                       { return vbox({text("Settings") | bold | center,
                                                      separator(),
                                                      settingsTab->Render()}) |
                                                border | flex; });

    /* ====================================================================================== */
    /* PREFERENCES TAB                                                                        */
    /* ====================================================================================== */
    bool compactView = true;
    auto preferencesTab = Container::Vertical({
        Checkbox("Dark Mode (Light Mode not recommended)", &GlobalVar::darkMode),
        Checkbox("Compact View", &compactView),
    });

    Component preferencesTabUI = Renderer(preferencesTab, [&]
                                          { return vbox({text("Preferences") | bold | center,
                                                         separator(),
                                                         preferencesTab->Render()}) |
                                                   border | flex; });

    // Tab selector menu
    auto tabSelector = Menu(&tabTitles, &selectedTab);

    // Tab content container
    Component tabContent = Container::Tab({signPatientTab,
                                           settingsTabUI,
                                           preferencesTabUI},
                                          &selectedTab);

    // UI layout with menu and content
    Component tabSelectorWindow = Renderer(tabSelector, [&]
                                           { return window(text("Menu") | bold, tabSelector->Render() | vscroll_indicator | frame) | color(GlobalVar::getColor()) | bgcolor(GlobalVar::getBg()); });

    Component contentWindow = Renderer(tabContent, [&]
                                       { return window(text(tabTitles[selectedTab]) | bold, tabContent->Render() | frame | flex) | color(GlobalVar::getColor()) | bgcolor(GlobalVar::getBg()); });

    // Combine everything into the main layout
    Component app = Container::Horizontal({tabSelectorWindow,
                                           contentWindow});

    screen.Loop(app);
}
