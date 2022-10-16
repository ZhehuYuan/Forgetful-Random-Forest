default:
	g++ -g -fno-stack-protector main_covtype.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o cov.out
	g++ -g -fno-stack-protector main_phi.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o phi.out
	g++ -g -fno-stack-protector main_Synth.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o synthetic.out
	g++ -g -fno-stack-protector main_M5.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o M5.out
	g++ -g -fno-stack-protector main_elec.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o elec.out

rfTestMix:
	g++ -g -fno-stack-protector main_mixed.cpp incrementalDecisionTree.cpp Evaluation.cpp RF.cpp -o mix.out

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

run2:
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
	./phi.out 1 1
	./phi.out 1 1
	./phi.out 1 1
	./phi.out 1 1
	./phi.out 1 1
	./phi.out 1 1


run:
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
	./elec.out 1 1
	./elec.out 1 1
	./elec.out 1 1
	./elec.out 1 1
	./elec.out 1 1
	./elec.out 1 1

run3:
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
	./phi.out 1 1
	./phi.out 1 1
	./phi.out 1 1
	./phi.out 1 1
	./phi.out 1 1
	./phi.out 1 1
	./synthetic.out 0 0 1
	./synthetic.out 0 0 1
	./synthetic.out 0 0 1
	./synthetic.out 0 0 1
	./synthetic.out 0 0 1
	./synthetic.out 0 0 1
	./synthetic.out 1 0 1
	./synthetic.out 1 0 1
	./synthetic.out 1 0 1
	./synthetic.out 1 0 1
	./synthetic.out 1 0 1
	./synthetic.out 1 0 1
	./synthetic.out 1 1 1
	./synthetic.out 0 0 0
	./synthetic.out 0 0 0
	./synthetic.out 0 0 0
	./synthetic.out 0 0 0
	./synthetic.out 0 0 0
	./synthetic.out 0 0 0
	./synthetic.out 1 0 0
	./synthetic.out 1 0 0
	./synthetic.out 1 0 0
	./synthetic.out 1 0 0
	./synthetic.out 1 0 0
	./synthetic.out 1 0 0
	./synthetic.out 1 1 0
	./synthetic.out 1 1 0
	./synthetic.out 1 1 0
	./synthetic.out 1 1 0
	./synthetic.out 1 1 0
	./synthetic.out 1 1 0

run5:
	./cov.out 1 1
	./cov.out 1 1
	./cov.out 1 1
	./cov.out 1 1
	./cov.out 1 1
	./cov.out 1 1
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

clear:
	rm ./*.out
