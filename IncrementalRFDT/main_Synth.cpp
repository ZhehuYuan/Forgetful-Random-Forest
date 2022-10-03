#include <iostream>
#include "RF.h"
#include <fstream>
#include <ctime>

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
	if(argc!=4){
		printf("Please input parameters: [0 for random forest or 1 for decision tree] [0 to 2 for different settings] [1 for abrupto 2 for gradual]\n");
		return -1;
	}
        long i,j,k, kkk=0;
        long frag = 100;
        long size = 40000;
        long no = size/frag+1;
        long noClasses = 7;
        long feature = 4;
        double*** data;
        long** result;
        int isSparse[feature] = {0, 0, 1, 1};
        char buf[1024] = { 0 };
        std::ifstream infile;
        if(atoi(argv[3])==1){
		infile.open("Synthetic/mixed_0101_abrupto", std::ios::in);
	}else{
		infile.open("Synthetic/mixed_0101_gradual", std::ios::in);
		size+=1000;
	}
        data = (double***)malloc(no*sizeof(double**));
        result = (long**)malloc(no*sizeof(long*));
        for(i=0;i<no;i++){
                data[i] = (double**)malloc(frag*sizeof(double*));
                result[i] = (long*)malloc(frag*sizeof(long));
        }
        for(i=0;i<size;i++){
                data[i/frag][i%frag] = (double*)malloc((feature)*sizeof(double));
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
		if(argv[2][0]=='0'){
        		test = new RandomForest(50, 20, 5, 8, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini);
		}else{
        		test = new RandomForest(20, 20, 5, 8, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini);
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
	        if(atoi(argv[2])==1){
			test= new DecisionTree(8, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini, -1);
		}else if(atoi(argv[2])==4){
			test= new DecisionTree(8, feature, isSparse, 0, feature, noClasses, Evaluation::gini, -1);
		}else if(atoi(argv[2])==3){
			test= new DecisionTree(8, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini, -1);
			test->Rebuild = true;
		}else if(atoi(argv[2])==0){
			test= new DecisionTree(8, feature, isSparse, 0.05, feature, noClasses, Evaluation::gini, -1);
		}else if(atoi(argv[2])==2){
			test= new DecisionTree(8, feature, isSparse, 0.2, feature, noClasses, Evaluation::gini, -1);	
		}else{
			test= new DecisionTree(8, feature, isSparse, 0.2, feature, noClasses, Evaluation::gini, atol(argv[2]));	
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

