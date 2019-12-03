#include <bits/stdc++.h> 
#include <string> 
using namespace std;

float max(int a, int b, int c, int d)
{
	float m=a;
	if(b>m) m=b;
	if(c>m) m=c;
	if(d>m) m=d;
	return m;
}


float ***Pooling(float ***b, int no_channel, int size, float ***c ) //b is input and c is output
{
	for(int k=0; k<no_channel; k++)
	{
		for(int i=0; i<size; i=i+2)
		{
			for(int j=0 ;j<size; j=j+2)
			{
				c[k][i/2][j/2] = max(b[k][i][j], b[k][i+1][j], b[k][i][j+1], b[k][i+1][j+1]);
			}
		}
	}

	return c;
}

