CXX := mpic++
CXXFLAGS += -std=c++17 -Wall -O3

LIBSRCS = $(filter-out main.cc,$(shell find -name \*.cc))

LIBOBJS = $(patsubst %.cc,%.o,$(LIBSRCS))

main: main.o libproject.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -L. -o $@ $< -l project

$(LIBOBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

libproject.a: $(LIBOBJS)
	ar rcs $@ $^

clean:
	rm -f libproject.a $(LIBOBJS) main

.PHONY: clean
