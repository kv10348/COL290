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
char* func_div_final(char*,char*);
char* func_div_final(char *token1, char *token2){
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
            char *f=func_div(a,b,true);
            return f;
        }else if(token1[0]=='-' && token2[0]!='-'){
            int length1=strlen(token1);
            char a[length1-1];
            for(int i=0;i<length1;i++){
                a[i]=token1[i+1];
            }
            a[length1]='\0';
            
            char *f=func_div(a,token2,false);
            return f;
        }else if(token1[0]!='-' && token2[0]=='-'){
            int length2=strlen(token2);
            char b[length2-1];
            for(int i=0;i<length2;i++){
                b[i]=token2[i+1];
                }
            b[length2]='\0';
            
                  //  func_mult_final(token[1],b);
            char *f=func_div(token1,b,false);
            return f;
        }else{
                  char *f=func_div(token1,token2,true);
                 
                  return f;
    }
}

    char* func_div(char *inp1, char *inp2,bool neg){
        char *radhe;
        char *p1=strtok(inp1,".");
        char *token1[2];
        int u=0;
        token1[1]="**";
        
        while(p1!=NULL){
            token1[u]=p1;
           
            p1=strtok(NULL, ".");
            u++;
        } 
        
        char *q1=strtok(inp2,".");
        char *token2[2];
        token2[1]="**";
        u=0;
        while(q1!=NULL){
            
            token2[u]=q1;
           
            q1=strtok(NULL, ".");
            u++;
        }
        int quo_length;
        if(strcmp(token1[1],"**")==0){
            quo_length=strlen(token1[0])+1+20;
        }else{
            quo_length=strlen(token1[0])+strlen(token1[1])+20+1;
        }
        char quo_ans[quo_length];

        int decimal_length;
        if(strcmp(token2[1],"**")!=0 && strcmp(token1[1],"**")!=0){
          
        decimal_length=strlen(token1[1])-strlen(token2[1])+20;
        int lenght_inp1=strlen(token1[0])+strlen(token1[1]);
        int lenght_inp2=strlen(token2[0])+strlen(token2[1]);
        char quo[strlen(token1[0])+strlen(token1[1])+20];
        char temp[strlen(token1[0])+strlen(token1[1])+1];
        char div[strlen(token2[0])+strlen(token2[1])+1];
        char dividend[strlen(token1[0])+strlen(token1[1])+20];
        char input1[lenght_inp1+20];
        char input2[lenght_inp2];
        strcpy(input1,token1[0]);
        strcat(input1,token1[1]);
        strcpy(input2,token2[0]);
        strcat(input2,token2[1]);
        div[0]='0';
        for(int i=0;i<(lenght_inp1+20);i++){
            quo[i]='0';
        }
        quo[lenght_inp1+20]='\0';
        for(int i=0;i<(lenght_inp2+1);i++){
            temp[i]='0';
            if(i==0){
                div[i]='0';
            }else{
                div[i]=input2[i-1];
            }
            
        }
        div[lenght_inp2+1]='\0';
        temp[lenght_inp2+1]='\0';
            for(int i=0;i<(lenght_inp1+20);i++){
            if(i<lenght_inp1){
                dividend[i]=input1[i];
            }else{
                dividend[i]='0';
            }
            
        }
        dividend[lenght_inp1+20]='\0';
        int k=0;
        int i=0;
        int q=0;
       while(k<(lenght_inp1+20)){
            sign_extend(temp,dividend[k],true);
            k++;
            func_sub_int(temp,div,0,0);
            int tempu=(int)(quo[q]-'0')+1;
            quo[q]=(char)(tempu+'0');
            if(final[0]==-1){
                int mun=(int)(quo[q]-'0');
                quo[q]=(char)(mun-1+'0');
                q++;
                // sign_extend(temp,inp1[k],true);
            }else{
                
                int mun=(int)(quo[q]-'0');
                quo[q]=(char)(mun-1+'0');
               // q++;
                
                   
                    int tempu=(int)(quo[q]-'0')+1;
                    for(int i=0;i<(lenght_inp2+1);i++){
                        temp[i]=(char)(final[i+1]+'0');

                    }
                    while(final[0]!=-1){
                    func_sub_int(temp, div,0,0);
                    if(final[0]!=-1){
                    for(int i=0;i<(lenght_inp2+1);i++){
                         temp[i]=(char)(final[i+1]+'0');
                     }
                    }
                     temp[lenght_inp2+1]='\0';
                     tempu=(int)(quo[q]-'0')+1;
                     quo[q]=(char)(tempu+'0');
                    
                    }
                    q++;
              
            }
        }

         int k1=0;
        int k2=quo_length-2;
        int k3=quo_length-1;
         quo_ans[quo_length]='\0';
        while(k2>=0){
            k1++;
          

            if(k1==(decimal_length+2)){
                
                quo_ans[k3]='.';
                k3--;
            }else if(k1>decimal_length){
                quo_ans[k3]=quo[k2];
                k2--;
                k3--;
            }else if(k1<decimal_length){
                quo_ans[k3]=quo[k2];
                k2--;
                k3--;
            }

            
            
        }
        int start=0;
        for(int i=0;i<quo_length;i++){
            if(quo_ans[i]!='0'){
                start=i;
                break;
            }
            start=i;
        }
        int end=quo_length;
        for(int i=end-1;i>=0;i--){
            if(quo_ans[i]!='0'){
                if(quo_ans[i]=='.'){
                end=i-1;
                }else{
                    end=i;
                }
                break;
               
            }
            end=i;
        }
        if(neg==true){
           
        if(quo_ans[start]=='.'){
        radhe=(char*)(malloc(sizeof(char)*(end+1-start+1)));
        radhe[0]='0';
        for(int i=start;i<=end;i++){
        radhe[i-start+1]=quo_ans[i];
        }
        }else{
        radhe=(char*)(malloc(sizeof(char)*(end+1-start)));
       // radhe[0]='0';
        for(int i=start;i<=end;i++){
        radhe[i-start]=quo_ans[i];
        } 
        }

        }else{

        if(quo_ans[start]=='.'){
        radhe=(char*)(malloc(sizeof(char)*(end+1-start+1+1)));
        radhe[0]='-';
          radhe[1]='0';
        for(int i=start;i<=end;i++){
        radhe[i+1-start+1]= quo_ans[i];
        }}else{
        radhe=(char*)(malloc(sizeof(char)*(end+1-start+1)));
        radhe[0]='-';
         // radhe[1]='0';
        for(int i=start;i<=end;i++){
        radhe[i-start+1]= quo_ans[i];
        }

        }




        }
        return radhe;
       

        }else if(strcmp(token1[1],"**")!=0 && strcmp(token2[1],"**")==0){
       
        decimal_length=strlen(token1[1])+20;
        int lenght_inp1=strlen(token1[0])+strlen(token1[1]);
        int lenght_inp2=strlen(token2[0]);
        char quo[strlen(token1[0])+strlen(token1[1])+20];
        char temp[strlen(token1[0])+strlen(token1[1])+1];
        char div[strlen(token2[0])];
        char dividend[strlen(token1[0])+strlen(token1[1])+20];
        char input1[lenght_inp1+20];
        char input2[lenght_inp2];
        strcpy(input1,token1[0]);
        strcat(input1,token1[1]);
        strcpy(input2,token2[0]);
        //strcat(input2,token2[1]);
        div[0]='0';
        for(int i=0;i<(lenght_inp1+20);i++){
            quo[i]='0';
        }
        quo[lenght_inp1+20]='\0';
        for(int i=0;i<(lenght_inp2+1);i++){
            temp[i]='0';
            if(i==0){
                div[i]='0';
            }else{
                div[i]=input2[i-1];
            }
            
        }
        div[lenght_inp2+1]='\0';
        temp[lenght_inp2+1]='\0';
        for(int i=0;i<(lenght_inp1+20);i++){
            if(i<lenght_inp1){
                dividend[i]=input1[i];
            }else{
                dividend[i]='0';
            }
            
        }
        dividend[lenght_inp1+20]='\0';
        int k=0;
        int i=0;
        int q=0;
        while(k<(lenght_inp1+20)){
            sign_extend(temp,dividend[k],true);
            k++;
            func_sub_int(temp,div,0,0);
            int tempu=(int)(quo[q]-'0')+1;
            quo[q]=(char)(tempu+'0');

            if(final[0]==-1){
                int mun=(int)(quo[q]-'0');
                quo[q]=(char)(mun-1+'0');
                q++;
                // sign_extend(temp,inp1[k],true);
            }else{
                int mun=(int)(quo[q]-'0');
                quo[q]=(char)(mun-1+'0');
               // q++;
                    int tempu=(int)(quo[q]-'0')+1;
                    for(int i=0;i<(lenght_inp2+1);i++){
                        temp[i]=(char)(final[i+1]+'0');

                    }
                    while(final[0]!=-1){
                    func_sub_int(temp, div,0,0);
                    if(final[0]!=-1){
                    for(int i=0;i<(lenght_inp2+1);i++){
                         temp[i]=(char)(final[i+1]+'0');
                     }
                    }                 
                     temp[lenght_inp2+1]='\0';
                     tempu=(int)(quo[q]-'0')+1;
                     quo[q]=(char)(tempu+'0');
                    }
                    q++;
              
            }
            }
            int k1=0;
            int k2=quo_length-2;
            int k3=quo_length-1;
            quo_ans[quo_length]='\0';
          
            while(k2>=0){
            k1++;
            if(k1==(decimal_length+2)){
                quo_ans[k3]='.';
                k3--;
            }else if(k1>decimal_length){
                quo_ans[k3]=quo[k2];
                k2--;
                k3--;
            }else if(k1<decimal_length){
                quo_ans[k3]=quo[k2];
                k2--;
                k3--;
            }

            
            
        }
        int start=0;
        for(int i=0;i<quo_length;i++){
            if(quo_ans[i]!='0'){
                start=i;
                break;
            }
            start=i;
        }
        int end=quo_length;
        for(int i=end-1;i>=0;i--){
            if(quo_ans[i]!='0'){
                if(quo_ans[i]=='.'){
                end=i-1;
                }else{
                    end=i;
                }
                break;
               
            }
            end=i;
        }
        if(neg==true){
            if(quo_ans[start]!='.'){
        radhe=(char*)(malloc(sizeof(char)*(end+1-start)));
        for(int i=start;i<=end;i++){
        radhe[i-start]=quo_ans[i];
        }
        }else{
            radhe=(char*)(malloc(sizeof(char)*(end+1-start+1)));
            radhe[0]='0';
        for(int i=start;i<=end;i++){
        radhe[i-start+1]=quo_ans[i];
        }


        }


        }else{

        if(quo_ans[start]!='.'){
        radhe=(char*)(malloc(sizeof(char)*(end+1-start+1)));
        radhe[0]='-';
        for(int i=start;i<=end;i++){
        radhe[i+1-start]= quo_ans[i];
        }
        }else{
        radhe=(char*)(malloc(sizeof(char)*(end+1-start+2)));
        radhe[0]='-';
        radhe[1]='.';
        for(int i=start;i<=end;i++){
        radhe[i+2-start]= quo_ans[i];
        }
        }
        }
        return radhe;



        }else if (strcmp(token1[1],"**")==0 && strcmp(token2[1],"**")!=0){
           
        decimal_length=-strlen(token2[1])+20;
        int lenght_inp1=strlen(token1[0]);
        int lenght_inp2=strlen(token2[0])+strlen(token2[1]);
        char quo[strlen(token1[0])+20];
        char temp[strlen(token1[0])+1];
        char div[strlen(token2[0])+strlen(token2[1])+1];
        char dividend[strlen(token1[0])+20];
        char input1[lenght_inp1+20];
        char input2[lenght_inp2];
        strcpy(input1,token1[0]);
        //strcat(input1,token1[1]);
        strcpy(input2,token2[0]);
        strcat(input2,token2[1]);
        div[0]='0';
        for(int i=0;i<(lenght_inp1+20);i++){
            quo[i]='0';
        }
        quo[lenght_inp1+20]='\0';
        for(int i=0;i<(lenght_inp2+1);i++){
            temp[i]='0';
            if(i==0){
                div[i]='0';
            }else{
                div[i]=input2[i-1];
            }
            
        }
        div[lenght_inp2+1]='\0';
        temp[lenght_inp2+1]='\0';
        for(int i=0;i<(lenght_inp1+20);i++){
            if(i<lenght_inp1){
                dividend[i]=input1[i];
            }else{
                dividend[i]='0';
            }
            
        }
        dividend[lenght_inp1+20]='\0';
        int k=0;
        int i=0;
        int q=0;
       while(k<(lenght_inp1+20)){
            sign_extend(temp,dividend[k],true);
            k++;
            func_sub_int(temp,div,0,0);
            int tempu=(int)(quo[q]-'0')+1;
            quo[q]=(char)(tempu+'0');
            if(final[0]==-1){
                int mun=(int)(quo[q]-'0');
                quo[q]=(char)(mun-1+'0');
                q++;
                // sign_extend(temp,inp1[k],true);
            }else{
                int mun=(int)(quo[q]-'0');
                quo[q]=(char)(mun-1+'0');
               // q++;
                    int tempu=(int)(quo[q]-'0')+1;
                   
                    for(int i=0;i<(lenght_inp2+1);i++){
                        temp[i]=(char)(final[i+1]+'0');

                    }
                    while(final[0]!=-1){
                    func_sub_int(temp, div,0,0);
                    if(final[0]!=-1){
                    for(int i=0;i<(lenght_inp2+1);i++){
                         temp[i]=(char)(final[i+1]+'0');

                     }
                     
                    }
                     temp[lenght_inp2+1]='\0';
                     tempu=(int)(quo[q]-'0')+1;
                     quo[q]=(char)(tempu+'0');
                    }
                    q++;
              
            }
         }
         int k1=0;
        int k2=quo_length-2;
        int k3=quo_length-1;
         quo_ans[quo_length]='\0';
        while(k2>=0){
            k1++;
          

            if(k1==(decimal_length+2)){
                
                quo_ans[k3]='.';
                k3--;
            }else if(k1>decimal_length){
                quo_ans[k3]=quo[k2];
                k2--;
                k3--;
            }else if(k1<decimal_length){
                quo_ans[k3]=quo[k2];
                k2--;
                k3--;
            }

            
            
        }
        int start=0;
        for(int i=0;i<quo_length;i++){
            if(quo_ans[i]!='0'){
                start=i;
                break;
            }
            start=i;
        }
        int end=quo_length;
        for(int i=end-1;i>=0;i--){
            if(quo_ans[i]!='0'){
                if(quo_ans[i]=='.'){
                end=i-1;
                }else{
                    end=i;
                }
                break;
               
            }
            end=i;
        }
        if(neg==true){
        if(quo_ans[start]!='.'){
        radhe=(char*)(malloc(sizeof(char)*(end+1-start)));
        for(int i=start;i<=end;i++){
        radhe[i-start]=quo_ans[i];
        }
        }else{
        radhe=(char*)(malloc(sizeof(char)*(end+1-start+1)));
        radhe[0]='0';
        for(int i=start;i<=end;i++){
        radhe[i-start+1]=quo_ans[i];
        }
        }
        }else{
        if(quo_ans[start]!='.'){
        radhe=(char*)(malloc(sizeof(char)*(end+1-start+1)));
        radhe[0]='-';
        for(int i=start;i<=end;i++){
        radhe[i+1-start]= quo_ans[i];
        }
        }else{
        radhe=(char*)(malloc(sizeof(char)*(end+1-start+2)));
        radhe[0]='-';
        radhe[1]='0';
        for(int i=start;i<=end;i++){
        radhe[i+2-start]= quo_ans[i];
        }
        }



        }
        return radhe;

        }else{

      
        decimal_length=20;
        int lenght_inp1=strlen(token1[0]);
        int lenght_inp2=strlen(token2[0]);
        char quo[strlen(token1[0])+20];
        char temp[strlen(token1[0])+1];
        char div[strlen(token2[0])+1];
        char dividend[strlen(token1[0])+20];
        char input1[lenght_inp1+20];
        char input2[lenght_inp2];
        strcpy(input1,token1[0]);
        //strcat(input1,token1[1]);
        strcpy(input2,token2[0]);
        //strcat(input2,token2[1]);
        div[0]='0';
        for(int i=0;i<(lenght_inp1+20);i++){
            quo[i]='0';
        }
        quo[lenght_inp1+20]='\0';
        for(int i=0;i<(lenght_inp2+1);i++){
            temp[i]='0';
            if(i==0){
                div[i]='0';
            }else{
                div[i]=input2[i-1];
            }
            
        }
        div[lenght_inp2+1]='\0';
        temp[lenght_inp2+1]='\0';
        for(int i=0;i<(lenght_inp1+20);i++){
            if(i<lenght_inp1){
                dividend[i]=input1[i];
            }else{
                dividend[i]='0';
            }
            
        }
        dividend[lenght_inp1+20]='\0';
        int k=0;
        int i=0;
        int q=0;
       while(k<(lenght_inp1+20)){
            sign_extend(temp,dividend[k],true);
            k++;
           
            func_sub_int(temp,div,0,0);
            int tempu=(int)(quo[q]-'0')+1;
            quo[q]=(char)(tempu+'0');
            

            if(final[0]==-1){
               
                int mun=(int)(quo[q]-'0');
                quo[q]=(char)(mun-1+'0');
                q++;
                
                // sign_extend(temp,inp1[k],true);
            }else{
               
                int mun=(int)(quo[q]-'0');
                quo[q]=(char)(mun-1+'0');
               // q++;
                    int tempu=(int)(quo[q]-'0')+1;
                    for(int i=0;i<(lenght_inp2+1);i++){
                        temp[i]=(char)(final[i+1]+'0');

                    }
                    while(final[0]!=-1){
                    func_sub_int(temp, div,0,0);
                    if(final[0]!=-1){
                    for(int i=0;i<(lenght_inp2+1);i++){
                         temp[i]=(char)(final[i+1]+'0');

                     }
                     
                    }
                     
                     
                     temp[lenght_inp2+1]='\0';
                     tempu=(int)(quo[q]-'0')+1;
                     quo[q]=(char)(tempu+'0');
                     
                    }
                    q++;
              
            }
        }
        int k1=0;
        int k2=quo_length-2;
        int k3=quo_length-1;
         quo_ans[quo_length]='\0';
        while(k2>=0){
            k1++;
          

            if(k1==(decimal_length+2)){
                
                quo_ans[k3]='.';
                k3--;
            }else if(k1>decimal_length){
                quo_ans[k3]=quo[k2];
                k2--;
                k3--;
            }else if(k1<decimal_length){
                quo_ans[k3]=quo[k2];
                k2--;
                k3--;
            }

            
            
        }
        int start=0;
        for(int i=0;i<quo_length;i++){
            if(quo_ans[i]!='0'){
                start=i;
                break;
            }
            start=i;
        }
        int end=quo_length;
        for(int i=end-1;i>=0;i--){
            if(quo_ans[i]!='0'){
                if(quo_ans[i]=='.'){
                end=i-1;
                }else{
                    end=i;
                }
                break;
               
            }
            end=i;
        }
         if(neg==true){
        if(quo_ans[start]!='.'){
        radhe=(char*)(malloc(sizeof(char)*(end+1-start)));
        for(int i=start;i<=end;i++){
        radhe[i-start]=quo_ans[i];
        }
        }else{
        radhe=(char*)(malloc(sizeof(char)*(end+1-start+1)));
        radhe[0]='0';
        for(int i=start;i<=end;i++){
        radhe[i-start+1]=quo_ans[i];
        }


        }

        }else{
        if(quo_ans[start]!='.'){
        radhe=(char*)(malloc(sizeof(char)*(end+1-start+1)));
        radhe[0]='-';
        for(int i=start;i<=end;i++){
        radhe[i+1-start]= quo_ans[i];
        }
        }else{
            radhe=(char*)(malloc(sizeof(char)*(end+1-start+1+1)));
        radhe[0]='-';
        radhe[1]='0';
        for(int i=start;i<=end;i++){
        radhe[i+1-start+1]= quo_ans[i];
        }


        }



        }
        return radhe;
        }
     
    }
      void sign_extend(char *inp,char amount,bool left){
       
        int length=strlen(inp);
        if(left){
        for(int i=0;i<(length-1);i++){
            inp[i]=inp[i+1];
        }
        inp[length-1]=amount;
        }
        
    }