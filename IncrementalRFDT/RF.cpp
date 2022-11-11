#include "RF.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <math.h>
#include <algorithm>


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

RandomForest::RandomForest(long mTree, int h, long feature, int* s, double forg, long noC, Evaluation eval, long rb){
	srand((long)clock());
	Rebuild = rb;
	activeTree = mTree;
	maxTree = mTree;
	treePointer = new bool[mTree];
	allT = new long[mTree];

	lastAcc = -1.0;
	long i;
	height = h;
	f = feature;
	sparse = new int[f];
	for(i=0; i<f; i++)sparse[i]=s[i];
	forget = forg;
	noClasses = noC;
	e = eval;
	minF = floor(sqrt((double)f))+1;

	DTrees = (DecisionTree**)malloc(mTree*sizeof(DecisionTree*));
	for(i=0; i<maxTree; i++){
		DTrees[i] = new DecisionTree(height, f, sparse, forget, minF+rand()%(f+1-minF), noClasses, e, rb);
		treePointer[i] = true;
	}
}

void RandomForest::fit(double** data, long* result, long size){
	long i, j, k;
	double** newData;
	long* newResult;
	long count = 0;
	int stale = 0;
	if(lastAcc<0){
		lastAcc=0.0;
	}else{
		for(i=0; i<maxTree; i++)allT[i] = 0;
		for(i=0; i<size; i++){
                	if(Test(data[i], result[i])==result[i])count++;
        	}
		if(lastAcc>0){
			double newAcc = (double)count/size;
			stale = round((newAcc-lastAcc)*maxTree);
			if(stale==0)stale=1;
			lastAcc = (double)count/size;
		}else if(lastAcc==0){
			lastAcc = (double)count/size;
		}
	}
	Rotate(stale);
	for(i=0; i<maxTree; i++){
		if(not treePointer[i])continue;
		newData = (double**)malloc(sizeof(double*)*size);
		newResult = (long*)malloc(sizeof(long)*size);
		for(j = 0; j<size; j++){
			newData[j] = (double*)malloc((f+1)*sizeof(double));
			for(k=0; k<f; k++){
				newData[j][k] = data[j][k];
			}
			newData[j][f] = 0;
			newResult[j] = result[j];
		}
		DTrees[i]->fit(newData, newResult, size);
	}
}

long* RandomForest::fitThenPredict(double** trainData, long* trainResult, long trainSize, double** testData, long testSize){
        fit(trainData, trainResult, trainSize);
        long* testResult = (long*)malloc(testSize*sizeof(long));
        for(long i=0; i<testSize; i++){
                testResult[i] = Test(testData[i]);
        }
        return testResult;
}

void RandomForest::Rotate(long stale){
	long i, j, k;
	long currentMax = -1;
	long maxIndex = -1;
	if(stale==0)return;
	else if(stale>0){
		stale = std::min(stale, maxTree-activeTree);
		while(stale>0){
			for(i = 0; i<maxTree; i++){
				if(not treePointer[i])continue;
				if(allT[i]>currentMax){
					currentMax=allT[i];
					maxIndex=i;
				}
			}
			stale--;
			activeTree--;
			treePointer[maxIndex]=false;
			DTrees[maxIndex]->Stablelize();
		}	
	}else{
		stale = std::min(stale, maxTree);
		stale*=-1;
		while(stale>0){
			long currentMin = 2147483647;
			long minIndex = -1;
			for(i = 0; i<maxTree; i++){
				if(allT[i]<currentMin){
					currentMin=allT[i];
					minIndex=i;
				}
			}
			stale--;
			allT[minIndex] = 2147483647; 
			double** newData;
			long* newResult;
			long size = 0;
			if(treePointer[minIndex]){
				size = DTrees[minIndex]->DTree->size;
				newData = (double**)malloc(sizeof(double*)*size);
				newResult = (long*)malloc(sizeof(long)*size);
				for(j = 0; j<size; j++){
					newData[j] = (double*)malloc(sizeof(double)*(f+1));
                			for(k=0; k<f+1; k++){
                        			newData[j][k] = DTrees[minIndex]->DTree->dataRecord[j][k];
                			}
                			newResult[j] = DTrees[minIndex]->DTree->resultRecord[j];
        			}
				DTrees[minIndex]->Stablelize();
			}else{
				for(i = 0; i<maxTree; i++){
					if(treePointer[i])break;
				}
				if(i==maxTree)i--;
				size = DTrees[i]->DTree->size;
				newData = (double**)malloc(sizeof(double*)*size);
				newResult = (long*)malloc(sizeof(long)*size);
				for(j = 0; j<size; j++){
					newData[j] = (double*)malloc(sizeof(double)*(f+1));
                			for(k=0; k<f+1; k++){
                        			newData[j][k] = DTrees[i]->DTree->dataRecord[j][k];
                			}
                			newResult[j] = DTrees[i]->DTree->resultRecord[j];
        			}
				treePointer[minIndex] = true;
				activeTree++;
			}
			DTrees[minIndex]->Free();
			delete DTrees[minIndex];
			DTrees[minIndex] = new DecisionTree(height, f, sparse, forget, minF+rand()%(f+1-minF), noClasses, e, Rebuild);
			DTrees[minIndex]->fit(newData, newResult, size);
		}	
	}
}


long RandomForest::Test(double* data, long result){
	long i;
	long predict[noClasses];
	for(i=0; i<noClasses; i++){
		predict[i]=0;
	}
	for(i=0; i<maxTree; i++){
		long tmp = DTrees[i]->Test(data, DTrees[i]->DTree);
		predict[tmp]++;
		if(tmp==result)allT[i]++;
	}
	
	long ret = 0;
	for(i=1; i<noClasses; i++){
		if(predict[i]>predict[ret])ret = i;
	}

	return ret;
}

long RandomForest::Test(double* data){
	long i;
	long predict[noClasses];
	for(i=0; i<noClasses; i++)predict[i]=0;
	for(i=0; i<maxTree; i++){
		predict[DTrees[i]->Test(data, DTrees[i]->DTree)]++;
	}
	
	long ret = 0;
	for(i=1; i<noClasses; i++){
		if(predict[i]>predict[ret])ret = i;
	}

	return ret;
}
