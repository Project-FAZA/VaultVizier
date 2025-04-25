#ifndef PAT_HPP
#define PAT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Date
{
    int d;
    int m;
    int y;
};

bool isValidDate(const Date &date);

struct Address
{
    string street;
    string city;
    string state;
    string zipCode;
    string country;
};

class Patient
{
private:
    string firstName;
    string lastName;
    Date dob;
    Address address;

public:
    Patient(const string &fname, const string &lname, const Date &date, const Address &addr);

    // Setters
    void
    setFirstName(const string &fname);
    void setLastName(const string &lname);
    void setDOB(const Date &date);
    void setAddress(const Address &addr);

    // Getters
    string getFirstName() const;
    string getLastName() const;
    Date getDOB() const;
    Address getAddress() const;

    // adds/updates to actual database;
    void save();
    static vector<Patient> fetchAll();
};

#endif