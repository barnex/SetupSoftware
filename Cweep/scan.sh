#!/bin/bash
i=0
while [ $i -le 50 ]
do
	./Cweep one_freq_2.txt
	(( i++ ))
done
