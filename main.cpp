/* Michael Jezreel Aquitania
2/15/2019
Purpose: Generates a trace by selecting random numbers from 4 random processes.

I can probably improve this by using a distribution instead of rand to generate random numbers.
Test out different distributions.

Inputs: 1.# of Processes,
		2.range of each process,
		3.# of elements taken from each process,
		4.distribution: 1. random 2.sequential 3. mix,
		5.	order of which elements are streamed in (interleaving pattern)
Use text file to take in inputs

IF FILE FORMAT CHANGES JUST MODIFY processes() and move around the array indices.

*/

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "Trace.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(0));

    vector<vector<string> > argumentVector = arguments("input.txt");
    int numberOfProcesses = argumentVector.size()-1; //Assuming input file is correctly formatted
    int interleaveOption; //The first argument in text file
    istringstream (argumentVector[0][0]) >> interleaveOption;
    vector<vector<int> > processMatrix = processes(numberOfProcesses,argumentVector); //Generate Processes
    vector<vector<int> > getElementsMatrix = generateElementsToInterLeave(processMatrix, argumentVector);
    vector<int> trace = Merge(getElementsMatrix, interleaveOption);

    //Comment out later
    cout << "Printing textfile arguments:\n\n";
    for(int i = 0; i<argumentVector.size(); i++)
    {
        for(int j = 0; j<argumentVector[i].size();j++)
        {
            cout << argumentVector[i][j] << ", ";
        }
        cout << endl;
    }

    cout<< "\n\nPrinting Processes:\n\n";
    for(int i = 0; i<processMatrix.size(); i++)
    {
        for(int j = 0; j<processMatrix[i].size();j++)
        {
            cout << processMatrix[i][j] << ", ";
        }
        cout << endl;
        cout << endl;
        cout << endl;
    }


    cout<< "\nPrinting Elements to InterLeave:\n\n";
    for(int i = 0; i<getElementsMatrix.size();i++)
    {
        for(int j = 0; j<getElementsMatrix[i].size(); j++)
        {
            cout<< getElementsMatrix[i][j]<< ", ";
        }
        cout << endl;
    }

    ofstream output("trace.txt", ios::out | ios::trunc);
    output.seekp(ios::beg);

    cout << "\nGenerated Trace:\n\n";
    for(int i = 0; i<trace.size();i++)
    {
            cout<< trace[i]<< " ";
            output<<trace[i]<<"\n";

    }
    cout << endl;
    output.close();

    return 0;
}

