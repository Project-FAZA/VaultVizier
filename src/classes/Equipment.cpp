#include "Equipment.hpp"
#include "Patient.hpp"
#include <iostream>

using namespace std;

Equipment::Equipment(const string &c, const bool &reqMed, const double &p)
: code(c) , requiresMedicare(reqMed), price(p) {}

void Equipment::setCode(const string &c)
{
    code = c;
}

void Equipment::setRequiresMedicare(const bool &medi)
{
    requiresMedicare = medi;
}

void Equipment::setPrice(const double &p)
{
    price = p;
}

string Equipment::getCode()
{
    return code;
}

bool Equipment::getRequiresMedicare()
{
    return requiresMedicare;
}

double Equipment::getPrice()
{
    return price;
}