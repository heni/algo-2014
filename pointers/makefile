all: test-shared test-unique test-weak

test-weak: test-weak.cpp
	g++ -std=c++11 $< -o $@

test-shared: test-shared.cpp
	g++ -std=c++11 $< -o $@

test-unique: test-unique.cpp
	g++ -Wno-deprecated-declarations -std=c++11 $< -o $@
