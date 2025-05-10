#include "components.hpp"

InputOption inputOption(bool password)
{
    InputOption option{InputOption::Default()};
    option.multiline = false;
    option.password = password;
    return option;
}

void updateList(const vector<Request> &requests, vector<string> &displayList)
{
    // Clear the current display list
    displayList.clear();

    // Populate the display list with formatted strings
    for (const auto &req : requests)
    {
        string status;
        switch (req.getReqStatus())
        {
        case -1:
            status = "Rejected";
            break;
        case 0:
            status = "Pending";
            break;
        case 1:
            status = "Accepted";
            break;
        default:
            status = "Unknown";
            break;
        }

        string entry = "Patient ID: " + req.getPatientId() +
                       " | Equipment ID: " + req.getEquipmentId() +
                       " | Status: " + status;

        if (!req.getSignedBy().empty())
        {
            entry += " | Signed By: " + req.getSignedBy();
        }

        displayList.push_back(entry);
    }
}