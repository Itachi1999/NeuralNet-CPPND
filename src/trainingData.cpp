#include "trainingData.h"


void TrainingData::getTopology(vector<unsigned> &topology)
{
    string line;
    string label;

    getline(_trainingDataFile, line);
    std::istringstream ss(line);
    ss >> label;
    if (this->isEof() || label.compare("topology:") != 0) {
        abort();
    }
	unsigned n = 0;
    while (ss >> n) {
        topology.push_back(n);
      	std::cout << "Pushed to topology is: " << n << std::endl;
    }

    return;
}

TrainingData::TrainingData(const string filename)
{
    _trainingDataFile.open(filename.c_str());
}

TrainingData::~TrainingData()
{
    _trainingDataFile.close();
}

unsigned TrainingData::getNextInputs(vector<double> &inputVals)
{
    inputVals.clear();

    string line;
    getline(_trainingDataFile, line);
    std::istringstream ss(line);

    string label;
    ss>> label;
    if (label.compare("in:") == 0) {
        double oneValue = 0.0;
        while (ss >> oneValue) {
            inputVals.push_back(oneValue);
        }
    }

    return inputVals.size();
}

unsigned TrainingData::getTargetOutputs(vector<double> &targetOutputVals)
{
    targetOutputVals.clear();

    std::string line;
    std::getline(_trainingDataFile, line);
    std::istringstream ss(line);

    std::string label = "";
    ss>> label;
    if (label.compare("out:") == 0) {
        double oneValue = 0.0;
        while (ss >> oneValue) {
            targetOutputVals.push_back(oneValue);
        }
    }

    return targetOutputVals.size();
}