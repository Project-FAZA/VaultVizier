#ifndef AUTH_HPP
#define AUTH_HPP

#include <iostream>
using namespace std;

class AuthUser
{
private:
    string username;
    string password;

public:
    string getUsername();

    static string encrypt(string p);
    static bool verifyPassword(string username, string inputPassword);
    static bool alreadyExists(string username);
};

#endif