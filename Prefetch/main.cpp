#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>
#include <iterator>
#include <unordered_set>
/* Orignal code from: https://www.geeksforgeeks.org/program-page-replacement-algorithms-set-1-lru/
   Modifying look ahead fetch values and how I should determine these values
*/

using namespace std;

int hits;

void printVector(vector <int> const &v)
{
    copy(v.begin(),v.end(),ostream_iterator<int>(cout, " "));
    cout<<"\n"<<endl;
}

void printSet(unordered_set<int> const &s)
{
    copy(s.begin(),s.end(),ostream_iterator<int>(cout, " "));
    cout<<"\n"<<endl;
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
    printVector(trace);
    return trace;
}


vector <int> prefetch(int valueAtTraceRequest)
{
    vector <int> buffer;
    buffer.push_back(valueAtTraceRequest+1);
    buffer.push_back(valueAtTraceRequest+2);
    buffer.push_back(valueAtTraceRequest+3);
    buffer.push_back(valueAtTraceRequest+4);
    buffer.push_back(valueAtTraceRequest+5);

    return buffer;
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

                for(int x = 0; x<capacity; x++)
                {
                    setT.insert(prefetch(traces[i])[x]);
                }
                misses++;
               // cout<<"Current buffer: ";
               // printVector(prefetch(traces[i]));


                cout<<"Current setBuffer: ";
                printSet(setT);

            }
            else{hits++;}
            indexes[traces[i]] = i;
            //cout<<"Current buffer: ";
            //printVector(prefetch(traces[i]));


            cout<<"Current setBuffer: ";
            printSet(setT);
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

                //cout<<"Current buffer: ";
                //printVector(prefetch(traces[i]));


                cout<<"Current setBuffer: ";
                printSet(setT);
            }
            else{hits++;}
            indexes[traces[i]] = i;
            //cout<<"Current buffer: ";
            //printVector(prefetch(traces[i]));


            cout<<"Current setBuffer: ";
            printSet(setT);
        }

    }
    return misses;
}



int main(int argc, char *argv[])
{
    vector <int> trace = readInFile(argv[1]);

    int cap = 5; //buffer size
    cout << "Misses: " << misses(trace,cap) - cap<<endl;
    cout << "Hits: " << hits;

    return 0;
}
