# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -I -g
OPENBLASPATH = /usr/lib/x86_64-linux-gnu/libopenblas.a

# Targets needed to bring the executable up to date

all: library

# library: sourceOB.o sourceMKL.o sourcePT.o
library: main.o sourceOB.o sourceMKL.o others.o
#	$(CXX) $(CXXFLAGS) -o library sourceOB.o sourceMKL.o sourcePT.o -I /include/ -L/lib/ -lopenblas -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_gnu_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lgomp -lpthread -lm -ldl
	$(CXX) $(CXXFLAGS) -o library main.o sourceOB.o sourceMKL.o others.o -I /include/ -L/lib/ -lopenblas -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_gnu_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lgomp -lpthread -lm -ldl

main.o: main.cpp

sourceMKL.o: sourceMKL.cpp
	$(CXX) -c -m64 -I${MKLROOT}/include sourceMKL.cpp

# sourcePT.o: sourcePT.cpp
	# $(CXX) -c -pthread sourcePT.cpp

sourceOB.o: sourceOB.cpp

others.o: others.cpp