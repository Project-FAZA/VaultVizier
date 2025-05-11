#include "components.hpp"
#include "../classes/GlobalVars.hpp"
#include "../classes/Patient.hpp"

void DoctorDashboard(ScreenInteractive &screen, ScreenStatus *status)
{
    using namespace ftxui;

    std::vector<std::string> tabTitles = {"Sign Patient", "Settings", "Preferences"};
    int selectedTab = 0;

    /* ====================================================================================== */
    /* SIGN PATIENT (TODO Placeholder)                                                       */
    /* ====================================================================================== */

    std::vector<Request> patientRequests = Request::fetchAll(true);
    int selectedRequest = 0;

    vector<string> reqDisplayList;

    auto requestMenu = Menu(&reqDisplayList, &selectedRequest);
    updateList(patientRequests, reqDisplayList);

    auto refreshButton = Button("Refresh Requests", [&]
                                {
                                    // Clear the list before fetching
                                    patientRequests.clear();

                                    // Fetch all requests (replace with your implementation logic)
                                    patientRequests = Request::fetchAll(true); // Assuming this returns a vector of Request objects

                                    updateList(patientRequests, reqDisplayList); });

    auto signButton = Button("Sign Patient", [&]
                             {
                                 if (!patientRequests.empty() && selectedRequest >= 0 && selectedRequest < patientRequests.size())
                                 {
                                     
                                     auto r = patientRequests[selectedRequest];
                                     
                                     if (!Patient::alreadyExists(r.getPatientId())) return;
                                     
                                     Request::sign(r.getPatientId(), r.getEquipmentId(), 1, GlobalVar::currAuthUsername);

                                     auto reqP = Patient::fetch(r.getPatientId());
                                     r.writeToTranscript(Equipment::getEquipment(r.getEquipmentId()).validateInsurance(reqP.getInsurance().first, reqP.getInsurance().second));

                                     patientRequests.clear();
                                     patientRequests = Request::fetchAll(true);
                                     updateList(patientRequests, reqDisplayList);
                                 } });

    auto rejectButton = Button("Reject Patient", [&]
                               {
                                 if (!patientRequests.empty() && selectedRequest >= 0 && selectedRequest < patientRequests.size())
                                 {
                                     auto r = patientRequests[selectedRequest];

                                     if (!Patient::alreadyExists(r.getPatientId())) return;

                                     Request::sign(r.getPatientId(), r.getEquipmentId(), -1, GlobalVar::currAuthUsername);
                                     
                                     patientRequests.clear();
                                     patientRequests = Request::fetchAll(true);
                                     updateList(patientRequests, reqDisplayList);
                                 } });

    auto signPatientTab = Container::Vertical({requestMenu, Container::Horizontal({refreshButton, signButton, rejectButton})});

    Component signPatientTabUI = Renderer(signPatientTab, [&]
                                          { return vbox({(!reqDisplayList.empty() ? requestMenu->Render() : text("No Pending Requests")) | borderRounded | flex_shrink,
                                                         hbox(refreshButton->Render(),
                                                              signButton->Render(), rejectButton->Render()) |
                                                             center}) |
                                                   flex | center; });

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
