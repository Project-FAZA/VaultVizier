#include "components.hpp"
#include "../classes/Patient.hpp"
#include "../classes/GlobalVars.hpp"
#include <vector>
#include <ftxui/dom/table.hpp>
#include <cctype>

using namespace std;

int numOfDots(string s)
{
    int count = 0;
    for (char c : s)
    {
        if (c == '.')
        {
            count++;
        }
    }
    return count;
}

ComponentDecorator getCharLimit(string *inputStr, int limit)
{
    return CatchEvent([inputStr, limit](Event e)
                      {
        if (!e.is_character()) return false;

        return !(inputStr->size() < limit); });
}

void Dashboard(ScreenInteractive &screen, ScreenStatus *status)
{
    vector<string> tabTitles = {"Add Patient", "View Patient", "Add Request", "View Requests", "Settings", "Preferences"};
    int selectedTab = 0;
    /* ====================================================================================== */
    /* ADD PT                                                                                 */
    /* ====================================================================================== */
    string msg = "";

    string ssn;

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
    auto ssnInput = Input(&ssn, "Social Security Number", inputOption()) | getCharLimit(&ssn, 9);
    auto firstNameInput = Input(&firstName, "First Name", inputOption()) | getCharLimit(&firstName, 20);
    auto lastNameInput = Input(&lastName, "Last Name", inputOption()) | getCharLimit(&lastName, 20);
    auto genderInput = Toggle(&genderList, &genderSelected);

    // CatchEvent
    auto integerEvent = CatchEvent([&](Event e)
                                   { return e.is_character() && !isdigit(e.character()[0]); });

    auto getFloatEvent = [&](string *floatStr)
    { return CatchEvent([floatStr](Event e)
                        {
            if (!e.is_character())
                return false;

            return !(isdigit(e.character()[0]) || ((e.character()[0] == '.') && (numOfDots(*floatStr) == 0))); }); };

    auto floatEventW = getFloatEvent(&weight);
    auto floatEventH = getFloatEvent(&height);

    // BIRTH
    auto dobDayInput = Input(&dobDay, "Day", inputOption()) | integerEvent;
    auto dobMonthInput = Input(&dobMonth, "Month", inputOption()) | integerEvent;
    auto dobYearInput = Input(&dobYear, "Year", inputOption()) | integerEvent;

    // Billing Address
    auto streetInput = Input(&street, "Street Address", inputOption());
    auto cityInput = Input(&city, "City", inputOption());
    auto stateInput = Input(&state, "State", inputOption());
    auto zipInput = Input(&zipCode, "Zip Code (12345)", inputOption()) | integerEvent | getCharLimit(&zipCode, 5);
    auto countryInput = Input(&country, "Country", inputOption());
    auto phoneInput = Input(&phoneNumber, "Phone Number (01234567890)", inputOption()) | integerEvent | getCharLimit(&phoneNumber, 11);

    // Clinical
    auto weightInput = Input(&weight, "Weight (kg)", inputOption()) | floatEventW;
    auto heightInput = Input(&height, "Height (cm)", inputOption()) | floatEventH;
    auto maritalStatusInput = Toggle(&maritalStatusList, &maritalStatusSelected);

    bool medicare = false;
    bool medicaid = false;

    auto insuranceInput = Container::Horizontal({Checkbox("Medicare", &medicare), Checkbox("Medicaid", &medicaid)});

    auto submitButton = Button("Submit", [&]
                               {
            if (ssn.empty() || firstName.empty() || lastName.empty() ||
                dobDay.empty() || dobMonth.empty() || dobYear.empty() ||
                street.empty() || city.empty() || state.empty() ||
                zipCode.empty() || country.empty() || phoneNumber.empty() ||
                weight.empty() || height.empty())
            {
                msg = "All fields must be filled out!";
                return;
            }

            if (ssn.find(',') != string::npos || firstName.find(',') != string::npos || lastName.find(',') != string::npos ||
                dobDay.find(',') != string::npos || dobMonth.find(',') != string::npos || dobYear.find(',') != string::npos ||
                street.find(',') != string::npos || city.find(',') != string::npos || state.find(',') != string::npos ||
                zipCode.find(',') != string::npos || country.find(',') != string::npos || phoneNumber.find(',') != string::npos ||
                weight.find(',') != string::npos || height.find(',') != string::npos) 
            {
                msg = "Fields must not contain commas!";
                return;
            }

            if (ssn.size() < 9) { msg = "Invalid SSN"; return; }
            if (phoneNumber.size() < 10) { msg = "Invalid Phone Number"; return; }

            try
            {
                int d = std::stoi(dobDay);
                int m = std::stoi(dobMonth);
                int y = std::stoi(dobYear);
                Date dob{d, m, y};

                if (!isValidDate(dob))
                {
                    msg = "Invalid Date of Birth!";
                    return;
                }

                patient.setSSN(ssn);
                patient.setFirstName(firstName);
                patient.setLastName(lastName);
                patient.setGender(!genderSelected);
                patient.setDOB(dob);
                patient.setAddress(Address{street, city, state, zipCode, country});
                patient.setPhoneNumber(phoneNumber);
                patient.setWeight(stof(weight));
                patient.setHeight(stof(height));
                patient.setMaritalStatus(maritalStatusSelected - 1);
                patient.setInsurance(medicare, medicaid);

                patient.save();
                msg = "Patient Registered Successfully!";
                // *status = ScreenStatus::LOGIN;
                screen.ExitLoopClosure()();
            }
            catch (...)
            {
                msg = "Invalid date values!";
            } });

    // Create layout container
    auto container = Container::Vertical({ssnInput, firstNameInput,
                                          lastNameInput,
                                          Container::Horizontal({dobDayInput, dobMonthInput, dobYearInput}),
                                          streetInput, cityInput, stateInput, zipInput, countryInput,
                                          phoneInput,
                                          genderInput,
                                          weightInput, heightInput,
                                          maritalStatusInput, insuranceInput,
                                          submitButton});

    // Decorate the UI
    Component add_p = Renderer(container, [&]
                               { 
                                if (GlobalVar::editMode) GlobalVar::assignEditValues(
                                    &ssn, &firstName, &lastName,
                                    &dobDay, &dobMonth, &dobYear,
                                    &street, &city, &state, &zipCode, &country,
                                    &phoneNumber, &weight, &height, &genderSelected, &maritalStatusSelected, &medicare, &medicaid);
                                
                                auto seq1 = vbox({
                                            text("Patient Registration Form") | bold | center | border,
                                            separator(),
                                            vbox({text("Personal Info") | bold,
                                                  ssnInput->Render(),
                                                  firstNameInput->Render(),
                                                  lastNameInput->Render()}) |
                                                borderRounded,

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
                                                  maritalStatusInput->Render(),
                                                  insuranceInput->Render()}) |
                                                borderRounded,

                                            submitButton->Render() | center,
                                        }) |
                                        borderRounded | flex | hcenter; 
                                    
                                    
                                        return vbox(seq1, text(msg) | color(Color::Yellow) | center); });

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

            int i = 1;
            for (const auto &p : Patient::fetchAll())
            {
                string fullName = p.getSSN() + ". " + p.getFirstName() + " " + p.getLastName();
                string lowerFullName = fullName;
                string lowerSearchQuery = searchQuery;
                std::transform(lowerFullName.begin(), lowerFullName.end(), lowerFullName.begin(), ::tolower);
                std::transform(lowerSearchQuery.begin(), lowerSearchQuery.end(), lowerSearchQuery.begin(), ::tolower);

                if (lowerFullName.find(lowerSearchQuery) != std::string::npos)
                {
                    searchResults.push_back(fullName);
                    i++;
                }
            }

            if (searchResults.empty())
            {
                searchResults.push_back("No results found");
            } });

    auto editButton = Button("Edit", [&]
                             {
        if (!searchResults.empty() && searchResults[0] != "No results found")
        {
            GlobalVar::editMode = true;
            selectedTab = 0;
        } });

    auto searchResultsMenu = Menu(&searchResults, &selectedResultIndex);

    // Combine all into one container
    auto viewPatientContainer = Container::Vertical({searchInput,
                                                     Container::Horizontal({searchButton, editButton}),
                                                     searchResultsMenu});

    Component viewPatientTabUI = Renderer(viewPatientContainer, [&]
                                          {
            // Try to get selected patient
            Patient selected;
            bool valid = (!searchResults.empty() && searchResults[0] != "No results found");
            
            if (!searchResults.empty() && searchResults[0] != "No results found")
            {
                const auto &name = searchResults[selectedResultIndex];
                for (const auto &p : Patient::fetchAll())
                {
                    std::string fullName = p.getSSN() + ". " + p.getFirstName() + " " + p.getLastName();
                    if (fullName == name)
                    {
                        selected = p;
                        valid = true;
                        break;
                    }
                }
            }

            auto resultBox = vbox({
                text("Search Patient") | bold | center,
                searchInput->Render() | flex,
                hbox({searchButton->Render(), editButton->Render()}) | center,
                separator(),
                text("Results") | bold | center,
                searchResultsMenu->Render() | frame | size(HEIGHT, LESS_THAN, 8),
            });
            
            if (!valid)
            {
                return vbox({
                    resultBox,
                    separator(),
                    text("No patient selected or not found.") | center | color(Color::Red),
                }) |
                borderRounded | flex;
            }

            GlobalVar::selectedSSN = selected.getSSN();

            const Address &addr = selected.getAddress();
            const Date &dob = selected.getDOB();

            auto insurance = selected.getInsurance();
            auto patientDetails = Table({{"Field", "Value"},
                                         {"SSN", selected.getSSN()},
                                         {"Name", selected.getFirstName() + " " + selected.getLastName()},
                                         {"Gender", std::string(selected.getGender() ? "Male" : "Female")},
                                         {"DOB", to_string(dob.d) + "/" + to_string(dob.m) + "/" + to_string(dob.y)},
                                         {"Street", addr.street},
                                         {"City", addr.city},
                                         {"State", addr.state},
                                         {"Zip Code", addr.zipCode},
                                         {"Country", addr.country},
                                         {"Phone Number", selected.getPhoneNumber()},
                                         {"Weight (kg)", to_string(selected.getWeight())},
                                         {"Height (ft)", to_string(selected.getHeight())},
                                         {"Marital Status", selected.getMaritalStatus() == -1 ? "Widowed" : (selected.getMaritalStatus() == 0 ? "Single" : "Married")},
                                         {"Medicare", insurance.first ? "Yes" : "No"},
                                         {"Medicaid", insurance.second ? "Yes" : "No"}});

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

            return vbox({resultBox,
                         separator(),
                         patientDetails.Render() | center}) |
                   borderRounded | flex; });
    // END

    /* ====================================================================================== */
    /* REQUEST PT                                                                             */
    /* ====================================================================================== */
    string reqMsg = "";
    string reqSSN, reqEq;
    auto reqSSNInput = Input(&reqSSN, "SSN", inputOption());

    int selectedEqIndex = 0;
    vector<string> equipmentNames;
    vector<string> equipmentCodes;

    for (const auto &eq : Equipment::equipments)
    {
        equipmentNames.push_back(eq.getName());
        equipmentCodes.push_back(eq.getCode());
    }

    auto reqEqInput = Dropdown(&equipmentNames, &selectedEqIndex);
    string reason;
    auto reasonInput = Input(&reason, "Reason for Request", inputOption());

    auto reqButton = Button("Submit Request", [&]
                            {
        if (reqSSN.empty() || reason.empty())
        {
            reqMsg = "All fields must be filled out!";
            return;
        }

        reqEq = Equipment::equipments[selectedEqIndex].getCode();

        if (Request::alreadyExists(reqSSN, reqEq))
        {
            reqMsg = "Request already exists";
            return;
        }

        if (!Patient::alreadyExists(reqSSN))
        {
            reqMsg = "Patient not found";
            return;
        }

        auto reqP = Patient::fetch(reqSSN);
        
        string v = Equipment::getEquipment(equipmentCodes[selectedEqIndex]).validateInsurance(reqP.getInsurance().first, reqP.getInsurance().second);
        
        if (v.empty()) 
        {
            reqMsg = "Not Eligible";
            return;
        }

        Request r(reqSSN, reqEq, 0, reason);
        r.save();

        // Logic to handle the request submission
        reqMsg = "Request submitted successfully for SSN: " + reqSSN; });

    auto requestPatientContainer = Container::Vertical({reqSSNInput,
                                                        reasonInput, reqEqInput,
                                                        reqButton});

    Component requestPatientTabUI = Renderer(requestPatientContainer, [&]
                                             { return vbox({
                                                          text("Request Patient Equipment") | flex | bold | center,
                                                          separator(),
                                                          reqSSNInput->Render() | flex,
                                                          reasonInput->Render() | flex,
                                                          reqEqInput->Render() | flex,
                                                          reqButton->Render() | flex | center,
                                                          text(reqMsg) | flex | color(Color::Yellow) | center,
                                                      }) |
                                                      borderRounded | flex | center; });
    // END

    /* ====================================================================================== */
    /* VIEW REQUEST PT                                                                        */
    /* ====================================================================================== */

    vector<Request> patientRequests = Request::fetchAll();

    Table reqTable = Table({{text("Test")}});

    updateRequestTable(&reqTable, patientRequests);

    auto refreshButton = Button("Refresh Requests", [&]
                                {
        // Clear the list before fetching
        patientRequests.clear();
        patientRequests = Request::fetchAll();

        updateRequestTable(&reqTable, patientRequests); });

    auto clearDoneButton = Button("Clear Done Requests", [&]
                                  {
                                      patientRequests.clear();
                                      Request::clearDone();
                                      patientRequests = Request::fetchAll();
                                      updateRequestTable(&reqTable, patientRequests); });

    auto viewRequestTab = Container::Horizontal({refreshButton, clearDoneButton});

    Component viewRequestTabUI = Renderer(viewRequestTab, [&]
                                          { 
                                            updateRequestTable(&reqTable, patientRequests);
                                            return vbox({ reqTable.Render(), 
                                                hbox({refreshButton->Render(), clearDoneButton->Render()}) | center }) | center; });

    /* ====================================================================================== */
    /* SETTINGS TAB                                                                           */
    /* ====================================================================================== */
    bool notifications = false;
    auto settingsTabUI = Container::Vertical({
        Renderer([&]
                 { return text(GlobalVar::currAuthUsername); }),
        Checkbox("Enable notifications", &notifications),
    });

    /* ====================================================================================== */
    /* PREFERENCES TAB                                                                        */
    /* ====================================================================================== */
    bool compactView = true;
    auto preferencesTabUI = Container::Vertical({
        Checkbox("Dark Mode (Light Mode not recommended)", &GlobalVar::darkMode),
        Checkbox("Compact View", &compactView),
    });

    // Tab list
    auto tabSelector = Menu(&tabTitles, &selectedTab);

    // Tab container: Shows the appropriate UI
    Component content = Container::Tab({add_p,
                                        viewPatientTabUI,
                                        requestPatientTabUI,
                                        viewRequestTabUI,
                                        settingsTabUI,
                                        preferencesTabUI},
                                       &selectedTab);

    auto logOutButton = Button("Log Out", [&]
                               {
        *status = ScreenStatus::LOGIN;
        screen.Exit(); });

    Component tabSelectorWindow = Renderer(Container::Vertical({tabSelector, logOutButton}), [&]
                                           { return window(text("Menu") | bold, vbox({tabSelector->Render() | vscroll_indicator | frame, logOutButton->Render()})) | color(GlobalVar::getColor()) | bgcolor(GlobalVar::getBg()); });
    Component contentWindow = Renderer(content, [&]
                                       { return window(text(tabTitles[selectedTab]) | bold, vbox({
                                                                                                content->Render(),
                                                                                            }) | frame |
                                                                                                flex) |
                                                color(GlobalVar::getColor()) | bgcolor(GlobalVar::getBg()); });

    // Combine menu and dynamic content
    Component app = Container::Horizontal({tabSelectorWindow,
                                           contentWindow});

    screen.Loop(app);
}