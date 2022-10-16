#!/bin/sh

x=0;
while [ $x -le 4 ]; 
	do 
	echo $x;
	y=1;
	while [ $y -le 15 ];
       		do	
		./synthetic.out 0 1 $x $y;
       		y=`expr $y + 1`;
	done;	
       	x=`expr $x + 1`; 
done;
