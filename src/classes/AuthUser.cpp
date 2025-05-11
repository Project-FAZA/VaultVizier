#include "AuthUser.hpp"
#include <fstream>
#include <string>
#include <sstream>

string AuthUser::encrypt(string p)
{
    return p;
}

bool AuthUser::verifyPassword(string username, string inputPassword)
{
    ifstream file("auth.csv");

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        stringstream lineStream(line);

        string fileUsername;
        getline(lineStream, fileUsername, ',');

        string actualPassword;
        getline(lineStream, actualPassword, ',');

        if (fileUsername == username)
            return actualPassword == encrypt(inputPassword);
    }

    return false;
}

bool AuthUser::alreadyExists(string username)
{
    GlobalVar::createIfDoesNotExist("auth.csv", "username,password,type,fname,lname");
    ifstream file("auth.csv");

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        stringstream lineStream(line);

        string fileUsername;
        getline(lineStream, fileUsername, ',');

        if (fileUsername == username)
            return true;
    }

    file.close();
    return false;
}

void AuthUser::create(string username, string pw, bool doctor, string firstName, string lastName)
{
    ofstream file;
    file.open("auth.csv", ios::app);

    if (!file)
    {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    file << username << "," << pw << "," << (doctor ? "1" : "0") << "," << firstName << "," << lastName << endl;
    file.close();
}

bool AuthUser::isDoctor(string username)
{
    ifstream file("auth.csv");

    string line;
    getline(file, line); // Skip header

    while (getline(file, line))
    {
        stringstream lineStream(line);

        string fileUsername;
        getline(lineStream, fileUsername, ',');

        string password;
        getline(lineStream, password, ',');

        string type;
        getline(lineStream, type, ',');

        if (fileUsername == username)
            return type == "1";
    }

    return false;
}

string AuthUser::fetchFullName(string username)
{
    ifstream file("auth.csv");
    string line;

    if (!file)
    {
        cerr << "Error: Unable to open file." << endl;
        return "";
    }

    // Read through the file line by line
    while (getline(file, line))
    {
        stringstream ss(line);
        string user, pw, doctorFlag, firstName, lastName;

        // Parse the CSV line
        getline(ss, user, ',');
        getline(ss, pw, ',');
        getline(ss, doctorFlag, ',');
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');

        // If the username matches, return the full name
        if (user == username)
        {
            file.close();
            return firstName + " " + lastName;
        }
    }

    file.close();
    return ""; // Username not found
}
