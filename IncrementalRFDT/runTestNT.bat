#!/bin/sh

x=0;
while [ $x -le 4 ]; 
	do 
	echo $x;
	y=6;
	while [ $y -le 14 ];
       		do	
		./synthetic.out 0 $y $x;
       		y=`expr $y + 2`;
	done;	
       	x=`expr $x + 1`; 
done;
