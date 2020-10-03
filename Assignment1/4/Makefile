#this is soemthing makefile and most important...
# for getting separate object file we have to compile them separately...

INSTDIR=/home/kapil/Desktop/COP_290/Top/obj
all: function4

function4: function4.c
	g++ -c -Wall function4.c -o func4
install: function4
	mv func4 $(INSTDIR)


clean:
	rm -rf func
	rm -rf *.exe
	rm -rf *.o
