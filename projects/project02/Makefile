# Include directories
BASE_DIR = ./

CXX = g++
CXXFLAGS = \
	-std=c++17 -g -Wall -O2 \
	-I $(BASE_DIR) 

PROG ?= main

# Main program objects
MAIN_OBJS = main.o

# Class objects
CLASS_OBJS = \
	$(BASE_DIR)/File.o \
	$(BASE_DIR)/FileUtils.o \
	$(BASE_DIR)/Clock.o \
	$(BASE_DIR)/Pixel.o \
	$(BASE_DIR)/TextFile.o \
	$(BASE_DIR)/ImageFile.o \
	$(BASE_DIR)/FileLoader.o \
	# You should add your files as you create and test them

OBJS = $(MAIN_OBJS) $(CLASS_OBJS)

mainprog: $(PROG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(PROG) *.o *.out \
		$(BASE_DIR)/*.o \

rebuild: clean mainprog