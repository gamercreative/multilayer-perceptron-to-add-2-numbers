#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
using namespace std;

class neural_network {
public:
    // Constructor to initialize weights and biases
    neural_network() {
        // Initial weights for connections from input layer to hidden layer
        weights_input_hidden = {{0.2, 0.5}, {0.3, 0.8}};  
        // Initial weights for connections from hidden layer to output layer
        weights_hidden_output = {0.4, 0.7};  
        // Biases for hidden layer neurons
        hidden_bais = {0.1, 0.1};  
        // Bias for the output layer
        out_bais = 0.1;  
    }

    // Forward propagation function to compute the output
    double ff(double in1, double in2) {
        vector<double> hidden_layer(2); // Vector to hold hidden layer outputs
        
        // Compute each hidden layer neuron output with weighted inputs and biases
        hidden_layer[0] = in1 * weights_input_hidden[0][0] + in2 * weights_input_hidden[1][0] + hidden_bais[0]; 
        hidden_layer[1] = in1 * weights_input_hidden[0][1] + in2 * weights_input_hidden[1][1] + hidden_bais[1]; 

        // Compute the final output using hidden layer outputs and output weights
        double output_layer = hidden_layer[0] * weights_hidden_output[0] + hidden_layer[1] * weights_hidden_output[1] + out_bais; 
        return output_layer; // Return the computed output
    }

    // Backpropagation function to update weights and biases
    void bp(double in1, double in2, double target) {
        vector<double> hidden_layer(2); // Vector to hold hidden layer outputs
        // Compute hidden layer outputs again for backpropagation
        hidden_layer[0] = in1 * weights_input_hidden[0][0] + in2 * weights_input_hidden[1][0] + hidden_bais[0];
        hidden_layer[1] = in1 * weights_input_hidden[0][1] + in2 * weights_input_hidden[1][1] + hidden_bais[1];

        // Compute the output from the network
        double output = hidden_layer[0] * weights_hidden_output[0] + hidden_layer[1] * weights_hidden_output[1] + out_bais;

        // Calculate the error in output
        double output_error = target - output; 

        vector<double> hidden_error(2); // Vector to hold errors for hidden layer
        // Calculate error for each hidden neuron
        hidden_error[0] = output_error * weights_hidden_output[0]; 
        hidden_error[1] = output_error * weights_hidden_output[1]; 

        // Update weights for connections from hidden layer to output layer
        weights_hidden_output[0] += hidden_layer[0] * output_error * learning_rate; 
        weights_hidden_output[1] += hidden_layer[1] * output_error * learning_rate; 
        // Update bias for the output layer
        out_bais += output_error * learning_rate; 

        // Update weights for connections from input layer to hidden layer
        weights_input_hidden[0][0] += hidden_error[0] * in1 * learning_rate; 
        weights_input_hidden[0][1] += hidden_error[0] * in2 * learning_rate; 
        weights_input_hidden[1][0] += hidden_error[1] * in1 * learning_rate; 
        weights_input_hidden[1][1] += hidden_error[1] * in2 * learning_rate; 

        // Update biases for hidden neurons
        hidden_bais[0] += hidden_error[0] * learning_rate; 
        hidden_bais[1] += hidden_error[1] * learning_rate; 
    }

private:
    // Private members for weights and biases
    vector<vector<double>> weights_input_hidden; // Weights between input and hidden layers
    vector<double> weights_hidden_output; // Weights between hidden and output layers
    vector<double> hidden_bais; // Biases for hidden neurons
    double out_bais; // Bias for output neuron
    double learning_rate = 0.0000001; // Learning rate for weight updates
};  

int main() {
    int epoch = 20000; // Number of training epochs
    neural_network ako; // Create instance of the neural network
    srand((unsigned) time(NULL)); // Seed random number generator

    vector<pair<pair<double, double>, double>> dataset; // Dataset to hold input-output pairs
    // Generate random dataset of input pairs and their sum
    for (int i = 0; i < 5000; i++) {
        double num1 = rand() % 50; // Generate random number 1
        double num2 = rand() % 50; // Generate random number 2
        dataset.push_back({{num1, num2}, num1 + num2}); // Store input pair and their sum
    }
    
    // Train the neural network over multiple epochs
    for (int i = 0; i < epoch; i++) {
        for (auto& data : dataset) {
            // Perform backpropagation for each data point
            ako.bp(data.first.first, data.first.second, data.second);
        }
    }
    
    // Test the neural network by predicting sums of random pairs
    for (int i = 0; i < 10; i++) {
        double num1 = rand() % 50; // Generate random number 1
        double num2 = rand() % 50; // Generate random number 2
        // Output the prediction from the neural network
        cout << num1 << " + " << num2 << " = " << ako.ff(num1, num2) << "\n"; 
    }
}
