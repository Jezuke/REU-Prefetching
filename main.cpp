/* Michael Jezreel Aquitania
1/25/2019
Purpose: Generates a trace by selecting random numbers from 4 random processes.

I can probably improve this by using a distribution instead of rand to generate random numbers.
Test out different distributions.

Inputs: # of Processes, # of elements taken from each process, distribution: 1. random 2.sequential 3. mix, order of which elements are streamed in (interleaving pattern)
Use text file to take in inputs

*/

#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

vector<vector<int> > processes(int numProcesses); //Generate processes with different amount of request
vector<int> Merge(vector<vector<int> > generatedProcesses); //Create a trace request pulling "requests" from each process.

int main(int argc, char *argv[])
{
   int row = atoi(argv[1]);

    vector<vector<int> > processMatrix = processes(row); //Generate Processes
    vector<int> requests = Merge(processMatrix); //Create a new request sequence using from all the processes

    cout<<endl;

    for (int i = 0; i < row; i++)
    {
        cout<<"Process " << (i+1) << ": ";
        for (int j = 0; j < processMatrix[i].size(); j++)//Print values of each process
            cout << processMatrix[i][j] << " ";
        cout << endl;
    }

    cout<<"\nGenerated Request Sequence:"<<endl;
    for(int j = 0; j<requests.size(); j++) //Print new request sequence
    {
        cout << requests[j] << " ";
    }
    cout<<"\n\nTotal Number of Requests: " << requests.size();
    cout << endl;

    return 0;
}

vector<vector <int> > processes(int numProcesses)
{
    vector<vector<int> > traceMatrix(numProcesses); //Create a 2D vector with 'numProcesses' amount of rows.

    for(int i = 0; i<numProcesses; i++)
    {
        //Declare number of columns/items per row
        int numOfItems;
        cout << "How many items for Process "<<i+1<<"? ";
        cin >> numOfItems;

        traceMatrix[i] = vector<int>(numOfItems); //Number of items for the first process initialized

        for(int j = 0; j<numOfItems; j++)
        {
            traceMatrix[i][j] =1+rand()%10; //Generate a random number (request) from 1-10
        }
    }

    return traceMatrix;
}


vector<int> Merge(vector<vector<int> > generatedProcesses)
{
    vector<vector<int> > temp = generatedProcesses;
    vector<int> generated;

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

    return generated;
}

