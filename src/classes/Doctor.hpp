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

    // Getters
    string getFirstName() const;
    string getLastName() const;
};

#endif