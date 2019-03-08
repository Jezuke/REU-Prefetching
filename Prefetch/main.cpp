#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
/* Orignal code from: https://www.geeksforgeeks.org/program-page-replacement-algorithms-set-1-lru/
   Modifying look ahead fetch values and how I should determine these values
*/

using namespace std;

int hits;
vector <int> readInFile(string fileName);
void printVector(vector <int> vectorName);
void prefetch(vector <int> trace);
int misses(vector <int> trace, int cap);


int main(int argc, char *argv[])
{
    vector <int> trace = readInFile(argv[1]);

    int cap = 4;
    cout << "Misses: " << misses(trace,cap) - cap<<endl;
    cout << "Hits: " << hits;

    return 0;
}

vector <int> readInFile(string fileName)
{
    vector <int> trace;
    ifstream input(fileName);

    while(input)
    {
        string line;
        if(!getline(input, line)) break;

        trace.push_back(stoi(line));
    }
    if(!input.eof())
    {
        cerr << "Error! No file found\n";
    }

    return trace;
}

void printVector(vector <int> vectorName)
{
    for(int i = 0; i<vectorName.size();i++)
    {
        cout << vectorName[i] << endl;
    }
}

int misses(vector <int> traces, int capacity)
{
    unordered_set<int> setT;

    unordered_map<int, int> indexes;

    int misses = 0;

    for(int i=0; i<traces.size(); i++)
    {
        if(setT.size()<capacity)
        {
            if(setT.find(traces[i])==setT.end())
            {
                setT.insert(traces[i]+1);
                misses++;
            }
            else{hits++;}
            indexes[traces[i]] = i;
        }
        else
        {
            if(setT.find(traces[i])==setT.end())
            {
                int lru = INT_MAX, val;
                for(auto it=setT.begin(); it!=setT.end(); it++)
                {
                    if(indexes[*it]<lru)
                    {
                        lru = indexes[*it];
                        val = *it;
                    }
                }
                setT.erase(val);
                setT.insert(traces[i]+1);
                misses++;
            }
            else{hits++;}
            indexes[traces[i]] = i;
        }

    }
    return misses;
}
