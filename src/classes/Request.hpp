#ifndef REQ_HPP
#define REQ_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "GlobalVars.hpp"
using namespace std;

class Request
{
private:
    string patientId;
    string equipmentId;
    int reqStatus; // -1 = Pending 0 = Rejected 1 = Accepted
    string reason;
    string signedBy;

public:
    Request(string patientId, string equipmentId, int reqStatus = 0, string reason = "", string signedBy = "")
        : patientId(patientId), equipmentId(equipmentId), reqStatus(reqStatus), reason(reason), signedBy(signedBy) {}

    void save();
    void writeToTranscript(string message);

    static bool alreadyExists(string patientId, string equipmentId);
    static void sign(string patientId, string equipmentId, int sign, string signedBy);
    static vector<Request> fetchAll(bool pendingOnly = false);
    static void clearDone();

    string getPatientId() const { return patientId; }
    string getEquipmentId() const { return equipmentId; }
    int getReqStatus() const { return reqStatus; }
    string getReason() const { return reason; }
    string getSignedBy() const { return signedBy; }
};

#endif