#include <bits/stdc++.h> 
#include <string> 

using namespace std;

#include "layer1.h"
#include "layer2.h"
#include "layer3.h"

int main(int argc, char *argv[])
{
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

	float ***b; //to hold the output from first layer

	b = (float***)malloc(sizeof(float**)*20);
	for(int i=0 ; i<20; i++)
		b[i] = (float**)malloc(sizeof(float*)*24);
	for(int j=0 ; j<20; j++)
	{
		for(int i=0 ; i<24; i++)
			b[j][i] = (float*)malloc(sizeof(float)*24);
	}	


	b = first_layer(word[0], 28, word[1], 5, 20, b);
	//1st layer applied
	//output after 1st layer in b

	float ***c;

	c = (float***)malloc(sizeof(float**)*20);
	for(int i=0 ; i<20; i++)
		c[i] = (float**)malloc(sizeof(float*)*(12));
	for(int j=0 ; j<20; j++)
	{
		for(int i=0 ; i<12; i++)
			c[j][i] = (float*)malloc(sizeof(float)*(12));
	}	

	c = Pooling(b, 20, 24, c );
	//second layer applied
	//output after second layer in c


	float ***d;
	d = (float***)malloc(sizeof(float**)*50);
	for(int i=0 ; i<50; i++)
		d[i] = (float**)malloc(sizeof(float*)*8);
	for(int j=0 ; j<50; j++)
	{
		for(int i=0 ; i<8; i++)
			d[j][i] = (float*)malloc(sizeof(float)*8);
	}	

	d = third_layer(c , word[2], 50, 20, 12, 5, d);
	//third layer applied
	//output after third layer in d

	float ***e;

	e = (float***)malloc(sizeof(float**)*50);
	for(int i=0 ; i<4; i++)
		e[i] = (float**)malloc(sizeof(float*)*(4));
	for(int j=0 ; j<4; j++)
	{
		for(int i=0 ; i<4; i++)
			e[j][i] = (float*)malloc(sizeof(float)*(4));
	}	

	e = Pooling(d, 50, 8, e );
	//output of 4th layer i.e. 2nd pooling in e =>  4*4*50

	float ***f;
	f = (float***)malloc(sizeof(float**)*500);
	for(int i=0 ; i<500; i++)
		f[i] = (float**)malloc(sizeof(float*)*1);
	for(int j=0 ; j<500; j++)
	{
		f[j][0] = (float*)malloc(sizeof(float)*1);
	}	

	f = third_layer(e , word[3], 500, 50, 4, 4, f);
	//5th layer applied
	//output after 5th layer in f => 1*1*500

	
	float ***g;
	g = (float***)malloc(sizeof(float**)*10);
	for(int i=0 ; i<10; i++)
		g[i] = (float**)malloc(sizeof(float*)*1);
	for(int j=0 ; j<10; j++)
	{
		g[j][0] = (float*)malloc(sizeof(float)*1);
	}	

	g = third_layer( f, word[4], 10, 500, 1, 1, g);
	//6th layer applied
	//output after 6th layer in g => 1*1*10

	for(int i=0 ;i<10; i++)
	{
		cout<<g[i][0][0];
	}
	//displaying output probability values of each digit 0-9

	//freeing memory
	for(int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 24; j++) 
			free(b[i][j]);
	}

	for (int j = 0; j < 20; j++) 
			free(b[j]);
	free(b);


	for(int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 12; j++) 
			free(c[i][j]);
	}

	for (int j = 0; j < 20; j++) 
			free(c[j]);
	free(c);

	for(int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 8; j++) 
			free(d[i][j]);
	}

	for (int j = 0; j < 50; j++) 
			free(d[j]);
	free(d);

	for(int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 4; j++) 
			free(e[i][j]);
	}

	for (int j = 0; j < 50; j++) 
			free(e[j]);
	free(e);

	for(int i = 0; i < 500; i++)
	{
			free(f[i][0]);
	}

	for (int j = 0; j < 500; j++) 
			free(f[j]);
	free(f);

	for(int i = 0; i < 10; i++)
	{
			free(g[i][0]);
	}

	for (int j = 0; j < 10; j++) 
			free(g[j]);
	free(g);


	//read the input from the terminal
	//input formal-> input.txt-conv1.txt-conv2.txt-fc1.txt-fc2.txt


	return 0;

}