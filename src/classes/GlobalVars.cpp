#include "GlobalVars.hpp"
#include "Patient.hpp"

void GlobalVar::createIfDoesNotExist(const string &filename, const string &content)
{
    ifstream infile(filename);
    if (!infile)
    {
        ofstream outfile(filename);
        if (!outfile)
        {
            cerr << "Failed to create file: " << filename << endl;
        }
        else
        {
            outfile << content << endl;
        }
    }
}

void GlobalVar::assignEditValues(string *ssn, string *firstName, string *lastName, string *dobDay, string *dobMonth, string *dobYear, string *street, string *city, string *state, string *zipCode, string *country, string *phoneNumber, string *weight, string *height, int *genderSelected, int *married, bool *medicare, bool *medicaid)
{
    if (selectedSSN.empty() || !editMode)
        return;

    editMode = false;
    Patient selected = Patient::fetch(selectedSSN);
    selectedSSN = "";

    if (ssn)
        *ssn = selected.getSSN();
    if (firstName)
        *firstName = selected.getFirstName();
    if (lastName)
        *lastName = selected.getLastName();

    auto dob = selected.getDOB();

    if (dobDay)
        *dobDay = to_string(dob.d);
    if (dobMonth)
        *dobMonth = to_string(dob.m);
    if (dobYear)
        *dobYear = to_string(dob.y);

    auto addr = selected.getAddress();

    if (street)
        *street = addr.street;
    if (city)
        *city = addr.city;
    if (state)
        *state = addr.state;
    if (zipCode)
        *zipCode = addr.zipCode;
    if (country)
        *country = addr.country;

    if (phoneNumber)
        *phoneNumber = selected.getPhoneNumber();
    if (weight)
    {
        *weight = to_string(selected.getWeight());
    }
    if (height)
        *height = to_string(selected.getHeight());

    if (genderSelected)
        *genderSelected = !selected.getGender();

    if (married)
        *married = selected.getMaritalStatus() + 1;

    if (medicare && medicaid)
    {
        *medicare = selected.getInsurance().first;
        *medicaid = selected.getInsurance().second;
    }
}
