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

string Equipment::validateInsurance(bool medicare, bool medicaid) const
{
    if (requiresMedicare && !medicare)
        return "";

    if (!requiresMedicare && !medicaid)
        return "";

    if (requiresMedicare)
    {
        if (medicaid)
            return "100% off (free) | " + to_string(0.0);
        else
            return "80% off | " + to_string(price * 0.2);
    }
    else
    {
        return "0% off (paid) | " + to_string(price);
    }

    return "";
}

Equipment Equipment::getEquipment(const string &c)
{
    for (const auto &equipment : equipments)
    {
        if (equipment.getCode() == c)
        {
            return equipment;
        }
    }

    throw runtime_error("Equipment with the given code not found");
}

vector<Equipment> Equipment::equipments = {
    Equipment("MWC", "Manual Wheelchair", true, 250.0),
    Equipment("ROL", "Rollator", false, 150.0),
    Equipment("WLK", "Walker", true, 100.0),
    Equipment("HBD", "Hospital Bed", false, 500.0)};