CC = gcc
CFLAGS = -Wall -o
SRC = blass.c
EXE1 = opteron
EXE2 = quad
EXE3 = nehalem

build opteron:
	$(CC) $(CFLAGS) $(EXE1) -L /opt/tools/libraries/atlas/3.10.1-opteron-gcc-4.4.6/lib/ -L /opt/tools/libraries/atlas/3.10.1-opteron-gcc-4.4.6/include/ blass.c -lcblas -latlas

build quad:
	$(CC) $(CFLAGS) $(EXE2) -L /opt/tools/libraries/atlas/3.10.1-quad-gcc-4.4.6/lib/ -L /opt/tools/libraries/atlas/3.10.1-quad-gcc-4.4.6/include/ blass.c -lcblas -latlas

build nehalem:
	$(CC) $(CFLAGS) $(EXE3) -L /opt/tools/libraries/atlas/3.10.1-nehalem-gcc-4.4.6/lib/ -L /opt/tools/libraries/atlas/3.10.1-nehalem-gcc-4.4.6/include/ blass.c -lcblas -latlas

clean:
	rm $(EXE1) $(EXE2) $(EXE3)

run:
	./$(EXE)


