#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "CART.h"
#include <fstream>
#include <ctime>


struct minGini{
	double value;
	double gini;
	long left;
};

struct DR{
	double value;
	bool result;
};

struct DT{
	long feature;
	double dpoint;
	int height;
	bool terminate;
	bool result;
	DT* left = nullptr;
	DT* right = nullptr;
};

DecisionTree::DecisionTree(int height, long f){
	maxHeight = height;
	feature = f;
}


//Assuming data is sorted
minGini DecisionTree::getMinGini(DR* data, long l){
	minGini ret;
	ret.gini = 2.0;
	long i = 0.0;
	double i2, gini;
	long tCount=0;
	long counts[l-1];

	for(;i<l-1;i++){
		if(data[i].result){
			tCount ++;
		}
		counts[i] = tCount;
	}
	if(data[l-1].result)tCount++;

	for(i=0;i<l-1;i++){
		i2 = i+1;
		if(data[i].value == data[i+1].value)continue;
		gini = (1 - pow(counts[i]/i2, 2) - pow((i2-counts[i])/i2, 2))*(i2/l) + (1 - pow((tCount-counts[i])/(l-i2), 2) - pow((l-i2-tCount+counts[i])/(l-i2), 2))*((l-i2)/l);
		if(gini<ret.gini){
			ret.gini = gini;
			ret.value = (data[i].value+data[i+1].value)/2;
			ret.left = i+1;
		}
	}
	return ret;
}

DR* DecisionTree::mySort(double* data, bool* result, long low, long size){
	bool* result2 = (bool*)malloc(size*sizeof(bool));
	double* data2 = (double*)malloc(size*sizeof(double));
	DR* ret = (DR*)malloc(size*sizeof(DR));
	long i = 0;
	for(;i<size; i++){
		result2[i] = result[i+low];
		data2[i] = data[i+low];
	}
	QSort(data2, result2, 0, size-1);
	for(i=0; i<size; i++){
		ret[i].value = data2[i];
		ret[i].result = result2[i];
	}
	free(result2);
	free(data2);
	return ret;	
}

void DecisionTree::QSort(double* data, bool* result, long low, long high){
	if(low<high){
		long i = low, j = high;
		double x = data[low];
		bool y = result[low];
		while(i<j)  {
			while(i<j && data[j] >= x) j--;
		  	if(i<j){ 
		  		data[i]=data[j];
				result[i]=result[j];
				i++;
			  }
			while(i<j && data[i] <= x) i++;
			if(i<j){
				data[j] = data[i];
				result[j] = result[i];
				j--;
		 	}
		} 
	        data[i] = x;
		result[i] = y;
		QSort(data, result, low ,i-1);
		QSort(data, result, i+1 ,high);
	}
}

void DecisionTree::QSort2(double** data, bool* result, long low, long high, long key){
        long k;
	if(low<high){
                long i = low, j = high;
                double* x = (double*)malloc(feature*sizeof(double));
		for(k=0; k<feature; k++){
			x[k]=data[k][i];
		}
                bool y = result[low];
                while(i<j)  {
                        while(i<j && data[key][j] >= x[key]) j--;
                        if(i<j){
				for(k=0; k<feature; k++){
                        		data[k][i]=data[k][j];
                		}
                                result[i]=result[j];
                                i++;
                          }
                        while(i<j && data[key][i] <= x[key]) i++;
                        if(i<j){
                                for(k=0; k<feature; k++){
                                        data[k][j]=data[k][i];
                                }
				result[j] = result[i];
                                j--;
                        }
                }
                for(k=0; k<feature; k++){
                        data[k][i] = x[k];
                }
                result[i] = y;
                QSort2(data, result, low ,i-1, key);
                QSort2(data, result, i+1 ,high, key);
		free(x);
	}
}


void DecisionTree::DataIn(double** data, bool* result, long size){
	DTree = (DT*)malloc(sizeof(DT));
	DTree->height=0;
	Update(data, result, size, DTree, 0);
}

void DecisionTree::Update(double** data, bool* result, long size, DT* current, long low){
	long i = low;
	int aaa;
	// end condition
	if(current->height == maxHeight){
		current->terminate = true;
		long t = 0;
		for(;i<low+size;i++){
			t+=result[i];
		}
		current->result = ((double)t/size)>=0.5;
		return;
	}
	long n=0;
	for(;i<low+size;i++)n+=result[i];
	if(n==0 or n==size){
		current->terminate = true;
		current->result = (n>0);
		return;
	}
	// find min entropy
	DR* tmp;
	minGini c, cMin;
	long cFeature;
	cMin.gini = 2.0;
	for(i=0;i<feature; i++){
		tmp = mySort(data[i], result, low, size);
		if(tmp[0].value==tmp[size-1].value)continue;
		c = getMinGini(tmp, size);
		if(c.gini<cMin.gini){
			cMin.gini = c.gini;
			cMin.value = c.value;
			cMin.left = c.left;
			cFeature = i;
		}
		free(tmp);
	}
	if(cMin.gini>1.0){
		current->terminate = true;
                long t = 0;
                for(i=low;i<low+size;i++){
                        t+=result[i];
                }
                current->result = ((double)t/size)>0.5;
		return;
	}
	current->terminate = false;
	current->feature = cFeature;
	current->dpoint = cMin.value;
	QSort2(data, result, low, low+size-1, cFeature);
	current->left = (DT*)malloc(sizeof(DT));
        current->left->height = current->height+1;
	Update(data, result, cMin.left, current->left, low);
	current->right = (DT*)malloc(sizeof(DT));
	current->right->height = current->height+1;
	Update(data, result, size-cMin.left, current->right, low+cMin.left);
}

void DecisionTree::print(DT* root){
	int x;
	//std::cin>>x;
	if(root->terminate){
		printf("%d", root->result);
		return;
	}
	printf("([%ld, %f]:", root->feature, root->dpoint);
	print(root->left);
	printf(", ");
	print(root->right);
	printf(")");
}

int main(){
	long frag = 1000;
        long feature = 10;
        long size = 10;
	double** data;
        double* tmp;
        bool* result;
	
	DecisionTree* test = new DecisionTree(2, feature);
	long i,j,k;
	
	char buf[1024] = { 0 };
	std::ifstream infile;
	infile.open("../data2.csv", std::ios::in);

	data = (double**)malloc(feature*sizeof(double*));
       	result = (bool*)malloc(frag*size*sizeof(bool));
	for(j=0;j<feature;j++){
		tmp = (double*)malloc(frag*size*sizeof(double));
		data[j] = tmp;
	}
	for(i=0;i<size*frag;i++){
		for(j=0;j<feature;j++){
			infile>>buf;
			data[j][i] = atof(buf); 
		}
		infile>>buf;
		result[i] = atoi(buf);
	}
	clock_t start,end;
	start = clock();
	for(k=0;k<1000;k++){
		test = new DecisionTree(2, feature);
		test->DataIn(data, result, (100)*size);
		//test->print(test->DTree);
		//printf("\n\n");
	}
	//test->print(test->DTree);
	end = clock();
	std::cout<<(double)(end-start)/CLOCKS_PER_SEC<<std::endl;
}
