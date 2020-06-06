# CPPND: Capstone Basic Neural Network Simulator Repo

### SCOPE and Purpose of the Project
As the capstone project I created a basic Neural Network Simulator using CPP. In this simulator if you provide a training data, it will adapt and create a function according to the data.

In this project I have given a XOR function training data where I simulated 2000 test cases of bitwise XOR between randomly generated bits every time

You can give anny kind of training data you want.

### Features and File Structure
1) The src directory:
	It contains all the cpp and header  files needed
    a) main.cpp : This is the main driver program of the system, it creates a neural net and creates a training data systematically trains the data and outputs the findings
    b) NeuralNet.cpp and Neural.h : These two files contains all the necessary classes (Net and Neuron) and methods to implement the neural network architecture. The class Net is the whole neural architechture whereas the Neurons are the building blocks of the architecture. The header file contains all the declarations and the cpp contains all the defeinitions of the required methods and member variables
    c) trainingData.cpp and trainingData.h : These two files creates the Training Data class which is responsible for the reading the trainingData file and ouputing the progress in the console. The header file contains all the declarations and the cpp contains all the defeinitions of the required methods and member variables

2) The data directory:
	It contains the trainingData.txt file which contains the 2000 test cases of Randomly generated data of the bitwise XOR function. Users can include any training file with the proper syntax that at first it should contain a valid topology of the neural network and after this line, a series of input and output respectively with in: /data/" and "out: /data/" format respectively
    
### The Rubric Review:
1) The submission must compile and run: The code runs without any compilation errors and exceptions

2) The project demonstrates an understanding of C++ functions and control structures: The main function  in the main.cpp itself has function implementation along with proper flow of control (function definition can be seen in line 5)
	
3) The project reads data from a file and process the data, or the program writes data to a file: The TrainingData constructor reads the data from a file and creates a file stream and the file name which is given to the TrainingData object in our case can be seen in main.cpp, line 17

4) The project accepts user input and processes the input: main.cpp, line 61 uses cin to get two user input of either 1.00 or 0.00 and network named "net" then processes the data and returns the output. This is used to test network with unknown data outside of training data

5) The project uses Object Oriented Programming techniques: The NeuralNet.h has two class declaration Net and Neuron and the trainingData.h has a declaration of TrainingData class.

6) Classes use appropriate access specifiers for class members: every data memeber and methods are properly accessed as public and private specifier. This can be seen in the NeuralNet.h (Net and Neuron class) and in the trainingData.h(TrainingData class)

7) The project makes use of references in function declarations: In the NeuralNet.h line 34 and 35 has both function using reference to pass parameter. These can be seen many times in the given project, not just the two.

8) The project uses destructors appropriately: trainingData.cpp, line 29 properly demonstrates the destructor function as it closes the file stream properly and for this no exception will be thorwn.

From the output and the testing facility at the end of the function, we can say that the neural netowrk shows almost 96 percent accuracy 
This can be further improved by playing around with topology of the architecture and the _eta and _alpha private memeber varibales of the Neuron class


### Dependencies for Running Locally
* cmake >= 3.5
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

### Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./net`.
