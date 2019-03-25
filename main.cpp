#include<iostream>
#include <time.h>
#include<cstdlib>
#include"classes.h"
using namespace std;

int main(int argc,char** argv){
	srand (time(NULL));

	int n,w;

	if(argc==1){														//In case user forgot to give the number of stations
			cout<<endl<<"Enter the amount of stations you would like: ";
			cin>>n;
	}
	else
	n=atoi(argv[argc-1]);												//Receiving the number of Stations

	cout<<"How many waggons would you like: ";

	cin>>w;

	Train T(n,w);														//Creating the Train 
	
	operate(&T);														//Operating and printing

	PrintStatistics(&T);
	
	return 0;
}
