#ifndef EQ_HPP
#define EQ_HPP

#include <iostream>
#include <vector>

using namespace std;

class Patient;

class Equipment
{
private:
    string code;
    string name;           // added name property
    bool requiresMedicare; // if false, then it requires Medicaid
    double price;

public:
    Equipment(const string &c, const string &n, const bool &reqMed, const double &p);

    // setters
    void setCode(const string &c);
    void setName(const string &n); // setter for name
    void setRequiresMedicare(const bool &medi);
    void setPrice(const double &p);

    // getters
    string getCode() const;
    string getName() const; // getter for name
    bool getRequiresMedicare() const;
    double getPrice() const;
    string validateInsurance(bool medicare, bool medicaid, bool equipmentRequiresMedicare, bool equipmentRequiresMedicaid) const;

    static vector<Equipment> equipments;
};

#endif
