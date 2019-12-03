#include <bits/stdc++.h> 
#include <string> 

#include "others.h"

using namespace std;


int readFile(float **x, int n, string file)
{

	//cout<<"1"<<endl;
	int count = 0;
	float *a;
	a = (float*)malloc(sizeof(float)*(n*n));
	ifstream inFile;
	inFile.open(file.c_str());

	//cout<<"1"<<endl;
	if (!inFile.is_open())
	{
		cout << "file doesn't open" << endl;
		return 0;
	}

	float word;
	//std::string::size_type sz; 
	while ((inFile >> word) && count<(n*n))
	{
		a[count] = word;
		count++;
	}

	if (count<(n*n))
	{
		cout << "Incompatible data" << endl;
		return 0;
	}
	inFile.close();
	int t = 0;
	for (int j = 0; j<sqrt(count); j++)
	{
		for (int i = 0; i<sqrt(count); i++)
		{
			x[i][j] = a[t];
			t++;
		}
	}
	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int readArray(float *v, int n, string file)
{
	int count = 0;
	ifstream inFile;
	inFile.open(file.c_str());

	//cout<<"1"<<endl;
	if (!inFile.is_open())
	{
		cout << "file doesn't open" << endl;
		return 0;
	}

	float word;

	while ((inFile >> word) && count<n)
	{
		v[count] = word;
		count++;
	}
	if (count<(n))
	{
		cout << "Incompatible data" << endl;
		return 0;
	}
	inFile.close();

	return 1;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void non_linear_activation(float **a, int n, string str)
{

	float e = 2.71828;

	float x, y;

	//applying relu
	if (str == "relu")
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

	//applying tanh
	else {
		for (int i = 0; i<n; i++)
		{
			for (int j = 0; j<n; j++)
			{
				if (a[i][j]>65) a[i][j] = 1;

				else
				{
					x = pow(e, a[i][j]);
					y = pow(e, -a[i][j]);

					a[i][j] = (x - y) / (x + y);
				}
			}
		}
	}
	//print final matrix
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
		{
			cout << a[i][j] << "  ";
		}

		cout << endl;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//finding maximum
float max(float **x, int n)
{
	float m = x[0][0];

	for (int i = 0; i<n / 2; i++)
	{
		for (int j = 0; j<n / 2; j++)
		{
			if (m < x[i][j])
				m = x[i][j];
		}
	}
	return (float)m;
}

//finding average
float avg(float **x, int n)
{
	float a = 0;

	for (int i = 0; i<n / 2; i++)
	{
		for (int j = 0; j<n / 2; j++)
		{
			a = a + x[i][j];
		}
	}

	//cout<< endl;

	return (float)(4 * a / (n*n));
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

float **multWithoutPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel) {

	int sizeOut = sizeInput - sizeKernel + 1;

	int rows = sizeOut * sizeOut;
	int columns = sizeInput * sizeInput;

	float **newA;
	newA = (float**)malloc(sizeof(float*) * columns);

	for (int i = 0; i < rows; i++) {
		newA[i] = (float*)malloc(sizeof(float*) * columns);
	}

	float **newB;
	newB = (float**)malloc(sizeof(float*) * 1);
	for (int i = 0; i<columns; i++)
	{
		newB[i] = (float*)malloc(sizeof(float) * 1);
	}


	for (int i = 0; i< columns; i++) {

		newB[i][0] = 0.0;
	}

	// Invert the kernel as well here

	if (sizeKernel % 2 == 0) {

		for (int i = 0; i < sizeKernel / 2; i++) {

			for (int j = 0; j < sizeKernel; j++) {

				float temp;
				temp = Kernel[i][j];
				Kernel[i][j] = Kernel[sizeKernel - 1 - i][sizeKernel - 1 - j];
				Kernel[sizeKernel - 1 - i][sizeKernel - 1 - j] = temp;

			}


		}
	}

	else {

		for (int i = 0; i < (sizeKernel - 1) / 2; i++) {

			for (int j = 0; j < sizeKernel; j++) {

				float temp;
				temp = Kernel[i][j];
				Kernel[i][j] = Kernel[sizeKernel - 1 - i][sizeKernel - 1 - j];
				Kernel[sizeKernel - 1 - i][sizeKernel - 1 - j] = temp;

			}


		}

		int p = (sizeKernel - 1) / 2;

		for (int j = 0; j< (sizeKernel - 1) / 2; j++) {

			float temp;
			temp = Kernel[p][j];
			Kernel[p][j] = Kernel[sizeKernel - 1 - p][sizeKernel - 1 - j];
			Kernel[sizeKernel - 1 - p][sizeKernel - 1 - j] = temp;

		}

	}

	int zeroCount = 0;
	int difference = sizeInput - sizeKernel;
	int countInA = 0;

	int currentRow = 0;

	int currentCol = 0;

	for (int i = 0; i< rows; i++) {

		currentRow = 0;
		currentCol = 0;

		countInA = 0;
		if ((i%sizeOut == 0) && (i != 0)) zeroCount = (zeroCount)+sizeKernel - 1;

		for (int j = 0; j< columns; j++) {

			if (j < zeroCount)    newA[i][j] = 0.0;
			//           cout << newA[i][j] << " ";}
			else {

				if (countInA < sizeKernel *sizeKernel) {

					if (currentCol == sizeKernel) {

						currentRow++;
						currentCol = 0;
						for (int z = 0; z< difference; z++) {

							newA[i][j + z] = 0.0;
							//      cout << newA[i][j+z] << " ";

						}

						j = j + difference - 1;
					}

					else {

						newA[i][j] = Kernel[currentRow][currentCol];
						currentCol++;
						countInA++;
						//cout << newA[i][j] << " "; 

					}

				}

				else {
					newA[i][j] = 0.0;
					//                  cout << newA[i][j] << " ";

				}

			}

		}

		zeroCount++;
		//     cout << "\n";
	}



	int countTemp = 0;

	for (int i = 0; i< sizeInput; i++) {

		for (int j = 0; j < sizeInput; j++) {

			newB[countTemp][0] = Input[i][j];

			countTemp++;
		}

	}
	cout << "\n";

	float **matrixOut;
	matrixOut = (float**)malloc(sizeof(float*) * sizeOut);

	for (int i = 0; i < sizeOut; i++) {
		matrixOut[i] = (float*)malloc(sizeof(float*) * sizeOut);
	}

	float **newC;

	newC = (float**)malloc(sizeof(float*) * 1);

	for (int i = 0; i<rows; i++)
	{
		newC[i] = (float*)malloc(sizeof(float) * 1);
	}

	float sum = 0.0;

	for (int i = 0; i < rows; i++) {

		sum = 0.0;

		for (int j = 0; j< columns; j++) {

			sum = sum + newA[i][j] * newB[j][0];

		}

		newC[i][0] = sum;

	}

	int rowNo = 0;
	int colNo = 0;

	for (int i = 0; i < rows; i++) {

		if ((i%sizeOut == 0) && (i != 0)) {

			rowNo++;
			colNo = 0;

		}

		matrixOut[rowNo][colNo] = newC[i][0];

		colNo++;


	}


	for (int i = 0; i < rows; i++) {
		free(newA[i]);
	}
	free(newA);

	return matrixOut;


}

float **convoWithPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel, int padding) {


	// Assuming that the size of kernel is Odd. I guess that we should throw an error on 
	//the command prompt if we try to do this for an even sized kernel

//	int padding = (sizeKernel - 1) / 2;

	int newSize = sizeInput + 2 * padding;

	float **newMatrixIn;
	newMatrixIn = (float**)malloc(sizeof(float*) * newSize);

	for (int i = 0; i < newSize; i++) {
		newMatrixIn[i] = (float*)malloc(sizeof(float*) * newSize);
	}


	for (int i = 0; i < newSize; i++) {
		for (int j = 0; j < newSize; j++) {

			if (i < padding)
				newMatrixIn[i][j] = 0.0;

			else if (i >= newSize - padding)
				newMatrixIn[i][j] = 0.0;

			else if (j < padding)
				newMatrixIn[i][j] = 0.0;

			else if (j >= newSize - padding)
				newMatrixIn[i][j] = 0.0;

			else
				newMatrixIn[i][j] = Input[i - padding][j - padding];
		}
	}

	int sizeOut = newSize - sizeKernel + 1;

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

					sum = sum + newMatrixIn[u + i][v + j] * Kernel[sizeKernel - u - 1][sizeKernel - v - 1];
				}
			}

			matrixOut[i][j] = sum;

		}
	}

	return matrixOut;

}

