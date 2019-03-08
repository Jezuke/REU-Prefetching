#ifndef TRACE_INCLUDE
#define TRACE_INCLUDE

#include <vector>

std::vector<std::vector<std::string> > arguments(std::string inputFile); //Splits text file into arguments
std::vector<std::vector<int> > processes(int numProcesses, std::vector<std::vector<std::string> > argumentVect); //Generate processes with different amount of request
std::vector<std::vector<int> > generateElementsToInterLeave(std::vector<std::vector<int> > processList, std::vector<std::vector<std::string> > argumentVect2);
std::vector<int> Merge(std::vector<std::vector<int> > generatedProcesses, int generateTraceOption);  //Create a trace request pulling "requests" from each process.


#endif
