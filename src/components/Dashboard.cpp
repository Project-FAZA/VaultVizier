#include "components.hpp"
#include "../classes/Patient.hpp"
#include "../classes/GlobalVars.hpp"
#include <vector>

using namespace std;

void Dashboard(ScreenInteractive &screen, ScreenStatus *status)
{
    /* ====================================================================================== */
    /* ADD PT                                                                                 */
    /* ====================================================================================== */
    std::string msg = "";

    std::string firstName, lastName;
    std::string dobDay, dobMonth, dobYear;
    std::string street, city, state, zipCode, country;

    Patient patient("", "", Date{0, 0, 0}, Address{"", "", "", "", ""});

    // Input fields
    auto firstNameInput = Input(&firstName, "First Name", inputOption());
    auto lastNameInput = Input(&lastName, "Last Name", inputOption());
    auto dobDayInput = Input(&dobDay, "Day", inputOption());
    auto dobMonthInput = Input(&dobMonth, "Month", inputOption());
    auto dobYearInput = Input(&dobYear, "Year", inputOption());

    auto streetInput = Input(&street, "Street Address", inputOption());
    auto cityInput = Input(&city, "City", inputOption());
    auto stateInput = Input(&state, "State", inputOption());
    auto zipInput = Input(&zipCode, "Zip Code", inputOption());
    auto countryInput = Input(&country, "Country", inputOption());

    auto submitButton = Button("Submit", [&]
                               {
        if (firstName.empty() || lastName.empty() ||
            dobDay.empty() || dobMonth.empty() || dobYear.empty() ||
            street.empty() || city.empty() || state.empty() ||
            zipCode.empty() || country.empty()) {
            msg = "All fields must be filled out!";
            return;
        }

        try {
            int d = std::stoi(dobDay);
            int m = std::stoi(dobMonth);
            int y = std::stoi(dobYear);
            Date dob{d, m, y};

            if (!isValidDate(dob)) {
                msg = "Invalid Date of Birth!";
                return;
            }

            patient.setFirstName(firstName);
            patient.setLastName(lastName);
            patient.setDOB(dob);
            patient.setAddress(Address{street, city, state, zipCode, country});

            msg = "Patient Registered Successfully!";
            // patient.save();
            *status = ScreenStatus::LOGIN;
            screen.ExitLoopClosure()();
        } catch (...) {
            msg = "Invalid date values!";
        } });

    // Create layout container
    auto container = Container::Vertical({firstNameInput,
                                          lastNameInput,
                                          Container::Horizontal({dobDayInput, dobMonthInput, dobYearInput}),
                                          streetInput, cityInput, stateInput, zipInput, countryInput,
                                          submitButton});

    // Decorate the UI
    Component add_p = Renderer(container, [&]
                               { return vbox({
                                            text("Patient Registration Form") | bold | center | border,
                                            separator(),
                                            vbox({
                                                text("Personal Info") | bold,
                                                firstNameInput->Render(),
                                                lastNameInput->Render(),
                                            }) | borderRounded |
                                                flex,

                                            vbox({
                                                text("Date of Birth") | bold,
                                                hbox({
                                                    dobDayInput->Render() | flex,
                                                    dobMonthInput->Render() | flex,
                                                    dobYearInput->Render() | flex,
                                                }),
                                            }) | borderRounded,

                                            vbox({
                                                text("Address") | bold,
                                                streetInput->Render(),
                                                cityInput->Render(),
                                                stateInput->Render(),
                                                zipInput->Render(),
                                                countryInput->Render(),
                                            }) | borderRounded,

                                            submitButton->Render() | center,
                                            text(msg) | color(Color::Yellow) | center,
                                        }) |
                                        borderRounded | flex | hcenter; });
    /* ====================================================================================== */
    /* VIEW PT                                                                                */
    /* ====================================================================================== */

    std::vector<std::string> tabTitles = {"Add Patient", "Settings", "Preferences"};
    int selectedTab = 0;

    // Tab 2: Settings
    std::string username;
    bool notifications = false;
    auto tab2 = Container::Vertical({
        Input(&username, "Username", inputOption()),
        Checkbox("Enable notifications", &notifications),
    });

    // Tab 3: Preferences
    // bool darkMode = false;
    bool compactView = true;
    auto tab3 = Container::Vertical({
        Checkbox("Dark Mode", &GlobalVar::darkMode),
        Checkbox("Compact View", &compactView),
    });

    // Tab list
    auto tabSelector = Menu(&tabTitles, &selectedTab);

    // Tab container: Shows the appropriate UI
    Component content = Container::Tab({add_p,
                                        tab2,
                                        tab3},
                                       &selectedTab);

    Component tabSelectorWindow = Renderer(tabSelector, [&]
                                           { return window(text("Menu") | bold, tabSelector->Render() | vscroll_indicator | frame) | color(GlobalVar::getColor()) | bgcolor(GlobalVar::getBg()); });
    Component contentWindow = Renderer(content, [&]
                                       { return window(text(tabTitles[selectedTab]) | bold, content->Render() | frame | flex) | color(GlobalVar::getColor()) | bgcolor(GlobalVar::getBg()); });

    // Combine menu and dynamic content
    Component app = Container::Horizontal({tabSelectorWindow,
                                           contentWindow});

    screen.Loop(app);
}