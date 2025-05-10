#include "Equipment.hpp"
#include "Patient.hpp"
#include <iostream>

using namespace std;

Equipment::Equipment(const string &c, const string &n, const bool &reqMed, const double &p)
    : code(c), name(n), requiresMedicare(reqMed), price(p) {}

void Equipment::setCode(const string &c)
{
    code = c;
}

void Equipment::setName(const string &n)
{
    name = n;
}

void Equipment::setRequiresMedicare(const bool &medi)
{
    requiresMedicare = medi;
}

void Equipment::setPrice(const double &p)
{
    price = p;
}

string Equipment::getCode() const
{
    return code;
}

string Equipment::getName() const
{
    return name;
}

bool Equipment::getRequiresMedicare() const
{
    return requiresMedicare;
}

double Equipment::getPrice() const
{
    return price;
}

string Equipment::validateInsurance(bool medicare, bool medicaid, bool equipmentRequiresMedicare, bool equipmentRequiresMedicaid) const
{
    if (!medicare)
        return "";

    if (equipmentRequiresMedicare)
    {
        if (medicaid)
            return "100% off (free)";
        else
            return "80% off";
    }
    else
    {
        if (!medicaid)
            return "";
        if (equipmentRequiresMedicaid)
            return "Paid full price aka 0% off";
    }

    return "";
}

vector<Equipment> Equipment::equipments = {
    Equipment("MWC", "Manual Wheelchair", true, 250.0),
    Equipment("ROL", "Rollator", false, 150.0),
    Equipment("WLK", "Walker", true, 100.0),
    Equipment("HBD", "Hospital Bed", false, 500.0)};