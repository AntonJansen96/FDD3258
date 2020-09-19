CXX = gcc

# Needed for CXX=g++
# STANDARD = -std=c++11

WARNINGS = -Wall
OPTIMIZATION = -g -O2
PARALLEL = -fopenmp
MATH_LIB = -lm

EXEC = DFTW
SRC = DFTW_mod.c 
OBJS = $(SRC: .c = .o)

.DEFAULT_GOAL = all

.PHONY: all clean distclean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(WARNINGS) $(PARALLEL) $(OPTIMIZATION) $^ -o $@ $(MATH_LIB)

clean:
	$(RM) $(EXEC)

distclean:
	$(RM) $(EXEC)
	$(RM) *.o
	$(RM) -r
