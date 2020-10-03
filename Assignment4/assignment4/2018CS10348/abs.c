#include<stdio.h> 
#include<string.h> 
#include <stdbool.h>
#include<stdlib.h> 
#include "basic.h"
char* func_abs(char *inp){
        int length=strlen(inp);
        char *final;
	    if(inp[0]=='-'){
            final = (char*)malloc (sizeof (char) * (length-1));
            for(int i=1;i<length;i++){
                final[i-1]=inp[i];
            }
            final[length-1]='\0';
            printf("%s\n",final);
        }else if(inp[0]=='+'){
                final = malloc (sizeof (char) * (length-1));
                for(int i=1;i<length;i++){
                final[i-1]=inp[i];
            }
            final[length-1]='\0';
        }else{
            final = malloc (sizeof (char) * (length));
            strcpy(final,inp);
        }
        
        
        
        return final;
    }
