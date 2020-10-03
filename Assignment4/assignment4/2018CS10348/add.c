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
char* func_start(char*, char*);
char* func_start(char *token1, char *token2){
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
                    
                   char *ret=func_add(a,b, false);
                   return ret;
               }else if(token1[0]=='-' && token2[0]!='-'){
                    int length1=strlen(token1);
                    char a[length1-1];
                    for(int i=0;i<length1;i++){
                        a[i]=token1[i+1];
                    }
                    a[length1]='\0';
                  
                    char *ret=func_sub_final(token2,a);
                    return ret;

               }else if(token1[0]!='-' && token2[0]=='-'){
                    int length2=strlen(token2);
                    char b[length2-1];
                    for(int i=0;i<length2;i++){
                        b[i]=token2[i+1];
                    }
                    b[length2]='\0';
                  
                    char *ret=func_sub_final(token1,b);
                    return ret;

               }else{
                       
                       
                        char *radhe=func_add(token1,token2,true);
                     
                        return radhe;
               }
}









void func_add_int(char *inp1, char *inp2,int a,int carry){
       
        int sum=0;
        
    
        int size_inp1= strlen(inp1);
        int size_inp2=strlen(inp2);
        int k=MAX(size_inp1,size_inp2);
        if(a==1){
            if(size_inp1<size_inp2){
            char inp3[size_inp2]; 
            strcpy(inp3,inp1);
            for(int i=size_inp1;i<size_inp2;i++){
                inp3[i]='0';
            }
            for(int i=(size_inp2-1);i>=0;i--){
                sum=  (int)(inp2[i]-48) +(int )(inp3[i]-48)+carry;
                if(sum>=10){
                    carry=1;
                    sum=sum-10;
                }else{
                    carry=0;
                }
                final[i+1]=sum;
            }
            final[0]=carry;
            }else if(size_inp2<size_inp1){
            char inp3[size_inp1];
            /*for(int i=0;i<(size_inp1+1);i++){
                final[i]=0;
            }*/
            strcpy(inp3,inp2);
            for(int i=size_inp2;i<size_inp1;i++){
                inp3[i]='0';
            }
            for(int i=(size_inp1-1);i>=0;i--){
                sum=  (int)(inp1[i]-48) +(int )(inp3[i]-48)+carry;
                if(sum>=10){
                    carry=1;
                    sum=sum-10;
                }else{
                    carry=0;
                }  
                final[i+1]=sum;
            } 
            final[0]=carry;  
            }else{
               
                for(int i=(size_inp1-1);i>=0;i--){
                sum=  (int)(inp1[i]-48) +(int )(inp2[i]-48)+carry;
                if(sum>=10){
                    carry=1;
                    sum=sum-10;
                }else{
                    carry=0;
                }  
                final[i+1]=sum;
                } 
            final[0]=carry; 
            
            
            }
        }else{
            if(size_inp1<size_inp2){
               
                char inp3[size_inp2];
                /*for(int i=0;i<(size_inp2+1);i++){
                    final[i]=0;
                }*/
                int k=(size_inp1-1);
                for(int i=(size_inp2-1);i>=0;i--){
                    if(k>=0){
                         inp3[i]=inp1[k];
                         k--;
                    }else{
                        inp3[i]='0';;
                    }
                }
                for(int i=(size_inp2-1);i>=0;i--){
                sum=  (int)(inp2[i]-48) +(int )(inp3[i]-48)+carry;
                if(sum>=10){
                    carry=1;
                    sum=sum-10;
                }else{
                    carry=0;
                }
                final[i+1]=sum;
            }
            final[0]=carry;
            }else{
                char inp3[k];
                int k=(size_inp2-1);
                for(int i=(size_inp1-1);i>=0;i--){
                    if(k>=0){
                         inp3[i]=inp2[k];
                         k--;
                    }else{
                        inp3[i]='0';
                    }
                }
                for(int i=(size_inp1-1);i>=0;i--){
                sum=  (int)(inp1[i]-48) +(int )(inp3[i]-48)+carry;
              
                if(sum>=10){
                    carry=1;
                    sum=sum-10;
                }else{
                    carry=0;
                }
                
                final[i+1]=sum;
            }
           
            final[0]=carry;
            }
    }       
}
    




 char* func_add(char *inp1, char *inp2,bool neg){
        char *radhe;
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
        int size_inp1= strlen(token1[0]);
        int size_inp2=strlen(token2[0]);
        int size_inp3= strlen(token1[1]);
        int size_inp4=strlen(token2[1]);
        int k=MAX(size_inp1,size_inp2);
        int k1=MAX(size_inp3,size_inp4);
        if(strcmp(token1[1],"0")==0 && strcmp(token2[1], "0")==0){
            func_add_int(token1[0],token2[0],0,0);
            int r=0;
            for(int i=0;i<(k+1);i++){
               if(final[i]!=0){
                   r=i;
                   break;
               }
               r=i;
            }
            if(neg==true){
            radhe = (char*)malloc (sizeof (char) * (k+1-r));
            for(int i=r;i<(k+1);i++){
                radhe[i-r]=(final[i]+'0');
                }
            radhe[k+1-r]='\0';
            }else{
                radhe = (char*)malloc (sizeof (char) * (k+1-r+1));
                radhe[0]='-';
                for(int i=r;i<(k+1);i++){
                radhe[i-r+1]=(final[i]+'0');
                }
            radhe[k+1-r+1]='\0'; 
            }
        }else{
            bool flag=false;
            int r=0;
            func_add_int(token1[1],token2[1],1,0);
            int temp[k1+1];
            int j=k1;
            for(int i=k1;i>=0;i--){
                if(final[i]!=0){
                    j=i; 
                    break;
                }
                j=i;
            }
            if(j!=0){
                flag = true;
            for(int i=0;i<=(j);i++){
                temp[i]=final[i];
               
            }
            }
          
           
            if(final[0]==1){
                func_add_int(token1[0],token2[0],0,1);
            }else{
               
                func_add_int(token1[0],token2[0],0,0);
            }
           
            for(int i=0;i<(k+1);i++){
               if(final[i]!=0){
                   r=i;
                   break;
               }
               r=i;
            }
            if(neg==true){
                 radhe = (char*)malloc (sizeof (char) * (k-r+j+2));
                for(int i=r;i<(k+1);i++){
                radhe[i-r]=(final[i]+'0');
                }
                if(flag){
                radhe[k+1-r]='.';
                for(int i=1;i<=(j);i++){
                radhe[k+i+1-r]=(temp[i]+'0');
                }
                }
                radhe[k+2-r+j]='\0';
            }else{
                 radhe = (char*)malloc (sizeof (char) * (k-r+j+2+1));
                 radhe[0]='-';
                for(int i=r;i<(k+1);i++){
                radhe[i-r+1]=(final[i]+'0');
                }
                if(flag){
                radhe[k+1-r+1]='.';
                for(int i=1;i<=(j);i++){
                radhe[k+i+1-r+1]=(temp[i]+'0');
                }
                }
                radhe[k+2-r+j+1]='\0';
            }
               
        } 
        return radhe;
    }