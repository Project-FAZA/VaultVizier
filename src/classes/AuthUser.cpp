#include "AuthUser.hpp"
#include <fstream>
#include <string>
#include <sstream>

string AuthUser::getUsername()
{
    return username;
}

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
