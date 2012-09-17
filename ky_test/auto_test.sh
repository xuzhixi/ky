#!/bin/bash

for (( i=0; i<100; i++ ))
do
	./a.out
	sleep 1
	i=$(expr $i + 1)
done
