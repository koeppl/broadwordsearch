CPPFILE=broad.cpp
CXX = g++
MYCXXFLAGS  = -ggdb -Wall -pedantic -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -std=gnu++17
TARGET = a.out
all: $(TARGET)

$(TARGET): $(CPPFILE)
	$(CXX) $(MYCXXFLAGS) $(CXXFLAGS) -o $(TARGET) $(CPPFILE)

clean:
	$(RM) $(TARGET)
