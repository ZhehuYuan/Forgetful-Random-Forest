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
        if(argc!=2){
                printf("Please input parameters: [0 to 2 for different settings]\n");
                return -1;
        }
	bool isSparse[67] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	long feature = 67;
	long no = 48000;
	long classes = 2;
	DecisionTree* test;
       	if(argv[1][0]=='0'){
		test = new DecisionTree(8, feature, (bool*)isSparse, 0.1, feature, classes, Evaluation::gini);
	}else if(argv[1][0]=='1'){
		test = new DecisionTree(8, feature, (bool*)isSparse, 0, feature, classes, Evaluation::gini);
	}else{
		test = new DecisionTree(8, feature, (bool*)isSparse, 0.1, feature, classes, Evaluation::gini);
		test->Rebuild = true;
	}
	double** data;
	long* result;
	char buf[1024] = { 0 };
	std::ifstream infile;
	std::string str = "AWS/";
	
	long i, j;

	double timeTaken = 0;
	clock_t start;
	double tmp;
	long c = 0;
	for(i = 950; i>470; i--){
		if((951-i)%12==1){
			data = (double**)malloc(no*sizeof(double*));
			result = (long*)malloc(no*sizeof(long));
			c=0;
		}
        	infile.open(str+std::to_string(i), std::ios::in);
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
		if((951-i)%12==0){
			start = clock();
			test->fit(data, result, c);
		
			tmp = (double)(clock()-start)/CLOCKS_PER_SEC;
			timeTaken += tmp;
		}
	}
	printf("%f\n", timeTaken);
	long T = 0, all = 0;
	data = (double**)malloc(no*sizeof(double*));
	result = (long*)malloc(no*sizeof(long));
	for(i=470;i>=0;i--){
		c = 0;
        	infile.open(str+std::to_string(i), std::ios::in);
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
        	for(j=0; j<c; j++){
                	if(test->Test(data[j], test->DTree)==result[j])T++;
			free(data[j]);
			all++;
        	}
	}
        printf("%f\n", (double)T/all);
}
