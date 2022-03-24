#ifndef CART_H
#define CART_H

struct minGini;

struct DR;

struct DT;

class DecisionTree{
public:

DT* DTree = nullptr;
int maxHeight;
long feature;

DecisionTree(int hight, long f);

minGini getMinGini(DR* data, long l);

DR* mySort(double* data, bool* result, long low, long size);

void DataIn(double** data, bool* result, long size);

void QSort(double* data, bool* result, long low, long high);

void QSort2(double** data, bool* result, long low, long high, long key);

void Update(double** data, bool* result, long size, DT* current, long low);

void IncrementalUpdate(double** data, bool* result, long size, DT* current, long low);

double** DataCombine(double** data1, double** data2, long size1, long size2, long low1, long low2);

bool* ResultCombine(bool* data1, bool* data2, long size1, long size2, long low1, long low2);

DR* IncrementalSort(DR* sortedOld, double* newData, bool* newResult, long size, long newSize, long low);

void print(DT* root);
};
#endif
