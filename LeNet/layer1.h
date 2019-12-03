#include <string> 

using namespace std;

float **convoWithoutPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel); 
float **add_bias(float **b, float bias, int size);
float ***first_layer(string input_file, int input_size, string kernel_file, int kernel_size, int number_of_kernel, float ***b)      ;