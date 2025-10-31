# Include directories
SUBMISSION_DIR = .

# Add each subfolder as include directories (prevents nasty relative imports!)
CXX = g++
CXXFLAGS = \
	-std=c++17 -g -Wall -O2 \
	-fsanitize=address \
	-I $(SUBMISSION_DIR) 

PROG ?= main

# Main program objects
MAIN_OBJS = main.o

# Submission objects
SUBMITTED_OBJS = \
	$(SUBMISSION_DIR)/File.o \
	$(SUBMISSION_DIR)/FileUtils.o \
	$(SUBMISSION_DIR)/FileLoader.o \
	$(SUBMISSION_DIR)/TextFile.o \
	$(SUBMISSION_DIR)/ImageFile.o \
	$(SUBMISSION_DIR)/Clock.o \
	$(SUBMISSION_DIR)/Pixel.o \

OBJS = $(MAIN_OBJS) $(SUBMITTED_OBJS)

mainprog: $(PROG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(PROG) *.o *.out \
		$(SUBMISSION_DIR)/*.o \

rebuild: clean mainprog