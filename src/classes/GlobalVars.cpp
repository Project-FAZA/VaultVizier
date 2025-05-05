#include "GlobalVars.hpp"

void GlobalVar::createIfDoesNotExist(const string &filename, const string &content)
{
    ifstream infile(filename);
    if (!infile)
    {
        ofstream outfile(filename);
        if (!outfile)
        {
            cerr << "Failed to create file: " << filename << endl;
        }
        else
        {
            outfile << content << endl;
        }
    }
}