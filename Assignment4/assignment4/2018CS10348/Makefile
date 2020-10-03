all:
	gcc -c add.c -L/usr/include -lreadline
	gcc -c sub.c -L/usr/include -lreadline
	gcc -c mult.c -L/usr/include -lreadline
	gcc -c div.c -L/usr/include -lreadline
	gcc -c abs.c -L/usr/include -lreadline
	gcc -c absolute.c -L/usr/include -lreadline
	gcc -c sqrt.c -L/usr/include -lreadline
	ar rs libarbprecision.a add.o sub.o mult.o div.o abs.o absolute.o sqrt.o
	gcc -c ronaldo.c -L/usr/include -lreadline
	gcc -o main ronaldo.o libarbprecision.a
	
	
	
	
	
	
clean:
	
	rm -rf *.exe
	rm -rf *.o
