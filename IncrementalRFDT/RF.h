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
long* allT;
double threshold;
DecisionTree** DTrees;
DecisionTree** backupTrees;

long height;
bool bagging;
long f;
int* sparse;
double forget;
long noClasses;
Evaluation e;
long lastT;
long lastAll;
int minF;

RandomForest(long maxTree, int height, long f, int* sparse, double forget, long noClasses=2, Evaluation e=Evaluation::entropy, bool b=false);

void fit(double** data, long* result, long size);

long* fitThenPredict(double** trainData, long* trainResult, long trainSize, double** testData, long testSize);

void Rotate(long stale);

long Test(double* data);

long Test(double* data, long result);
};
#endif
