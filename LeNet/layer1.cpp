#include <bits/stdc++.h> 
#include <string> 
using namespace std;

float **convoWithoutPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel) {

	int sizeOut = sizeInput - sizeKernel + 1;
	float **matrixOut;
	matrixOut = (float**)malloc(sizeof(float*) * sizeOut);

	for (int i = 0; i < sizeOut; i++) {
		matrixOut[i] = (float*)malloc(sizeof(float*) * sizeOut);
	}

	float sum = 0.0;

	for (int i = 0; i < sizeOut; i++) {
		for (int j = 0; j < sizeOut; j++) {
			sum = 0.0;
			for (int u = 0; u < sizeKernel; u++) {
				for (int v = 0; v < sizeKernel; v++) {

					sum = sum + Input[u + i][v + j] * Kernel[sizeKernel - u - 1][sizeKernel - v - 1];
				}
			}

			matrixOut[i][j] = sum;
		}
	}
	return matrixOut;
}


float **add_bias(float **b, float bias, int size)
{
	for(int i=0 ; i<size; i++)
	{
		for(int j=0 ; j<size; j++)
		b[i][j] = b[i][j]+bias; 
	}
	return b;
}

//For layer 1 convolution => input_size = 28, kernel_size = 5, number_of_kernel = 20)
float*** first_layer(string input_file, int input_size, string kernel_file, int kernel_size, int number_of_kernel, float ***b)       //n is number of feature maps
{
	float **a;
	a = (float**)malloc(sizeof(float*)*input_size);
	for(int i=0 ; i<input_size; i++)
		a[i] = (float*)malloc(sizeof(float)*input_size);

	float **k;
	k = (float**)malloc(sizeof(float*)*kernel_size);
	for(int i=0 ; i<kernel_size; i++)
		k[i] = (float*)malloc(sizeof(float)*kernel_size);
	
	int output_size = input_size - kernel_size +1;

	//a in the input matrix , k takes kernel matrix and b is a 3 dimensional (number_of_kernel*out_size*output_size) output matrices
	
	float bias[number_of_kernel];

	ifstream inFile;
	inFile.open(input_file.c_str());

	int count =0 ;
	if (!inFile.is_open())
	{
		cout << "file doesn't open" << endl;
		return NULL ;
	}

	float word;
	while ((inFile >> word) && count<(input_size*input_size))
	{
		for(int i=0 ; i<input_size ; i++)
		{
			for(int j=0 ; j<input_size; j++ )
			{
				a[i][j]=word;   //row major form
				count++;
			}
		}
	}

	inFile.close();
	
	ifstream inFile1;
	inFile1.open(kernel_file.c_str());

	if (!inFile1.is_open())
	{
		cout << "file doesn't open" << endl;
		return NULL ;
	}

	for(int i = 0; i<number_of_kernel ; i++)
	{
		count =0;
		while ((inFile1 >> word) && count<(kernel_size*kernel_size))
		{
			for(int i=0 ; i<kernel_size ; i++)
			{
				for(int j=0 ; j<kernel_size; j++ )
				{
					k[i][j]=word;   //row major form
					count++;
				}
			}
		}

		b[i] = convoWithoutPadding(a, input_size, k , kernel_size);
	}	

	int t=0;
	while((inFile1 >> word) && (t<number_of_kernel))
	{
		bias[t] = word;
		t++;
	}

	for(int j=0; j<number_of_kernel; j++)
		b[j] = add_bias(b[j], bias[j], output_size);

	inFile1.close();
	
	
	for (int i = 0; i < input_size; i++) 
		free(a[i]);
	free(a);

	for (int i = 0; i < kernel_size; i++) 
		free(k[i]);
	free(k);
	
	//freeing memory
	
	return b;
}