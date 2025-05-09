#include "Doctor.hpp"

// Setters
void Doctor::setFirstName(const string &fname)
{
    if (fname.empty() || fname.length() > 20)
    {
        // std::cerr << "Invalid first name. Must be 1-20 characters.\n";
        firstName = "Unknown";
    }
    else
    {
        firstName = fname;
    }
}

void Doctor::setLastName(const string &lname)
{
    if (lname.empty() || lname.length() > 20)
    {
        // std::cerr << "Invalid last name. Must be 1-20 characters.\n";
        lastName = "Unknown";
    }
    else
    {
        lastName = lname;
    }
}

void Doctor::setFaxNumber(const string &fax)
{
    if (fax.empty() || fax.length() > 20)
    {
        // std::cerr << "Invalid last name. Must be 1-20 characters.\n";
        faxNumber = "000-000-000-0000";
    }
    else
    {
        faxNumber = fax;
    }
}

// Getters
string Doctor::getFirstName() const { return firstName; }
string Doctor::getLastName() const { return lastName; }
string Doctor::getFaxNumber() const { return faxNumber; }
