#include <stdio.h>
#include "function.h"



extern int mySquare();
extern int myPythonInC();
int main(int argc, char	*argv[]){
start();
int a=3,b;
b=mySquare(a);
printf("%d\n",b);
myPythonInC(1,argv);
end();
}




