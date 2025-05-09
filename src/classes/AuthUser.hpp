#ifndef AUTH_HPP
#define AUTH_HPP

#include <iostream>
#include "GlobalVars.hpp"
using namespace std;

class AuthUser
{
public:
    static string encrypt(string p);
    static bool verifyPassword(string username, string inputPassword);
    static bool alreadyExists(string username);
    static void create(string username, string pw, bool doctor, string firstName, string lastName);
    static bool isDoctor(string username);
    static string fetchFullName(string username);
};

#endif