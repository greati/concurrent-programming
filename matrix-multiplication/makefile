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
main: bin build Mat.o MatTestUtils.o multimat.o
	$(CXX) $(BUILDDIR)Mat.o $(BUILDDIR)MatTestUtils.o $(BUILDDIR)multimat.o \
	-o $(BINDIR)multimat $(OPTIONSCXX)

tests: bin build Mat.o MatTestUtils.o perftests.o
	$(CXX) $(BUILDDIR)Mat.o $(BUILDDIR)MatTestUtils.o $(BUILDDIR)perftests.o \
	-o $(BINDIR)perftests $(OPTIONSCXX)

bin:
	mkdir -p ./bin/
build:
	mkdir -p ./build/

%.o: $(SRCDIR)%.cpp
	$(CXX) -c $< -o $(BUILDDIR)$@ $(OPTIONSCXX) $(DECLRDIR)

Mat.o: $(SRCDIR)Mat.cpp
MatTestUtils.o: $(SRCDIR)MatTestUtils.cpp
multimat.o: $(SRCDIR)multimat.cpp
perftests.o: $(SRCDIR)perftests.cpp


### clear objects & executables
clean: bin build
	$(DEL) -rf $(BINDIR)
	$(DEL) -rf $(BUILDDIR)
