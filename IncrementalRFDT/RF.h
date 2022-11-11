#ifndef RF_H
#define RF_H

#include "DecisionTree.h"

struct minEval;

struct DR;

struct DT;

//enum Evaluation {gini, entropy, logLoss};

class RandomForest{
public:

long maxTree;
long activeTree;
bool* treePointer;
long* allT;
double threshold;
DecisionTree** DTrees = nullptr;

long height;
long Rebuild;
long f;
int* sparse;
double forget;
long noClasses;
Evaluation e;
double lastAcc;
int minF;

RandomForest(long maxTree, int height, long f, int* sparse, double forget, long noClasses=2, Evaluation e=Evaluation::gini, long rb=2147483647);

void fit(double** data, long* result, long size);

long* fitThenPredict(double** trainData, long* trainResult, long trainSize, double** testData, long testSize);

void Rotate(long stale);

long Test(double* data);

long Test(double* data, long result);
};
#endif
