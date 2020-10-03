#include<stdio.h> 
#include<string.h> 
#include <stdbool.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h>
#include <complex.h>
#include <time.h>
#include <math.h>
#include "basic.h"
#define NUM_COMMANDS 4
#define MAX(a,b) ((a) > (b) ? (a) : (b));
void add(char*, char*,FILE*);
double complex add1(char*, char*);
double complex sub1(char*, char*);
double complex prod1(char*, char*);
double complex quot1(char*,char*);
void abs_radhe(char*);
double square_root1(char*);
 void main(){
        char* commandsForGnuplot[]={"set boxwidth 1","set xlabel \"(Instruction Type) ---->\"","set ylabel \"(Average time in us) ---->\"","set title \"Time Comparison Arbitrary Precision vs GCC Compiler\"","set style fill solid border -1","set style data histograms","plot \"data.txt\" using 2:xtic(1) title \"Arbitrary Precision\" lt rgb \"#40AF00\",\"\" using 3 title \"GCC\" lt rgb \"#403090\"","set term pngcairo","set output \"graph.png\"","set terminal png","replot","set output"};
        int noofcommands=12;
        char* filename="input.txt";
        FILE * temp = fopen("data.txt", "w");
	    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
        int i=0;
	    char c1='\"';
        FILE *fp = fopen(filename,"r");
         FILE * output = fopen("output.txt", "w");
        char parse_str1[4]={'0'};
        char parse_str2[100000];
        char* parse_str3;
        char buf[10];
        int k=0;
        double mytime[5];
        double gcctime[5];
        if(fp==NULL){
            printf("could not open the file");
            return;
        }
        while(fgets(parse_str2,100000,fp)!=NULL){
            int i=0;
            char *p=strtok(parse_str2," ");
            char *token[3];
           
            while(p!=NULL){
                token[i]=p;
            
                p=strtok(NULL, " ");
                i++;
                }
                if(strcmp(token[0],"ADD")==0){
                    int len1=strlen(token[1]);
                    int len2=strlen(token[2]);
                    char inp1[len1];
                    char inp2[len2];
                    strcpy(inp1,token[1]);
                    strcpy(inp2,token[2]);
                    double time_spent=0.0;
                    clock_t begin=clock();
                    add(token[1], token[2],output);
                    clock_t end1=clock();
                    time_spent+=(double)(end1-begin)/CLOCKS_PER_SEC;
                   mytime[0]=time_spent;
                    add1(inp1, inp2);
                    clock_t end2=clock();
                    time_spent+=(double)(end2-end1)/CLOCKS_PER_SEC;
                   gcctime[0]=time_spent;
                }else if(strcmp(token[0],"SUB")==0){
                    int len1=strlen(token[1]);
                    int len2=strlen(token[2]);
                    char inp1[len1];
                    char inp2[len2];
                    strcpy(inp1,token[1]);
                    strcpy(inp2,token[2]);
                    double time_spent=0.0;
                    clock_t begin=clock();
                    sub(token[1],token[2],output);
                    clock_t end1=clock();
                    time_spent+=(double)(end1-begin)/CLOCKS_PER_SEC;
                   mytime[1]=time_spent;
                    time_spent=0.0;
                    sub1(inp1,inp2);
                    clock_t end2=clock();
                    time_spent+=(double)(end2-end1)/CLOCKS_PER_SEC;
                   gcctime[1]=time_spent;
                }else if(strcmp(token[0],"PROD")==0){
                    int len1=strlen(token[1]);
                    int len2=strlen(token[2]);
                    char inp1[len1];
                    char inp2[len2];
                    strcpy(inp1,token[1]);
                    strcpy(inp2,token[2]);
                    double time_spent=0.0;
                    clock_t begin=clock();
                    prod(token[1],token[2],output);
                    clock_t end1=clock();
                    time_spent+=(double)(end1-begin)/CLOCKS_PER_SEC;
                   mytime[2]=time_spent;
                    time_spent=0.0;
                    prod1(inp1,inp2);
                    
                    clock_t end2=clock();
                    time_spent+=(double)(end2-end1)/CLOCKS_PER_SEC;
                    gcctime[2]=time_spent;
                }else if(strcmp(token[0],"QUOT")==0){
                    int len1=strlen(token[1]);
                    int len2=strlen(token[2]);
                    char inp1[len1];
                    char inp2[len2];
                    strcpy(inp1,token[1]);
                    strcpy(inp2,token[2]);
                    double time_spent=0.0;
                    clock_t begin=clock();
                    quot(token[1],token[2],output);
                    clock_t end1=clock();
                    time_spent+=(double)(end1-begin)/CLOCKS_PER_SEC;
                    
                    mytime[3]=time_spent;
                    time_spent=0.0;
                    quot1(inp1,inp2);
                   
                    clock_t end2=clock();
                    time_spent+=(double)(end2-end1)/CLOCKS_PER_SEC;
                   gcctime[3]=time_spent;
                } else if(strcmp(token[0],"ABS")==0){
                    double time_spent=0.0;
                    clock_t begin=clock();
                    char *f=square_root(token[1],output);
                    clock_t end1=clock();
                    time_spent+=(double)(end1-begin)/CLOCKS_PER_SEC;
                     mytime[4]=time_spent;
                    time_spent=0.0;
                    square_root1(token[1]);
                    clock_t end2=clock();
                    time_spent+=(double)(end2-end1)/CLOCKS_PER_SEC;
                   gcctime[4]=time_spent;
                } 
               
        }
        fclose(fp);
       
        fprintf(temp, "%s %lf %lf\n","ADD", mytime[0],gcctime[0]);
	    fprintf(temp, "%s %lf %lf\n","SUB", mytime[1],gcctime[1]);
	    fprintf(temp, "%s %lf %lf\n","PROD", mytime[2],gcctime[2]);
	    fprintf(temp, "%s %lf %lf\n","QUOT", mytime[3],gcctime[3]);
	    fprintf(temp, "%s %lf %lf\n","ABS", mytime[4],gcctime[4]);
	for(i=0; i<noofcommands; i++){
	     fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);
	}
     fclose(temp);
    }


    double square_root1(char *inp){
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
            double z11=atof(inp11);
            double z12=atof(inp12);
            double complex r1=z11+z12*I;
           double radhe=sqrt (z11 * z11 + z12 * z12);
            return radhe;
           
    }








    void add(char* inp1, char* inp2,FILE * output){
      
        char *p=strtok(inp1,",");
            char *token1[2];
            int i=0;
            while(p!=NULL){
            token1[i]=p;
            p=strtok(NULL, ",");
            i++;
                }
            i=0;
            char *token2[2];
            p=strtok(inp2,",");
            while(p!=NULL){
            token2[i]=p;
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

            int len21=strlen(token2[0]);
            char inp21[len21-1];
            for(int i=0;i<(len21-1);i++){
                inp21[i]=token2[0][i+1];
            }
            inp21[len21-1]='\0';
            int len22=strlen(token2[1]);
            char inp22[len22-1];
          
            for(int i=0;i<(len22-1);i++){
                inp22[i]=token2[1][i];
            }
            inp22[len22-1]='\0';
            char *f1=func_start(inp11,inp21);
            char *f2=func_start(inp12,inp22);
            
            fprintf(output, "(%s,%s)\n",f1,f2);
        
          

    }

void sub(char* inp1,char* inp2,FILE * output){
            char *p=strtok(inp1,",");
            char *token1[2];
            int i=0;
            while(p!=NULL){
                token1[i]=p;
                p=strtok(NULL, ",");
                i++;
                }
            i=0;
            char *token2[2];
            p=strtok(inp2,",");
            while(p!=NULL){
                token2[i]=p;
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

            int len21=strlen(token2[0]);
            char inp21[len21-1];
            for(int i=0;i<(len21-1);i++){
                inp21[i]=token2[0][i+1];
            }
            inp21[len21-1]='\0';
            int len22=strlen(token2[1]);
            char inp22[len22-1];
            for(int i=0;i<(len22-1);i++){
                inp22[i]=token2[1][i];
            }
            inp22[len22-1]='\0';
            char *f1=func_sub_final(inp11,inp21);
            char *f2=func_sub_final(inp12,inp22);
           fprintf(output, "(%s,%s)\n",f1,f2);
}

void prod(char *inp1, char *inp2,FILE * output){
    
    char *p=strtok(inp1,",");
            char *token1[2];
            int i=0;
            while(p!=NULL){
                token1[i]=p;
                p=strtok(NULL, ",");
                i++;
            }
            i=0;
            char *token2[2];
            p=strtok(inp2,",");
                while(p!=NULL){
                token2[i]=p;
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

            int len21=strlen(token2[0]);
            char inp21[len21-1];
            for(int i=0;i<(len21-1);i++){
                inp21[i]=token2[0][i+1];
            }
            inp21[len21-1]='\0';
            int len22=strlen(token2[1]);
            char inp22[len22-1];
            for(int i=0;i<(len22-1);i++){
                inp22[i]=token2[1][i];
            }
            inp22[len22-1]='\0';
            char *f1=func_mult_start(inp11,inp21);
            char *f2=func_mult_start(inp12,inp22);
            int len5=strlen(f2);
            char f3[len5+1];
            if(f2[0]!='-'){
            f3[0]='-';
            for(int i=0;i<len5;i++){
                f3[i+1]=f2[i];
            }
            f3[len5+1]='\0';
            }else{
                for(int i=1;i<len5;i++){
                f3[i-1]=f2[i];
                }
                f3[len5-1]='\0';
            }



            char *f4=func_start(f1,f3);
            
            char *f5=func_mult_start(inp11,inp22);
            char *f6=func_mult_start(inp12,inp21);
            char *f7=func_start(f5,f6);
            fprintf(output, "(%s,%s)\n",f4,f7);
}
 
 void quot(char *inp1, char *inp2,FILE * output){
    
        char *p=strtok(inp1,",");
            char *token1[2];
            int i=0;
            while(p!=NULL){
            token1[i]=p;
            p=strtok(NULL, ",");
            i++;
                }
            i=0;
            char *token2[2];
            p=strtok(inp2,",");
            while(p!=NULL){
            token2[i]=p;
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

            int len21=strlen(token2[0]);
            char inp21[len21-1];
            for(int i=0;i<(len21-1);i++){
                inp21[i]=token2[0][i+1];
            }
            inp21[len21-1]='\0';
            int len22=strlen(token2[1]);
            char inp22[len22-1];
            for(int i=0;i<(len22-1);i++){
                inp22[i]=token2[1][i];
            }
            inp22[len22-1]='\0';
            char *f1=func_mult_start(inp11,inp21);
            int len5=strlen(inp22);
            char f3[len5+1];
            if(inp22[0]!='-'){
            f3[0]='-';
            for(int i=0;i<len5;i++){
                f3[i+1]=inp22[i];
            }
            f3[len5+1]='\0';
            }else{
                for(int i=1;i<len5;i++){
                    f3[i-1]=inp22[i];
                }
            f3[len5-1]='\0';
            }
            char *f2=func_mult_start(inp12, f3);
            int len6=strlen(f2);
            char f4[len6+1];

            if(f2[0]!='-'){
            f4[0]='-';
            for(int i=0;i<len6;i++){
                f4[i+1]=f2[i];
            }
            f4[len6+1]='\0';
            }else{
                for(int i=1;i<len6;i++){
                f4[i-1]=f2[i];
                }
                f4[len6-1]='\0';
            }
            char *f5=func_start(f1,f4);
            char *f6=func_mult_start(inp11,f3);
            char *f7=func_mult_start(inp12,inp21);
            char *f8=func_start(f6,f7);
            char *f9=func_mult_start(inp21,inp21);
            char *f10=func_mult_start(inp22,inp22);
            char *f11=func_start(f9,f10);
            char *f12=func_div_final(f5,f11);
            char *f13=func_div_final(f8,f11);
            fprintf(output, "(%s,%s)\n",f12,f13);
            // printf("(%s",f12);
            // printf(",%s)\n",f13);  
           //  printf("%s\n",inp1); 


 }

 //for library complex calculations..
 double complex add1(char *inp1,char *inp2){
            char *p=strtok(inp1,",");
            char *token1[2];
            int i=0;
            while(p!=NULL){
            token1[i]=p;
            p=strtok(NULL, ",");
            i++;
                }
            i=0;
            char *token2[2];
            p=strtok(inp2,",");
            while(p!=NULL){
            token2[i]=p;
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

            int len21=strlen(token2[0]);
            char inp21[len21-1];
            for(int i=0;i<(len21-1);i++){
                inp21[i]=token2[0][i+1];
            }
            inp21[len21-1]='\0';
            int len22=strlen(token2[1]);
            char inp22[len22-1];
            for(int i=0;i<(len22-1);i++){
                inp22[i]=token2[1][i];
            }
            inp22[len22-1]='\0';
            double z11=atof(inp11);
            double z12=atof(inp12);
            double z21=atof(inp21);
            double z22=atof(inp22);
            double complex r1=z11+z12*I;
            double complex r2=z21+z22*I;
            double complex sum=r1+r2;
           
            return sum;

 }
 double complex sub1(char *inp1, char *inp2){
            char *p=strtok(inp1,",");
            char *token1[2];
            int i=0;
            while(p!=NULL){
            token1[i]=p;
            p=strtok(NULL, ",");
            i++;
                }
            i=0;
            char *token2[2];
            p=strtok(inp2,",");
            while(p!=NULL){
            token2[i]=p;
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

            int len21=strlen(token2[0]);
            char inp21[len21-1];
            for(int i=0;i<(len21-1);i++){
                inp21[i]=token2[0][i+1];
            }
            inp21[len21-1]='\0';
            int len22=strlen(token2[1]);
            char inp22[len22-1];
            for(int i=0;i<(len22-1);i++){
                inp22[i]=token2[1][i];
            }
            inp22[len22-1]='\0';
            double z11=atof(inp11);
            double z12=atof(inp12);
            double z21=atof(inp21);
            double z22=atof(inp22);
            double complex r1=z11+z12*I;
            double complex r2=z21+z22*I;
            double complex sub=r1-r2;
           
            return sub;
 }

 double complex prod1(char *inp1, char *inp2){
              char *p=strtok(inp1,",");
            char *token1[2];
            int i=0;
            while(p!=NULL){
            token1[i]=p;
            p=strtok(NULL, ",");
            i++;
                }
            i=0;
            char *token2[2];
            p=strtok(inp2,",");
            while(p!=NULL){
            token2[i]=p;
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

            int len21=strlen(token2[0]);
            char inp21[len21-1];
            for(int i=0;i<(len21-1);i++){
                inp21[i]=token2[0][i+1];
            }
            inp21[len21-1]='\0';
            int len22=strlen(token2[1]);
            char inp22[len22-1];
            for(int i=0;i<(len22-1);i++){
                inp22[i]=token2[1][i];
            }
            inp22[len22-1]='\0';
            double z11=atof(inp11);
            double z12=atof(inp12);
            double z21=atof(inp21);
            double z22=atof(inp22);
            double complex r1=z11+z12*I;
            double complex r2=z21+z22*I;
            double complex prod=r1*r2;
           
           
            return prod;
 }
 double complex quot1(char *inp1,char *inp2){
            char *p=strtok(inp1,",");
            char *token1[2];
            int i=0;
            while(p!=NULL){
            token1[i]=p;
            p=strtok(NULL, ",");
            i++;
                }
            i=0;
            char *token2[2];
            p=strtok(inp2,",");
            while(p!=NULL){
            token2[i]=p;
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

            int len21=strlen(token2[0]);
            char inp21[len21-1];
            for(int i=0;i<(len21-1);i++){
                inp21[i]=token2[0][i+1];
            }
            inp21[len21-1]='\0';
            int len22=strlen(token2[1]);
            char inp22[len22-1];
            for(int i=0;i<(len22-1);i++){
                inp22[i]=token2[1][i];
            }
            inp22[len22-1]='\0';
            double z11=atof(inp11);
            double z12=atof(inp12);
            double z21=atof(inp21);
            double z22=atof(inp22);
            double complex r1=z11+z12*I;
            double complex r2=z21+z22*I;
            double complex div=r1/r2;
          
           return div;

 }