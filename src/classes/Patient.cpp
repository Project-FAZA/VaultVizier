#include "Patient.hpp"
#include <iostream>

// Simple date validation
bool isValidDate(const Date &date)
{
    if (date.y < 0 || date.m < 1 || date.m > 12 || date.d < 1)
        return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31};

    // Leap year check
    if (date.m == 2 && ((date.y % 4 == 0 && date.y % 100 != 0) || (date.y % 400 == 0)))
    {
        daysInMonth[1] = 29;
    }

    return date.d <= daysInMonth[date.m - 1];
}

Patient::Patient(const std::string &firstName, const std::string &lastName, const Date &dob, const Address &address)
    : firstName(firstName), lastName(lastName), dob(dob), address(address) {}

// Setters
void Patient::setFirstName(const string &fname)
{
    if (fname.empty() || fname.length() > 20)
    {
        std::cerr << "Invalid first name. Must be 1-20 characters.\n";
        firstName = "Unknown";
    }
    else
    {
        firstName = fname;
    }
}

void Patient::setLastName(const string &lname)
{
    if (lname.empty() || lname.length() > 20)
    {
        std::cerr << "Invalid last name. Must be 1-20 characters.\n";
        lastName = "Unknown";
    }
    else
    {
        lastName = lname;
    }
}

void Patient::setDOB(const Date &date)
{
    if (isValidDate(date))
    {
        dob = date;
    }
    else
    {
        std::cerr << "Invalid date of birth. Setting to default 01/01/2000.\n";
        dob = {1, 1, 2000};
    }
}

void Patient::setAddress(const Address &addr)
{
    address = addr; // You could add validation here too if needed
}

// Getters
string Patient::getFirstName() const { return firstName; }
string Patient::getLastName() const { return lastName; }
Date Patient::getDOB() const { return dob; }
Address Patient::getAddress() const { return address; }

void Patient::save()
{
    cout << "Saved!"; // Yeh toh hyderabadi karega // Update: abay yaar ab mujhy hee karna parega
}

vector<Patient> Patient::fetchAll()
{
    ifstream file("patients.csv");

    if (!file.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return {};
    }

    string line;
    vector<Patient> pats;

    getline(file, line); // to skip header line
    while (getline(file, line))
    {
        stringstream lineStream(line);

        string firstName, lastName;
        string dob_dStr, dob_mStr, dob_yStr;
        string add_street, add_city, add_state, add_zipCode, add_country;

        getline(lineStream, firstName, ',');
        getline(lineStream, lastName, ',');
        getline(lineStream, dob_dStr, ',');
        getline(lineStream, dob_mStr, ',');
        getline(lineStream, dob_yStr, ',');
        getline(lineStream, add_street, ',');
        getline(lineStream, add_city, ',');
        getline(lineStream, add_state, ',');
        getline(lineStream, add_zipCode, ',');
        getline(lineStream, add_country, ',');

        Patient p(firstName, lastName, Date{stoi(dob_dStr), stoi(dob_mStr), stoi(dob_yStr)}, Address{add_street, add_city, add_state, add_zipCode, add_country});

        pats.push_back(p);
    }

    file.close();
    return pats;
}