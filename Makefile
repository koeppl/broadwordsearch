CXX = g++
DEBUGFLAGS = -O0 -ggdb
RELEASEFLAGS = -O3 -DNDEBUG
MYCXXFLAGS  = -Wall -pedantic -std=gnu++17 -I/home/niki/opt/include/ -L/home/niki/opt/lib/ $(RELEASEFLAGS) # $(DEBUGFLAGS)

TARGET = test bench
all: $(TARGET)

test : test.cpp broadword.hpp
	$(CXX) $(MYCXXFLAGS) $(CXXFLAGS) -o test test.cpp -lsdsl -ldivsufsort -ldivsufsort64 -lglog -lgtest -lpthread

bench: bench.cpp broadword.hpp
	$(CXX) $(MYCXXFLAGS) $(CXXFLAGS) -o bench bench.cpp -lsdsl -ldivsufsort -ldivsufsort64 -lcelero -lglog -lpthread

clean:
	$(RM) $(TARGET)
