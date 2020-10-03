# this is a makefike

all:
	(cd 1; make all)
	(cd 2; make all)
	(cd 3; make all)
	(cd 4; make all)
	g++ -c -Wall myApp.c -o m
	mv m /home/kapil/Desktop/COP_290/Top/obj
	make install
install:
	(cd 1; make install INSTDIR=/home/kapil/Desktop/COP_290/Top/obj)
	(cd 2; make install INSTDIR=/home/kapil/Desktop/COP_290/Top/obj)
	(cd 3; make install INSTDIR=/home/kapil/Desktop/COP_290/Top/obj)
	(cd 4; make install INSTDIR=/home/kapil/Desktop/COP_290/Top/obj)
	(cd obj; g++ func1 func2 func3 func4 m -o final -L/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu -lpython3.6m)
	(cd obj; mv final /home/kapil/Desktop/COP_290/Top/)
	(mv final /home/kapil/Desktop/COP_290/Top/exe )
RUN:
	(cd exe; ./final)	
clean:	
	(cd obj; rm -rf *.o)
	(cd obj; rm -rf func1)
	(cd obj; rm -rf func2)
	(cd obj; rm -rf func3)
	(cd obj; rm -rf func4)
	(cd obj; rm -rf m) 
	(cd exe; rm -rf final)
	
