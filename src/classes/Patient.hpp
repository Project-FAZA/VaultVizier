#ifndef PAT_HPP
#define PAT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

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
    string firstName;
    string lastName;
    Date dob;
    Address address;
    bool gender;        // F = female , T = male
    string phoneNumber; //+92-301-23456789
    float weight;       // kg
    float height;       // ft
    int maritalStatus;  //{-1 = widowed, 0 = single, 1 = married}

public:
    Patient(const string &fname, const string &lname, const Date &date, const Address &addr);

    // Setters
    void setFirstName(const string &fname);
    void setLastName(const string &lname);
    void setDOB(const Date &date);
    void setAddress(const Address &addr);
    void setGender(const bool &sex);
    void setPhoneNumber(const string &num);
    void setWeight(const float &w);
    void setHeight(const float &h);
    void setMaritalStatus(const int &married);

    // Getters
    string getFirstName() const;
    string getLastName() const;
    Date getDOB() const;
    Address getAddress() const;
    bool getGender() const;
    string getPhoneNumber() const;
    float getHeight() const;
    float getWeight() const;
    int getMaritalStatus() const;

    // adds/updates to actual database
    string toCSV();
    void save();
    static vector<Patient> fetchAll();
};

#endif
