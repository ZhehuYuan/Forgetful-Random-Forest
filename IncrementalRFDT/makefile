default:
	g++ -std=c++11 main_covtype.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o cov.out
	g++ -std=c++11 main_phi.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o phi.out
	g++ -std=c++11 main_Synth.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o synthetic.out
	g++ -std=c++11 main_elec.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o elec.out
	g++ -std=c++11 main_mixed.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o mix.out

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
	#echo Synthetic
	#./synthetic.out 0
	#./synthetic.out 0
	#./synthetic.out 0
	#./synthetic.out 0
	#./synthetic.out 0
	#./synthetic.out 0
	#./synthetic.out 1
	#./synthetic.out 1
	#./synthetic.out 1
	#./synthetic.out 1
	#./synthetic.out 1
	#./synthetic.out 1
	echo phi
	./phi.out 0 $(rf)
	./phi.out 0 $(rf)
	./phi.out 0 $(rf)
	./phi.out 0 $(rf)
	./phi.out 0 $(rf)
	./phi.out 0 $(rf)
	./phi.out 1 $(rf)
	./phi.out 1 $(rf)
	./phi.out 1 $(rf)
	./phi.out 1 $(rf)
	./phi.out 1 $(rf)
	./phi.out 1 $(rf)
	echo elec
	./elec.out 0 $(rf)
	./elec.out 0 $(rf)
	./elec.out 0 $(rf)
	./elec.out 0 $(rf)
	./elec.out 0 $(rf)
	./elec.out 0 $(rf)
	./elec.out 1 $(rf)
	./elec.out 1 $(rf)
	./elec.out 1 $(rf)
	./elec.out 1 $(rf)
	./elec.out 1 $(rf)
	./elec.out 1 $(rf)
	echo gradual
	./mix.out 0 0 $(rf)
	./mix.out 0 0 $(rf)
	./mix.out 0 0 $(rf)
	./mix.out 0 0 $(rf)
	./mix.out 0 0 $(rf)
	./mix.out 0 0 $(rf)
	./mix.out 1 0 $(rf)
	./mix.out 1 0 $(rf)
	./mix.out 1 0 $(rf)
	./mix.out 1 0 $(rf)
	./mix.out 1 0 $(rf)
	./mix.out 1 0 $(rf)
	echo abrupt
	./mix.out 0 1 $(rf) 
	./mix.out 0 1 $(rf)
	./mix.out 0 1 $(rf)
	./mix.out 0 1 $(rf)
	./mix.out 0 1 $(rf)
	./mix.out 0 1 $(rf)
	./mix.out 1 1 $(rf)
	./mix.out 1 1 $(rf)
	./mix.out 1 1 $(rf)
	./mix.out 1 1 $(rf)
	./mix.out 1 1 $(rf)
	./mix.out 1 1 $(rf)
	echo cov
	./cov.out 0 $(rf)
	./cov.out 0 $(rf)
	./cov.out 0 $(rf)
	./cov.out 0 $(rf)
	./cov.out 0 $(rf)
	./cov.out 0 $(rf)
	./cov.out 1 $(rf)
	./cov.out 1 $(rf)
	./cov.out 1 $(rf)
	./cov.out 1 $(rf)
	./cov.out 1 $(rf)
	./cov.out 1 $(rf)

clear:
	rm ./*.out
