#include "NeuralNet.h"


/* -------------------Network Definition ---------------------------*/

double Net::_recentAverageSmoothingFactor = 100.0; // Number of training samples to average over

Net::Net(const std::vector<unsigned> topology) {
	unsigned numOfLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numOfLayers; layerNum++){
		_layers.push_back(Layer());
    	
      	//if last layer then zero connections
      	unsigned noOfOutputs = layerNum == (numOfLayers - 1) ? 0 : topology[layerNum + 1]; 
		
		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++){ //One extra neuron for the bias
			_layers.back().push_back(Neuron(noOfOutputs, neuronNum));
			std::cout << "Neuron of layer " << layerNum << " of which " << neuronNum << " neuron is made" << std::endl;
		}
      
    	_layers.back().back().setOutputValue(1.0); //Hardcoding bias neurons value
	}
}
void Net::feedForward(const std::vector<double> &inputValues) {
	assert(inputValues.size() == _layers[0].size() - 1); //since we're excluding the bias in the assertion
  
  	//Setting the outputValues of first layer as inputValues
  	for(unsigned i = 0; i < inputValues.size(); i++){
      _layers[0][i].setOutputValue(inputValues[i]);
    }
  	//std::cout << "Entered Feedforward" << std::endl;
  	//Doing the forward pass
  	for(unsigned layerNum = 1; layerNum < _layers.size(); layerNum++){
      	Layer &prevLayer = _layers[layerNum - 1];
      	for(unsigned neu = 0; neu < _layers[layerNum].size() - 1; neu++){
          	_layers[layerNum][neu].feedForward(prevLayer);
        }
    }
}
void Net::backPropagation(const std::vector<double> &targetValues) {

  	Layer &outputLayer = _layers.back();
  	//Calculate the overall error [RMS is being used in this case to calc the errors]
  	_error = 0.0;
  	for(unsigned neu = 0; neu < outputLayer.size() - 1; neu++){ //not including the bias
      	double delta = targetValues[neu] - outputLayer[neu].getOutputValue();
      	_error += delta * delta;
    }
  	_error /= outputLayer.size() - 1; //not including the bias
  	_error = sqrt(_error);
  
  	// Implement a recent average measurement
    _recentAverageError =
            (_recentAverageError * _recentAverageSmoothingFactor + _error)
            / (_recentAverageSmoothingFactor + 1.0);
  	//calculate output layer gradients
  	for(unsigned n = 0; n < outputLayer.size() - 1; n++){
      	outputLayer[n].calcOutputGradients(targetValues[n]);
    }
  	//calculate hidden layers gradients
  	for(unsigned layerNum = _layers.size() - 2; layerNum > 0; layerNum--) { //excuding the output layer and input layer
      	Layer &hiddenLayer = _layers[layerNum];
      	Layer &nextLayer = _layers[layerNum + 1];
      	for(unsigned n = 0; n < hiddenLayer.size(); n++){
          	hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }
  	//for all layers from output to hidden layers
  	//update the connection weights
    for(unsigned layerNum = _layers.size() - 1; layerNum > 0; layerNum--){ 
    	Layer &layer = _layers[layerNum];
      	Layer &prevLayer = _layers[layerNum - 1];
      	for(unsigned n = 0; n < layer.size() - 1; n++){ //except the bias
        	layer[n].updateInputWeights(prevLayer);
        }
    }      	
}
        
void Net::getResults(std::vector<double> &resultValues) const {
  	std::cout << "Getting Result" << std::endl;
	resultValues.clear();
  	for(unsigned n = 0; n < _layers.back().size() - 1; n++){
    	resultValues.push_back(_layers.back()[n].getOutputValue());
    }
  	std::cout << "Done results" << std::endl;
}


/* -------------------Neuron Definition ---------------------------*/
        
double Neuron::_eta = 0.15;
double Neuron::_alpha = 0.5;
        
Neuron::Neuron(unsigned noOfOutputs, unsigned neuIndex){
  	for(unsigned c = 0; c < noOfOutputs; c++){
      	_outputWeights.push_back(Connection());
      	_outputWeights.back().weight = randomWeight();
    }
  	this -> _neuIndex = neuIndex;
}

void Neuron::feedForward(const Layer &prevLayer){
  	double sum = 0.0;
  	//std::cout << "Doing Feedforward" << std::endl;
  	//Sum the previous layers outputs and also add the bias
	for(unsigned n = 0; n < prevLayer.size(); n++){
    	sum += prevLayer[n].getOutputValue() * 
        	prevLayer[n]._outputWeights[this->_neuIndex].weight;
    }
  	
  	//Use Activation Function
  	this->_outputVal = Neuron::activationFunction(sum);
}
        
void Neuron::calcOutputGradients(double targetValue){
	double delta = targetValue - this->_outputVal;
  	this->_gradient = delta * Neuron::activationFunctionDerivative(this-> _outputVal);
}

        
double Neuron::sumDOW(const Layer &nextLayer) const{
	double sum = 0.0;
	//Sum of the contributions of the errors at the the nodes we feed
  	for(unsigned n = 0; n < nextLayer.size() - 1; n++){
    	sum += this->_outputWeights[n].weight * nextLayer[n]._gradient;
    }
  	return sum;
}
        
void Neuron::calcHiddenGradients(const Layer &nextLayer){
	double dow = sumDOW(nextLayer);
  	this->_gradient = dow * Neuron::activationFunctionDerivative(this->_outputVal);
}
        
void Neuron::updateInputWeights(Layer &prevLayer){
	//The weights to be updated are in the connection container in the prevLayer
  	for(unsigned n = 0; n < prevLayer.size(); n++){
    	Neuron &prevNeuron = prevLayer[n];
    	double oldDeltaWeight = prevNeuron._outputWeights[this->_neuIndex].deltaWeight;
      	
      	double newDeltaWeight =
          //Individual input magnified by the gradient and training rate
          _eta * prevNeuron.getOutputValue() *  this -> _gradient
          //Also adding momentum which is the fraction of the previous deltaWeight
          + _alpha * oldDeltaWeight;
      
      	prevNeuron._outputWeights[this->_neuIndex].deltaWeight = newDeltaWeight;
      	prevNeuron._outputWeights[this->_neuIndex].weight += newDeltaWeight;
    
    }
}
        
double Neuron::activationFunction(double sum)
{
	//we're going to use the hyperbolic tangent function
  	//tanh -> [-1.0. 1.0]
  	return tanh(sum);
}

double Neuron::activationFunctionDerivative(double x)
{
  	//Approximation of the tanh-1(x) function
	return 1.0 - (x * x);
}

