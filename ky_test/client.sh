#!/bin/bash

i=0
while [ "$i" -lt "$1" ] 
do 
./client
i=$(expr $i + 1)
done
