#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include "classes/Patient.hpp"
#include "components/components.hpp"

using namespace ftxui;

// ftxui::InputOption input_option()
// {
//     ftxui::InputOption option{ftxui::InputOption::Default()};
//     option.multiline = false;
//     return option;
// }

// int main()
// {

//     std::string msg = "";

//     std::string firstName, lastName;
//     std::string dobDay, dobMonth, dobYear;
//     std::string street, city, state, zipCode, country;

//     auto screen = ScreenInteractive::TerminalOutput();
//     Patient patient("", "", Date{0, 0, 0}, Address{"", "", "", "", ""});

//     // Input fields
//     auto firstNameInput = Input(&firstName, "First Name", input_option());
//     auto lastNameInput = Input(&lastName, "Last Name", input_option());
//     auto dobDayInput = Input(&dobDay, "Day", input_option());
//     auto dobMonthInput = Input(&dobMonth, "Month", input_option());
//     auto dobYearInput = Input(&dobYear, "Year", input_option());

//     auto streetInput = Input(&street, "Street Address", input_option());
//     auto cityInput = Input(&city, "City", input_option());
//     auto stateInput = Input(&state, "State", input_option());
//     auto zipInput = Input(&zipCode, "Zip Code", input_option());
//     auto countryInput = Input(&country, "Country", input_option());

//     auto submitButton = Button("Submit", [&]
//                                {
//         if (firstName.empty() || lastName.empty() ||
//             dobDay.empty() || dobMonth.empty() || dobYear.empty() ||
//             street.empty() || city.empty() || state.empty() ||
//             zipCode.empty() || country.empty()) {
//             msg = "All fields must be filled out!";
//             return;
//         }

//         try {
//             int d = std::stoi(dobDay);
//             int m = std::stoi(dobMonth);
//             int y = std::stoi(dobYear);
//             Date dob{d, m, y};

//             if (!isValidDate(dob)) {
//                 msg = "Invalid Date of Birth!";
//                 return;
//             }

//             patient.setFirstName(firstName);
//             patient.setLastName(lastName);
//             patient.setDOB(dob);
//             patient.setAddress(Address{street, city, state, zipCode, country});

//             msg = "Patient Registered Successfully!";
//             patient.save();
//             screen.Exit();
//         } catch (...) {
//             msg = "Invalid date values!";
//         } });

//     // Create layout container
//     auto container = Container::Vertical({firstNameInput,
//                                           lastNameInput,
//                                           Container::Horizontal({dobDayInput, dobMonthInput, dobYearInput}),
//                                           streetInput, cityInput, stateInput, zipInput, countryInput,
//                                           submitButton});

//     // Decorate the UI
//     Component decorated = Renderer(container, [&]
//                                    { return vbox({
//                                                 text("Patient Registration Form") | bold | center | border,
//                                                 separator(),
//                                                 vbox({
//                                                     text("Personal Info") | bold,
//                                                     firstNameInput->Render(),
//                                                     lastNameInput->Render(),
//                                                 }) | border |
//                                                     flex,

//                                                 vbox({
//                                                     text("Date of Birth") | bold,
//                                                     hbox({
//                                                         dobDayInput->Render() | flex,
//                                                         dobMonthInput->Render() | flex,
//                                                         dobYearInput->Render() | flex,
//                                                     }),
//                                                 }) | border,

//                                                 vbox({
//                                                     text("Address") | bold,
//                                                     streetInput->Render(),
//                                                     cityInput->Render(),
//                                                     stateInput->Render(),
//                                                     zipInput->Render(),
//                                                     countryInput->Render(),
//                                                 }) | border,

//                                                 submitButton->Render() | center,
//                                                 text(" "),
//                                                 text(msg) | color(Color::Yellow) | center,
//                                             }) |
//                                             border | flex | hcenter; });

//     screen.Loop(decorated);
// }

int main()
{
    auto status = ScreenStatus::LOGIN;
    auto screen = ScreenInteractive::TerminalOutput();

    while (true)
    {
        std::cout << "\033[2J\033[H";
        std::cout.flush();

        if (status == ScreenStatus::DASHBOARD)
            Dashboard(screen, &status);
        else if (status == ScreenStatus::DOCTOR_DASHBOARD)
            DoctorDashboard(screen, &status);
        else if (status == ScreenStatus::LOGIN)
            Login(screen, &status);
        else if (status == ScreenStatus::CREATE_ACC)
            CreateAcc(screen, &status);

        std::cout << "\033[2J\033[H";
        std::cout.flush();
    }

    // vector<Patient> pats = Patient::fetchAll();

    // cout << pats[0].getFirstName() << " " << pats[0].getLastName() << endl;

    // int x;
    // cin >> x;
}
