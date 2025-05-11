#include "Request.hpp"

void Request::save()
{
    if (alreadyExists(patientId, equipmentId))
        return;

    ofstream fout("requests.csv", ios::app);

    if (!fout)
        return;

    fout << patientId << "," << equipmentId << "," << to_string(reqStatus) << "," << reason << "," << signedBy << endl;
}

void Request::writeToTranscript(string message)
{
    ofstream file("transcript.txt", ios::app);

    if (!file)
        return;

    file << "Patient (" << patientId << ") bought Equipment (" << equipmentId << ") | " << message << endl;
}

bool Request::alreadyExists(string patientId, string equipmentId)
{
    GlobalVar::createIfDoesNotExist("requests.csv", "patient,equipment,signed,reason,signed_by");

    ifstream fin("requests.csv");
    if (!fin)
        return false;

    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string patient, equipment;

        getline(ss, patient, ',');
        getline(ss, equipment, ',');

        if (patient == patientId && equipment == equipmentId)
            return true;
    }

    return false;
}

void Request::sign(string patientId, string equipmentId, int sign, string signedBy)
{
    if (sign != -1 && sign != 1)
        return;

    fstream file("requests.csv", ios::in | ios::out);

    if (!file)
        return;

    string line;
    vector<string> lines;

    bool updated = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        string patient, equipment, reqStatus, reason, _signedBy;

        getline(ss, patient, ',');
        getline(ss, equipment, ',');
        getline(ss, reqStatus, ',');
        getline(ss, reason, ',');
        getline(ss, _signedBy, ',');

        if (patient == patientId && equipment == equipmentId)
        {
            reqStatus = to_string(sign);
            line = patient + "," + equipment + "," + reqStatus + "," + reason + "," + signedBy;
            updated = true;
        }

        lines.push_back(line);
    }

    if (updated)
    {
        file.close();
        ofstream fout("requests.csv", ios::trunc);
        for (const auto &l : lines)
        {
            fout << l << endl;
        }
        fout.close();
    }
}

vector<Request> Request::fetchAll(bool pendingOnly)
{
    vector<Request> requests;
    ifstream fin("requests.csv");

    if (!fin)
        return requests;

    string line;

    getline(fin, line); // Skip header
    while (getline(fin, line))
    {
        stringstream ss(line);
        string patient, equipment, reqStatus, reason, signedBy;

        getline(ss, patient, ',');
        getline(ss, equipment, ',');
        getline(ss, reqStatus, ',');
        getline(ss, reason, ',');
        getline(ss, signedBy, ',');

        Request req(patient, equipment);
        req.reqStatus = stoi(reqStatus);
        req.reason = reason;
        req.signedBy = signedBy;

        if (!pendingOnly || (pendingOnly && (req.reqStatus == 0)))
            requests.push_back(req);
    }

    return requests;
}

void Request::clearDone()
{
    fstream file("requests.csv", ios::in);

    if (!file)
        return;

    string line;
    vector<string> lines;

    while (getline(file, line))
    {
        stringstream ss(line);
        string patient, equipment, reqStatus, reason, _signedBy;

        getline(ss, patient, ',');
        getline(ss, equipment, ',');
        getline(ss, reqStatus, ',');
        getline(ss, reason, ',');
        getline(ss, _signedBy, ',');

        if (reqStatus == "0")
        {
            lines.push_back(line); // Only keep if status is 0
        }
    }

    file.close();

    ofstream fout("requests.csv", ios::trunc);

    fout << "patient,equipment,signed,reason,signed_by" << endl;
    for (const auto &l : lines)
    {
        fout << l << endl;
    }
    fout.close();
}