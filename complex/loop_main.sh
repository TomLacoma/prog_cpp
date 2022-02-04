#!/bin/bash
rm toto.txt
N=100
while [ "$N" != "1000" ]
do 
	TPS=`./main $N`
	echo $N $TPS >> toto.txt
	echo $N $TPS
	N=`expr $N + 10`
done
