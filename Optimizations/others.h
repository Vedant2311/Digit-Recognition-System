#include <string>

using namespace std;

int readFile(float **x, int n, string file);
int readArray(float *v, int n, string file);
void non_linear_activation(float **a, int n, string str);
float max(float **x, int n);
float avg(float **x, int n);
void pooling(float **a, int n, string s);
float **convoWithoutPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel);
float **multWithoutPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel);
float **convoWithPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel, int padding);
float **multWithPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel, int padding);
float **multWithPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel, int padding);
