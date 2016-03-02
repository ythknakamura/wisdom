CXX = g++
CXXFLAGS = -fopenmp -MMD -MP -O3 -Wall -Wextra -Wunused-parameter -Wfloat-equal -funroll-all-loops -std=c++14 -march=native
LIB = -lm -llapacke -lgomp
TARGET = ../bin/$(shell basename `readlink -f ..`)
SRCS = $(shell ls *.cpp)
HEADS= $(shell ls *.h)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
PLTS = $(shell ls *.plt)
.PHONY: all clean

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LIB)

all: clean $(TARGET)

-include $(DEPS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET) 

run: 
	$(TARGET)

plot:
	for d in $(PLTS); do gnuplot $$d; done

full: all run plot
