# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable name
TARGET = P2

# Object files
OBJS = main.o scanner.o parser.o testTree.o

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation rules for object files
main.o: main.cpp parser.hpp testTree.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

scanner.o: scanner.cpp scanner.hpp token.hpp
	$(CXX) $(CXXFLAGS) -c scanner.cpp

parser.o: parser.cpp parser.hpp scanner.hpp token.hpp node.hpp
	$(CXX) $(CXXFLAGS) -c parser.cpp

testTree.o: testTree.cpp testTree.hpp node.hpp
	$(CXX) $(CXXFLAGS) -c testTree.cpp

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET) output.txt

# Phony targets
.PHONY: all clean