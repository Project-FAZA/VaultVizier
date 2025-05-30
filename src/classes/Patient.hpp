#ifndef PAT_HPP
#define PAT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include "GlobalVars.hpp"

using namespace std;

struct Date
{
    int d;
    int m;
    int y;
};

struct Address
{
    string street;
    string city;
    string state;
    string zipCode;
    string country;
};

// validation func
bool isValidDate(const Date &date);
string validateField(const string &field, int maxLength, const string &fieldName);
bool isAllDigits(const string &s);
bool validatePhoneNumber(const string &phone);

class Patient
{
private:
    string ssn; // XXXXX-XXXXXX-X
    string firstName;
    string lastName;
    Date dob;
    Address address;
    bool gender;        // F = female , T = male
    string phoneNumber; //+92-301-23456789
    float weight;       // kg
    float height;       // ft
    int maritalStatus;  //{-1 = widowed, 0 = single, 1 = married}
    bool medicare;      // true if patient has Medicare
    bool medicaid;      // true if patient has Medicaid

public:
    Patient(const string &fname, const string &lname, const Date &date, const Address &addr);
    Patient();
    Patient(const string &ssn,
            const string &fname,
            const string &lname,
            const Date &date,
            const Address &addr,
            const bool &gender,
            const string &phone,
            const float &weight,
            const float &height,
            const int &maritalStatus);

    // Setters
    void setSSN(const string s);
    void setFirstName(const string &fname);
    void setLastName(const string &lname);
    void setDOB(const Date &date);
    void setAddress(const Address &addr);
    void setGender(const bool &sex);
    void setPhoneNumber(const string &num);
    void setWeight(const float &w);
    void setHeight(const float &h);
    void setMaritalStatus(const int &married);
    void setInsurance(const bool &medicare, const bool &medicaid);

    // Getters
    string getSSN() const;
    string getFirstName() const;
    string getLastName() const;
    Date getDOB() const;
    Address getAddress() const;
    bool getGender() const;
    string getPhoneNumber() const;
    float getHeight() const;
    float getWeight() const;
    int getMaritalStatus() const;
    pair<bool, bool> getInsurance() const;

    // adds/updates to actual database
    string toCSV() const;
    void save();

    static bool alreadyExists(string s);
    static vector<Patient> fetchAll();
    static Patient fetch(string c);
};

#endif
