one=1
two=2
rfTestCov:
	g++ -g -fno-stack-protector main_covtype.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o cov.out

rfTestPhi:
	g++ -g -fno-stack-protector main_phi.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o phi.out

rfTestSynth:
	g++ -g -fno-stack-protector main_Synth.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o synthetic.out

rfTestM5:
	g++ -g -fno-stack-protector main_M5.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o M5.out

rfTestElec:
	g++ -g -fno-stack-protector main_elec.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o elec.out

rfTestAWS:
	g++ -g -fno-stack-protector main_AWS.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o AWS.out

runDTtest:
	echo ${shell x=10000;while [ $$x -le 100000 ]; do echo $$x:[; ./*.out $$x; echo ]; x=`expr $$x + 10000`; done;}
	echo ${shell x=100000;while [ $$x -le 200000 ]; do echo $$x:[; ./*.out $$x; echo ]; x=`expr $$x + 10000`; done;}
	echo ${shell x=200000;while [ $$x -le 300000 ]; do echo $$x:[; ./*.out $$x; echo ]; x=`expr $$x + 10000`; done;}

runTestM5:
	echo ${shell x=10000;while [ $$x -le 100000 ]; do echo $$x:[; ./*.out $$x; echo ]; x=`expr $$x + 10000`; done;}
	echo ${shell x=100000;while [ $$x -le 200000 ]; do echo $$x:[; ./*.out $$x; echo ]; x=`expr $$x + 10000`; done;}
	echo ${shell x=200000;while [ $$x -le 300000 ]; do echo $$x:[; ./*.out $$x; echo ]; x=`expr $$x + 10000`; done;}

runTestElec:
	echo ${shell x=100;while [ $$x -le 2000 ]; do echo $$x:[; ./*.out 1 $$x; echo ]; x=`expr $$x + 100`; done;}

runTestPhi:
	echo ${shell x=100;while [ $$x -le 3000 ]; do echo $$x:[; ./*.out 1 $$x; echo ]; x=`expr $$x + 100`; done;}

runTestCov:
	echo ${shell x=1000;while [ $$x -le 10000 ]; do echo $$x:[; ./*.out 1 $$x; echo ]; x=`expr $$x + 1000`; done;}
	echo ${shell x=10000;while [ $$x -le 20000 ]; do echo $$x:[; ./*.out 1 $$x; echo ]; x=`expr $$x + 1000`; done;}
	echo ${shell x=20000;while [ $$x -le 30000 ]; do echo $$x:[; ./*.out 1 $$x; echo ]; x=`expr $$x + 1000`; done;}

run:
	./*.out 0 0
	./*.out 0 0
	./*.out 0 0
	./*.out 0 0
	./*.out 0 0
	./*.out 0 0
	./*.out 0 1
	./*.out 0 1
	./*.out 0 1
	./*.out 0 1
	./*.out 0 1
	./*.out 0 1
	./*.out 1 0
	./*.out 1 0
	./*.out 1 0
	./*.out 1 0
	./*.out 1 0
	./*.out 1 0
	./*.out 1 1
	./*.out 1 1
	./*.out 1 1
	./*.out 1 1
	./*.out 1 1
	./*.out 1 1
	./*.out 1 2
	./*.out 1 2
	./*.out 1 2
	./*.out 1 2
	./*.out 1 2
	./*.out 1 2
	./*.out 1 3
	./*.out 1 3
	./*.out 1 3
	./*.out 1 3
	./*.out 1 3
	./*.out 1 3
	./*.out 1 4
	./*.out 1 4
	./*.out 1 4
	./*.out 1 4
	./*.out 1 4
	./*.out 1 4


runDT:
	./*.out 0
	./*.out 0
	./*.out 0
	./*.out 0
	./*.out 0
	./*.out 0
	./*.out 1
	./*.out 1
	./*.out 1
	./*.out 1
	./*.out 1
	./*.out 1
	./*.out 2
	./*.out 2
	./*.out 2
	./*.out 2
	./*.out 2
	./*.out 2
	./*.out 3
	./*.out 3
	./*.out 3
	./*.out 3
	./*.out 3
	./*.out 3
	./*.out 4
	./*.out 4
	./*.out 4
	./*.out 4
	./*.out 4
	./*.out 4


clear:
	rm ./*.out
