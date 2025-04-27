#include "Patient.hpp"
#include <iostream>

// Simple date validation
bool isValidDate(const Date &date)
{
    if (date.y < 0 || date.m < 1 || date.m > 12 || date.d < 1)
        return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31};

    // Leap year check
    if (date.m == 2 && ((date.y % 4 == 0 && date.y % 100 != 0) || (date.y % 400 == 0)))
    {
        daysInMonth[1] = 29;
    }

    return date.d <= daysInMonth[date.m - 1];
}

string validateField(const string &field, int maxLength, const string &fieldName)
{
    if (field.empty() || field.length() > maxLength)
    {
        std::cerr << "Invalid " << fieldName << ".\n";
        return "Unknown";
    }
    return field;
}

// digit checker
bool isAllDigits(const string &s)
{
    for (char c : s)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

bool validatePhoneNumber(const string &phone)
{
    string digitsOnly;
    int start = 0, dashes = 0;
    if (phone[0] == '+')
    {
        start = 1;
    }

    for (int i = start; i < phone.length(); i++)
    {
        if (phone[i] == '-')
        {
            dashes++;
            if (dashes > 1)
            {
                return false; // check for consecutive dashes
            }

            continue;
        }
        if (!isdigit(phone[i]))
        {
            return false;
        }
        else
        {
            digitsOnly += phone[i];
            dashes = 0;
        }
    }

    if (digitsOnly.length() < 10 || digitsOnly.length() > 15)
    {
        return false;
    }

    return true;
}

Patient::Patient(const std::string &firstName, const std::string &lastName, const Date &dob, const Address &address)
    : firstName(firstName), lastName(lastName), dob(dob), address(address) {}

// Setters
void Patient::setFirstName(const string &fname)
{
    if (fname.empty() || fname.length() > 20)
    {
        std::cerr << "Invalid first name. Must be 1-20 characters.\n";
        firstName = "Unknown";
    }
    else
    {
        firstName = fname;
    }
}

void Patient::setLastName(const string &lname)
{
    if (lname.empty() || lname.length() > 20)
    {
        std::cerr << "Invalid last name. Must be 1-20 characters.\n";
        lastName = "Unknown";
    }
    else
    {
        lastName = lname;
    }
}

void Patient::setDOB(const Date &date)
{
    if (isValidDate(date))
    {
        dob = date;
    }
    else
    {
        std::cerr << "Invalid date of birth. Setting to default 01/01/2000.\n";
        dob = {1, 1, 2000};
    }
}

void Patient::setAddress(const Address &addr)
{
    // Zain Bhai edit validating address
    address.street = validateField(addr.street, 100, "Street name");
    address.city = validateField(addr.city, 25, "City name");
    address.state = validateField(addr.state, 25, "State name");
    address.country = validateField(addr.country, 25, "Country name");
    if (addr.zipCode.empty() || addr.zipCode.length() != 5 || !isAllDigits(addr.zipCode))
    {
        std::cerr << "Invalid Zip Code. It must be exactly 5 digits.\n";
        address.zipCode = "Unknown";
    }
    else
    {
        address.zipCode = addr.zipCode;
    }
}

void Patient::setGender(const bool &sex)
{
    gender = sex;
}

void Patient::setPhoneNumber(const string &num)
{
    if (validatePhoneNumber(num))
    {
        phoneNumber = num;
    }
    else
    {
        std::cerr << "Invalid phone number.\n Expected format: +92-300-1234567 or 923001234567.\n Setting to default.\n";
        phoneNumber = "+00-000-000000";
    }
}

void Patient::setHeight(const float &h)
{
    if (h <= 0 || h >= 9)
    {
        std::cerr << "Invalid height value. Setting to 0.\n";
        height = 0.0f;
    }
    else
    {
        height = h;
    }
}

void Patient::setWeight(const float &w)
{
    if (w <= 0 || w > 200)
    {
        std::cerr << "Invalid weight value. Setting to 0.\n";
        weight = 0.0f;
    }
    else
    {
        weight = w;
    }
}

void Patient::setMaritalStatus(const int &married)
{
    if (married >= -1 && married <= 1)
    {
        maritalStatus = married;
    }
    else
    {
        std::cerr << "Invalid Marital Status. Setting to single\n";
        maritalStatus = 0;
    }
}

// Getters
string Patient::getFirstName() const { return firstName; }
string Patient::getLastName() const { return lastName; }
Date Patient::getDOB() const { return dob; }
Address Patient::getAddress() const { return address; }
bool Patient::getGender() const { return gender; }
string Patient::getPhoneNumber() const { return phoneNumber; }
float Patient::getHeight() const { return height; }
float Patient::getWeight() const { return weight; }
int Patient::getMaritalStatus() const { return maritalStatus; }

string Patient::toCSV()
{
    return firstName + "," +
           lastName + "," +
           to_string(dob.d) + "," + to_string(dob.m) + "," + to_string(dob.y) + "," +
           address.street + "," +
           address.city + "," +
           address.state + "," +
           address.zipCode + "," +
           address.country;
}

void Patient::save()
{
    ofstream file;
    file.open("patients.csv", ios::app);

    if (!file)
    {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    file << toCSV() << endl; // Write CSV line
    file.close();
}

vector<Patient> Patient::fetchAll()
{
    ifstream file("patients.csv");

    if (!file.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return {};
    }

    string line;
    vector<Patient> pats;

    getline(file, line); // to skip header line
    while (getline(file, line))
    {
        stringstream lineStream(line);

        string firstName, lastName;
        string dob_dStr, dob_mStr, dob_yStr;
        string add_street, add_city, add_state, add_zipCode, add_country;

        getline(lineStream, firstName, ',');
        getline(lineStream, lastName, ',');
        getline(lineStream, dob_dStr, ',');
        getline(lineStream, dob_mStr, ',');
        getline(lineStream, dob_yStr, ',');
        getline(lineStream, add_street, ',');
        getline(lineStream, add_city, ',');
        getline(lineStream, add_state, ',');
        getline(lineStream, add_zipCode, ',');
        getline(lineStream, add_country, ',');

        Patient p(firstName, lastName, Date{stoi(dob_dStr), stoi(dob_mStr), stoi(dob_yStr)}, Address{add_street, add_city, add_state, add_zipCode, add_country});

        pats.push_back(p);
    }

    file.close();
    return pats;
}
