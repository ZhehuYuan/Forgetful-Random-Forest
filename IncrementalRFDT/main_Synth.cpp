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
	if(argc!=4 and argc!=5){
		printf("Please input parameters: [0 for random forest or 1 for decision tree] [0 to 2 for different settings] [1 for abrupto 2 for gradual]\n");
		return -1;
	}
	long rb=2147483647;
        long i,j,k, kkk=0;
        long frag = 100;
        long size = 100000;
        long noClasses = 2;
        long feature = 4;
	long maxH = 4;
	long memSize = 400;//=2*feature*noClasses*sqrt(size/4);
        double*** data;
        long** result;
        char buf[1024] = { 0 };
	int isSparse[20] = {1, 1, 1, 1};
	if(atoi(argv[3])==1){
		size=200000;
		memSize = 800;
	}
	else if(atoi(argv[3])==2){
		noClasses=10;
		memSize = 400;
	}
	else if(atoi(argv[3])==3){
		feature=20;
		memSize = 800;
		int isSparse1[feature] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
		for(i=0; i<feature; i++){
			isSparse[i] = isSparse1[i];
		}
	}
	else if(atoi(argv[3])==4){
        	memSize = 100;
	}
        long no = size/frag;
	//maxH = sqrt(sqrt(memSize));
        data = (double***)malloc(no*sizeof(double**));
        result = (long**)malloc(no*sizeof(long*));
        std::ifstream infile;
	const char* name[5] = {"benchmark", "200000Data", "5classes" , "20features", "32concept"}; 
	std::string fname = name[atoi(argv[3])];
	std::string dname = "Synthetic/";
	infile.open(dname+fname, std::ios::in);
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
                result[i/frag][i%frag] = atoi(buf);
        }
	long T=0, TF=0;
	double t = 0.0;
        clock_t start,end;
        if(argv[1][0]=='0'){
               	long maxF =(int)sqrt(feature);
		RandomForest* test;
		if(atol(argv[2])==0){
        		test = new RandomForest(12, 12, 5, 8, feature, isSparse, 0.1, maxF, noClasses, Evaluation::gini, 400);
		}else if(atol(argv[2])==1){
                        if (argc==5)maxF = atol(argv[4]);
			if (maxF>feature) return 0;
        		test = new RandomForest(10, 10, 5, 8, feature, isSparse, 0.1, maxF, noClasses, Evaluation::gini, 400);
		}else{
                        long totalQueue = atol(argv[2]);
                        test = new RandomForest(totalQueue, totalQueue, 5, maxH, feature, (int*)isSparse, 0, maxF, noClasses, Evaluation::gini, memSize);
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
			test= new DecisionTree(maxH, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini, memSize, 1);
		}else if(atoi(argv[2])==1){
			int tmp = 1;
			if(argc==5)tmp = atoi(argv[4]);
			test= new DecisionTree(tmp, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini, 400, 2147483647);
		}else{
			test= new DecisionTree(10, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini, atol(argv[2]), rb);	
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
	}
	printf("%f\n", (double)T/TF);
}

