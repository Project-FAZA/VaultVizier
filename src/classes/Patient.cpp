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
    : first_name(firstName), last_name(lastName), dob(dob), address(address) {}

// Setters
void Patient::setFirstName(const string &fname)
{
    if (fname.empty() || fname.length() > 20)
    {
        std::cerr << "Invalid first name. Must be 1-20 characters.\n";
        first_name = "Unknown";
    }
    else
    {
        first_name = fname;
    }
}

void Patient::setLastName(const string &lname)
{
    if (lname.empty() || lname.length() > 20)
    {
        std::cerr << "Invalid last name. Must be 1-20 characters.\n";
        last_name = "Unknown";
    }
    else
    {
        last_name = lname;
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
string Patient::getFirstName() const { return first_name; }
string Patient::getLastName() const { return last_name; }
Date Patient::getDOB() const { return dob; }
Address Patient::getAddress() const { return address; }

void Patient::save()
{
    cout << "Saved!"; // Yeh toh hyderabadi karega
}