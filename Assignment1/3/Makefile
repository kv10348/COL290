#this is soemthing makefile and most important...
# for getting separate object file we have to compile them separately...

INSTDIR=/home/kapil/Desktop/COP_290/Top/obj
all: function3

function3: function3.c
	g++ -c -Wall function3.c -o func3
install: function3
	mv func3 $(INSTDIR)


clean:
	rm -rf func
	rm -rf *.exe
	rm -rf *.o
