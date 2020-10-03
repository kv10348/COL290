all:
	@gcc -c main.c -o try.o
	@gcc -o plagChecker try.o -lm
	@./plagChecker input.txt ./corpus_files


This is my makefile and if you want to run the program in some other file which does not have names like this then please do change Here!!. 
