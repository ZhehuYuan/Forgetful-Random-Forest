#include "DecisionTree.h"
#include "RF.h"
#include <string>
#include <algorithm>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cfloat>
#include <float.h>

struct DT{
        int height;
        long* featureId;
        DT* left = nullptr;
        DT* right = nullptr;

        // split info
        bool terminate;
        double dpoint;
        long feature;
        long result;

        // Sparse data record
        double** sortedData; // for each feature, sorted data
        long** sortedResult;

        // Dense data record
        long*** count = nullptr;// for each feature, number of data belongs to each class and dense value 
        double** record = nullptr;// for each feature, record each dense data
        long* max = nullptr;// number of dense value of each feature

        //long* T; // number of data in each class in this node
        double** dataRecord = nullptr;// Record the data
        long* resultRecord = nullptr;// Record the result
        long size = 0;// Size of the dataset
};

int main(int argc, char* argv[]){
	if(argc != 2 and argc!=3){
		printf("Please input in form of: [0-4 for different settings or larger than 5 for memeory size]");
		return -1;
	}
	long rb=1000000;
	if(argc==3)rb=atol(argv[2]);
	int isSparse[30] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	long feature = 30;
	long no = 30490;
	long classes = 2;
	double forgetRate = 0.1;
	long memSize = 100483;
	DecisionTree* test;
	long maxH = 17;
       	if(atol(argv[1])==1){
		test = new DecisionTree(maxH, feature, (int*)isSparse, 0.1, feature, classes, Evaluation::gini, memSize, 1);
	}else if(atol(argv[1])==0){
		int tmp=maxH;
		if(argc==3)tmp = atoi(argv[2]);
		test = new DecisionTree(tmp, feature, (int*)isSparse, 0.1, feature, classes, Evaluation::gini, memSize, 2147483647);
	}else{
		test = new DecisionTree(18, feature, (int*)isSparse, 0, feature, classes, Evaluation::gini, 300000, 2147483647);
	}
	double** data;
	long* result;
	char buf[1024] = { 0 };
	std::ifstream infile;
	std::string str = "M5/day_";
	
	long i, j;

	double timeTaken = 0;
	clock_t start;
	double tmp;
	long c = 0;
	long maxSize = 0;
	long T = 0, all = 0;
	for(i = 0; i<133; i++){
		data = (double**)malloc(no*sizeof(double*));
		result = (long*)malloc(no*sizeof(long));
        	infile.open(str+std::to_string(i), std::ios::in);
		c=0;
		while(1){
			data[c] = (double*)malloc(feature*sizeof(double));
			for(long j=0; j<feature; j++){
				infile >> buf;
				data[c][j] = atof(buf); 
			}
			infile.get(buf, 20);
			if(atoi(buf)==0){
				result[c] = 0;
			}else{
				result[c] = 1;
			}
			c++;
			if(infile.get() == EOF){
				break;
			}
		}
		infile.close();
		if(i>=20){
        	//if(i>=1){
			for(j=0; j<c; j++){
				all++;
                		if(test->Test(data[j], test->DTree)==result[j])T++;
        		}
			//printf("%f %ld %ld\n", (double)T/all,  test->DTree->size, test->maxHeight);
			//T = 0;
			//all =0;
		}
		if(i!=132){
			//int tmp2 = sqrt(sqrt(test->DTree->size+c));
			//test->maxHeight = tmp2;
			//if(tmp2>18)return 0;
			start = clock();
			test->fit(data, result, c);	
			tmp = (double)(clock()-start)/CLOCKS_PER_SEC;
		}
		timeTaken += tmp;
		if(maxSize<test->DTree->size)maxSize = test->DTree->size;
	}
	printf("%f\n%f\n%ld\n", timeTaken, (double)T/all,  maxSize);
}
