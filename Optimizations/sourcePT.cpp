#include<bits/stdc++.h>
#include <bits/stdc++.h>
#include <string>
#include "sourcePT.h"
#include<pthread.h>


//multWithoutPadding_pthread-m1.txt-32-m2.txt-3
//multWithPadding_pthread-m1.txt-32-m2.txt-3

using namespace std;


float newP[50000];
float new_A[20000][20000];
float new_B[20000][1];

//newP = (float*)malloc(sizeof(float)*50000); //rows = 400

int row_size; //=rows = size_out^2
int colm_size; //colums = size_input^2
int row_num;
int row_div;

void *mult_thread(void *t)
{
     //int row_num = *((int *)t);
     float sum=0;
     for(int j= row_num*row_div ; j< (row_num+1)*row_div; j++ )
     {
         sum = 0;
         for(int i=0; i<colm_size; i++)
         {
             sum = new_A[j][i]*new_B[i][0] + sum;
         }
     newP[j] = sum;
     }
     cout<< "thread finished \n" ;
         pthread_exit(NULL);
}

void *mult_thread_last(void *t)
{
     //int row_num = *((int *)t);
     float sum=0;
     for(int j= row_div*3 ; j< row_size; j++ )
     {
         sum = 0;
         for(int i=0; i<colm_size; i++)
         {
             sum = new_A[j][i]*new_B[i][0] + sum;
         }
     newP[j] = sum;
     }
     cout<< "thread finished \n" ;
         pthread_exit(NULL);
}

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
                         cout<<x[i][j]<<" ";
             t++;
         }
         cout<<endl;
     }
     return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float **multWithoutPadding_pthread(float **Input, int sizeInput, float 
**Kernel, int sizeKernel) {

     float **newA;
     float **newB;
     int sizeOut = sizeInput - sizeKernel + 1;

     int rows = sizeOut * sizeOut;  //17*17=289
     int columns = sizeInput * sizeInput;
     row_size = rows;
     colm_size = columns;
//cout<<"1"<<endl;

     newA = (float**)malloc(sizeof(float*) * rows);
     for (int i = 0; i < rows; i++)
     {
         newA[i] = (float*)malloc(sizeof(float*) * columns);
     }

     newB = (float**)malloc(sizeof(float*) * columns);
     for (int i = 0; i<columns; i++)
     {
         newB[i] = (float*)malloc(sizeof(float) * 1);
     }

     for (int i = 0; i<columns; i++) {

         newB[i][0] = 0.0;
     }

     // Invert the kernel as well here
//cout<<"111"<<endl;

     if (sizeKernel % 2 == 0) {

         for (int i = 0; i < sizeKernel / 2; i++) {

             for (int j = 0; j < sizeKernel; j++) {

                 float temp;
                 temp = Kernel[i][j];
                 Kernel[i][j] = Kernel[sizeKernel - 1 - i][sizeKernel - 1 
- j];
                 Kernel[sizeKernel - 1 - i][sizeKernel - 1 - j] = temp;

             }
         }
     }

     else {

         for (int i = 0; i < (sizeKernel - 1) / 2; i++) {

             for (int j = 0; j < sizeKernel; j++) {

                 float temp;
                 temp = Kernel[i][j];
                 Kernel[i][j] = Kernel[sizeKernel - 1 - i][sizeKernel - 1 
- j];
                 Kernel[sizeKernel - 1 - i][sizeKernel - 1 - j] = temp;

             }


         }
//cout<<"2"<<endl;

         int p = (sizeKernel - 1) / 2;

         for (int j = 0; j< (sizeKernel - 1) / 2; j++) {

             float temp;
             temp = Kernel[p][j];
             Kernel[p][j] = Kernel[sizeKernel - 1 - p][sizeKernel - 1 - 
j];
             Kernel[sizeKernel - 1 - p][sizeKernel - 1 - j] = temp;

         }

     }

     int zeroCount = 0;
     int difference = sizeInput - sizeKernel;
     int countInA = 0;

     int currentRow = 0;

     int currentCol = 0;
cout<<"3"<<endl;
     for (int i = 0; i< rows; i++) {

         currentRow = 0;
         currentCol = 0;

         countInA = 0;
         if ((i%sizeOut == 0) && (i != 0)) zeroCount = 
(zeroCount)+sizeKernel - 1;

         for (int j = 0; j< columns; j++) {

             if (j < zeroCount)    newA[i][j] = 0.0;
             else {

                 if (countInA < sizeKernel *sizeKernel) {

                     if (currentCol == sizeKernel) {

                         currentRow++;
                         currentCol = 0;
                         for (int z = 0; z< difference; z++) {

                             newA[i][j + z] = 0.0;
                         }

                         j = j + difference - 1;
                     }

                     else {

                         newA[i][j] = Kernel[currentRow][currentCol];
                         currentCol++;
                         countInA++;
                     }
                 }

                 else {
                     newA[i][j] = 0.0;
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
cout<<"33"<<endl;
     float **matrixOut;
     matrixOut = (float**)malloc(sizeof(float*) * sizeOut);

     for (int i = 0; i < sizeOut; i++) {
         matrixOut[i] = (float*)malloc(sizeof(float*) * sizeOut);
     }
cout<<"7"<<endl;

     //newP = (float*)malloc(sizeof(float)*rows);
     //copied teh newA to global matrix new_A
        for(int i=0; i<rows; i++)
        {
                for(int j = 0; j< columns; j++)
                {
                        new_A[i][j] = newA[i][j];
                }
        }

        //copied teh newB to global matrix new_B

        for(int j = 0; j< columns; j++)
        {
                new_B[j][0] = newB[j][0];
        }
     pthread_t pthread[4];
cout<<"7"<<endl;
     row_div = rows/3;

cout<<"77"<<endl;

     for (row_num=0; row_num<3; row_num++)
     {
         cout<<"row_num "<<row_num<<endl;
         pthread_create(&pthread[row_num],NULL,mult_thread, NULL);
     }
  cout<<"777"<<endl;
     pthread_create(&pthread[3],NULL,mult_thread_last, NULL);
cout<<"7777"<<endl;
     for (row_num=0; row_num<4; row_num++)
         pthread_join(pthread[row_num],NULL);

cout<<"4"<<endl;

     int rowNo = 0;
     int colNo = 0;

     for (int i = 0; i < rows; i++) {

         if ((i%sizeOut == 0) && (i != 0)) {

             rowNo++;
             colNo = 0;

         }

         matrixOut[rowNo][colNo] = newP[i];

         colNo++;


     }


     for (int i = 0; i < rows; i++)
         free(newA[i]);

     free(newA);

     for (int i = 0; i < columns; i++)
         free(newB[i]);

     free(newB);

    // free(newP);

     return matrixOut;
}


float **multWithPadding_pthread(float **Input, int sizeInput, float 
**Kernel, int sizeKernel, int padding) {

     // Assuming that the size of kernel is Odd. I guess that we should 
throw an error on
     //the command prompt if we try to do this for an even sized kernel

//    int padding = (sizeKernel - 1) / 2;

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
     Answer = multWithoutPadding_pthread(newMatrixIn, newSize, Kernel, 
sizeKernel);

     return Answer;

}