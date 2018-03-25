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
BUILDDIR = ./build/

MULT_EXEC = multimat
TESTS_EXEC = perftests

### executable targets
main: bin build Mat.o multimat.o
	$(CXX) $(BUILDDIR)Mat.o $(BUILDDIR)multimat.o \
	-o $(BINDIR)$(MULT_EXEC) $(OPTIONSCXX)

tests: bin build Mat.o perftests.o
	$(CXX) $(BUILDDIR)Mat.o $(BUILDDIR)perftests.o \
	-o $(BINDIR)$(TESTS_EXEC) $(OPTIONSCXX)

### bin folder (created only if it doesnt exist)
bin:
	mkdir -p ./bin/
build:
	mkdir -p ./build/

%.o: $(SRCDIR)%.cpp
	$(CXX) -c $< -o $(BUILDDIR)$@ $(OPTIONSCXX) $(DECLRDIR)

Mat.o: $(SRCDIR)Mat.cpp
multimat.o: $(SRCDIR)multimat.cpp
perftests.o: $(SRCDIR)perftests.cpp


### clear objects & executables
clean: bin build
	$(DEL) -rf $(BINDIR)
	$(DEL) -rf $(BUILDDIR)
