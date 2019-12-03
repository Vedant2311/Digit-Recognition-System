#include <string> 

using namespace std;

float **multWithoutPadding_OB(float **Input, int sizeInput, float **Kernel, int sizeKernel);
float **multWithPadding_OB(float **Input, int sizeInput, float **Kernel, int sizeKernel, int padding);