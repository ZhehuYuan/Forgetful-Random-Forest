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
	if(argc!=3){
		printf("Please input parameters: [0 for random forest or 1 for decision tree] [0 to 2 for different settings]\n");
		return -1;
	}
        long i,j,k, kkk=0;
        long frag = 400;
        long size = 125973/5;
        long no = size/frag+1;
        long noClasses = 2;
        long feature = 122;
        double*** data;
        long** result;
        int isSparse[122] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1};
        char buf[1024] = { 0 };
        std::ifstream infile;
        infile.open("KDD/KDDTrain+.txt", std::ios::in);

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
                result[i/frag][i%frag] = atoi(buf);
        }
        double** testData = (double**)malloc(10000*sizeof(double*));
        long* testResult = (long*)malloc(10000*sizeof(long));
        for(i=0;i<10000;i++){
                testData[i] = (double*)malloc(feature*sizeof(double));
                for(j=0;j<feature;j++){
                        infile>>buf;
                        testData[i][j] = atof(buf);
                }
                infile>>buf;
                testResult[i] = atoi(buf);
        }

        long count=0;
        clock_t start,end;
        if(argv[1][0]=='0'){
		RandomForest* test;
		if(argv[2][0]=='0'){
        		test = new RandomForest(50, 20, 5, 8, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini);
		}else{
        		test = new RandomForest(20, 20, 5, 8, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini);
		}
		start = clock();
        	for(kkk=0;kkk<no;kkk++){
                	test->fit(data[kkk], result[kkk], std::min(frag, size-frag*kkk));
		}
        	std::cout<<(double)(clock()-start)/CLOCKS_PER_SEC<<std::endl;
        	count = 0;
        	for(i=0; i<10000; i++){
                	if(test->Test(testData[i])==testResult[i])count++;
		}
	}else if(argv[1][0]=='1'){
		DecisionTree* test;
	        if(argv[2][0]=='0'){
			test= new DecisionTree(8, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini);
		}else if(argv[2][0]=='1'){
			test= new DecisionTree(8, feature, isSparse, 0, feature, noClasses, Evaluation::gini);
		}else if(argv[2][0]=='2'){
			test= new DecisionTree(8, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini);
			test->Rebuild = true;
		}else if(argv[2][0]=='3'){
			test= new DecisionTree(8, feature, isSparse, 0.05, feature, noClasses, Evaluation::gini);
		}else{
			test= new DecisionTree(8, feature, isSparse, 0.2, feature, noClasses, Evaluation::gini);	
		}
		start = clock();
		long maxSize = 0;
        	for(kkk=0;kkk<no;kkk++){
                	test->fit(data[kkk], result[kkk], std::min(frag, size-frag*kkk));
                	if(test->DTree->size>maxSize)maxSize=test->DTree->size;
			//std::cout<<(double)(clock()-start)/CLOCKS_PER_SEC<<std::endl;
                	//start=clock();
		}
        	std::cout<<(double)(clock()-start)/CLOCKS_PER_SEC<< "   " << maxSize <<std::endl;
        	count = 0;
        	for(i=0; i<10000; i++){
			if(test->Test(testData[i], test->DTree)==testResult[i])count++;
		}
	
	}
        printf("accuracy: %f\n", (double)count/(10000));
}

