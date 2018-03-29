# commands
UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
	CXX = g++-7
else
	CXX = g++
endif
DEL = rm

# options
DEBUG = -g
WARNING = -Wall
OPTMIZE = -O3
STD = -std=c++17
THREAD_LINK = -pthread
FILESYSTEM_LINK = -lstdc++fs
OPTIONSCXX = $(STD) $(WARNING) $(THREAD_LINK) $(FILESYSTEM_LINK)

# directories
DECLRDIR = -I ./include
SRCDIR = ./src/
BINDIR = ./bin/
BUILDDIR = ./build/

### executable targets
main: bin build MatTestUtils.o multimat.o 
	$(CXX) $(BUILDDIR)MatTestUtils.o $(BUILDDIR)multimat.o \
	-o $(BINDIR)multimat $(OPTIONSCXX)

tests: bin build MatTestUtils.o perftests.o 
	$(CXX) $(BUILDDIR)MatTestUtils.o $(BUILDDIR)perftests.o \
	-o $(BINDIR)perftests $(OPTIONSCXX)

bin:
	mkdir -p ./bin/
build:
	mkdir -p ./build/

#Matrix.o: ./include/Matrix.h ./src/Matrix.inl
#	$(CXX) -c $< -o $(BUILDDIR)$@ $(OPTIONSCXX) $(DECLRDIR)

%.o: $(SRCDIR)%.cpp 
	$(CXX) -c $< -o $(BUILDDIR)$@ $(OPTIONSCXX) $(DECLRDIR)

MatTestUtils.o: $(SRCDIR)MatTestUtils.cpp ./include/Matrix.h
multimat.o: $(SRCDIR)multimat.cpp ./include/Matrix.h
perftests.o: $(SRCDIR)perftests.cpp ./include/Matrix.h


### clear objects & executables
clean: bin build
	$(DEL) -rf $(BINDIR)
	$(DEL) -rf $(BUILDDIR)
