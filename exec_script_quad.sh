#!/bin/bash

[[ -z $COMPILER ]] && COMPILER="gcc"

#build source for quad arhitecture
make quad > /dev/null

if [[ $COMPILER="gcc" ]]; then
	for ((i = 1000; i <= 20000; i += 1000))
	do
   		./quad $i quad
	done
fi

rm quad

#build source for quad arhitecture with compile optimization
make quad -f Makefile_optimized > /dev/null

if [[ $COMPILER="gcc" ]]; then
	for ((i = 1000; i <= 20000; i += 1000))
	do
   		./quad $i quad_optim
	done
fi
