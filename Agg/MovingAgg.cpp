#include <cstdint>
#include <stdio.h>
#include <deque>
#include <time.h>
#include <algorithm>

#define BSIZE 1000
#define BNO 1000
#define WINDOW 1000

std::deque<long> dataStore;

std::deque<long> sums;
std::deque<long> count;
std::deque<double> avg;
std::deque<long> min;
std::deque<long> max;

std::deque<long> sums2;
std::deque<long> count2;
std::deque<double> avg2;
std::deque<long> min2;
std::deque<long> max2;

long lastSum;
long lastCount;
long lastMax;
long lastMin;

void movingSumWindow(long dataIn[], long length){
	long tmp, i;
	for(i=0;i<length;i++){
                tmp=dataIn[i];
		lastSum += tmp-dataStore.back();
		dataStore.push_front(tmp);
		dataStore.pop_back();
        	sums.push_front(lastSum);
	}
}

void movingCountWindow(long dataIn[], long length){
	long i;
        for(i=0;i<length;i++){
                dataStore.push_front(dataIn[i]);
		if(dataStore.size()>WINDOW){
			dataStore.pop_back();
		}else{
			lastCount++;
		}
		count.push_front(lastCount);
        }
}

void movingAverageWindow(long dataIn[], long length){
        long i, tmp;
        for(i=0;i<length;i++){
                tmp=dataIn[i];
		lastSum+=tmp;
		dataStore.push_front(tmp);
                if(dataStore.size()>WINDOW){
			dataStore.pop_back();
			lastSum-=dataStore.back();
		}else{
			lastCount++;
		}
                avg.push_front((double)lastSum/lastCount);
        }
}


void movingSum(long dataIn[], long length){
	long tmp, i;
        for(i=0;i<length;i++){
                tmp=dataIn[i];
                lastSum += tmp;
                dataStore.push_front(tmp);
                sums2.push_front(lastSum);
        }
}

void movingCount(long dataIn[], long length){
        long i;
        for(i=0;i<length;i++){
                dataStore.push_front(dataIn[i]);
                lastCount++;
		count2.push_front(lastCount);
        }
}

void movingAverage(long dataIn[], long length){
        long i, tmp;
        for(i=0;i<length;i++){
                tmp=dataIn[i];
                lastSum+=tmp;
		lastCount++;
                dataStore.push_front(tmp);
                avg2.push_front((double)lastSum/lastCount);
        }
}

void movingMin(long dataIn[], long length){
	long i,tmp;
	for(i=0;i<length;i++){
                tmp=dataIn[i];
                lastMin=std::min(lastMin,tmp);
                dataStore.push_front(tmp);
                min2.push_front(lastMin);
        }
}

void movingMax(long dataIn[], long length){
        long i,tmp;
        for(i=0;i<length;i++){
                tmp=dataIn[i];
                lastMax=std::max(lastMax,tmp);
                dataStore.push_front(tmp);
                max2.push_front(lastMax);
        }
}

void init(){
	dataStore.resize(WINDOW,0);
	lastSum=0;
}

int main(){
	long dataIn[BSIZE];
	double start, end, end2;
	int i;
//Initialize
	for(i=0; i<BSIZE; i++){
		dataIn[i]=i;
	}
//Windowed moving sum
	init();
	start = clock();
        for(i=0;i<BNO;i++){
        	movingSumWindow(dataIn, BSIZE);
	}
        end = clock();
        printf("windowed moving sum: %f\n", (end-start)/ CLOCKS_PER_SEC);
//Windowed moving count
	dataStore.resize(0);
	lastCount=0;
	start = clock();
        for(i=0;i<BNO;i++){
                movingCountWindow(dataIn, BSIZE);
        }
        end = clock();
        printf("windowed moving count: %f\n", (end-start)/ CLOCKS_PER_SEC);
//Windowed moving average
	dataStore.resize(0);
	lastSum=0;
	lastCount=0;
        start = clock();
        for(i=0;i<BNO;i++){
                movingAverageWindow(dataIn, BSIZE);
        }
        end = clock();
        printf("windowed moving average: %f\n", (end-start)/ CLOCKS_PER_SEC);
//Moving sum
	dataStore.resize(0);
	lastSum=0;
	start = clock();
        for(i=0;i<BNO;i++){
                movingSum(dataIn, BSIZE);
        }
        end = clock();
        printf("moving sum: %f\n", (end-start)/ CLOCKS_PER_SEC);
//moving count
        dataStore.resize(0);
        lastCount=0;
	start = clock();
        for(i=0;i<BNO;i++){
                movingCount(dataIn, BSIZE);
        }
        end = clock();
        printf("moving count: %f\n", (end-start)/ CLOCKS_PER_SEC);
//moving average
        dataStore.resize(0);
        lastSum=0;
	lastCount=0;
	start = clock();
        for(i=0;i<BNO;i++){
                movingAverage(dataIn, BSIZE);
        }
        end = clock();
        printf("moving average: %f\n", (end-start)/ CLOCKS_PER_SEC);
//moving min
        dataStore.resize(0);
        start = clock();
        for(i=0;i<BNO;i++){
                movingMin(dataIn, BSIZE);
        }
        end = clock();
        printf("moving min: %f\n", (end-start)/ CLOCKS_PER_SEC);
//moving max
        dataStore.resize(0);
        lastSum=0;
        start = clock();
        for(i=0;i<BNO;i++){
                movingMax(dataIn, BSIZE);
        }
        end = clock();
        printf("moving max: %f\n", (end-start)/ CLOCKS_PER_SEC);

}
