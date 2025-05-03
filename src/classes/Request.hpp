#ifndef REQ_HPP
#define REQ_HPP

#include <iostream>
using namespace std;

class Request
{
private:
    string patientId;
    string equipmentId;
    int quantity;
    int reqStatus; // -1 = Pending 0 = Rejected 1 = Accepted

public:
    void save();
    static bool alreadyExists();
};

#endif