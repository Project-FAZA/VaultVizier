#include "Request.hpp"

void Request::save()
{
    if (alreadyExists(patientId, equipmentId))
        return;

    ofstream fout("requests.csv", ios::app);

    if (!fout)
        return;

    fout << patientId << "," << equipmentId << "," << to_string(reqStatus) << "," << signedBy << endl;
}

bool Request::alreadyExists(string patientId, string equipmentId)
{
    GlobalVar::createIfDoesNotExist("requests.csv", "patient,equipment,signed,signed_by");

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
        string patient, equipment, reqStatus, _signedBy;

        getline(ss, patient, ',');
        getline(ss, equipment, ',');
        getline(ss, reqStatus, ',');
        getline(ss, _signedBy, ',');

        if (patient == patientId && equipment == equipmentId)
        {
            reqStatus = to_string(sign);
            line = patient + "," + equipment + "," + reqStatus + "," + signedBy;
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

    getline(fin, line);
    while (getline(fin, line))
    {
        stringstream ss(line);
        string patient, equipment, reqStatus, signedBy;

        getline(ss, patient, ',');
        getline(ss, equipment, ',');
        getline(ss, reqStatus, ',');
        getline(ss, signedBy, ',');

        Request req(patient, equipment);
        req.reqStatus = stoi(reqStatus);
        req.signedBy = signedBy;

        if (!pendingOnly || (pendingOnly && (req.reqStatus == 0)))
            requests.push_back(req);
    }

    return requests;
}