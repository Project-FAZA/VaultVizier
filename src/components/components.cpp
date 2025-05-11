#include "components.hpp"
#include <vector>

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

void updateRequestTable(Table *table, vector<Request> req)
{
    // Create a new table with updated data
    vector<vector<Element>> rows;

    // Add header row
    rows.push_back({text("Patient ID"),
                    text("Equipment ID"),
                    text("Status"),
                    text("Reason"),
                    text("Signed By")});

    // Add rows from the vector of requests
    for (const auto &request : req)
    {
        string status;
        switch (request.getReqStatus())
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

        Color statusColor;
        if (request.getReqStatus() == -1)
        {
            statusColor = Color::RedLight;
        }
        else if (request.getReqStatus() == 1)
        {
            statusColor = Color::GreenLight;
        }
        else
        {
            statusColor = Color::LightSkyBlue1;
        }

        rows.push_back({text(request.getPatientId()),
                        text(request.getEquipmentId()) | color(Color::BlueLight),
                        text(status) | color(statusColor),
                        text(request.getReason()) | color(Color::PaleGreen1),
                        text(request.getSignedBy()) | color(Color::Green3)});
    }

    // Set the new table content
    *table = Table(std::move(rows));

    table->SelectRow(0).Border();
    table->SelectAll().Border();
    table->SelectAll().SeparatorVertical();
    table->SelectColumn(0).Decorate(bold);
    table->SelectRow(0).SeparatorHorizontal();
    table->SelectColumn(0).DecorateCells(align_right);

    table->SelectRow(0).DecorateCells(color(Color::Yellow2));
    table->SelectColumn(0).DecorateCells(color(Color::Yellow2));
    table->SelectAll().Decorate(color(Color::Yellow2));
}