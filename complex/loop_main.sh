#!/bin/bash
rm toto.txt
N=10
while [ "$N" != "100" ]
do 
	TPS=`./main $N`
	echo $N $TPS >> toto.txt
	echo $N $TPS
	N=`expr $N + 1`
done
