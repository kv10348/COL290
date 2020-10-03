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
char* func_sub_final(char*, char*);
char* func_sub_final(char* token1, char* token2){
        if(token1[0]=='-' && token2[0]=='-'){
            char *ret=func_sub(token1,token2);
            return ret;
        }else if(token1[0]=='-' && token2[0]!='-'){
            int length1=strlen(token1);
            char a[length1-1];
            for(int i=0;i<length1;i++){
                    a[i]=token1[i+1];}
            a[length1]='\0';
           
            char *ret=func_add(token2,a,false);
            return ret;
            

            }else if(token1[0]!='-' && token2[0]=='-'){
                    int length2=strlen(token2);
                    char b[length2-1];
                    for(int i=0;i<length2;i++){
                        b[i]=token2[i+1];
                    }
                    b[length2]='\0';
                  
                    func_start(token1,b);

               }else{
                   char *radhe=func_sub(token1,token2);
                   return radhe;
               }
}
char* func_sub(char *inp1, char *inp2){
        char *radhe;
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
        int size_inp1= strlen(token1[0]);
        int size_inp2=strlen(token2[0]);
        int size_inp3= strlen(token1[1]);
        int size_inp4=strlen(token2[1]);
        int k=MAX(size_inp1,size_inp2);
        int k1=MAX(size_inp3,size_inp4);
        
        if(strcmp(token1[1],"0")==0 && strcmp(token2[1], "0")==0){
            
            func_sub_int(token1[0],token2[0],0,0);
            
            if(final[0]==-1){
           
                func_sub_int(token2[0],token1[0],0,0);
                int ind=0;
                for(int i=0;i<(k+1);i++){
                    if(final[i]!=0){
                        ind=i;
                        break;
                    }
                }
                radhe = (char*)malloc (sizeof (char) * (k+2-ind));
                radhe[0]='-';
              
                for(int i=ind;i<(k+1);i++){
                    radhe[i-ind+1]=(final[i]+'0');
                   
                }
                radhe[k+2-ind]='\0';
                return radhe;
            }else{
               
                int ind=0;
                for(int i=0;i<(k+1);i++){
                    if(final[i]!=0){
                        ind=i;
                        break;
                    }
                    ind=i;
                } 
                radhe = (char*)malloc (sizeof (char) * (k+1-ind));
                for(int i=ind;i<(k+1);i++){ 
                    radhe[i-ind]=(final[i]+'0'); 
                  
                }
                radhe[k+1-ind]='\0';
                return radhe;
            }
         
        }else{
            
            func_sub_int(token1[1],token2[1],0,1);
            int temp[k1+1];

            int t=(k1);
            for(int i=(k1);i>=0;i--){
                if(final[i]!=0){
                   
                    t=i;
                    break;
                    }
                    t=i;
                }
            if(t!=0){
                flag=true;
                for(int i=0;i<=(t);i++){
                    temp[i]=final[i];
                    }
            }
            if(final[0]==-1){
                func_sub_int(token1[0],token2[0],-1,0);
            }else{
                func_sub_int(token1[0],token2[0],0,0);
            }
            if(final[0]==-1){
              
                flag=false;
                func_sub_int(token2[1],token1[1],0,1);
               
                t=k1;
                for(int i=k1;i>=0;i--){
                    if(final[i]!=0){
                        t=i;
                        break;
                    }
                    t=i;
                }
                flag=false;
                if(t!=0){
                   
                    flag=true;
                    for(int i=0;i<=(t);i++){
                       
                        temp[i]=final[i];

                    }
                }
              
                
                if(final[0]==-1){
                func_sub_int(token2[0],token1[0],-1,0);
                }else{
                func_sub_int(token2[0],token1[0],0,0);
                }
            
                int ind=0;
            for(int i=0;i<(k+1);i++){
                if(final[i]!=0){
                    ind=i;
                    break;
                }
                ind=i;
            }
            radhe = (char*)malloc (sizeof (char) * (k-ind+t+3));
            radhe[0]='-';
            for(int i=ind;i<(k+1);i++){
                radhe[1+i-ind]=final[i]+'0';
               
            }
            
            
            if(flag){
              
                radhe[1+k+1-ind]='.';
            for(int i=1;i<=(t);i++){
                radhe[2+k-ind+i]=temp[i]+'0';
                
            }
            radhe[k+3-ind+t]='\0';
            }else{
                radhe[k+1]='\0';
            }
            return radhe;
            }else{
              
            int ind=0;
            for(int i=0;i<(k+1);i++){
                if(final[i]!=0){
                    ind=i;
                    break;
                }
                ind=i;
            }
            radhe = (char*)malloc (sizeof (char) * (k+1-ind+t+1));
            for(int i=ind;i<(k+1);i++){
                radhe[i-ind]=final[i]+'0';
               
            }
            
            
            if(flag){
                radhe[k+1-ind]='.';
              
            for(int i=1;i<=(t);i++){
                radhe[k+1+i-ind]=temp[i]+'0';
               
            }
            radhe[k+2-ind+t]='\0';
            }else{
                radhe[k+1]='\0';
            }

                return radhe;
            }
            
            
          
        }


    
}

void func_sub_int(char *inp1,char *inp2,int carry, int a){
        int sub;
         sub=0;
        int size_inp1=strlen(inp1);
        int size_inp2=strlen(inp2);
        int maximum=MAX(size_inp1,size_inp2);
        for(int i=0;i<(maximum+1);i++){
            final[i]=0;
        }
        if(a==1){
        if(size_inp1<size_inp2){
            char inp3[size_inp2];
            strcpy(inp3,inp1);
            for(int i=size_inp1;i<size_inp2;i++){
                inp3[i]='0';
            }
            for(int i=(size_inp2-1);i>=0;i--){

                sub=  (int)(inp3[i]-48) -(int )(inp1[i]-48)+carry;
                if(sub<0){
                    sub=abs(sub+10);
                    carry=-1;
                }else{
                    carry=0;
                }
               
                final[i+1]=sub;
            }
            final[0]=carry;
           
        }else {
            
            char inp3[size_inp1];
            strcpy(inp3,inp2);
            for(int i=size_inp2;i<size_inp1;i++){
                inp3[i]='0';
            }
            for(int i=(size_inp1-1);i>=0;i--){

                sub=  (int)(inp1[i]-48+carry) -(int )(inp3[i]-48);
                if(sub<0){
                   
                    sub=abs(sub+10);
                    carry=-1;
                }else{
                    carry=0;
                }
               
                final[i+1]=sub;
            }
            final[0]=carry;

        }
        }else{
            if(size_inp1<size_inp2){
                char inp3[size_inp2];
                int k=(size_inp1-1);
                for(int i=(size_inp2-1);i>=0;i--){
                    if(k>=0){
                         inp3[i]=inp1[k];
                         k--;
                    }else{
                        inp3[i]='0';
                    }
                }
                for(int i=(size_inp2-1);i>=0;i--){

                sub=  (int)(inp3[i]-'0'+carry) -(int )(inp2[i]-'0');
               
                if(sub<0){
                    sub=abs(sub+10);
                    carry=-1;
                }else{
                    carry=0;
                }
               
                final[i+1]=sub;
                }
                final[0]=carry;
           
        }else{
            
            char inp3[size_inp1];      
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

                sub=  (int)(inp1[i]-48) -(int )(inp3[i]-48)+carry;
                if(sub<0){
                    sub=abs(sub+10);
                    carry=-1;
                }else{
                    carry=0;
                }
               
                final[i+1]=sub;
            }
            final[0]=carry;


        }

}
}