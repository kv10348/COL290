#include<stdio.h> 
#include<string.h> 
#include <stdbool.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 
#include "basic.h"
#define MAX(a,b) ((a) > (b) ? (a) : (b));
 int final[100000];
char* func_mult_start(char *token1, char *token2){
      if(token1[0]=='-' && token2[0]=='-'){
                    int length1=strlen(token1);
                    int length2=strlen(token2);
                    char a[length1-1];
                    char b[length2-1];
                    for(int i=0;i<length1;i++){
                        a[i]=token1[i+1];
                    }
                    for(int i=0;i<length2;i++){
                        b[i]=token2[i+1];
                    }
                    a[length1]='\0';
                    b[length2]='\0';
                   char *f=func_mult_final(a,b,true);
                   return f;
                   
               }else if(token1[0]=='-' && token2[0]!='-'){
                    int length1=strlen(token1);
                    char a[length1-1];
                    for(int i=0;i<length1;i++){
                        a[i]=token1[i+1];
                    }
                    a[length1]='\0';
                    char *f=func_mult_final(a,token2,false);
                    return f;
               }else if(token1[0]!='-' && token2[0]=='-'){
                    int length2=strlen(token2);
                    char b[length2-1];
                    for(int i=0;i<length2;i++){
                        b[i]=token2[i+1];
                    }
                    b[length2]='\0';
                    char *f=func_mult_final(token1,b,false);
                    return f;
               }else{
                    char *f=func_mult_final(token1,token2,true);
                    return f;
               }
            }







 void func_mult(char *inp1, int inp2,char *final2,int a,int length){
       
       int size_inp=strlen(inp1);
        int sum=0;
        int carry=0;
        int k=0;
       
        for(int i=(size_inp-1);i>=0;i--){
            sum=(int)(inp1[i]-'0')*(inp2)+carry;
            if(sum>=10){
                carry=sum/10;
                sum=sum%10;
            
            }else{
                carry=0;
            }
            k++;
            final2[length-k-a]=(sum+'0');
          
            
        } 
        final2[length-k-1-a]=(carry+'0');

        
      

     

    }
    
    char* func_mult_final(char *inp1, char *inp2,bool neg){
        char* radhe;
        bool flag=false;
        char *p=strtok(inp1,".");
        char *token1[2];
        int i=0;
        token1[1]="0";
        while(p!=NULL){
            token1[i]=p;
            p=strtok(NULL, ".");
            i++;
        } 
        char *q=strtok(inp2,".");
        char *token2[2];
        token2[1]="0";
        i=0;
        while(q!=NULL){
            token2[i]=q;
            q=strtok(NULL, ".");
            i++;
        }
        
       if(strcmp(token1[1],"0")==0 && strcmp(token2[1],"0")==0){
        int a=strlen(inp1);
        int b=strlen(inp2);
        int c=a+b;
        char final1[c];
        char final2[c];
        for(int i=0;i<c;i++){
            final[i]=0;
            final1[i]='0';
            final2[i]='0';
        }
        final[c]='\0';
        final1[c]='\0';
        final2[c]='\0';
           flag =false;
        for(int i=(b-1);i>=0;i--){
            int a=(int)(inp2[i]-'0');
            func_mult(inp1, a,final2,(b-i-1), c);
            func_add_int(final1,final2,0,0);
            
            
            for(int i=0;i<(c);i++){
            final2[i]='0';
            final1[i]=(final[i+1]+'0');
            }
            final2[c]='\0';
        } 
        int j=0;
                for(int i=0;i<c;i++){
                    if(final1[i]!='0'){
                    j=i;
                    break;
                    }
                    j=i;
                }
                if(neg==true){
                radhe = (char*)malloc (sizeof (char) * (c-j));
                for(int i=j;i<c;i++){
                    radhe[i-j]=(final1[i]);
                   
                }
                radhe[c-j]='\0';
                return radhe;
                }else
                {
                radhe = (char*)malloc (sizeof (char) * (c-j+1));
                radhe[0]='-';
                for(int i=j;i<c;i++){
                    radhe[i-j+1]=(final1[i]); 
                }
                radhe[c-j+1]='\0';
                return radhe;
                }
                
       }else{
          
           if(strcmp(token1[1],"0")!=0 && strcmp(token2[1],"0")!=0){
            int a=strlen(inp1);
            int b=strlen(inp2);
            b=b+strlen(token2[1]);
            a=a+strlen(token1[1]);
            char inp_chn1[a];
            char inp_chn2[b];
            strcpy(inp_chn1,token1[0]);
            strcat(inp_chn1,token1[1]);
            strcpy(inp_chn2,token2[0]);
            strcat(inp_chn2,token2[1]);
            int c=a+b;
            char final1[c];
            char final2[c];
            for(int i=0;i<(c);i++){
            final[i]=0;
            final1[i]='0';
            final2[i]='0';
            }
            final[c]='\0';
            final1[c]='\0';
            final2[c]='\0';
           flag=true;
           int k=c-strlen(token2[1])-strlen(token1[1]);
                for(int i=(b-1);i>=0;i--){
                int a=(int)(inp_chn2[i]-'0');
                func_mult(inp_chn1, a,final2,(b-i-1), c);
                func_add_int(final1,final2,0,0);
                for(int i=0;i<(c);i++){
                final2[i]='0';
                final1[i]=(final[i+1]+'0');
                }
                final2[c]='\0';
                } 

                int j=0;
                for(int i=0;i<c;i++){
                    if(final1[i]!='0'){
                    j=i;
                    break;
                    }
                    j=i;
                }
                k=k-j;
                int kade=j;
                if(neg==true){
                radhe = (char*)malloc (sizeof (char) * (c-kade+1));  
                int counter=0;          
                while(j<c){
                    if(counter==(k)){
                        radhe[counter]='.';
                        k=0;
                        counter++;
                    }else{
                        radhe[counter]=(final1[j]);
                        j++; 
                        counter++;
                    }
                }
                radhe[c-kade+1]='\0';
                return radhe;
                }else{
                    radhe = (char*)malloc (sizeof (char) * (c-kade+1+1));
                    radhe[0]='-';  
                int counter=1;          
                while(j<c){
                    if(counter==(k+1)){
                      
                        radhe[counter]='.';
                        k=0;
                        counter++;
                    }else{
                      
                        radhe[counter]=(final1[j]);
                        j++; 
                        counter++;
                    }
                }
                radhe[c-kade+1+1]='\0'; 
                return radhe;

                }
           }else if(strcmp(token1[1],"0")==0 && strcmp(token2[1],"0")!=0){
            int a=strlen(inp1);
            int b=strlen(inp2);
            char inp_chn2[b-1];
            strcpy(inp_chn2,token2[0]);
            strcat(inp_chn2,token2[1]);
            b=b+strlen(token2[1]);
            int c=a+b;
            char final1[c];
            char final2[c];
            for(int i=0;i<(c);i++){
            final[i]=0;
            final1[i]='0';
            final2[i]='0';
            }
            final[c]='\0';
            final1[c]='\0';
            final2[c]='\0';
           flag=true;
          
           int k=c-strlen(token2[1]);
            for(int i=(b-1);i>=0;i--){
                int a=(int)(inp_chn2[i]-'0');
                func_mult(inp1, a,final2,(b-i-1), c);
                func_add_int(final1,final2,0,0);
                for(int i=0;i<(c);i++){
                final2[i]='0';
                final1[i]=(final[i+1]+'0');
            
                }
                final2[c]='\0';
                } 
            int j=0;
                for(int i=0;i<c;i++){
                    if(final1[i]!='0'){
                    j=i;
                    break;
                    }
                    j=i;
                }
                k=k-j;
                int kade=j;
                if(neg==true){
                radhe = (char*)malloc (sizeof (char) * (c-kade+1));  
                int counter=0;    
                while(j<c){
                    if(counter==(k)){
                        radhe[counter]='.';
                        k=0;
                        counter++;
                    }else{
                       radhe[counter]=(final1[j]);
                        j++; 
                        counter++;
                    }
                }
                radhe[c-kade+1]='\0';
                return radhe;
                }else{
                radhe = (char*)malloc (sizeof (char) * (c-kade+1+1));  
                radhe[0]='-';
                int counter=1;    
                while(j<c){
                    if(counter==(k+1)){
                        radhe[counter]='.';
                        k=0;
                        counter++;
                    }else{
                       radhe[counter]=(final1[j]);
                        j++; 
                        counter++;
                    }
                }
                radhe[c-kade+1+1]='\0'; 
                return radhe;
                }
           }else{
            int a=strlen(inp1);
            int b=strlen(inp2);
            char inp_chn1[a-1];
            strcpy(inp_chn1,token1[0]);
            strcat(inp_chn1,token1[1]);
            a=a+strlen(token1[1]);
            int c=a+b;
            char final1[c];
            char final2[c];
            for(int i=0;i<(c);i++){
            final[i]=0;
            final1[i]='0';
            final2[i]='0';
            }
            final[c]='\0';
            final1[c]='\0';
            final2[c]='\0';
           flag=true;
          
           int k=c-strlen(token2[1]);
            for(int i=(b-1);i>=0;i--){
                int a=(int)(inp2[i]-'0');
                func_mult(inp_chn1, a,final2,(b-i-1), c);
                func_add_int(final1,final2,0,0);         
                for(int i=0;i<(c);i++){
                final2[i]='0';
                final1[i]=(final[i+1]+'0');            
                }
                final2[c]='\0';            
                } 
            int j=0;
                for(int i=0;i<c;i++){
            
                if(final1[i]!='0'){
                j=i;
                break;
                }
                j=i;
                }
                k=k-j;
                int kade=j;
                if(neg==true){
                radhe = (char*)malloc (sizeof (char) * (c-kade+1));  
                int counter=0;          
                while(j<c){
                    if(counter==(k)){
                        
                        radhe[counter]='.';
                        k=0;
                        counter++;
                    }else{
                      
                        radhe[counter]=(final1[j]);
                        j++; 
                        counter++;
                    }
                }
                radhe[c-kade+1]='\0';
                return radhe;
                }else{
                    radhe = (char*)malloc (sizeof (char) * (c-kade+1+1));  
                    int counter=1;
                    radhe[0]='-';  
                    while(j<c){
                        if(counter==(k+1)){
                            radhe[counter]='.';
                            k=0;
                            counter++;
                        }else{
                            radhe[counter]=(final1[j]);
                            j++; 
                            counter++;
                        }
                    }
                    radhe[c-kade+2]='\0';
                    return radhe;
                }
           }

       }
        return radhe;

    }
