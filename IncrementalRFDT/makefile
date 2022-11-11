default:
	g++ main_covtype.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o cov.out
	g++ main_phi.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o phi.out
	g++ main_Synth.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o synthetic.out
	g++ main_M5.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o M5.out
	g++ main_elec.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o elec.out

testMix:
	g++ -g -fno-stack-protector main_mixed.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o mix.out

testCov:
	g++ -g -fno-stack-protector main_covtype.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o cov.out

testPhi:
	g++ -g -fno-stack-protector main_phi.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o phi.out

testSynth:
	g++ -g -fno-stack-protector main_Synth.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o synthetic.out

testElec:
	g++ -g -fno-stack-protector main_elec.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o elec.out

run:
	echo Synthetic
	./synthetic.out 0
	./synthetic.out 0
	./synthetic.out 0
	./synthetic.out 0
	./synthetic.out 0
	./synthetic.out 0
	./synthetic.out 1
	./synthetic.out 1
	./synthetic.out 1
	./synthetic.out 1
	./synthetic.out 1
	./synthetic.out 1
	echo elec
	./elec.out 0 0
	./elec.out 0 0
	./elec.out 0 0
	./elec.out 0 0
	./elec.out 0 0
	./elec.out 0 0
	./elec.out 1 0
	./elec.out 1 0
	./elec.out 1 0
	./elec.out 1 0
	./elec.out 1 0
	./elec.out 1 0
	echo gradual
	./mix.out 0 0
	./mix.out 0 0
	./mix.out 0 0
	./mix.out 0 0
	./mix.out 0 0
	./mix.out 0 0
	./mix.out 1 0
	./mix.out 1 0
	./mix.out 1 0
	./mix.out 1 0
	./mix.out 1 0
	./mix.out 1 0
	echo abrupt
	./mix.out 0 1
	./mix.out 0 1
	./mix.out 0 1
	./mix.out 0 1
	./mix.out 0 1
	./mix.out 0 1
	./mix.out 1 1
	./mix.out 1 1
	./mix.out 1 1
	./mix.out 1 1
	./mix.out 1 1
	./mix.out 1 1
	echo cov
	./cov.out 0 0
	./cov.out 0 0
	./cov.out 0 0
	./cov.out 0 0
	./cov.out 0 0
	./cov.out 0 0
	./cov.out 1 0
	./cov.out 1 0
	./cov.out 1 0
	./cov.out 1 0
	./cov.out 1 0
	./cov.out 1 0
	echo phi
	./phi.out 0 0
	./phi.out 0 0
	./phi.out 0 0
	./phi.out 0 0
	./phi.out 0 0
	./phi.out 0 0
	./phi.out 1 0
	./phi.out 1 0
	./phi.out 1 0
	./phi.out 1 0
	./phi.out 1 0
	./phi.out 1 0

clear:
	rm ./*.out
