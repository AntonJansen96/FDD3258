CXX = gcc

# Needed for CXX=g++
# STANDARD = -std=c++11

WARNINGS = -Wall
OPTIMIZATION = -g -O2
PARALLEL = -fopenmp
MATH_LIB = -lm

# Parallel computing options
N=10000

EXEC = DFTW
# SRC = DFTW_mod.c 
SRC = DFTW_fin.c
OBJS = $(SRC: .c = .o)

.DEFAULT_GOAL = all

.PHONY: all clean distclean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) -DSIZE=$(N) $(WARNINGS) $(PARALLEL) $(OPTIMIZATION) $^ -o $@ $(MATH_LIB)

clean:
	$(RM) $(EXEC)

distclean:
	$(RM) $(EXEC)
	$(RM) *.o
	$(RM) -r
