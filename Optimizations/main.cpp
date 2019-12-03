
#include <bits/stdc++.h> 
#include <string> 
#include <ctime>

using namespace std;

#include "others.h"
#include "sourcePT.h"
#include "sourceMKL.h"
#include "sourceOB.h"

int main(int argc, char *argv[])
{
	clock_t time;
	string str;
	cin >> str;
	string word[10];

	for (int i = 0; i<6; i++)
	{
		word[i] = "";
	}

	short counter = 0;


	for (short i = 0; i<str.length(); i++)
	{

		if (str[i] == '-') {

			counter++;
			i++;
		}
		word[counter] += str[i];

	}

	string matrix1;
	string matrix2;
	string vector1;
	int d1;
	int d2;
	int d3;

	if (word[0] == "convoWithoutPadding")
	{
		matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
		if (d1 <= d2)
		{
			cout << "invalid input: dim of kernel >= dim of input matrix" << endl;
		}
		else {
			float **p;
			p = (float**)malloc(sizeof(float*)*d1);

			for (int i = 0; i<d1; i++)
				p[i] = (float*)malloc(sizeof(float*)*d1);

			float **q;
			q = (float**)malloc(sizeof(float*)*d2);

			for (int i = 0; i<d2; i++)
				q[i] = (float*)malloc(sizeof(float*)*d2);

			if (readFile(p, d1, matrix1) == 1 && readFile(q, d2, matrix2) == 1)   //for valid input from the txt file
			{

				float **Answer;
				//Answer = convoWithoutPadding(p, d1, q, d2);

				// p = matrix1 is the INPUT matrix
				// q = matrix2 is the Kernel            
				// d1 = dimensions of p
				// d2 = dimensions of q

 				 for(int i=0; i<25; i++)
					{
						time = clock();
						Answer = convoWithoutPadding(p, d1, q, d2);
						time = clock()-time;
						ofstream out("plot_convoWith.txt", ofstream::app);
						out << d1 <<"  "<<((double)time/CLOCKS_PER_SEC)<<endl;
						out.close();
					}

				int dimOut = d1 - d2 + 1;

				for (int u = 0; u < dimOut; u++) {
					for (int v = 0; v <dimOut; v++) {

						cout << Answer[u][v] << " ";
					}


					cout << "\n";
				}


				for (int i = 0; i < dimOut; i++) {
					free(Answer[i]);
				}
				free(Answer);

			}
		}
	}

	else if (word[0] == "convoWithPadding")
	{
		matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
		d3 = atoi(word[5].c_str());


		if (d1 <= d2)
		{
			cout << "invalid input: dim of kernel >= dim of input matrix" << endl;
		}

		else if ((2*d3) > (d2-1)) {

			cout << "invalid input: dim of padding is more and will result in a greater sized output" << endl;


		}

		
		else {
			float **p;
			
			
			p = (float**)malloc(sizeof(float*)*d1);

			for (int i = 0; i<d1; i++)
				p[i] = (float*)malloc(sizeof(float*)*d1);

			float **q;
			q = (float**)malloc(sizeof(float*)*d2);

			for (int i = 0; i<d2; i++)
				q[i] = (float*)malloc(sizeof(float*)*d2);

			if (readFile(p, d1, matrix1) == 1 && readFile(q, d2, matrix2) == 1)   //for valid input from the txt file
			{

				float **Answer;
				//Answer = convoWithPadding(p, d1, q, d2, d3);

				// p = matrix1 is the INPUT matrix
				// q = matrix2 is the Kernel            
				// d1 = dimensions of p
				// d2 = dimensions of q

				 for(int i=0; i<25; i++)
					{
						time = clock();
						Answer = convoWithPadding(p, d1, q, d2);
						time = clock()-time;
						ofstream out("plot_convoWith.txt", ofstream::app);
						out << d1 <<"  "<<((double)time/CLOCKS_PER_SEC)<<endl;
						out.close();
					}


				int dimOut = d1 + 2*d3 - d2 + 1;


				for (int u = 0; u < dimOut; u++) {
					for (int v = 0; v <dimOut; v++) {

						cout << Answer[u][v] << " ";
					}


					cout << "\n";
				}


				for (int i = 0; i < dimOut; i++) {
					free(Answer[i]);
				}
				free(Answer);

			}
		}




	}

	else if (word[0] == "multWithoutPadding")
	{
		matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
		if (d1 <= d2)
		{
			cout << "invalid input: dim of kernel >= dim of input matrix" << endl;
		}
		else {
			float **p;
			p = (float**)malloc(sizeof(float*)*d1);

			for (int i = 0; i<d1; i++)
				p[i] = (float*)malloc(sizeof(float*)*d1);

			float **q;
			q = (float**)malloc(sizeof(float*)*d2);

			for (int i = 0; i<d2; i++)
				q[i] = (float*)malloc(sizeof(float*)*d2);

			if (readFile(p, d1, matrix1) == 1 && readFile(q, d2, matrix2) == 1)   //for valid input from the txt file
			{
				float **Answer;
				//Answer = multWithoutPadding(p, d1, q, d2);

				// p = matrix1 is the INPUT matrix
				// q = matrix2 is the Kernel            
				// d1 = dimensions of p
				// d2 = dimensions of q
				
				 for(int i=0; i<25; i++)
					{
						time = clock();
						Answer = multWithoutPadding(p, d1, q, d2);
						time = clock()-time;
						ofstream out("plot_multWithout.txt", ofstream::app);
						out << d1 <<"  "<<((double)time/CLOCKS_PER_SEC)<<endl;
						out.close();
					}
				int dimOut = d1 - d2 + 1;

				for (int u = 0; u < dimOut; u++) {
					for (int v = 0; v <dimOut; v++) {

						cout << Answer[u][v] << " ";
					}


					cout << "\n";
				}


				for (int i = 0; i < dimOut; i++) {
					free(Answer[i]);
				}
				free(Answer);

			}
		}
	}

	else if (word[0] == "multWithPadding")
	{
		matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
		d3 = atoi(word[5].c_str());

		
		if (d1 <= d2)
		{
			cout << "invalid input: dim of kernel >= dim of input matrix" << endl;
		}

		else if ((2*d3) > (d2-1)) {

			cout << "invalid input: dim of padding is more and will result in a greater sized output" << endl;


		}

		
		else {
			float **p;
			p = (float**)malloc(sizeof(float*)*d1);

			for (int i = 0; i<d1; i++)
				p[i] = (float*)malloc(sizeof(float*)*d1);

			float **q;
			q = (float**)malloc(sizeof(float*)*d2);

			for (int i = 0; i<d2; i++)
				q[i] = (float*)malloc(sizeof(float*)*d2);

			if (readFile(p, d1, matrix1) == 1 && readFile(q, d2, matrix2) == 1)   //for valid input from the txt file
			{
				float **Answer;
				//Answer = multWithPadding(p, d1, q, d2, d3);

				// p = matrix1 is the INPUT matrix
				// q = matrix2 is the Kernel            
				// d1 = dimensions of p
				// d2 = dimensions of q
 				for(int i=0; i<25; i++)
					{
						time = clock();
						Answer = multWithoutPadding(p, d1, q, d2);
						time = clock()-time;
						ofstream out("plot_multWith.txt", ofstream::app);
						out << d1 <<"  "<<((double)time/CLOCKS_PER_SEC)<<endl;
						out.close();
					}

				int dimOut = d1 + 2*d3 - d2 +1;

				for (int u = 0; u < dimOut; u++) {
					for (int v = 0; v <dimOut; v++) {

						cout << Answer[u][v] << " ";
					}


					cout << "\n";
				}


				for (int i = 0; i < dimOut; i++) {
					free(Answer[i]);
				}
				free(Answer);

			}
		}




	}

	else if (word[0] == "multWithPadding_MKL")
	{
		matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
		d3 = atoi(word[5].c_str());
		
		if (d1 <= d2)
		{
			cout << "invalid input: dim of kernel >= dim of input matrix" << endl;
		}

		else if ((2*d3) > (d2-1)) {

			cout << "invalid input: dim of padding is more and will result in a greater sized output" << endl;


		}

		
		else {
			float **p;
			p = (float**)malloc(sizeof(float*)*d1);

			for (int i = 0; i<d1; i++)
				p[i] = (float*)malloc(sizeof(float*)*d1);

			float **q;
			q = (float**)malloc(sizeof(float*)*d2);

			for (int i = 0; i<d2; i++)
				q[i] = (float*)malloc(sizeof(float*)*d2);

			//cout << "Got the inputs xD" << endl;

			if (readFile(p, d1, matrix1) == 1 && readFile(q, d2, matrix2) == 1)   //for valid input from the txt file
			{
				float **Answer;
				//Answer = multWithPadding_MKL(p, d1, q, d2, d3);

				// p = matrix1 is the INPUT matrix
				// q = matrix2 is the Kernel            
				// d1 = dimensions of p
				// d2 = dimensions of q

				  for(int i=0; i<25; i++)
					{
						time = clock();
						Answer = multWithPadding_MKL(p, d1, q, d2);
						time = clock()-time;
						ofstream out("plot_MKLwith.txt", ofstream::app);
						out << d1 <<"  "<<((double)time/CLOCKS_PER_SEC)<<endl;
						out.close();
					}

				int dimOut = d1 + 2*d3 - d2 +1;

				for (int u = 0; u < dimOut; u++) {
					for (int v = 0; v <dimOut; v++) {

						cout << Answer[u][v] << " ";
					}


					cout << "\n";
				}


				for (int i = 0; i < dimOut; i++) {
					free(Answer[i]);
				}
				free(Answer);

			}
		}




	}


	else if (word[0] == "multWithoutPadding_MKL") {

		matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
		if (d1 <= d2)
		{
			cout << "invalid input: dim of kernel >= dim of input matrix" << endl;
		}
		else {
			float **p;
			p = (float**)malloc(sizeof(float*)*d1);

			for (int i = 0; i<d1; i++)
				p[i] = (float*)malloc(sizeof(float*)*d1);

			float **q;
			q = (float**)malloc(sizeof(float*)*d2);

			for (int i = 0; i<d2; i++)
				q[i] = (float*)malloc(sizeof(float*)*d2);



			if (readFile(p, d1, matrix1) == 1 && readFile(q, d2, matrix2) == 1)   //for valid input from the txt file
			{
				float **Answer;
//				Answer = multWithoutPadding_MKL(p, d1, q, d2);

				// p = matrix1 is the INPUT matrix
				// q = matrix2 is the Kernel            
				// d1 = dimensions of p
				// d2 = dimensions of q

				 for(int i=0; i<25; i++)
					{
						time = clock();
						Answer = multWithoutPadding_MKL(p, d1, q, d2);
						time = clock()-time;
						ofstream out("plot_MKLwithout.txt", ofstream::app);
						out << d1 <<"  "<<((double)time/CLOCKS_PER_SEC)<<endl;
						out.close();
					}

				int dimOut = d1 - d2 + 1;

				for (int u = 0; u < dimOut; u++) {
					for (int v = 0; v <dimOut; v++) {

						cout << Answer[u][v] << " ";
					}


					cout << "\n";
				}


				for (int i = 0; i < dimOut; i++) {
					free(Answer[i]);
				}
				free(Answer);

			}
		}



	}

	else if (word[0] == "multWithPadding_OB")
	{
		matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
		d3 = atoi(word[5].c_str());
		
		if (d1 <= d2)
		{
			cout << "invalid input: dim of kernel >= dim of input matrix" << endl;
		}

		else if ((2*d3) > (d2-1)) {

			cout << "invalid input: dim of padding is more and will result in a greater sized output" << endl;


		}

		
		else {
			float **p;
			p = (float**)malloc(sizeof(float*)*d1);

			for (int i = 0; i<d1; i++)
				p[i] = (float*)malloc(sizeof(float*)*d1);

			float **q;
			q = (float**)malloc(sizeof(float*)*d2);

			for (int i = 0; i<d2; i++)
				q[i] = (float*)malloc(sizeof(float*)*d2);

			//cout << "Got the inputs xD" << endl;

			if (readFile(p, d1, matrix1) == 1 && readFile(q, d2, matrix2) == 1)   //for valid input from the txt file
			{
				float **Answer;
				//Answer = multWithPadding_OB(p, d1, q, d2, d3);
				
				 for(int i=0; i<25; i++)
					{
						time = clock();
						Answer = multWithPadding_OB(p, d1, q, d2, d3);
						time = clock()-time;
						ofstream out("plot_OBwith.txt", ofstream::app);
						out << d1 <<"  "<<((double)time/CLOCKS_PER_SEC)<<endl;
						out.close();
					}

				// p = matrix1 is the INPUT matrix
				// q = matrix2 is the Kernel            
				// d1 = dimensions of p
				// d2 = dimensions of q

				int dimOut = d1 + 2*d3 - d2 +1;

				for (int u = 0; u < dimOut; u++) {
					for (int v = 0; v <dimOut; v++) {

						cout << Answer[u][v] << " ";
					}


					cout << "\n";
				}


				for (int i = 0; i < dimOut; i++) {
					free(Answer[i]);
				}
				free(Answer);

			}
		}




	}


	else if (word[0] == "multWithoutPadding_OB") {

		matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
		if (d1 <= d2)
		{
			cout << "invalid input: dim of kernel >= dim of input matrix" << endl;
		}
		else {
			float **p;
			p = (float**)malloc(sizeof(float*)*d1);

			for (int i = 0; i<d1; i++)
				p[i] = (float*)malloc(sizeof(float*)*d1);

			float **q;
			q = (float**)malloc(sizeof(float*)*d2);

			for (int i = 0; i<d2; i++)
				q[i] = (float*)malloc(sizeof(float*)*d2);



			if (readFile(p, d1, matrix1) == 1 && readFile(q, d2, matrix2) == 1)   //for valid input from the txt file
			{
				float **Answer;
			//	Answer = multWithoutPadding_OB(p, d1, q, d2);
			
					for(int i=0; i<25; i++)
					{
						time = clock();
						Answer = multWithoutPadding_OB(p, d1, q, d2);
						time = clock()-time;
						ofstream out("plot_OBwithout.txt", ofstream::app);
						out << d1 <<"  "<<((double)time/CLOCKS_PER_SEC)<<endl;
					}

				// p = matrix1 is the INPUT matrix
				// q = matrix2 is the Kernel            
				// d1 = dimensions of p
				// d2 = dimensions of q

				int dimOut = d1 - d2 + 1;

				for (int u = 0; u < dimOut; u++) {
					for (int v = 0; v <dimOut; v++) {

						cout << Answer[u][v] << " ";
					}


					cout << "\n";
				}


				for (int i = 0; i < dimOut; i++) {
					free(Answer[i]);
				}
				free(Answer);

			}
		}



	}
	
	else if (word[0] == "multWithoutPadding_pthread") {

            cout<<"4"<<endl;
		matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
                cout<<"8"<<endl;
		if (d1 <= d2)
		{
			cout << "invalid input: dim of kernel >= dim of input matrix" << endl;
		}
		else {
			float **p;
			p = (float**)malloc(sizeof(float*)*d1);

			for (int i = 0; i<d1; i++)
				p[i] = (float*)malloc(sizeof(float*)*d1);

			float **q;
			q = (float**)malloc(sizeof(float*)*d2);

			for (int i = 0; i<d2; i++)
				q[i] = (float*)malloc(sizeof(float*)*d2);


			if (readFile(p, d1, matrix1) == 1 && readFile(q, d2, matrix2) == 1)   //for valid input from the txt file
			{
				float **Answer;
       
			for(int i=0; i<25; i++)
					{
						time = clock();
						Answer = multWithoutPadding_pthread(p, d1, q, d2);
						time = clock()-time;
						ofstream out("plot_PTwithout.txt", ofstream::app);
						out << d1 <<"  "<<((double)time/CLOCKS_PER_SEC)<<endl;
						out.close();
					}
			
            cout<<"5"<<endl;
			// p = matrix1 is the INPUT matrix
				// q = matrix2 is the Kernel            
				// d1 = dimensions of p
				// d2 = dimensions of q

				int dimOut = d1 - d2 + 1;

				for (int u = 0; u < dimOut; u++) {
					for (int v = 0; v <dimOut; v++) {

						cout << Answer[u][v] << " ";
					}
					cout << "\n";
				}


				for (int i = 0; i < dimOut; i++) {
					free(Answer[i]);
				}
				free(Answer);
			}
		}
	}

	else if (word[0] == "multWithPadding_pthread")
	{
		matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
		d3 = atoi(word[5].c_str());

		
		if (d1 <= d2)
		{
			cout << "invalid input: dim of kernel >= dim of input matrix" << endl;
		}

		else if ((2*d3) > (d2-1)) {

			cout << "invalid input: dim of padding is more and will result in a greater sized output" << endl;


		}

		
		else {
			float **p;
			p = (float**)malloc(sizeof(float*)*d1);

			for (int i = 0; i<d1; i++)
				p[i] = (float*)malloc(sizeof(float*)*d1);

			float **q;
			q = (float**)malloc(sizeof(float*)*d2);

			for (int i = 0; i<d2; i++)
				q[i] = (float*)malloc(sizeof(float*)*d2);

			//cout << "Got the inputs xD" << endl;

			if (readFile(p, d1, matrix1) == 1 && readFile(q, d2, matrix2) == 1)   //for valid input from the txt file
			{
				float **Answer;
       
				// p = matrix1 is the INPUT matrix
				// q = matrix2 is the Kernel            
				// d1 = dimensions of p
				// d2 = dimensions of q

       
				for(int i=0; i<25; i++)
					{
						time = clock();
						Answer = multWithPadding_pthread(p, d1, q, d2, d3);
						time = clock()-time;
						ofstream out("plot_PTwith.txt", ofstream::app);
						out << d1 <<"  "<<((double)time/CLOCKS_PER_SEC)<<endl;
						out.close();
					}
			

				int dimOut = d1 + 2*d3 - d2 +1;

				for (int u = 0; u < dimOut; u++) {
					for (int v = 0; v <dimOut; v++) {

						cout << Answer[u][v] << " ";
					}


					cout << "\n";
				}


				for (int i = 0; i < dimOut; i++) 
     			        {
					free(Answer[i]);
				}
				free(Answer);
			}
		}
	}





	else if (word[0] == "maxPool")
	{
		matrix1 = word[1];

		d1 = atoi(word[2].c_str());

		if (d1 % 2 == 1)
		{
			cout << "input matrix should have even dimensions" << endl;
		}
		else
		{
			float **a;
			a = (float**)malloc(sizeof(float*)*d1);

			for (int i = 0; i<d1; i++)
				a[i] = (float*)malloc(sizeof(float)*d1);

			int b = readFile(a, d1, matrix1);
			if (b == 1)
			{
				pooling(a, d1, word[0]);
			}
		}
	}


	else if (word[0] == "avgPool")
	{
		matrix1 = word[1];
		d1 = atoi(word[2].c_str());

		if (d1 % 2 == 1)
		{
			cout << "input matrix should have even dimensions" << endl;
		}

		else
		{
			float **a;
			a = (float**)malloc(sizeof(float*)*d1);

			for (int i = 0; i<d1; i++)
				a[i] = (float*)malloc(sizeof(float)*d1);

			int b = readFile(a, d1, matrix1);
			if (b == 1)
			{
				pooling(a, d1, word[0]);
			}
		}
	}

	else if (word[0] == "relu")
	{
		matrix1 = word[1];
		d1 = atoi(word[2].c_str());

		float **a;
		a = (float**)malloc(sizeof(float*)*d1);

		for (int i = 0; i<d1; i++)
			a[i] = (float*)malloc(sizeof(float)*d1);

		int b = readFile(a, d1, matrix1);
		if (b == 1)
		{
			non_linear_activation(a, d1, word[0]);
		}

	}

	else if (word[0] == "tanh")
	{
		matrix1 = word[1];
		d1 = atoi(word[2].c_str());

		float **a;
		a = (float**)malloc(sizeof(float*)*d1);

		for (int i = 0; i<d1; i++)
			a[i] = (float*)malloc(sizeof(float)*d1);

		int b = readFile(a, d1, matrix1);
		if (b == 1)
		{
			non_linear_activation(a, d1, word[0]);
		}

	}


	else if (word[0] == "sigmoid")
	{
		matrix1 = word[1];

		// please change the final ReadMe with you where you have to give the size of the matrix as well in the input

		d1 = atoi(word[2].c_str());

		float* v;
		v = (float*)malloc(sizeof(float)*d1);

		// Just as you have a file read function for n * n matrix; make one for n * 1 matrix and name it readArray(float **v, int size, string fileName)

		if (readArray(v, d1, matrix1) == 1)
		{
			float *ReturnVal;
			ReturnVal = (float*)malloc(sizeof(float)*d1);

			for (int i = 0; i< d1; i++)
				ReturnVal[i] = 1 / (1 + exp(v[i]));

			for (int i = 0; i<d1; i++)
				cout << ReturnVal[i] << " ";
			//softmax_sigmoid(v, d1, "sigmoid");
		}

	}

	else if (word[0] == "softmax")
	{

		matrix1 = word[1];

		d1 = atoi(word[2].c_str());

		float* v;
		v = (float*)malloc(sizeof(float)*d1);

		if (readArray(v, d1, matrix1) == 1)
		{
			float sum = 0.0;

			float *ReturnVal;
			ReturnVal = (float*)malloc(sizeof(float)*d1);

			for (int i = 0; i<d1; i++)
				sum = sum + exp(v[i]);

			for (int i = 0; i<d1; i++)
				ReturnVal[i] = exp(v[i]) / sum;

			for (int i = 0; i<d1; i++)
				cout << ReturnVal[i] << " ";


		}
		// softmax_sigmoid(v, d1, "sigmoid");

		cout << "Got the inputs xD" << endl;

	}

	


	else {
		cout << "Invalid command" << endl;
	}

}
