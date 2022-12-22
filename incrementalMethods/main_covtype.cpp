#include <iostream>
#include <fstream>
#include <ctime>
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
/*int main(int argc, char* argv[]){
	bool rf=false;
	double ir = 0.3;
	bool bagging = false;
	long nTree = 0;*/
void mainCov(bool rf, double ir, bool bagging, long nTree){
	long i,j,k, kkk=0;
        long frag = 400;
        long size = 581012;
        long no = size/frag+1;
        long noClasses = 7;
        long feature = 54;
        double*** data;
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
        if(rf){
		RandomForest* test;
        	test = new RandomForest(nTree, feature, isSparse, ir, noClasses, Evaluation::entropy, bagging);
		for(kkk=0;kkk<no;kkk++){
				long localT=0;
				long localTF=0;
				if(kkk == no-1){
					for(i=0; i<size-kkk*frag;i++){
                				if(test->Test(data[kkk][i])==result[kkk][i]){
							T++;
							localT++;
						}
						TF++;
						localTF++;
					}
				}else if(kkk!=0){
					for(i=0; i<frag;i++){
                				if(test->Test(data[kkk][i])==result[kkk][i]){
							if(kkk>=60)T++;
							localT++;
						}
						if(kkk>=60)TF++;
						localTF++;
					}
				}
			if(kkk==no-1)continue;
			start = clock();
			test->fit(data[kkk], result[kkk], std::min(frag, size-frag*kkk));
			t += (double)(clock()-start)/CLOCKS_PER_SEC;
		}
	}else{
		DecisionTree* test;
		test= new DecisionTree(feature, isSparse, ir, feature, noClasses, Evaluation::entropy);
		long maxSize = 0;
        	for(kkk=0;kkk<no;kkk++){
				long localT = 0;
				long localTF = 0;
				if(kkk==no-1){
                                	for(i=0; i<size-kkk*frag;i++){
                                        	if(test->Test(data[kkk][i], test->DTree)==result[kkk][i]){
							T++;
							localT++;
						}
                                        	TF++;
						localTF++;
                                	}
				}else if(kkk!=0){
					for(i=0; i<frag;i++){
                                                if(test->Test(data[kkk][i], test->DTree)==result[kkk][i]){
							if(kkk>=60)T++;
							localT++;
						}
                                                if(kkk>=60)TF++;
						localTF++;
                                        }
				}
				//printf("%f\n", (double)localT/localTF);
				//test->print(test->DTree);
				//printf("\n  ");
			if(kkk==no-1)continue;
			start = clock();
                	test->fit(data[kkk], result[kkk], std::min(frag, size-frag*kkk));
			t+=(double)(clock()-start)/CLOCKS_PER_SEC;
                	if(test->DTree->size>maxSize)maxSize=test->DTree->size;
		}
		/*printf("%ld\n", maxSize);*/
	}
	printf("time: %f second\naccuracy: %f\n", t, (double)T/TF);
}

