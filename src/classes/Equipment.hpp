#ifndef EQ_HPP
#define EQ_HPP

#include <iostream>
using namespace std;

class Patient;

class Equipment
{

private:
    string code;
    bool requiresMedicare; //if false, then it requires Medicaid
    double price;

public: 

    Equipment(const string &c, const bool &reqMed, const double &p);
    //setters
    void setCode(const string &c);
    void setRequiresMedicare(const bool &medi);
    void setPrice(const double &p);

    //getters
    string getCode();
    bool getRequiresMedicare();
    double getPrice();

    double calculateActualPrice(Patient &pt);

};

#endif
