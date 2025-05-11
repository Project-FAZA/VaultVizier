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
        // cerr << "Invalid " << fieldName << ".\n";
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

Patient::Patient(const string &firstName, const string &lastName, const Date &dob, const Address &address)
    : firstName(firstName), lastName(lastName), dob(dob), address(address) {}

Patient::Patient()
{
}

Patient::Patient(const string &ssn, const string &fname, const string &lname, const Date &date, const Address &addr, const bool &gender, const string &phone, const float &weight, const float &height, const int &maritalStatus)
    : ssn(ssn), firstName(fname), lastName(lname), dob(date), address(addr),
      gender(gender), phoneNumber(phone), weight(weight), height(height), maritalStatus(maritalStatus)
{
}

void Patient::setSSN(const string s)
{
    ssn = s;
}

// Setters
void Patient::setFirstName(const string &fname)
{
    if (fname.empty() || fname.length() > 20)
    {
        // cerr << "Invalid first name. Must be 1-20 characters.\n";
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
        // cerr << "Invalid last name. Must be 1-20 characters.\n";
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
        // cerr << "Invalid date of birth. Setting to default 01/01/2000.\n";
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
        // cerr << "Invalid Zip Code. It must be exactly 5 digits.\n";
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
    phoneNumber = num;
}

void Patient::setHeight(const float &h)
{
    if (h <= 0)
    {
        // cerr << "Invalid height value. Setting to 0.\n";
        height = 0.0f;
    }
    else
    {
        height = h;
    }
}

void Patient::setWeight(const float &w)
{
    if (w <= 0)
    {
        // cerr << "Invalid weight value. Setting to 0.\n";
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
        // cerr << "Invalid Marital Status. Setting to single\n";
        maritalStatus = 0;
    }
}

void Patient::setInsurance(const bool &medicare, const bool &medicaid)
{
    this->medicare = medicare;
    this->medicaid = medicaid;
}

string Patient::getSSN() const
{
    return ssn;
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

pair<bool, bool> Patient::getInsurance() const
{
    return pair(medicare, medicaid);
}

string Patient::toCSV() const
{
    return ssn + "," +
           firstName + "," +
           lastName + "," +
           to_string(dob.d) + "," + to_string(dob.m) + "," + to_string(dob.y) + "," +
           address.street + "," +
           address.city + "," +
           address.state + "," +
           address.zipCode + "," +
           address.country + "," +
           phoneNumber + "," +
           (gender ? "1" : "0") + "," +
           to_string(weight) + "," +
           to_string(height) + "," +
           to_string(maritalStatus) + "," +
           (medicare ? "1" : "0") + "," +
           (medicaid ? "1" : "0");
}

void Patient::save()
{
    vector<Patient> allPatients = Patient::fetchAll();
    bool found = false;

    // Update if exists, else add
    for (auto &p : allPatients)
    {
        if (p.getSSN() == this->ssn)
        {
            p = *this;
            found = true;
            break;
        }
    }

    if (!found)
    {
        allPatients.push_back(*this);
    }

    const string tempFileName = "patients_temp.csv";
    ofstream tempFile(tempFileName);
    if (!tempFile.is_open())
    {
        // cerr << "Error: Unable to open temporary file for writing." << endl;
        return;
    }

    // Write header
    tempFile << "ssn,firstname,lastname,d,m,y,street,city,state,zip,country,phone,gender,weight,height,married,medicare,medicaid" << endl;

    // Write patient records
    for (const Patient p : allPatients)
    {
        tempFile << p.toCSV() << endl;
    }

    tempFile.close();

    // Replace the original file with the temp file
    if (remove("patients.csv") != 0)
    {
        // cerr << "Error: Could not remove original file." << endl;
        return;
    }

    if (rename(tempFileName.c_str(), "patients.csv") != 0)
    {
        // cerr << "Error: Could not rename temporary file." << endl;
        return;
    }
}

bool Patient::alreadyExists(const string ssnToFind)
{
    GlobalVar::createIfDoesNotExist("patients.csv", "ssn,firstname,lastname,d,m,y,street,city,state,zip,country,phone,gender,weight,height,married");
    ifstream file("patients.csv");

    if (!file.is_open())
    {
        // cerr << "Error: Unable to open file." << endl;
        return false;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream lineStream(line);
        string ssn;

        getline(lineStream, ssn, ',');

        if (ssn == ssnToFind)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

vector<Patient> Patient::fetchAll()
{
    GlobalVar::createIfDoesNotExist("patients.csv", "firstname,lastname,d,m,y,street,city,state,zip,country,phone,gender,weight,height,married,medicare,medicaid");
    ifstream file("patients.csv");

    if (!file.is_open())
    {
        // cerr << "Error: Unable to open file." << endl;
        return {};
    }

    string line;
    vector<Patient> pats;

    getline(file, line); // to skip header line
    while (getline(file, line))
    {
        stringstream lineStream(line);
        string ssn, firstName, lastName;
        string dStr, mStr, yStr;
        string street, city, state, zip, country;
        string phone, genderStr, weightStr, heightStr, maritalStr, medicareStr, medicaidStr;

        getline(lineStream, ssn, ',');
        getline(lineStream, firstName, ',');
        getline(lineStream, lastName, ',');
        getline(lineStream, dStr, ',');
        getline(lineStream, mStr, ',');
        getline(lineStream, yStr, ',');
        getline(lineStream, street, ',');
        getline(lineStream, city, ',');
        getline(lineStream, state, ',');
        getline(lineStream, zip, ',');
        getline(lineStream, country, ',');
        getline(lineStream, phone, ',');
        getline(lineStream, genderStr, ',');
        getline(lineStream, weightStr, ',');
        getline(lineStream, heightStr, ',');
        getline(lineStream, maritalStr, ',');
        getline(lineStream, medicareStr, ',');
        getline(lineStream, medicaidStr, ',');

        Date dob = {stoi(dStr), stoi(mStr), stoi(yStr)};
        Address addr = {street, city, state, zip, country};
        bool gender = (genderStr == "1");
        float weight = stof(weightStr);
        float height = stof(heightStr);
        int maritalStatus = stoi(maritalStr);
        bool medicare = (medicareStr == "1");
        bool medicaid = (medicaidStr == "1");

        // ✅ Use full constructor here
        Patient p(ssn, firstName, lastName, dob, addr, gender, phone, weight, height, maritalStatus);
        p.setInsurance(medicare, medicaid);

        pats.push_back(p);
    }

    file.close();
    return pats;
}

Patient Patient::fetch(string ssnToFind)
{
    GlobalVar::createIfDoesNotExist("patients.csv", "ssn,firstname,lastname,d,m,y,street,city,state,zip,country,phone,gender,weight,height,married,medicare,medicaid");
    ifstream file("patients.csv");

    if (!file.is_open())
    {
        // cerr << "Error: Unable to open file." << endl;
        return Patient(); // Return default patient if file can't be opened
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line))
    {
        stringstream lineStream(line);

        string ssn, firstName, lastName;
        string dob_dStr, dob_mStr, dob_yStr;
        string add_street, add_city, add_state, add_zipCode, add_country;
        string phone, genderStr, weightStr, heightStr, marriedStr, medicareStr, medicaidStr;

        getline(lineStream, ssn, ',');
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
        getline(lineStream, phone, ',');
        getline(lineStream, genderStr, ',');
        getline(lineStream, weightStr, ',');
        getline(lineStream, heightStr, ',');
        getline(lineStream, marriedStr, ',');
        getline(lineStream, medicareStr, ',');
        getline(lineStream, medicaidStr, ',');

        if (ssn == ssnToFind)
        {
            Date dob = {stoi(dob_dStr), stoi(dob_mStr), stoi(dob_yStr)};
            Address addr = {add_street, add_city, add_state, add_zipCode, add_country};
            bool gender = (genderStr == "1" || genderStr == "true");
            float weight = stof(weightStr);
            float height = stof(heightStr);
            int maritalStatus = stoi(marriedStr);
            bool medicare = (medicareStr == "1");
            bool medicaid = (medicaidStr == "1");

            Patient p(ssn, firstName, lastName, dob, addr, gender, phone, weight, height, maritalStatus);
            p.setInsurance(medicare, medicaid);

            file.close();
            return p;
        }
    }

    file.close();
    return Patient(); // Return default if not found
}
