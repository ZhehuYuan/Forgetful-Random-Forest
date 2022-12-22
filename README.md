# Forgetful-Random-Forest

## Library Requirement

### Install Python3 and sklearn
```
sudo apt-get install python3.8.10
sudo apt-get install python3-pip
sudo pip3 install scikit-learn==1.0.2
sudo pip3 install scikit-multiflow==0.5.3
sudo pip3 install numpy==1.22.1
```

### Install Boost
##### Follow the following instruction to install.

https://www.boost.org/doc/libs/1_61_0/more/getting_started/unix-variants.html

## Run the test

### Run Experiment

#### Run Forgetful Methods
```
make
make runDT
make runRFNoBagging
make runRFBagging
```

#### Run Compare Methods
```
make runCompare
```

### Run Tuning
```
make tune
./tune.sh
```

## Options
Running "test.out", you may have a few options
#####-R
Running random forest, while the default setting is running decision tree.
#####-B
Running random forest with bagging, while the default setting is running without bagging. It will be ignored if you are running decision tree.
#####-nXX
Running random forest with nTree=XX, while the default setting is running with nTree=20. XX must be an integer. It will be ignored if you are running decision tree.
#####-iXX
Running random forest or decision tree with initial iRate=XX, while the default setting is running with initial iRate=0.3. XX could be either an integer or a float. It will be ignored if you are running decision tree.
#####-E
Running random forest or decision tree on Electricity Dataset.
#####-P
Running random forest or decision tree on Phing Dataset.
#####-G
Running random forest or decision tree on Gradual Synthetic Dataset.
#####-A
Running random forest or decision tree on Abrupto Synthetic Dataset.
#####-C
Running random forest or decision tree on Forest Cover Type Dataset.
