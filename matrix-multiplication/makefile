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

EXEC = multimat

### executable target
main: bin Mat.o multimat.o
	$(CXX) $(BINDIR)Mat.o $(BINDIR)multimat.o \
	-o $(EXEC) $(OPTIONSCXX)

tests: bin Mat.o perftests.o
	$(CXX) $(BINDIR)Mat.o $(BINDIR)perftests.o \
	-o perftests $(OPTIONSCXX)

### bin folder (created only if it doesnt exist)
bin:
	mkdir -p ./bin/

%.o: $(SRCDIR)%.cpp
	$(CXX) -c $< -o $(BINDIR)$@ $(OPTIONSCXX) $(DECLRDIR)

main.o: $(SRCDIR)multimat.cpp
Mat.o: $(SRCDIR)Mat.cpp
perftests.o: $(SRCDIR)perftests.cpp


### clear objects & executable
clean: bin
	$(DEL) ./$(EXEC)
	$(DEL) $(BINDIR)*.o
