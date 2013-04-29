#!/bin/bash

[[ -z $COMPILER ]] && COMPILER="gcc"

#build source for opteron arhitecture
make opteron > /dev/null

if [[ $COMPILER="gcc" ]]; then
   	for ((i = 1000; i <= 20000; i+= 1000))
	do
		./opteron $i opteron
	done
fi

rm opteron

#build source for opteron arhitecture with compile optimization
make opteron -f Makefile_optimized > /dev/null

if [[ $COMPILER="gcc" ]]; then
   	for ((i = 1000; i <= 20000; i+= 1000))
	do
		./opteron $i opteron_optim
	done
fi
