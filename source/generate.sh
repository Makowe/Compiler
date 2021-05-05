bison -d parser/parser.y
mv parser.tab.c parser/parser.tab.c
mv parser.tab.h parser/parser.tab.h

flex -t scanner/scanner.l > scanner/scanner.c

gcc -c -o bin/scanner.o scanner/scanner.c
gcc -c -o bin/parser.tab.o parser/parser.tab.c
gcc -c -o bin/symboltable.o symboltable/symboltable.c
gcc -c -o bin/syntaxtree.o syntaxtree/syntaxtree.c

gcc bin/scanner.o bin/symboltable.o bin/syntaxtree.o bin/parser.tab.o -o pl