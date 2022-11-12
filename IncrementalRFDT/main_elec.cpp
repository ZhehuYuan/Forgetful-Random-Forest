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
        bool created;


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
	if(argc!=3 and argc!=4){
                printf("Please input parameters: [0 for random forest or 1 for decision tree] [0 to 2 for different settings]\n");
                return -1;
        }
	long rb=2147483647;
	long memSize = 1500;
	if(argc==4)rb=atol(argv[3]);
	int isSparse[7] = {0, 1, 1, 1, 1, 1, 1};
	long feature = 7;
	long no = 2000;
	long classes = 2;
	double forgetRate = 0.1;
	int maxH=8;	

	double** data;
	long* result;
	char buf[1024] = { 0 };
	std::ifstream infile;
	std::string str = "electricity/electricity";
	std::string str2 = ".txt";
	long i, j;

	double timeTaken = 0;
	clock_t start;
	double tmp;
	long c = 0;
	long trainSize = 400;
	
	long T = 0, all = 0;
	if(argv[1][0]=='0'){
		RandomForest* test;
		long maxF = 3;
	       	if(atoi(argv[2])==0){
			test = new RandomForest(10, 7, feature, (int*)isSparse, -10.0, classes, Evaluation::gini);
		}
		for(i = 1; i<944; i++){
			data = (double**)malloc(no*sizeof(double*));
			result = (long*)malloc(no*sizeof(long));
			c=0;
        		infile.open(str+std::to_string(i)+str2, std::ios::in);
			while(1){
				data[c] = (double*)malloc((feature+1)*sizeof(double));
				data[c][feature] = 0;
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
        		if(i>20){
				for(j=0; j<c; j++){
					if(test->Test(data[j])==result[j])T++;
					all++;
        			}
			}
			if(i!=943){
				start = clock();
				test->fit(data, result, c);
				tmp = (double)(clock()-start)/CLOCKS_PER_SEC;
				timeTaken += tmp;
			}
		}
		printf("%f\n%f\n", timeTaken, (double)T/all);
	}
	else if(argv[1][0]=='1'){
		DecisionTree* test;
	       	if(atoi(argv[2])==0){
			test = new DecisionTree(7, feature, isSparse, -10.0, feature, classes, Evaluation::gini, 2147483647);
		}else{
			test = new DecisionTree(7, feature, isSparse, 0, feature, classes, Evaluation::gini, 2147483647);
		}
		long maxSize = 0;
		long lastT=0;
		long lastAll=0;
		for(i = 1; i<944; i++){
			data = (double**)malloc(no*sizeof(double*));
			result = (long*)malloc(no*sizeof(long));
			c=0;
        		infile.open(str+std::to_string(i)+str2, std::ios::in);
			while(1){
				data[c] = (double*)malloc((feature+1)*sizeof(double));
				data[c][feature] = 0;
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
			long localT = 0;
			long localAll = 0;
        		if(i>20){
				for(j=0; j<c; j++){
					if(test->Test(data[j], test->DTree)==result[j])localT++;
					localAll++;
        			}
				all+=localAll;
				T+=localT;
			}
			if(i!=943){
				start = clock();
				test->fit(data, result, c);
				tmp = (double)(clock()-start)/CLOCKS_PER_SEC;
				timeTaken += tmp;
				if (maxSize<test->DTree->size)maxSize=test->DTree->size;
			}
		}
		printf("%ld\n", maxSize);
		printf("%f\n%f\n", timeTaken, (double)T/all);
	}
}
