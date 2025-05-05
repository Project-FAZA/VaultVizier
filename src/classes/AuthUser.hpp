#ifndef AUTH_HPP
#define AUTH_HPP

#include <iostream>
#include "GlobalVars.hpp"
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
    static void create(string username, string pw, bool doctor = false);
    static bool isDoctor(string username);
};

#endif