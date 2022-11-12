#include <iostream>
#include "RF.h"
#include <fstream>
#include <ctime>
#include <cmath>

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
	if(argc!=3){
		printf("Please input parameters: [0 for random forest or 1 for decision tree] [0 for gradual 1 for abrupto]\n");
		return -1;
	}
        long i,j,k, kkk=0;
        long frag = 100;
        long size = 40000;
        long noClasses = 2;
        long feature = 4;
        double*** data;
        long** result;
        int isSparse[4]={0, 0, 1, 1};
        char buf[1024] = { 0 };
        std::ifstream infile;
	if(atoi(argv[2])==0){
        	infile.open("mixed/mixed_0101_gradual.csv", std::ios::in);
		size += 1000;
	}else{
        	infile.open("mixed/mixed_0101_abrupto.csv", std::ios::in);
	}
        long no = size/frag;
        data = (double***)malloc(no*sizeof(double**));
        result = (long**)malloc(no*sizeof(long*));
        for(i=0;i<no;i++){
                data[i] = (double**)malloc(frag*sizeof(double*));
                result[i] = (long*)malloc(frag*sizeof(long));
        }
	
        for(i=0;i<size;i++){
                data[i/frag][i%frag] = (double*)malloc((feature+1)*sizeof(double));
                data[i/frag][i%frag][feature] = 0;
		for(j=0;j<feature;j++){
                        infile>>buf;
                        data[i/frag][i%frag][j] = atof(buf);
                }
                infile>>buf;
                result[i/frag][i%frag] = atoi(buf);
        }

        long count=0, total=0;
	double time=0.0;
        clock_t start,end;
        if(argv[1][0]=='0'){
		RandomForest* test;
        	test = new RandomForest(10, 9, feature, isSparse, -10.0, noClasses, Evaluation::gini);
        	for(kkk=0;kkk<no;kkk++){
			if(kkk!=no-1){
				if(kkk>=20){
					total += frag;
					for(i=0; i<frag; i++){
                				if(test->Test(data[kkk][i])==result[kkk][i])count++;
					}
				}
				start = clock();
                		test->fit(data[kkk], result[kkk], std::min(frag, size-frag*kkk));
				time += (double)(clock()-start)/CLOCKS_PER_SEC;
			}else{
				total += size-frag*no;
				for(i=0; i<size-frag*no; i++){
                			if(test->Test(data[kkk][i])==result[kkk][i])count++;
				}
			}
		}
		printf("%f\n%f\n", time, (double)count/total);
	}else if(argv[1][0]=='1'){
		DecisionTree* test;
		test= new DecisionTree(9, feature, isSparse, -10.0, feature, noClasses, Evaluation::gini, 2147483647);
        	long maxSize=0;
		for(kkk=0;kkk<no;kkk++){
			if(kkk!=no-1){
				if(kkk>=20){
					total += frag;
					for(i=0; i<frag; i++){
                				if(test->Test(data[kkk][i], test->DTree)==result[kkk][i])count++;
					}
				}
				start = clock();
                		test->fit(data[kkk], result[kkk], std::min(frag, size-frag*kkk));
				time += (double)(clock()-start)/CLOCKS_PER_SEC;
				if(test->DTree->size>maxSize)maxSize=test->DTree->size;
			}else{
				total += size-frag*no;
				for(i=0; i<size-frag*no; i++){
                			if(test->Test(data[kkk][i], test->DTree)==result[kkk][i])count++;
				}
				if(test->DTree->size>maxSize)maxSize=test->DTree->size;
                        }
                }
                printf("%ld\n", maxSize);
		printf("%f\n%f\n", time, (double)count/total);
	}
}

