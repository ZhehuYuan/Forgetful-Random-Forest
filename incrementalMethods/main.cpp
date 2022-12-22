#include "main.h"
#include <stdio.h>
#include <stdlib.h>

enum BUFF {None, nTree, IR};

int main(int argc, char* argv[]){
	bool elec=false, phi=false, gradual=false, abrupt=false, cov=false;
	bool rf = false;
	bool bagging = false;
	long nTree = 20;
	double ir = 0.3;
	
	char* buf;
	long bufId = 0;
	BUFF bufItem = BUFF::None;

	if(argc>1){
		for(long i=1; i<argc; i++){
			if(argv[i][0]!='-')continue;
			long j=1;
			while(argv[i][j]!='\0'){
				char tmp = argv[i][j];
				j++;
				if(((int)tmp<=57 and (int)tmp>=48) or tmp=='.'){
					if(bufItem!=BUFF::None){
						buf[bufId] = tmp;
						bufId++;
					}
				}else{
					if(bufItem==BUFF::IR){
						buf[bufId]='\0';
						ir = atof(buf);
						bufItem = BUFF::None;
						free(buf);
						bufId=0;
					}else if(bufItem==BUFF::nTree){
						buf[bufId]='\0';
						nTree = atoi(buf);
						bufItem = BUFF::None;
						free(buf);
						bufId=0;
					}
					switch(tmp){
						case 'E':
							elec=true;
							break;
						case 'P':
							phi=true;
							break;
						case 'G':
							gradual=true;
							break;
						case 'A':
							abrupt=true;
							break;
						case 'C':
							cov=true;
							break;
						case 'R':
							rf = true;
							break;
						case 'B':
							bagging=true;
							break;
						case 'n':
							bufItem=BUFF::nTree;
							buf = (char*)malloc(1024*sizeof(char));
							break;
						case 'i':
							bufItem=BUFF::IR;
							buf = (char*)malloc(1024*sizeof(char));
							break;
					}
					
				}
			}
		}
	}
	if(bufItem==BUFF::IR){
		buf[bufId]='\0';
		ir = atof(buf);
		bufItem = BUFF::None;
		free(buf);
		bufId=0;
	}else if(bufItem==BUFF::nTree){
		buf[bufId]='\0';
		nTree = atoi(buf);
		bufItem = BUFF::None;
		free(buf);
		bufId=0;
	}
	
	if(elec){
		printf("Electricity:");
		mainElec(rf, ir, bagging, nTree);	
	}
	if(phi){
		printf("Phishing:");
		mainPhi(rf, ir, bagging, nTree);	
	}
	if(gradual){
		printf("Gradual Synthetic:");
		mainMix(true, rf, ir, bagging, nTree);	
	}
	if(abrupt){
		printf("Abrupt Synthetic:");
		mainMix(false, rf, ir, bagging, nTree);	
	}
	if(cov){
		printf("Forest Cover:");
		mainCov(rf, ir, bagging, nTree);	
	}
}
