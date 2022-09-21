#include <iostream>
#include "RF.h"
#include <fstream>
#include <ctime>

int main(){
        long i,j,k, kkk=0;
        long frag = 400;
        long size = 15120*2;
        long no = size/frag+1;
        long noClasses = 7;
        long feature = 54;
        double*** data;
        long** result;
        bool isSparse[54] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        char buf[1024] = { 0 };
        std::ifstream infile;
        infile.open("covtype/covtype.txt", std::ios::in);

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
        double** testData = (double**)malloc(1000*sizeof(double*));
        long* testResult = (long*)malloc(1000*sizeof(long));
        for(i=0;i<1000;i++){
                testData[i] = (double*)malloc(feature*sizeof(double));
                for(j=0;j<feature;j++){
                        infile>>buf;
                        testData[i][j] = atof(buf);
                }
                infile>>buf;
                testResult[i] = atoi(buf)-1;
        }

        long count;
        clock_t start,end;
        RandomForest* test;
	test = new RandomForest(50, 20, 10, 8, feature, isSparse, 0.1, 12, noClasses, Evaluation::gini);
        //DecisionTree* test;
	//test = new DecisionTree(8, feature, isSparse, 0.1, feature, noClasses, Evaluation::gini);
	//test->Rebuild = true;
	start = clock();
        for(kkk=0;kkk<no;kkk++){
        	test->fit(data[kkk], result[kkk], std::min(frag, size-frag*kkk));
                //std::cout<<(double)(clock()-start)/CLOCKS_PER_SEC<<std::endl;
                //start=clock();
		//test->print(test->DTree);printf("\n");
	}
        //std::cout<<(double)(clock()-start)/CLOCKS_PER_SEC<<std::endl;
        
	count = 0;
        for(i=0; i<1000; i++){
                if(test->Test(testData[i])==testResult[i]){
			count++;
			printf("1\n");
		}else{
			printf("0\n");
		}
                //if(test->Test(testData[i], test->DTree)==testResult[i])count++;
	}
        printf("accuracy: %f\n", (double)count/(1000));
}

