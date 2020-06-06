#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cmath>

/* ---------------------Type Definitions----------------------------------*/

struct Connection{ //each connection of neuron containing the weights for forward prop and delta for backward
  double weight;
  double deltaWeight;
};

class Neuron;

typedef std::vector<Neuron> Layer;

/* ---------------------Class Neuron Definition --------------------------*/
class Neuron{
	public:
  		//constructors
  		Neuron(unsigned noOfOutputs, unsigned neuIndex); //because it only needs the no of outputs in next layer to calculate the 
  		//no of connections it need to make
  		
		//Accesors and Mutators  
  		double getOutputValue() const {	return _outputVal; }
  		void setOutputValue(double value) { _outputVal = value; } 
  
  		//functions
  		void feedForward(const Layer &prevLayer);
  		void calcHiddenGradients(const Layer &nextLayer);
  		void calcOutputGradients(double targetValue);
  		void updateInputWeights(Layer &prevLayer);
  	private:
  		static double _eta; //the training rate
  		static double _alpha; //the momentum rate
  		static double activationFunction(double sum);
  		static double activationFunctionDerivative(double x);
  		static double randomWeight(){ return rand() / double(RAND_MAX);} //returns random number bw (0, 1)
  		double sumDOW(const Layer &nextLayer) const;
  		double _outputVal;
  		double _gradient;
  		unsigned _neuIndex;
  		std::vector<Connection> _outputWeights;
};

/* ---------------------Class Net Declaration --------------------------*/
class Net {
	public:
		Net(const std::vector<unsigned> topology); //as topology won't change
		void feedForward(const std::vector<double> &inputValues);  //The i/p layer just takes the values, 
  		//deosn't modify it
  		void backPropagation(const std::vector<double> &targetValues); //The o/p layer just takes the values, doesn't modify it
		void getResults(std::vector<double> &resultValues) const; //here the result values will be changed as they will be calculated;
		//However it won't change the object itself or more specifically the object parameters;
  		
  		double getRecentAverageError(void) const { return _recentAverageError; }
	private:
		std::vector<Layer> _layers; //vector<vector<Neuron>> basically it is that
  		double _error;
  		double _recentAverageError;
    	static double _recentAverageSmoothingFactor;
};


#endif // !NEURALNET
