#include <exception>
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
	int height;
	long feature;
	double dpoint;
	bool terminate;
	bool result;

	long low;
	long dataNo;
	double** rawData;
	bool* rawResult;
	DR** DRs;
	
	DT* left = nullptr;
	DT* right = nullptr;
};

// Improvement: remove useless variables

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
		if(data[i].value == data[i+1].value)continue;
		i2 = i+1;
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
	//void* x = (void*)data2;
	//void* y = (void*)result2;
	DR* ret = (DR*)malloc(size*sizeof(DR));
	long i;
	for(i=0;i<size; i++){
		result2[i] = result[i+low];
		data2[i] = data[i+low];
	}
	QSort(data2, result2, 0, size-1);
	for(i=0; i<size; i++){
		ret[i].value = data2[i];
		ret[i].result = result2[i];
	}
	free(data2);
	free(result2);
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

// Sort the whole data
void DecisionTree::QSort2(double** data, bool* result, long low, long high, long key){
	if(low<high){
                long k, i = low, j = high;
                double* x = (double*)malloc(feature*sizeof(double));
		k=0;
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
	low=0;
}


void DecisionTree::DataIn(double** data, bool* result, long size){
	long i;
	if(DTree == nullptr){
		// first tree
		DTree = (DT*)malloc(sizeof(DT));
		DTree->height=0;
		Update(data, result, size, DTree, 0);
	}else if(DTree->terminate){
		// root only
		DTree->dataNo+=size;
		double** newdata = (double**)malloc(DTree->dataNo*sizeof(double*));
                bool* newresult = (bool*)malloc(DTree->dataNo*sizeof(bool));
                for(i=0; i<DTree->dataNo-size; i++){
                        newresult[i] = DTree->rawResult[i];
                }
                for(;i<DTree->dataNo;i++){
                        newresult[i] = result[i-DTree->dataNo+size];
                }
		newdata = DataCombine(DTree->rawData, data, DTree->dataNo, size, 0, 0);
		Update(newdata, newresult, DTree->dataNo, DTree, 0);
		
	}else{
		IncrementalUpdate(data, result, size, DTree, 0);
	}
}

double** DecisionTree::DataCombine(double** data1, double** data2, long size1, long size2, long low1, long low2){
	double** ret = (double**) malloc(feature*sizeof(double*));
	double* tmp;
	long i, j;
	for(i=0; i<feature; i++){
		tmp = (double*) malloc((size1+size2)*sizeof(double));
		for(j=0; j<size1; j++){
			tmp[j]=data1[i][low1+j];
		}
		for(j=0; j<size2; j++){
			tmp[size1+j]=data2[i][low2+j];
		}
		ret[i] = tmp;
	}
	return ret;
}

bool* DecisionTree::ResultCombine(bool* result1, bool* result2, long size1, long size2, long low1, long low2){
	bool* ret = (bool*) malloc((size1+size2)*sizeof(bool));
	long j;
	for(j=0; j<size1; j++){
		ret[j]=result1[low1+j];
	}
	for(j=0; j<size2; j++){
		ret[size1+j]=result2[low2+j];
	}
	return ret;
}

//Incremental Version of Update
void DecisionTree::IncrementalUpdate(double** data, bool* result, long size, DT* current, long low){
	long i = 0;
	int aaa;
	// reach height limit
	if(current->height == maxHeight){
                current->terminate = true;
                long t = 0;
                for(;i<size;i++){
                        t+=result[low+i];
                }
		current->dataNo += size;
		//Use feature to store count at height limit leaves
		current->feature += t;
                current->result = ((double)current->feature/current->dataNo)>=0.5;
		return;
        }
	// all same results
	// first assert previous results are all same result
	if(current->terminate and current->DRs==nullptr){
		long n=current->result;
		for(i=low;i<low+size;i++)n+=result[i];
		if(n==0 or n==size+1){
			current->terminate = true;
			current->result = n>0;
			current->rawData = DataCombine(current->rawData, data, current->dataNo, size, current->low, low);
			current->rawResult = ResultCombine(current->rawResult, result, current->dataNo, size, current->low, low);
			current->low = 0;
			current->dataNo += size;
			current->DRs = nullptr;
			return;
		}
	}
	if(current->DRs==nullptr){
		DR** tmpDRs = (DR**)malloc(feature*sizeof(DR*));
		for(i=0;i<feature;i++){
			tmpDRs[i] = mySort(current->rawData[i], current->rawResult, current->low, current->dataNo);
		}
		current->DRs=tmpDRs;
	}
	// find min entropy
	DR* tmp;
	minGini c, cMin;
	long cFeature;
	cMin.gini = 2.0;
	DR** sortedDRs = (DR**)malloc(feature*sizeof(DR*));
	for(i=0;i<feature;i++){
		tmp = IncrementalSort(current->DRs[i], data[i], result, current->dataNo, size, low);
		free(current->DRs[i]);
		if(tmp[0].value==tmp[current->dataNo+size-1].value){sortedDRs[i]=tmp;continue;}
		c = getMinGini(tmp, current->dataNo+size);
                if(c.gini<cMin.gini){
                        cMin.gini = c.gini;
                        cMin.value = c.value;
                        cMin.left = c.left;
                        cFeature = i;
                }
                sortedDRs[i] = tmp;
	}
	free(current->DRs);
	// In case all data are same
	// It's garentee that all old data are same
	if(cMin.gini>1.0){
		current->terminate = true;
                long t = 0;
                for(i=low;i<low+size;i++){
                        t+=result[i];
                }
		current->rawData = DataCombine(current->rawData, data, current->dataNo, size, current->low, low);
		current->rawResult = ResultCombine(current->rawResult, result, current->dataNo, size, current->low, low);
                current->result = ((double)t/size)>=0.5;
		current->low = 0;
		current->dataNo += size;
		current->DRs = sortedDRs;
		return;
	}
	// update new data
	current->rawData = DataCombine(current->rawData, data, current->dataNo, size, current->low, low);
	current->rawResult = ResultCombine(current->rawResult, result, current->dataNo, size, current->low, low);
	current->low = 0;
	current->dataNo += size;
	current->DRs = sortedDRs;
	current->terminate = false;
	
	// If diverse point keeps the same, do incremental at next level
	if(current->dpoint == cMin.value and cFeature == current->feature){
		QSort2(data, result, low, size-1, cFeature);
		long count = 0;
		while(data[cFeature][low+count]<cMin.value){
			if(count==size)break;
			count++;
		}
		IncrementalUpdate(data, result, count, current->left, low);
		IncrementalUpdate(data, result, size-count, current->right, low+count);
	}
	// Otherwise, do normal at next level
	else{
		current->dpoint = cMin.value;
		current->feature = cFeature;
		double** newData = current->rawData;
		bool* newResult = current->rawResult;
		QSort2(newData, newResult, 0, current->dataNo-1, cFeature);
		current->left = (DT*)malloc(sizeof(DT));
        	current->left->height = current->height+1;
		Update(newData, newResult, cMin.left, current->left, 0);
		current->right = (DT*)malloc(sizeof(DT));
        	current->right->height = current->height+1;
		Update(newData, newResult, current->dataNo-cMin.left, current->right, cMin.left);
	}
}

DR* DecisionTree::IncrementalSort(DR* sortedOld, double* data, bool* result, long size, long newSize, long low){
	double* newData = (double*) malloc(newSize*sizeof(double));
	bool* newResult = (bool*) malloc(newSize*sizeof(bool));
	long i;
	for(i=0; i<newSize; i++){
		newData[i]=data[low+i];
		newResult[i]=1+result[low+i];
	}
	QSort(newData, newResult, 0, newSize-1);
	long j=0;
	i=0;
	DR* ret = (DR*)malloc((size+newSize)*sizeof(DR));
	while(i<size or j<newSize){
		if(i>=size){
                        ret[size+j].value = newData[j];
                        ret[size+j].result = newResult[j];
                        j++;
			continue;	
		}else if(j>=newSize){
			ret[i+newSize] = sortedOld[i];
			i++;
			continue;
		}
		if(sortedOld[i].value>newData[j]){
			ret[i+j].value = newData[j];
			ret[i+j].result = newResult[j];
			j++;
		}else{
			ret[i+j] = sortedOld[i];
                        i++;
		}
	}
	free(newData);
	free(newResult);
	return ret;
}

void DecisionTree::Update(double** data, bool* result, long size, DT* current, long low){
	long j, i = low;
	int aaa;
	// end condition
	// reach height limit
	if(current->height >= maxHeight){
		current->terminate = true;
		long t = 0;
		for(;i<low+size;i++){
			t+=result[i];
		}
		current->dataNo = size;
		// use feature to save count of height limit leaves
		// rawData and rawResult don't need to be stored
		current->feature = t;
		current->result = ((double)t/size)>=0.5;
		current->low = low;
		return;
	}
	// all same results
	long n=0;
	for(;i<low+size;i++)n+=result[i];
	if(n==0 or n==size){
		current->terminate = true;
		current->result = n>0;
		current->low = low;
		current->rawData = data;
		current->rawResult = result;
		current->dataNo = size;
		current->DRs = nullptr;
		return;
	}
	// find min entropy
	DR* tmp;
	minGini c, cMin;
	long cFeature;
	cMin.gini = 2.0;
	DR** sortedDRs = (DR**)malloc(feature*sizeof(DR*));
	for(i=0;i<feature; i++){
		tmp = mySort(data[i], result, low, size);
		if(tmp[0].value==tmp[size-1].value){sortedDRs[i]=tmp;continue;}
		c = getMinGini(tmp, size);
		if(c.gini<cMin.gini){
			cMin.gini = c.gini;
			cMin.value = c.value;
			cMin.left = c.left;
			cFeature = i;
		}
		sortedDRs[i] = tmp;
	}
	// In case all features of all data are same
	if(cMin.gini>1.0){
		current->terminate = true;
                long t = 0;
                for(i=low;i<low+size;i++){
                        t+=result[i];
                }
                current->result = ((double)t/size)>0.5;
		current->rawData = data;
		current->rawResult = result;
		current->low = low;
		current->dataNo = size;
		current->DRs = sortedDRs;
		return;
	}
	current->terminate = false;
	current->feature = cFeature;
	current->dpoint = cMin.value;
	current->DRs = sortedDRs;
	current->dataNo = size;
	current->low = low;
	current->rawData = data;
        current->rawResult = result;
	
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
	long frag = 10;
        long feature = 10;
        long size = 300;
	double*** dataSet = (double***)malloc(frag*sizeof(double**));
	double** data;
        double* tmp;
	bool** resultSet = (bool**)malloc(frag*sizeof(bool*));
        bool* result;
	
	DecisionTree* test = new DecisionTree(2, feature);
	long i,j,k;
	
	char buf[1024] = { 0 };
	std::ifstream infile;
	infile.open("../data2.csv", std::ios::in);

	for(k=0;k<frag;k++){
		data = (double**)malloc(feature*sizeof(double*));
        	result = (bool*)malloc(size*sizeof(bool));
		for(j=0;j<feature;j++){
			tmp = (double*)malloc(size*sizeof(double));
			data[j] = tmp;
		}
		for(i=0;i<size;i++){
			for(j=0;j<feature;j++){
				infile>>buf;
				data[j][i] = atof(buf); 
			}
			infile>>buf;
			result[i] = atoi(buf);
		}
		dataSet[k] = data;
		resultSet[k] = result;
	}
	clock_t start,end;
	start = clock();
	/*for(k=0;k<frag;k++){
		test->DataIn(dataSet[k], resultSet[k], size);
		if(k>2) {
			for(i=0;i<feature;i++){
				free(dataSet[k-2][i]);
			}
			free(dataSet[k-2]);
			free(resultSet[k-2]);
		}
	}*/
	for(k=0;k<1000;k++){
		test = new DecisionTree(2, feature);
		test->DataIn(dataSet[0], resultSet[0], size);
		end = clock();
	}
	std::cout<<(double)(end-start)/CLOCKS_PER_SEC<<std::endl;
}
