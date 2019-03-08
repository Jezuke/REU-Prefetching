#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "Trace.h"

using namespace std;

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
    else if(generateTraceOption == 2) //Random elements grabbed from random each process
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
    else if (generateTraceOption == 4) //Random elements grabbed from each process but each process is in order.
    {
        //Get random values or structured values? from each process array and put in merged array.
        while(!temp.empty())//While we still have elements from each process keep grabbing elements.
        {
            for(int i = 0; i<temp.size(); i++)
            {
                int randomElementIndex = rand()%(temp[i].size()); //Choose a random request index from each process
                generated.push_back(temp[i][randomElementIndex]); //Choose a random element from the process and insert into a new merged trace vector
                temp[i].erase(temp[i].begin()+randomElementIndex);//Erase the element to denote that it's already been used
                if(temp[i].size()==0)//If there are no more elements in a process to use, delete the process
                    temp.erase(temp.begin()+i);
            }
        }
    }
    else
    {
        cout << "Not a valid option." << endl;
        exit(0);
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
               /* if(j==numberOfElementsToGen-1)
                {
                    j = 0;
                    continue;
                } */
                returnElements[i].push_back(processList[i][j]);
            }
        }
        else if(generateElementsOption == 2)//random
        {
            for(int x = 0; x<numberOfElementsToGen; x++)
            {
                /*
                if(x==numberOfElementsToGen-1)
                {
                    x = 0;
                    continue;
                }
                */
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
