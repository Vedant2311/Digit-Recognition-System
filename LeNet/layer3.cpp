#include <bits/stdc++.h> 
#include <string> 
using namespace std;

//make a read file to generate kernel matrix of 50*5*5*20 /////////////////////////////////////////////////////

void relu(float **a, int n)
{
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
		{
			if (a[i][j]<0)
				a[i][j] = 0;
		}
	}	
}

void readKernel(float ****x, float *b, int nk, int ic, int out_size, string file)
{

	int count = 0;
	ifstream inFile;
	inFile.open(file.c_str());

	//cout<<"1"<<endl;
	if (!inFile.is_open())
	{
		cout << "file doesn't open" << endl;
		return ;
	}

	float word;
	//std::string::size_type sz; 
	while ((inFile >> word) && count<(nk*ic*out_size*out_size))
	{
		for(int p=0; p<nk; p++)
		{
			for(int q=0; q<ic; q++)
			{
				for(int r=0; r<out_size; r++)
				{
					for(int s=0; s<out_size; s++)
					{	x[p][q][r][s]=word;
					count++;}
				}
			}
		}
	}

	count=0;
	while((inFile >> word) && count<nk)
	{
		b[count]=word;
		count++;
	}
	inFile.close();
	return ;
}

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

float **add(float **x, float **y, int size)
{
	for(int q=0; q<size; q++)
		{
			for(int r=0; r<size; r++)
				x[q][r]= x[q][r]+ y[q][r]/(size*size) ;
		}

	return x;
}

float **add_bias(float **b, float bias, int size)
{
	for(int i=0 ; i<size; i++)
	{
		for(int j=0 ; j<size; j++)
		b[i][j] = b[i][j] + bias; 
	}
	return b;
}

float ***third_layer(float ***a, string kernel, int num_kernel, int input_channels, int input_size, int kernel_size, float ***b)
{
	int output_size =  input_size - kernel_size +1;

	float bias[num_kernel];
	float ****k;

	k = (float****)malloc(sizeof(float***)*num_kernel);
	for(int i=0; i<num_kernel; i++)
	{
		k[i] = (float***)malloc(sizeof(float**)*input_channels);
	}

	for(int i=0; i<num_kernel; i++)
	{
		for(int j=0; j<input_channels; j++)
		{
			k[i][j] = (float**)malloc(sizeof(float*)*output_size);
		}		
	}

	for(int i=0; i<num_kernel; i++)
	{
		for(int j=0; j<input_channels; j++)
		{
			for(int l=0; l<output_size; l++)
				k[i][j][l]= (float*)malloc(sizeof(float)*output_size);
		}		
	}

	//assigned memory to ****k

	readKernel(k, bias, num_kernel, input_channels, output_size, kernel);
	
	//initialised output matrix to '0'
	for(int p=0; p<num_kernel; p++)
	{
		for(int q=0; q<output_size; q++)
		{
			for(int r=0; r<output_size; r++)
				b[p][q][r]=0;
		}
	}

	float **temp;
	temp = (float**)malloc(sizeof(float*)*output_size);
	for(int i=0 ; i<output_size; i++)
		temp[i] = (float*)malloc(sizeof(float)*output_size);

	for(int j=0; j<num_kernel; j++)
	{	for(int i=0; i<input_channels ; i++)
		{
			temp = convoWithoutPadding(a[i], input_size, k[j][i], kernel_size);
			b[j] = add(b[j], temp, output_size);  //adding corresponding elements of convolved matrix
		}
	}

	for(int i=0; i<num_kernel; i++)
	{
		b[i] = add_bias(b[i], bias[i], output_size);
	}

	return b;
}


/* For layer FC_1: input matrix => 4*4*50
	Kernel =>  4*4*50 , 500
	bias values => 500
	output => 1*1*500

	with a relu layer
*/

/* For layer FC_2:  input matrix => 1*1*500
	kernel => 1*1*500, 10
	bias values => 10
	output => 1*1*10 
*/
