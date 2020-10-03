#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "basic.h"

char* square_root(char *inp,FILE* output){
            char* radhe=(char*)(malloc(sizeof(char)*(strlen(inp))));
            char *p=strtok(inp,",");
            char *token1[2];
            int i=0;
            while(p!=NULL){
            token1[i]=p;
            p=strtok(NULL, ",");
            i++;
                }
          
            int len11=strlen(token1[0]);
            char inp11[len11-1];
            for(int i=0;i<(len11-1);i++){
                inp11[i]=token1[0][i+1];
            }
            inp11[len11-1]='\0';
            int len12=strlen(token1[1]);
            char inp12[len12-1];
            for(int i=0;i<(len12-1);i++){
                inp12[i]=token1[1][i];
            }
            inp12[len12-1]='\0';
        //printf("inp11 %s\n",inp11);
        //printf("inp12 %s\n",inp12);
        char *f1= func_mult_start(inp11,inp11);
        //printf("%s\n", f1);
        char *f2=func_mult_start(inp12,inp12);
       //  printf("%s\n", f2);
        char *f3=func_start(f1,f2);
        // printf("%s\n", f3);
        ///printf("%S\n",f3);
        char *f4=absolute(f3);
        strcpy(radhe,f4);
        fprintf(output, "%s\n",f4);
       // return radhe;
       /// printf("%s\n",f4);

}