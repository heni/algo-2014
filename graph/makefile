INCLUDE_OPTS := -I/usr/include/x86_64-linux-gnu/c++/4.8 -I/usr/include/c++/4.8
LIBS_OPTS := -L/usr/lib/gcc/x86_64-linux-gnu/4.8/

graph-test: test.cpp graph.h
	clang++ $(INCLUDE_OPTS) $(LIBS_OPTS) -std=c++11 -O3 -o $@ $<
