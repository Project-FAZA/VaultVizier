#include "components.hpp"
#include "../classes/Patient.hpp"
#include "../classes/GlobalVars.hpp"
#include <vector>
#include <ftxui/dom/table.hpp>

using namespace std;

void Dashboard(ScreenInteractive &screen, ScreenStatus *status)
{
    /* ====================================================================================== */
    /* ADD PT                                                                                 */
    /* ====================================================================================== */
    string msg = "";

    string firstName, lastName;

    string dobDay, dobMonth, dobYear;

    string street, city, state, zipCode, country;

    string phoneNumber, weight, height;

    vector<string> maritalStatusList = {"Widowed", "Single", "Married"};
    int maritalStatusSelected = 0;

    vector<string> genderList = {"Male", "Female"};
    int genderSelected = 0;

    Patient patient("", "", Date{0, 0, 0}, Address{"", "", "", "", ""});

    // Input fields
    // Personal
    auto firstNameInput = Input(&firstName, "First Name", inputOption());
    auto lastNameInput = Input(&lastName, "Last Name", inputOption());
    auto genderInput = Toggle(&genderList, &genderSelected);

    // BIRTH
    auto dobDayInput = Input(&dobDay, "Day", inputOption());
    auto dobMonthInput = Input(&dobMonth, "Month", inputOption());
    auto dobYearInput = Input(&dobYear, "Year", inputOption());

    // Billing Address
    auto streetInput = Input(&street, "Street Address", inputOption());
    auto cityInput = Input(&city, "City", inputOption());
    auto stateInput = Input(&state, "State", inputOption());
    auto zipInput = Input(&zipCode, "Zip Code", inputOption());
    auto countryInput = Input(&country, "Country", inputOption());
    auto phoneInput = Input(&phoneNumber, "Phone Number", inputOption());

    // Clinical
    auto weightInput = Input(&weight, "Weight (kg)", inputOption());
    auto heightInput = Input(&height, "Height (cm)", inputOption());
    auto maritalStatusInput = Toggle(&maritalStatusList, &maritalStatusSelected);

    auto submitButton = Button("Submit", [&]
                               {
        if (firstName.empty() || lastName.empty() ||
        dobDay.empty() || dobMonth.empty() || dobYear.empty() ||
        street.empty() || city.empty() || state.empty() ||
        zipCode.empty() || country.empty() || phoneNumber.empty() ||
        weight.empty() || height.empty()) {
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
            patient.setGender(!genderSelected);
            patient.setDOB(dob);
            patient.setAddress(Address{street, city, state, zipCode, country});
            patient.setPhoneNumber(phoneNumber);
            patient.setWeight(stof(weight));
            patient.setHeight(stof(height));
            patient.setMaritalStatus(maritalStatusSelected - 1);

            patient.save();
            msg = "Patient Registered Successfully!";
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
                                          phoneInput,
                                          genderInput,
                                          weightInput, heightInput,
                                          maritalStatusInput,
                                          submitButton});

    // Decorate the UI
    Component add_p = Renderer(container, [&]
                               { return vbox({
                                            text("Patient Registration Form") | bold | center | border,
                                            separator(),
                                            vbox({text("Personal Info") | bold,
                                                  firstNameInput->Render(),
                                                  lastNameInput->Render()}) |
                                                borderRounded | flex,

                                            vbox({text("Date of Birth") | bold,
                                                  hbox({
                                                      dobDayInput->Render() | flex,
                                                      dobMonthInput->Render() | flex,
                                                      dobYearInput->Render() | flex,
                                                  })}) |
                                                borderRounded,

                                            vbox({text("Billing Address") | bold,
                                                  streetInput->Render(),
                                                  cityInput->Render(),
                                                  stateInput->Render(),
                                                  zipInput->Render(),
                                                  countryInput->Render(),
                                                  phoneInput->Render()}) |
                                                borderRounded,

                                            vbox({text("Clinical") | bold,
                                                  genderInput->Render(),
                                                  weightInput->Render(),
                                                  heightInput->Render(),
                                                  maritalStatusInput->Render()}) |
                                                borderRounded,

                                            submitButton->Render() | center,
                                            text(msg) | color(Color::Yellow) | center,
                                        }) |
                                        borderRounded | flex | hcenter; });
    /* ====================================================================================== */
    /* VIEW PT                                                                                */
    /* ====================================================================================== */

    // Search input and logic
    std::string searchQuery;
    std::vector<std::string> searchResults;
    int selectedResultIndex = 0;

    // Search input and button
    auto searchInput = Input(&searchQuery, "Search by name", inputOption());

    auto searchButton = Button("Search", [&]
                               {
    searchResults.clear();
    selectedResultIndex = 0;

    for (const auto &p : Patient::fetchAll()) {
        std::string fullName = p.getFirstName() + " " + p.getLastName();
        if (fullName.find(searchQuery) != std::string::npos) {
            searchResults.push_back(fullName);
        }
    }

    if (searchResults.empty()) {
        searchResults.push_back("No results found");
    } });

    auto searchResultsMenu = Menu(&searchResults, &selectedResultIndex);

    // Combine all into one container
    auto viewPatientContainer = Container::Vertical({searchInput,
                                                     searchButton,
                                                     searchResultsMenu});

    Component viewPatientTabUI = Renderer(viewPatientContainer, [&]
                                          {
    // Try to get selected patient
    Patient selected;
    bool valid = false;
    if (!searchResults.empty() && searchResults[0] != "No results found") {
        const auto &name = searchResults[selectedResultIndex];
        for (const auto &p : Patient::fetchAll()) {
            std::string fullName = p.getFirstName() + " " + p.getLastName();
            if (fullName == name) {
                selected = p;
                valid = true;
                break;
            }
        }
    }

    auto resultBox = vbox({
        text("Search Patient") | bold | center,
        searchInput->Render(),
        searchButton->Render() | center,
        separator(),
        text("Results") | bold | center,
        searchResultsMenu->Render() | frame | size(HEIGHT, LESS_THAN, 8),
    });

    if (!valid) {
        return vbox({
            resultBox,
            separator(),
            text("No patient selected or not found.") | center | color(Color::Red),
        }) | borderRounded | flex;
    }

    const Address &addr = selected.getAddress();
    const Date &dob = selected.getDOB();

    auto patientDetails = Table({
        {"Field",     "Value"},
        {"Name",      selected.getFirstName() + " " + selected.getLastName()},
        {"Gender",    std::string(selected.getGender() ? "Male" : "Female")},
        {"DOB",       to_string(dob.d) + "/" + to_string(dob.m) + "/" + to_string(dob.y)},
        {"Street",    addr.street},
        {"City",      addr.city},
        {"State",     addr.state},
        {"Zip Code",  addr.zipCode},
        {"Country",   addr.country}
    });
    
    patientDetails.SelectRow(0).Border(LIGHT);
    patientDetails.SelectAll().Border(HEAVY);
    patientDetails.SelectAll().SeparatorVertical(LIGHT);
    patientDetails.SelectColumn(0).Decorate(bold);
    patientDetails.SelectRow(0).SeparatorHorizontal(LIGHT);
    patientDetails.SelectColumn(0).DecorateCells(align_right);

    patientDetails.SelectRow(0).DecorateCells(color(Color::Yellow1));
    patientDetails.SelectColumn(1).DecorateCells(color(Color::LightSkyBlue1));
    patientDetails.SelectColumn(0).DecorateCells(color(Color::Yellow1));
    patientDetails.SelectAll().Decorate(color(Color::Yellow1));

    return vbox({
        resultBox,
        separator(),
        patientDetails.Render() | center
    }) | borderRounded | flex; });
    // END

    std::vector<std::string> tabTitles = {"Add Patient", "View Patient", "Settings", "Preferences"};
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
        Checkbox("Dark Mode (Light Mode not recommended)", &GlobalVar::darkMode),
        Checkbox("Compact View", &compactView),
    });

    // Tab list
    auto tabSelector = Menu(&tabTitles, &selectedTab);

    // Tab container: Shows the appropriate UI
    Component content = Container::Tab({add_p,
                                        viewPatientTabUI,
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