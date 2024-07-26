# Makefile

# The C++ compiler
CXX = g++

# Compilation flags
CXXFLAGS = -std=c++11 -Wall -I/usr/include -I include

# Linker flags for SQLite3
LDFLAGS = -lsqlite3

# The source file
SRCS = interface.cpp

# The output executable
TARGET = interface

# Default target
all: $(TARGET)

# Build the target
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Clean up
clean:
	rm -f $(TARGET)
