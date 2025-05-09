#ifndef DOC_HPP
#define DOC_HPP

#include "AuthUser.hpp"

class Doctor : AuthUser
{
private:
    string firstName;
    string lastName;
    string faxNumber;

public:
    // Setters
    void setFirstName(const string &fname);
    void setLastName(const string &lname);
    void setFaxNumber(const string &fax);

    // Getters
    string getFirstName() const;
    string getLastName() const;
    string getFaxNumber() const;
};

#endif