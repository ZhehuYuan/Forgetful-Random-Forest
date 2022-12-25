#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include "RF.h"
#include "main.h"

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


void mainPow(bool rf, double ir, bool bagging, long nTree){
        long i,j,k, kkk=0;
        long frag = 100;
        long size = 29928;
        long no = size/frag;
        long noClasses = 24;
        long feature = 2;
        double*** data;
        long** result;
        int isSparse[feature]={1, 1};
        char buf[1024] = { 0 };
        std::ifstream infile;
        infile.open("power/powersupply.txt", std::ios::in);

        data = (double***)malloc((no+1)*sizeof(double**));
        result = (long**)malloc((no+1)*sizeof(long*));
        for(i=0;i<no;i++){
                data[i] = (double**)malloc(frag*sizeof(double*));
                result[i] = (long*)malloc(frag*sizeof(long));
        }
        data[no] = (double**)malloc((size-no*frag)*sizeof(double*));
        result[no] = (long*)malloc((size-no*frag)*sizeof(long));
	
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
        if(rf){
		RandomForest* test;
        	test = new RandomForest(nTree, feature, isSparse, ir, noClasses, Evaluation::entropy, bagging);
        	for(kkk=0;kkk<=no;kkk++){
			long localT=0;
			if(kkk!=no){
				if(kkk>=10)total += frag;
				for(i=0; i<frag; i++){
                			if(test->Test(data[kkk][i])==result[kkk][i]){
						if(kkk>=5){
							count++;
						}
						localT++;
					}
				}
				//printf("%f\n", (double)localT/frag);
				start = clock();
                		test->fit(data[kkk], result[kkk], std::min(frag, size-frag*kkk));
				time += (double)(clock()-start)/CLOCKS_PER_SEC;
			}else{
				total += size-frag*no;
				for(i=0; i<size-frag*no; i++){
                			if(test->Test(data[kkk][i])==result[kkk][i]){
						count++;
						localT++;
					}
				}
				//printf("%f\n", (double)localT/(size-frag*no));
			}
		}
		printf("time: %f second\naccuracy: %f\n", time, (double)count/total);
	}else{
		DecisionTree* test;
		test= new DecisionTree(feature, isSparse, ir, feature, noClasses, Evaluation::entropy);
        	long maxSize = 0;
        	for(kkk=0;kkk<=no;kkk++){
			long localT=0;
			if(kkk!=no){
					if(kkk>=10)total += frag;
					for(i=0; i<frag; i++){
                				if(test->Test(data[kkk][i], test->DTree)==result[kkk][i]){
							if(kkk>=5){
								count++;
							}
							localT++;
						}
					}
					//printf("%f\n", (double)localT/frag);
				start = clock();
                		test->fit(data[kkk], result[kkk], std::min(frag, size-frag*kkk));
				time += (double)(clock()-start)/CLOCKS_PER_SEC;
				if(maxSize<test->DTree->size)maxSize = test->DTree->size;
			}else{
				total += size-frag*no;
				for(i=0; i<size-frag*no; i++){
                			if(test->Test(data[kkk][i], test->DTree)==result[kkk][i]){
						count++;
						localT++;
					}
				}
				if(maxSize<test->DTree->size)maxSize = test->DTree->size;
				//printf("%f\n", (double)localT/(size-frag*no));
			}
		}
		printf("time: %f second\naccuracy: %f\n", time, (double)count/total);
	}
}

