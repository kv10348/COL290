#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "basic.h"

char* absolute(char *inp){

      
        int sizex=strlen(inp);
        int i=0;
        bool isfloat=false;
        int dp=0;
        for(i=0; i<sizex; i++){
                if(inp[i]=='.'){
                dp=i;
                isfloat=true;
                break;
          }
        }
        if(isfloat==true){
                i=0;
                for(i=sizex; i<=dp+20; i++){
                inp[i]='0';
          }
          inp[i]='\0';
     }
     else{
          inp[sizex]='.';
          i=0;
          for(i=sizex+1; i<=sizex+21; i++){
               inp[i]='0';
          }
          inp[i]='\0';
     }
        int len1=strlen(inp);
        char* x=(char*)(malloc(sizeof(char)*len1));
        strcpy(x,inp);

        char* y=(char*)(malloc(sizeof(char)*len1));
        y[0]='1';
        y[1]='\0';
        char e[21];
        e[0]='0';
        e[1]='.';
        for(i=2; i<20; i++){
          e[i]='0';
        }
        e[i]='1';
        e[i+1]='\0';
        char two[2];
        two[0]='2';
        two[1]='\0';
   
       int count=0;
        char c[strlen(inp)];
       while(count<400){
               char xtemp[len1];
               char ytemp[len1];
               char xtemp1[len1];
               char ytemp1[len1];
               for(int i=0;i<len1;i++){
                       xtemp[i]=x[i];
                       ytemp[i]=y[i];
                       xtemp1[i]=x[i];
                       ytemp1[i]=y[i];
               }
               xtemp[len1]='\0';
               ytemp[len1]='\0';
               xtemp1[len1]='\0';
               ytemp1[len1]='\0';
               char *xy=(char*)(malloc(sizeof(char)*len1));
               strcpy(xy,func_sub_final(xtemp,ytemp));
               char *f1=(char*)(malloc(sizeof(char)*strlen(e)));
               strcpy(f1,e);
               char *f=func_sub_final(xy,f1);
               
               if(f[0]=='-'){
                       break;
               }
      
               char xplusy[len1];
            
               strcpy(xplusy,func_start(xtemp1,ytemp1));
            
               char xplusydiv2[len1];
               strcpy(xplusydiv2,func_div_final(xplusy,two));
               xplusydiv2[len1]='\0';
              
               strcpy(x,xplusydiv2);
             
               char xarr[len1];
               strcpy(xarr,x);
              
               int i=0;
                for(i=0;i<strlen(inp);i++){
                        c[i]=inp[i];
                }
                c[i]='\0';
                
                char *ndivxarr=(char*)(malloc(sizeof(char)*len1));
               
                strcpy(ndivxarr,func_div_final(c,xarr));
                i=0;
                int ndivxarrlen=strlen(ndivxarr);
                for(i=0; i<len1; i++){
                        y[i]=ndivxarr[i];
                }
                y[i]='\0';
               


       }
     
        return x;




     
}