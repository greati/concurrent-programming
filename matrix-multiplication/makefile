# commands
CXX = g++
DEL = rm

# options
DEBUG = -g
WARNING = -Wall
OPTMIZE = -O3
STD = -std=c++11
THREAD_FLAG = -pthread
OPTIONSCXX = $(STD) $(WARNING) $(THREAD_FLAG)

# directories
DECLRDIR = -I ./include
SRCDIR = ./src/
BINDIR = ./bin/

MULT_EXEC = multimat
TESTS_EXEC = perftests

### executable targets
main: bin Mat.o multimat.o
	$(CXX) $(BINDIR)Mat.o $(BINDIR)multimat.o \
	-o $(MULT_EXEC) $(OPTIONSCXX)

tests: bin Mat.o perftests.o
	$(CXX) $(BINDIR)Mat.o $(BINDIR)perftests.o \
	-o $(TESTS_EXEC) $(OPTIONSCXX)

### bin folder (created only if it doesnt exist)
bin:
	mkdir -p ./bin/

%.o: $(SRCDIR)%.cpp
	$(CXX) -c $< -o $(BINDIR)$@ $(OPTIONSCXX) $(DECLRDIR)

Mat.o: $(SRCDIR)Mat.cpp
multimat.o: $(SRCDIR)multimat.cpp
perftests.o: $(SRCDIR)perftests.cpp


### clear objects & executables
clean: bin
	$(DEL) ./$(MULT_EXEC)
	$(DEL) ./$(TESTS_EXEC)
	$(DEL) $(BINDIR)*.o
