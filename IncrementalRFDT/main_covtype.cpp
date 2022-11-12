#include <iostream>
#include "RF.h"
#include <fstream>
#include <ctime>

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
		printf("Please input parameters: [0 for random forest or 1 for decision tree] [0 to 1 for different settings or >2 for memory size]\n");
		return -1;
	}
	long rb=100000;
	if(argc==4)rb=atol(argv[3]);
        long i,j,k, kkk=0;
        long frag = 400;
        long size = 581012;
        long no = size/frag+1;
        long noClasses = 7;
        long feature = 54;
        double*** data;
	long memSize = 10000;
        long** result;
        int isSparse[54] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        char buf[1024] = { 0 };
        std::ifstream infile;
        infile.open("covtype/covtype", std::ios::in);

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
                result[i/frag][i%frag] = atoi(buf)-1;
        }
        long T=0, TF=0;
	double t = 0.0;
        clock_t start,end;
        if(argv[1][0]=='0'){
		RandomForest* test;
		if(atol(argv[2])==0){
        		test = new RandomForest(10, 11, feature, isSparse, -10.0, noClasses, Evaluation::gini);
		}
		for(kkk=0;kkk<no;kkk++){
                	if(kkk>=20){
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
			}
			if(kkk!=no-1){
				start = clock();
				test->fit(data[kkk], result[kkk], std::min(frag, size-frag*kkk));
				t += (double)(clock()-start)/CLOCKS_PER_SEC;
			}
		}
	}else if(argv[1][0]=='1'){
		DecisionTree* test;
	        if(atoi(argv[2])==0){
			test= new DecisionTree(11, feature, isSparse, -10.0, feature, noClasses, Evaluation::gini, 2147483647);
		}else{
			test= new DecisionTree(11, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini, rb);	
		}
		long maxSize = 0;
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
			}
		}
		printf("%ld\n", maxSize);
	}
	printf("%f\n%f\n", t, (double)T/TF);
}

