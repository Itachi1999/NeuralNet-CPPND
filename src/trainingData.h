#ifndef TRAININGDATA_H
#define TRAININGDATA_H

#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;

class TrainingData
{
public:
    TrainingData(const string filename);
    ~TrainingData();
    bool isEof(void) { return _trainingDataFile.eof(); }
    void getTopology(vector<unsigned> &topology);

    // Returns the number of input values read from the file:
    unsigned getNextInputs(vector<double> &inputVals);
    unsigned getTargetOutputs(vector<double> &targetOutputVals);

private:
    ifstream _trainingDataFile;
};

#endif