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

using namespace std;

vector<vector<string> > arguments(string inputFile); //Splits text file into arguments
vector<vector<int> > processes(int numProcesses, vector<vector<string> > argumentVect); //Generate processes with different amount of request
vector<vector<int> > generateElementsToInterLeave(vector<vector<int> > processList, vector<vector<string> > argumentVect2);
vector<int> Merge(vector<vector<int> > generatedProcesses, int generateTraceOption);  //Create a trace request pulling "requests" from each process.




int main(int argc, char *argv[])
{
    srand(time(0));

    vector<vector<string> > argumentVector = arguments("file.txt");
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

    cout << "\nGenerated Trace:\n\n";
    for(int i = 0; i<trace.size();i++)
    {
            cout<< trace[i]<< ", ";
    }
    cout << endl;

    return 0;
}

vector<vector<int> > processes(int numProcesses, vector<vector<string> > argumentVect)
{
    vector<vector<int> > traceMatrix(numProcesses); //Create a 2D vector with 'numProcesses' amount of rows.

    for(int i = 0; i<numProcesses; i++)
    {
        //Declare number of columns/items per row.
        int beginRange;
        istringstream ( argumentVect[i+1][0]) >> beginRange;
        int endRange;
        istringstream ( argumentVect[i+1][1]) >> endRange;
        int numOfItems = (endRange-beginRange)+1;



        traceMatrix[i] = vector<int>(numOfItems); //Number of items for the first process initialized

        for(int j = 0; j<numOfItems; j++)
        {
            traceMatrix[i][j]= beginRange; //start at beginRange specified
            beginRange++;
        }
    }

    return traceMatrix;
}


vector<int> Merge(vector<vector<int> > generatedProcesses, int generateTraceOption)
{
    vector<vector<int> > temp = generatedProcesses;
    vector<int> generated;

    if(generateTraceOption == 1)//Grab elements sequentially popping from array each round
    {
        while(!temp.empty())
        {
                for(int i = 0; i<temp.size(); i++)
                {
                    generated.push_back(temp[i].back());
                    temp[i].pop_back();
                    if(temp[i].size()==0)
                        temp.erase(temp.begin()+i);
                }
        }
    }
    else if(generateTraceOption == 2) //Random elements grabbed from each process
    {
        //Get random values or structured values? from each process array and put in merged array.
        while(!temp.empty())//While we still have elements from each process keep grabbing elements.
        {
            int i = rand()%temp.size(); //Choose a random process
            int randomElementIndex = rand()%(temp[i].size()); //Choose a random request index from each process
            generated.push_back(temp[i][randomElementIndex]); //Choose a random element from the process and insert into a new merged trace vector
            temp[i].erase(temp[i].begin()+randomElementIndex);//Erase the element to denote that it's already been used
            if(temp[i].size()==0)//If there are no more elements in a process to use, delete the process
                temp.erase(temp.begin()+i);
        }
    }

    return generated;
}


vector<vector<int> > generateElementsToInterLeave(vector<vector<int> > processList, vector<vector<string> > argumentVector2)
{
    vector<vector<int> > returnElements(processList.size());
    int generateElementsOption;
    int numberOfElementsToGen;

    int a = processList.size();
    for(int i = 0; i<processList.size(); i++)
    {
        istringstream(argumentVector2[i+1][2])>>numberOfElementsToGen;
        istringstream(argumentVector2[i+1][3])>>generateElementsOption;

        if(numberOfElementsToGen>processList[i].size())
        {
            cout << "Exceeded max range of elements. Exiting...";
            exit(0);
        }
        if(generateElementsOption == 1) //Sequential
        {
            for(int j = 0; j<numberOfElementsToGen; j++)
            {
                returnElements[i].push_back(processList[i][j]);
            }
        }
        else if(generateElementsOption == 2)//random
        {
            for(int x = 0; x<numberOfElementsToGen; x++)
            {
                int randomElementIndex = rand()%(processList[i].size()+1); //Choose a random request index from each process
                returnElements[i].push_back(processList[i][randomElementIndex]); //Choose a random element from the process and insert into a new vector
            }
        }
        else
        {
            cout << "Not a valid argument. Exiting." << endl;
            exit(0);
        }
    }

    return returnElements;
}



vector<vector<string> > arguments(string inputFile)
{
    vector<vector<string> >args;
    ifstream input(inputFile);

    while(input)
    {
        string line;
        if(!getline(input, line)) break;

        istringstream lineArguments(line); //Parse through each line
        vector<string> lineArgs; //Vector for each line to hold arguments

        while (lineArguments)
        {
            string line;
            if(!getline(lineArguments, line, ',')) break;
            lineArgs.push_back(line);
        }
        args.push_back(lineArgs);
    }
    if(!input.eof())
    {
        cerr << "Error! No file found\n";
    }

    return args;
}