float **multWithPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel, int padding) {

	// Assuming that the size of kernel is Odd. I guess that we should throw an error on 
	//the command prompt if we try to do this for an even sized kernel

//	int padding = (sizeKernel - 1) / 2;

	int newSize = sizeInput + 2 * padding;

	float **newMatrixIn;
	newMatrixIn = (float**)malloc(sizeof(float*) * newSize);

	for (int i = 0; i < newSize; i++) {
		newMatrixIn[i] = (float*)malloc(sizeof(float*) * newSize);
	}


	for (int i = 0; i < newSize; i++) {
		for (int j = 0; j < newSize; j++) {

			if (i < padding)
				newMatrixIn[i][j] = 0.0;

			else if (i >= newSize - padding)
				newMatrixIn[i][j] = 0.0;

			else if (j < padding)
				newMatrixIn[i][j] = 0.0;

			else if (j >= newSize - padding)
				newMatrixIn[i][j] = 0.0;

			else
				newMatrixIn[i][j] = Input[i - padding][j - padding];
		}
	}

	float **Answer;
	Answer = multWithoutPadding(newMatrixIn, newSize, Kernel, sizeKernel);

	return Answer;

}


void pooling(float **a, int n, string s)
{

	float **x;
	x = (float**)malloc(sizeof(float*)*n / 2);

	for (int i = 0; i<n / 2; i++)
	{
		x[i] = (float*)malloc(sizeof(float)*n / 2);
	}

	float y[2][2];
	float z[2][2];

	if (s == "maxPool")
	{ //max pooling
		for (int i = 0; i <= n / 2; i = i + n / 2)
		{
			for (int j = 0; j <= n / 2; j = j + n / 2)
			{
				for (int p = i; p<i + n / 2; p++)
				{
					for (int q = j; q<j + n / 2; q++)
					{
						x[p % (n / 2)][q % (n / 2)] = a[p][q];
					}
				}
				y[i / (n / 2)][j / (n / 2)] = max(x, n);
			}
		}

		//print max pooling
		cout << "The max pooling output is: " << endl;
		cout << y[0][0] << "  " << y[0][1] << endl;
		cout << y[1][0] << "  " << y[1][1] << endl;
	}

	else
	{ //avg pooling
		for (int i = 0; i <= n / 2; i = i + n / 2)
		{
			for (int j = 0; j <= n / 2; j = j + n / 2)
			{
				for (int p = i; p<i + n / 2; p++)
				{
					for (int q = j; q<j + n / 2; q++)
					{
						x[p % (n / 2)][q % (n / 2)] = a[p][q];
					}
				}

				z[i / (n / 2)][j / (n / 2)] = avg(x, n);
			}
		}

		cout << "The avg pooling output is: " << endl;
		cout << z[0][0] << "  " << z[0][1] << endl;
		cout << z[1][0] << "  " << z[1][1] << endl;
	}



}
