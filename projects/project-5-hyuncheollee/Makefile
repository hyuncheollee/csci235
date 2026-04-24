CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g -I.

SRCS = Vector3D.cpp Translation.cpp Scale.cpp TransformPipeline.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

rebuild: clean all
