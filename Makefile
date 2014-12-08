BISON	= bison -d -v
FLEX	= flex
CC		= gcc
CXX		= g++
FLAGS   = # add the -g flag to compile with debugging output for gdb
TARGET	= lang

OBJS = ast.o parser.o lexer.o symbol.o codegen.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

lexer.o: lexer.l
	$(FLEX) -o lexer.cpp lexer.l
	$(CXX) $(FLAGS) -c -o lexer.o lexer.cpp

parser.o: parser.y
	$(BISON) -o parser.cpp parser.y
	$(CXX) $(FLAGS) -c -o parser.o parser.cpp

genast: ast.cpp

ast.cpp:
	python3 genast.py -i lang.def -o ast

ast.o: ast.cpp ast.hpp
	$(CXX) $(FLAGS) -c -o ast.o ast.cpp
	
symbol.o: symbol.cpp symbol.hpp
	$(CXX) $(FLAGS) -c -o symbol.o symbol.cpp

codegen.o: codegeneration.cpp codegeneration.hpp
	$(CXX) $(FLAGS) -c -o codegen.o codegeneration.cpp

main.o: main.cpp
	$(CXX) $(FLAGS) -c -o main.o main.cpp

.PHONY: clean
clean:
	rm -f *.o lexer.cpp parser.cpp parser.hpp ast.hpp ast.cpp parser.output generated-output.txt output.txt $(TARGET)
	rm -f tests/*.s tests/*.c

.PHONY: run
run: $(TARGET)
	@python3 run.py

.PHONY: compare
compare: $(TARGET)
	@ python3 run.py > generated-output.txt
	- diff generated-output.txt expected-output.txt
	@ rm -f generated-output.txt
