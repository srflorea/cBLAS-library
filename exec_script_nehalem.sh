#!/bin/bash

[[ -z $COMPILER ]] && COMPILER="gcc"

#build source for nehalem arhitecture
make nehalem > /dev/null

if [[ $COMPILER="gcc" ]]; then
	for ((i = 1000; i <= 20000; i += 1000))
	do
   		./nehalem $i nehalem
	done
fi

rm nehalem

#build source for nehalem arhitecture with compile optimization
make nehalem -f Makefile_optimized > /dev/null

if [[ $COMPILER="gcc" ]]; then
	for ((i = 1000; i <= 20000; i += 1000))
	do
   		./nehalem $i nehalem_optim
	done
fi
