#! /bin/bash

echo Tune Initial iRate
for((i=1;i<10;i++));
do
	echo Initial iRate=0.$i
	for((j=0;j<18;j++));
	do
		./tune.out 1 $j 0.$i f
	done
done
for((j=0;j<18;j++));
do
	./tune.out 1 $j 0.3 t > $j.txt
done


echo Tune nTree

echo No Bagging
for((i=10;i<=80;i*=2));
do
	echo nTree=$i
	for((j=0;j<18;j++));
	do
		./tune.out 0 $j 0.3 0 $i 1
	done
done

echo With Bagging
for((i=10;i<=80;i*=2));
do
	echo nTree=$i
	for((j=0;j<18;j++));
	do
		./tune.out 0 $j 0.3 1 $i 1
	done
done


echo Tune tThresh

echo No Bagging
for((i=1;i<=10000;i*=10));
do
	echo tThresh=0.05/$i
	for((j=0;j<18;j++));
	do
		./tune.out 0 $j 0.3 0 20 $i
	done
done

echo With Bagging
for((i=1;i<=10000;i*=10));
do
	echo tThresh=0.05/$i
	for((j=0;j<18;j++));
	do
		./tune.out 0 $j 0.3 1 20 $i
	done
done


