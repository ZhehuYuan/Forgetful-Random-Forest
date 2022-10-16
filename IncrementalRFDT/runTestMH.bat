#!/bin/sh

x=4;
while [ $x -le 4 ];
	do 
	echo $x;
	y=0;
	while [ $y -le 10 ];
		do 
		./synthetic.out 1 1 $x $y;
       		y=`expr $y + 1`; 
	done;
       	x=`expr $x + 1`; 
done;
