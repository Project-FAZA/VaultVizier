#include "components.hpp"
#include "../classes/GlobalVars.hpp"

void updateList(const vector<Request> &requests, vector<string> &displayList)
{
    // Clear the current display list
    displayList.clear();

    // Populate the display list with formatted strings
    for (const auto &req : requests)
    {
        std::string status;
        switch (req.getReqStatus())
        {
        case -1:
            status = "Rejected";
            break;
        case 0:
            status = "Pending";
            break;
        case 1:
            status = "Accepted";
            break;
        default:
            status = "Unknown";
            break;
        }

        displayList.push_back("Patient ID: " + req.getPatientId() +
                              " | Equipment ID: " + req.getEquipmentId() +
                              " | Status: " + status);
    }
}

void DoctorDashboard(ScreenInteractive &screen, ScreenStatus *status)
{
    using namespace ftxui;

    std::vector<std::string> tabTitles = {"Sign Patient", "Settings", "Preferences"};
    int selectedTab = 0;

    /* ====================================================================================== */
    /* SIGN PATIENT (TODO Placeholder)                                                       */
    /* ====================================================================================== */

    std::vector<Request> patientRequests = Request::fetchAll();
    int selectedRequest = 0;

    vector<string> reqDisplayList;

    auto requestMenu = Menu(&reqDisplayList, &selectedRequest);
    updateList(patientRequests, reqDisplayList);

    auto refreshButton = Button("Refresh Requests", [&]
                                {
                                    // Clear the list before fetching
                                    patientRequests.clear();

                                    // Fetch all requests (replace with your implementation logic)
                                    patientRequests = Request::fetchAll(); // Assuming this returns a vector of Request objects

                                    updateList(patientRequests, reqDisplayList); });

    auto signButton = Button("Sign Patient", [&]
                             {
                                 if (!patientRequests.empty() && selectedRequest >= 0 && selectedRequest < patientRequests.size())
                                 {
                                     auto r = patientRequests[selectedRequest];
                                     Request::sign(r.getPatientId(), r.getEquipmentId(), 1);

                                     patientRequests.clear();
                                     patientRequests = Request::fetchAll();
                                     updateList(patientRequests, reqDisplayList);
                                 } });

    auto rejectButton = Button("Reject Patient", [&]
                               {
                                 if (!patientRequests.empty() && selectedRequest >= 0 && selectedRequest < patientRequests.size())
                                 {
                                     auto r = patientRequests[selectedRequest];
                                     Request::sign(r.getPatientId(), r.getEquipmentId(), -1);
                                     
                                     patientRequests.clear();
                                     patientRequests = Request::fetchAll();
                                     updateList(patientRequests, reqDisplayList);
                                 } });

    auto signPatientTab = Container::Vertical({requestMenu, Container::Horizontal({refreshButton, signButton, rejectButton})});

    Component signPatientTabUI = Renderer(signPatientTab, [&]
                                          { return vbox({requestMenu->Render() | center,
                                                         hbox(refreshButton->Render(),
                                                              signButton->Render(), rejectButton->Render()) |
                                                             center}) |
                                                   flex; });

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

    // Tab selector menu
    auto tabSelector = Menu(&tabTitles, &selectedTab);

    // Tab content container
    Component tabContent = Container::Tab({signPatientTabUI,
                                           settingsTabUI,
                                           preferencesTabUI},
                                          &selectedTab);

    auto logOutButton = Button("Log Out", [&]
                               {
                                *status = ScreenStatus::LOGIN;
                                screen.Exit(); });

    // UI layout with menu and content
    Component tabSelectorWindow = Renderer(Container::Vertical({tabSelector, logOutButton}), [&]
                                           { return window(text("Menu") | bold, vbox({tabSelector->Render() | vscroll_indicator | frame, logOutButton->Render()})) | color(GlobalVar::getColor()) | bgcolor(GlobalVar::getBg()); });

    Component contentWindow = Renderer(tabContent, [&]
                                       { return window(text(tabTitles[selectedTab]) | bold, tabContent->Render() | frame | flex) | color(GlobalVar::getColor()) | bgcolor(GlobalVar::getBg()); });

    // Combine everything into the main layout
    Component app = Container::Horizontal({tabSelectorWindow,
                                           contentWindow});

    screen.Loop(app);
}
