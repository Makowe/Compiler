
all: clear link 

clear:
	@echo "Clear old Data"
	@rm -r -f bin
	@rm -f scanner/scanner.c
	@rm -f parser/parser.tab.h
	@rm -f parser/parser.tab.c

parser/parser.tab.h: parser/parser.y
	@echo "Generate Parser"
	@bison -d parser/parser.y
	@mv parser.tab.c parser/parser.tab.c
	@mv parser.tab.h parser/parser.tab.h

parser/parser.tab.c: parser/parser.y
	@echo "Generate Parser"
	@bison -d parser/parser.y
	@mv parser.tab.c parser/parser.tab.c
	@mv parser.tab.h parser/parser.tab.h

scanner/scanner.c: scanner/scanner.l parser/parser.tab.h
	@echo "Generate Scanner"
	@flex -t scanner/scanner.l > scanner/scanner.c

compile: scanner/scanner.c parser/parser.tab.c
	@mkdir -p bin
	@gcc -c -o bin/scanner.o scanner/scanner.c
	@gcc -c -o bin/parser.tab.o parser/parser.tab.c
	@gcc -c -o bin/symboltable.o symboltable/symboltable.c
	@gcc -c -o bin/syntaxtree.o syntaxtree/syntaxtree.c
	@gcc -c -o bin/printer.o printer/printer.c
	@gcc -c -o bin/optimizer.o optimizer/optimizer.c
	@echo "Compilation successful"

link: compile
	@gcc bin/scanner.o bin/symboltable.o bin/syntaxtree.o bin/printer.o bin/optimizer.o bin/parser.tab.o -o pl
	@echo "Linking successful.\n\nCall './pl input/filename.pl1 output/filename.pl1' to run the program"