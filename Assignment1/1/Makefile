#this is soemthing makefile and most important...
# for getting separate object file we have to compile them separately...
INSTDIR=/home/kapil/Desktop/COP_290/Top/obj
all: mySqr

mySqr: mySqr.c
	g++ -c -Wall mySqr.c -o func1
install: mySqr
	mv func1 $(INSTDIR)


clean:
	rm -rf func1
	rm -rf *.exe
	rm -rf *.o
