#include <string> 

using namespace std;

float **multWithoutPadding_MKL(float **Input, int sizeInput, float **Kernel, int sizeKernel);
float **multWithPadding_MKL(float **Input, int sizeInput, float **Kernel, int sizeKernel, int padding);
void *mult_thread(void *t);