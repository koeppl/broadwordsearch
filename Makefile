CPPFILE=broad.cpp
CXX = g++
MYCXXFLAGS  = -Wall -pedantic -std=gnu++17 -I/home/niki/opt/include/ -L/home/niki/opt/lib/ -DNDEBUG -O3 # -ggdb
#-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC  -ggdb

TARGET = a.out
all: $(TARGET)

$(TARGET): $(CPPFILE)
	$(CXX) $(MYCXXFLAGS) $(CXXFLAGS) -o $(TARGET) $(CPPFILE) -lsdsl -ldivsufsort -ldivsufsort64 -lcelero -lglog -lgtest -lpthread

clean:
	$(RM) $(TARGET)
