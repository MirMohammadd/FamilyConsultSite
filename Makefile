# Variables
CXX = g++
CXXFLAGS = -std=c++11
INCLUDES = -I include \
           -I/opt/homebrew/Cellar/mysql-connector-c++/8.3.0/include
LDFLAGS = -L/opt/homebrew/Cellar/mysql-connector-c++/8.3.0/lib \
          -lmysqlcppconn8.2.8.3.0

# Target executable
TARGET = interface

# Source files
SRC = interface.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Default rule to build the target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LDFLAGS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJ)
