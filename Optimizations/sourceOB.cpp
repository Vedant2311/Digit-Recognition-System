#include <bits/stdc++.h> 
#include <string> 

#include "cblas.h"

#include "sourceOB.h"

using namespace std;

// void convolution(float **a, int n, string s)
float **multWithoutPadding_OB(float **Input, int sizeInput, float **Kernel, int sizeKernel) {

	int sizeOut = sizeInput - sizeKernel + 1;

	int rows = sizeOut * sizeOut;
	int columns = sizeInput * sizeInput;

	//float **newA;
	//newA = (float**)malloc(sizeof(float*) * columns);

	//  for(int i = 0; i < rows; i++) {
	//     newA[i] = (float*) malloc(sizeof(float*) * columns);
	// }

	//  float newB[columns][1];

	// for(int i =0; i< columns; i++){

	//    newB[i][0] = 0.0;
	// }

	float *newA;
	float *newB;

	newA = (float *)malloc(rows*columns * sizeof(float));
	newB = (float *)malloc(columns * 1 * sizeof(float));

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

			if (j < zeroCount)    newA[i*columns + j] = 0.0;
			//           cout << newA[i][j] << " ";}
			else {

				if (countInA < sizeKernel *sizeKernel) {

					if (currentCol == sizeKernel) {

						currentRow++;
						currentCol = 0;
						for (int z = 0; z< difference; z++) {

							newA[i*columns + (j + z)] = 0.0;
							//      cout << newA[i][j+z] << " ";

						}

						j = j + difference - 1;
					}

					else {

						newA[i*columns + j] = Kernel[currentRow][currentCol];
						currentCol++;
						countInA++;
						//cout << newA[i][j] << " "; 

					}

				}

				else {
					newA[i*columns + j] = 0.0;
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

			newB[countTemp * 1 + 0] = Input[i][j];

			countTemp++;
		}

	}
	cout << "\n";

	float **matrixOut;
	matrixOut = (float**)malloc(sizeof(float*) * sizeOut);

	for (int i = 0; i < sizeOut; i++) {
		matrixOut[i] = (float*)malloc(sizeof(float*) * sizeOut);
	}



	//float newC[rows][1];

	float *newC;
	newC = (float *)malloc(rows * 1 * sizeof(float));

	// float sum = 0.0;

	// for(int i =0; i < rows; i++){

	//     sum = 0.0;    

	//    for(int j = 0 ; j< columns; j++)   {

	//       sum = sum + newA[i][j]* newB[j][0];

	//  }

	//  newC[i][0] = sum;    

	// }

	float alpha, beta;
	alpha = 1.0; beta = 0.0;

	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		rows, 1, columns, alpha, newA, columns, newB, 1, beta, newC, 1);

	int rowNo = 0;
	int colNo = 0;

	for (int i = 0; i < rows; i++) {

		if ((i%sizeOut == 0) && (i != 0)) {

			rowNo++;
			colNo = 0;

		}

		matrixOut[rowNo][colNo] = newC[i * 1 + 0];

		colNo++;


	}

	free(newA);
	free(newB);
	free(newC);


	return matrixOut;


}




float **multWithPadding_OB(float **Input, int sizeInput, float **Kernel, int sizeKernel, int padding) {

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
	Answer = multWithoutPadding_OB(newMatrixIn, newSize, Kernel, sizeKernel);

	return Answer;

}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


