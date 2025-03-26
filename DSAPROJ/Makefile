# Minimal Makefile for building a console application

CXX      = g++
CXXFLAGS = -std=c++14 -g
INCLUDE  = -I include

SRC_DIR = src
SRCS    = $(wildcard $(SRC_DIR)/*.cpp)
OBJS    = $(SRCS:.cpp=.o)

TARGET  = Project

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)