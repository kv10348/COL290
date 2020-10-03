#this is soemthing makefile and most important...
# for getting separate object file we have to compile them separately...

INSTDIR=/home/kapil/Desktop/COP_290/Top/obj
all: myPythonlnC
myPythonlnC: myPythonlnC.c
	g++ -c -Wall myPythonlnC.c -o func2 -I/usr/include/python3.6m
install: myPythonlnC
	mv func2 $(INSTDIR)


clean:
	rm -rf func2
	rm -rf *.exe
	rm -rf *.o
