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

tune:
	./synth.out 1 0 0.3 > ir1 
	./synth.out 1 1 0.3 > ir2
	./synth.out 1 2 0.3 > ir3
	./synth.out 1 3 0.3 > ir4
	./synth.out 1 4 0.3 > ir5
	./synth.out 1 5 0.3 > ir6
	./synth.out 1 6 0.3 > ir7
	./synth.out 1 7 0.3 > ir8
	./synth.out 1 8 0.3 > ir9

tune2:
	./synth.out 0 0 0.3
	./synth.out 0 1 0.3
	./synth.out 0 2 0.3
	./synth.out 0 3 0.3
	./synth.out 0 4 0.3
	./synth.out 0 5 0.3
	./synth.out 0 6 0.3
	./synth.out 0 7 0.3
	./synth.out 0 8 0.3
	./synth.out 0 9 0.3
	./synth.out 0 10 0.3
	./synth.out 0 11 0.3
	./synth.out 0 12 0.3
	./synth.out 0 13 0.3
	./synth.out 0 14 0.3
	./synth.out 0 15 0.3
	./synth.out 0 16 0.3
	./synth.out 0 17 0.3

tune3:
	./synth2.out 0 0 0.3
	./synth2.out 0 1 0.3
	./synth2.out 0 2 0.3
	./synth2.out 0 3 0.3
	./synth2.out 0 4 0.3
	./synth2.out 0 5 0.3
	./synth2.out 0 6 0.3
	./synth2.out 0 7 0.3
	./synth2.out 0 8 0.3
	./synth2.out 0 9 0.3
	./synth2.out 0 10 0.3
	./synth2.out 0 11 0.3
	./synth2.out 0 12 0.3
	./synth2.out 0 13 0.3
	./synth2.out 0 14 0.3
	./synth2.out 0 15 0.3
	./synth2.out 0 16 0.3
	./synth2.out 0 17 0.3

tune4:
	./synth3.out 0 0 0.3
	./synth3.out 0 1 0.3
	./synth3.out 0 2 0.3
	./synth3.out 0 3 0.3
	./synth3.out 0 4 0.3
	./synth3.out 0 5 0.3
	./synth3.out 0 6 0.3
	./synth3.out 0 7 0.3
	./synth3.out 0 8 0.3
	./synth3.out 0 9 0.3
	./synth3.out 0 10 0.3
	./synth3.out 0 11 0.3
	./synth3.out 0 12 0.3
	./synth3.out 0 13 0.3
	./synth3.out 0 14 0.3
	./synth3.out 0 15 0.3
	./synth3.out 0 16 0.3
	./synth3.out 0 17 0.3

tune5:
	./synth4.out 0 0 0.3
	./synth4.out 0 1 0.3
	./synth4.out 0 2 0.3
	./synth4.out 0 3 0.3
	./synth4.out 0 4 0.3
	./synth4.out 0 5 0.3
	./synth4.out 0 6 0.3
	./synth4.out 0 7 0.3
	./synth4.out 0 8 0.3
	./synth4.out 0 9 0.3
	./synth4.out 0 10 0.3
	./synth4.out 0 11 0.3
	./synth4.out 0 12 0.3
	./synth4.out 0 13 0.3
	./synth4.out 0 14 0.3
	./synth4.out 0 15 0.3
	./synth4.out 0 16 0.3
	./synth4.out 0 17 0.3

tune6:
	./synth5.out 0 0 0.3
	./synth5.out 0 1 0.3
	./synth5.out 0 2 0.3
	./synth5.out 0 3 0.3
	./synth5.out 0 4 0.3
	./synth5.out 0 5 0.3
	./synth5.out 0 6 0.3
	./synth5.out 0 7 0.3
	./synth5.out 0 8 0.3
	./synth5.out 0 9 0.3
	./synth5.out 0 10 0.3
	./synth5.out 0 11 0.3
	./synth5.out 0 12 0.3
	./synth5.out 0 13 0.3
	./synth5.out 0 14 0.3
	./synth5.out 0 15 0.3
	./synth5.out 0 16 0.3
	./synth5.out 0 17 0.3

tune7:
	./synth6.out 0 0 0.3
	./synth6.out 0 1 0.3
	./synth6.out 0 2 0.3
	./synth6.out 0 3 0.3
	./synth6.out 0 4 0.3
	./synth6.out 0 5 0.3
	./synth6.out 0 6 0.3
	./synth6.out 0 7 0.3
	./synth6.out 0 8 0.3
	./synth6.out 0 9 0.3
	./synth6.out 0 10 0.3
	./synth6.out 0 11 0.3
	./synth6.out 0 12 0.3
	./synth6.out 0 13 0.3
	./synth6.out 0 14 0.3
	./synth6.out 0 15 0.3
	./synth6.out 0 16 0.3
	./synth6.out 0 17 0.3

tune8:
	./synth7.out 0 0 0.3
	./synth7.out 0 1 0.3
	./synth7.out 0 2 0.3
	./synth7.out 0 3 0.3
	./synth7.out 0 4 0.3
	./synth7.out 0 5 0.3
	./synth7.out 0 6 0.3
	./synth7.out 0 7 0.3
	./synth7.out 0 8 0.3
	./synth7.out 0 9 0.3
	./synth7.out 0 10 0.3
	./synth7.out 0 11 0.3
	./synth7.out 0 12 0.3
	./synth7.out 0 13 0.3
	./synth7.out 0 14 0.3
	./synth7.out 0 15 0.3
	./synth7.out 0 16 0.3
	./synth7.out 0 17 0.3

tune9:
	./synth8.out 0 0 0.3
	./synth8.out 0 1 0.3
	./synth8.out 0 2 0.3
	./synth8.out 0 3 0.3
	./synth8.out 0 4 0.3
	./synth8.out 0 5 0.3
	./synth8.out 0 6 0.3
	./synth8.out 0 7 0.3
	./synth8.out 0 8 0.3
	./synth8.out 0 9 0.3
	./synth8.out 0 10 0.3
	./synth8.out 0 11 0.3
	./synth8.out 0 12 0.3
	./synth8.out 0 13 0.3
	./synth8.out 0 14 0.3
	./synth8.out 0 15 0.3
	./synth8.out 0 16 0.3
	./synth8.out 0 17 0.3

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
