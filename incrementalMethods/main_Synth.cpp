#include <cmath>
#include <iostream>
#include "RF.h"
#include <fstream>
#include <ctime>
#include <string>

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
        long i,j,k, kkk=0;
        long frag = 100;
        long size = 50000;
        long noClasses = 2;
        long feature = 10;
	double ir = 0.3;
        double*** data;
        long** result;
        char buf[1024] = { 0 };
	int isSparse[feature];
	for(i=0; i<feature; i++){
		isSparse[i] = 0;
	}
        long no = size/frag;
        data = (double***)malloc(no*sizeof(double**));
        result = (long**)malloc(no*sizeof(long*));
        std::ifstream infile;
	const char* name[18] = {"gauss_synthetic_100_1", "gauss_synthetic_100_3", "gauss_synthetic_100_5", "gauss_synthetic_50_1", "gauss_synthetic_50_3", "gauss_synthetic_50_5", "gauss_synthetic_20_1", "gauss_synthetic_20_3", "gauss_synthetic_20_5", "synthetic_100_1", "synthetic_100_3", "synthetic_100_5", "synthetic_50_1", "synthetic_50_3", "synthetic_50_5", "synthetic_20_1", "synthetic_20_3", "synthetic_20_5"}; 
	std::string fname = name[atoi(argv[2])];
	std::string dname = "Synthetic/";
	infile.open(dname+fname, std::ios::in);
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
	long T=0, TF=0;
	double t = 0.0;
        clock_t start,end;
	long maxSize = 0;
        if(argv[1][0]=='0'){
		RandomForest* test;
        	test = new RandomForest(atol(argv[5]), feature, isSparse, atof(argv[3]), noClasses, Evaluation::entropy, atoi(argv[4])!=0, 0.05/atoi(argv[6]));
        	for(kkk=0;kkk<no;kkk++){
				if(kkk == no-1){
					for(i=0; i<size-kkk*frag;i++){
                				if(test->Test(data[kkk][i])==result[kkk][i])T++;
						TF++;
					}
				}else{
					for(i=0; i<frag;i++){
                				if(test->Test(data[kkk][i])==result[kkk][i])T++;
						TF++;
					}
				}
			if(kkk!=no-1){
				start = clock();
				test->fit(data[kkk], result[kkk], std::min(frag, size-frag*kkk));
				t += (double)(clock()-start)/CLOCKS_PER_SEC;
			}
		}
		printf("accuracy: %f\n", (double)T/TF);
	}else if(argv[1][0]=='1'){
		DecisionTree* test;
		test= new DecisionTree(feature, isSparse, atof(argv[3]), feature, noClasses, Evaluation::entropy);
        	for(kkk=0;kkk<no;kkk++){
			if(kkk>=20){
				if(kkk==no-1){
                                	for(i=0; i<size-kkk*frag;i++){
                                        	if(test->Test(data[kkk][i], test->DTree)==result[kkk][i])T++;
                                        	TF++;
                                	}
				}else{
					for(i=0; i<frag;i++){
                                                if(test->Test(data[kkk][i], test->DTree)==result[kkk][i])T++;
                                                TF++;
                                        }
				}
                        }
			if(kkk!=no-1){
				start = clock();
                		test->fit(data[kkk], result[kkk], std::min(frag, size-frag*kkk));
				t+=(double)(clock()-start)/CLOCKS_PER_SEC;
                		if(test->DTree->size>maxSize)maxSize=test->DTree->size;
				if(argv[4][0]=='t'){
					printf("%f\n", test->increaseRate);
				}
			}
		}
		if(argv[4][0]=='f'){
			printf("accuracy: %f\n", (double)T/TF);
		}
	}
}

