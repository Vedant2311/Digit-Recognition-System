#include <string> 

using namespace std;

void relu(float **a, int n);
void readKernel(float ****x, float *b, int nk, int ic, int out_size, string file);
float **convoWithoutPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel);
float **add(float **x, float **y, int size);
float **add_bias(float **b, float bias, int size);
float ***third_layer(float ***a, string kernel, int num_kernel, int input_channels, int input_size, int kernel_size, float ***b);
