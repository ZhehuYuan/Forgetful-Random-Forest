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
	if(argc!=3){
                printf("Please input parameters: [0 for random forest or 1 for decision tree] [0 to 2 for different settings]\n");
                return -1;
        }
	int isSparse[7] = {0, 1, 1, 1, 1, 1, 1};
	long feature = 7;
	long no = 2000;
	long classes = 2;
	double forgetRate = 0.1;
	
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
	       	if(argv[2][0]=='0'){
			test = new RandomForest(50, 20, 5, 8, feature, (int*)isSparse, forgetRate, 7, classes, Evaluation::gini);
		}else{
			test = new RandomForest(20, 20, 5, 8, feature, (int*)isSparse, forgetRate, 7, classes, Evaluation::gini);
		}
		for(i = 1; i<944; i++){
			if(i%7==1){
				data = (double**)malloc(no*sizeof(double*));
				result = (long*)malloc(no*sizeof(long));
				c=0;
			}
        		infile.open(str+std::to_string(i)+str2, std::ios::in);
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
			if(i%7!=0 and i!=943)continue;
			if(i>140){
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
	       	if(argv[2][0]=='0'){
			test = new DecisionTree(8, feature, isSparse, 0.1, feature, classes, Evaluation::gini);
		}else if(argv[2][0]=='1'){
			test = new DecisionTree(8, feature, isSparse, 0, feature, classes, Evaluation::gini);
		}else if(argv[2][0]=='2'){
			test = new DecisionTree(8, feature, isSparse, 0.1, feature, classes, Evaluation::gini);
			test->Rebuild = true;
		}else if(argv[2][0]=='3'){
			test = new DecisionTree(8, feature, isSparse, 0.05, feature, classes, Evaluation::gini);
		}else if(argv[2][0]=='4'){
			test = new DecisionTree(8, feature, isSparse, 0.2, feature, classes, Evaluation::gini);
		}
		long maxSize = 0;
		for(i = 1; i<944; i++){
			if(i%7==1){
				data = (double**)malloc(no*sizeof(double*));
				result = (long*)malloc(no*sizeof(long));
				c=0;
			}
        		infile.open(str+std::to_string(i)+str2, std::ios::in);
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
			if(i%7==0 or i==943){
				if(i>140){
        				for(j=0; j<c; j++){
						if(test->Test(data[j], test->DTree)==result[j])T++;
						all++;
        				}
				}
				if(i!=943){
					start = clock();
					test->fit(data, result, c);
					tmp = (double)(clock()-start)/CLOCKS_PER_SEC;
					timeTaken += tmp;
					if (maxSize<test->DTree->size)maxSize=test->DTree->size;
				}
			}
		}
		printf("%f\n%f\n%ld\n", timeTaken, (double)T/all, maxSize);
	}
}
