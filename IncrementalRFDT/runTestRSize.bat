#!/bin/sh

x=4;
while [ $x -le 4 ];
	do 
	echo $x;
	y=100;
	while [ $y -le 2000 ];
		do 
		./synthetic.out 1 $y $x;
       		y=`expr $y + 100`; 
	done;
       	x=`expr $x + 1`; 
done;
