#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

typedef vector< vector <float> >  VVF;
VVF independent(int n, int d);
VVF correlated(int n, int d);
VVF anti_correlated(int n, int d);
double gaussian(double mean, double sigma);
void printVVF(VVF& ret);

int main (int argc, char* argv[])
{
	cout<<"Synthetic dataset generator"<<endl;
	int mode = atoi(argv[1]); 
	int n = atoi(argv[2]);
	int d = atoi(argv[3]);
	VVF ret;
	if(mode==0)
	{
		ret = correlated(n,d);	
		printVVF(ret);
	}
	else if(mode==1)
	{
		ret = independent(n,d);
		printVVF(ret);
	}
	else if(mode==2)
	{
		ret = anti_correlated(n,d);
		printVVF(ret);
	}
	else
	{
		cout<<"error, undefined mode!"<<endl;
	}
	return 0;
};

void printVVF(VVF& ret)
{
	for(int i=0; i<ret.size(); i++)
	{
		for(int j=0; j<ret[i].size(); j++)
		{
			printf("%.4f,",ret[i][j]-0.0001);
		}
		for(int j=0; j<ret[i].size(); j++)
		{
			printf("%.4f,",ret[i][j]+0.0001);
		}
		cout<<endl;
	}
};

VVF independent(int n, int d) 
{
	VVF ret;
	vector<float> tuple;
	for(int i=0; i<n; i++)
	{
		tuple.clear();
		for (int j=0;j<d;j++)
		{
			tuple.push_back(drand48());
		}
		ret.push_back(tuple);
	}
	return ret;
};

VVF correlated(int n, int d) 
{
	VVF ret;
	vector<float> pt(d,0);

	for(int i=0; i<n; i++)
	{
		float value=drand48();
		pt[0]=value;
		for(int j=1;j<d;j++)
		{
			float newval=gaussian(value, 0.05);
			while (newval<0||newval>1)
				newval=gaussian(value, 0.05);
			pt[j]=newval;
		}
		ret.push_back(pt);
	}
	return ret;
};

VVF anti_correlated(int n, int d) 
{
	VVF ret;
	vector<float> pt(d,0);

	for(int i=0; i<n; i++)
	{
		double sigma=0.05;
		double range=0.5*d + gaussian(0,sigma);

		pt[0] = drand48()*min(1.0,range);
		for (int j=1; j<d; j++) 
		{
			range=range-pt[j-1];
			pt[j]=drand48()*min(1.0,range);
			if (j==d-1)
				pt[j]=min(1.0,range);
		}
		ret.push_back(pt);
	}
	return ret;
};

double gaussian(double mean, double sigma) 
{
	double v1,v2,s,x;
	do {
		v1 = drand48();
		if (rand()%2) v1 = -v1;
		v2 = drand48();
		if (rand()%2) v2 = -v2;
		s = v1*v1 + v2*v2;
	} while (s >= 1.);
	x = v1 * sqrt ( -2. * log (s) / s);
	x = x * sigma + mean;
	return x;
};
