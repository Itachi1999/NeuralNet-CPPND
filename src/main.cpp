//
#include "trainingData.h"
#include "NeuralNet.h"

void showVectorVals(string label, vector<double> &v)
{
    cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }

    cout << endl;
}

int main() {
  	std::srand(std::time(0)); //creates random number w.r.t time
	double testData1 = 0.00, testData2 = 0.00;  	
	TrainingData trainData("../data/trainingData.txt");

    // in the file it is 2 4 1 but you can change accordingly
    vector<unsigned> topology;
    trainData.getTopology(topology);
  	
  	//for(unsigned i = 0; i < topology.size(); i++){std::cout << topology[i] << " "<<std::endl;}
  	 

    Net net(topology);

    vector<double> inputVals, targetVals, resultVals;
    int trainingPass = 0;

    while (!trainData.isEof()) {
        // Get new input data and feed it forward:
        if (trainData.getNextInputs(inputVals) != topology[0]) {
            break;
        }
      	cout << endl << "Pass " << trainingPass++;
      	
        showVectorVals(": Inputs:", inputVals);
        net.feedForward(inputVals);

        // Collect the net's actual output results:
        net.getResults(resultVals);
        showVectorVals("Outputs:", resultVals);

        // Train the net what the outputs should have been:
        trainData.getTargetOutputs(targetVals);
        showVectorVals("Targets:", targetVals);
        assert(targetVals.size() == topology.back());

        net.backPropagation(targetVals);

        // Report how well the training is working, average over recent samples:
        cout << "Net recent average error: "
                << net.getRecentAverageError() << endl;
    }

    cout << endl << "Training Done" << endl;
  	cout << endl << "Time to test!!" << endl;
  	cout << "Give two data(0.00 / 1.00): ";
  	cin >> testData1 >> testData2;
  	inputVals.clear();
  	inputVals.push_back(testData1); inputVals.push_back(testData2);
  	showVectorVals(": Inputs:", inputVals);
    net.feedForward(inputVals);

     // Collect the net's output results:
    net.getResults(resultVals);
    showVectorVals("Outputs:", resultVals);
}	