default:
	g++ -g -std=c++14 -IincrementalMethods incrementalMethods/main.cpp incrementalMethods/main_covtype.cpp incrementalMethods/incrementalDecisionTree.cpp incrementalMethods/Evaluation.cpp incrementalMethods/RF.cpp incrementalMethods/main_phi.cpp incrementalMethods/main_elec.cpp incrementalMethods/main_mixed.cpp incrementalMethods/main_power.cpp -o test.out

tune:
	g++ -g -std=c++14 -IincrementalMethods incrementalMethods/main_Synth.cpp incrementalMethods/incrementalDecisionTree.cpp incrementalMethods/Evaluation.cpp incrementalMethods/RF.cpp -o tune.out

runDT:
	./test.out -E
	./test.out -P
	./test.out -G
	./test.out -A
	./test.out -C

runRFNoBagging:
	./test.out -ER
	./test.out -PR
	./test.out -GR
	./test.out -AR
	./test.out -CR

runRFBagging:
	./test.out -ERB
	./test.out -PRB
	./test.out -GRB
	./test.out -ARB
	./test.out -CRB

runCompare:
	python3 compareMethods/HoeffdingTree.py Synth 1 0
	python3 compareMethods/HoeffdingTree.py Synth 2 0
	python3 compareMethods/HoeffdingTree.py Synth 3 0
	python3 compareMethods/HoeffdingTree.py Synth 4 0
	python3 compareMethods/HoeffdingTree.py Synth 5 0
	python3 compareMethods/HoeffdingTree.py Synth 1 1
	python3 compareMethods/HoeffdingTree.py Synth 2 1
	python3 compareMethods/HoeffdingTree.py Synth 3 1
	python3 compareMethods/HoeffdingTree.py Synth 4 1
	python3 compareMethods/HoeffdingTree.py Synth 5 1
	python3 compareMethods/HoeffdingTree.py phi 1
	python3 compareMethods/HoeffdingTree.py phi 2
	python3 compareMethods/HoeffdingTree.py phi 3
	python3 compareMethods/HoeffdingTree.py phi 4
	python3 compareMethods/HoeffdingTree.py phi 5
	python3 compareMethods/HoeffdingTree.py Elec 1
	python3 compareMethods/HoeffdingTree.py Elec 2
	python3 compareMethods/HoeffdingTree.py Elec 3
	python3 compareMethods/HoeffdingTree.py Elec 4
	python3 compareMethods/HoeffdingTree.py Elec 5
	python3 compareMethods/HoeffdingTree.py covtype 1
	python3 compareMethods/HoeffdingTree.py covtype 2
	python3 compareMethods/HoeffdingTree.py covtype 3
	python3 compareMethods/HoeffdingTree.py covtype 4
	python3 compareMethods/HoeffdingTree.py covtype 5

clear:
	rm ./*.out
	rm ./*.txt
