#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159265

double executing(FILE* in_file, char** testfile );
int exist(char* input[], int len, char* elemet);
int stablise(FILE* in_file);
int dotproduct(char** input1,int* D1, int len1, char** input2,int* D2, int len2);
int reading(char* testfile, char* corpus_folder);
double vector_angle(char** input2,int* D2, int len2);
char** testfilestring;
int* testfilesint;
int len=0;
int numberofelement=10000;




int main(int argc, char* argv[])
{
     //printf("%s\n",argv[0]);
//      printf("%s\n",argv[1]);
//      printf("%s\n",argv[2]);
        char* testfile=argv[1];
        char* corpus_folder= argv[2];
       reading(argv[1],argv[2]);
        // char* t[10];
        // t[0]="kapil";
        // t[1]="kamli";
        // t[2]="kartik";
        // int te=exist(t, 3, "ka");
        // printf("%d\n", te);
        // pront( t);
        return 0;
}
// int pront(char* t[]){
//         printf("%s\n","===");
//         for (int i = 0; i < 10; i++)
//         {
//                 /* code */
//                 printf("%s\n",t[i]);
//         }
        
// }

int reading(char* testfile, char* corpus_folder){
        // char in_name[80];
        // FILE *file;
        
        //char* matching_file[]= (char*)(malloc(10000, sizeof(STRING)));
        DIR* FD;
        struct dirent* in_file;
        FILE    *input1;
        FILE    *entry_file;
        char    buffer[BUFSIZ];

    /* Openiing common file for writing */
        input1 = fopen(testfile, "r");
        //printf("%s\n", testfile);
        // if (input1 == NULL)
        // {
        //         fprintf(stderr, "Error : Failed to open common_file - %s\n", strerror(errno));

        //         return 1;
        // }
        stablise(input1);
    /* Scanning the in directory */
       // printf("%s\n", corpus_folder);
        if (NULL == (FD = opendir (corpus_folder))) 
        {
                fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
                fclose(input1);

                return 1;
        }
       // printf("%s\n","===============" );
          int i=0;
        while ((in_file = readdir(FD))) 
        {
                        /* On linux/Unix we don't want current and parent directories
                        * On windows machine too, thanks Greg Hewgill
                        */
                
                char temp[200];
                strcpy(temp, corpus_folder);
                strcat(temp, "/");
                strcat(temp, in_file->d_name);
                 

                
                if (!strcmp (in_file->d_name, "."))
                        continue;
                if (!strcmp (in_file->d_name, ".."))    
                        continue;
                /* Open directory entry file for common operation */
                /* TODO : change permissions to meet your need! */
               // printf("%s\n",(in_file->d_name));
                entry_file = fopen(temp, "r");
                //printf("%s\n",temp );
                if (entry_file == NULL)
                {
                        fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));
                        fclose(input1);

                        return 1;
                }
                
                /* Doing some struf with entry_file : */
                /* For example use fgets */
                
                printf("%s\n%s\n", "*****************",in_file->d_name);
                double t=executing(entry_file, testfilestring);
                printf("%s %lf\n", in_file->d_name, t);
                i++;
                printf("%d\n",i);
                /* When you finish with the file, close it */
                fclose(entry_file);
        }
                ////printf("%s\n","===============" );

    /* Don't forget to close common file before leaving */
        fclose(input1);




//     printf("Enter file name:\n");
//     scanf("%s", in_name);

//     in_file = fopen(in_name, "r");
//       reading(in_file);
        return 0; 
  

}

int stablise(FILE* in_file){    // for stablizing the system ..reading testfile only here.
        printf("%s\n", "Establiseing");

   
        char word[100];
        int k=0;
        testfilestring =(char**) malloc(numberofelement * sizeof(char*));
        testfilesint=malloc(numberofelement * sizeof(int));
        // for(int i = 0; i < numberofelement; i++) {
        //         testfilestring[i] = (char*)malloc((100 + 1) * sizeof(char));
        // }
        if (in_file == NULL){
                printf("Can't open %s for reading.\n", "input.txt");
        }else
        {
             //   printf("%s\n", "Establiseing");
                while (fscanf(in_file, "%s", word) != EOF)
                {
             //  printf("%s\n", word);
                        int temp=exist1(testfilestring,k, word);
                        if(temp==-1){
                                testfilestring[k]=(char*)malloc(strlen(word+1) * sizeof(char));
                                strcpy(testfilestring[k], word);
                                testfilesint[k]=1;
                                k++;
                        }else{
                                testfilesint[temp]=testfilesint[temp]+1;
                        }
                        
                //printf("%s\n", orderIds[k]);
            
                }
             
        }

        for(int i=0;i<k;i++){
                printf("%s %d\n", testfilestring[i], testfilesint[i]);
        }
        len=k;
        return 0;

}

double executing(FILE* in_file, char** testfile){
       
       
        
        //int numberofelement=10000;
         printf("%s\n","-----------");
       // char* inputfilestring[10000];
        char** inputfilestring=(char**) malloc(numberofelement * sizeof(char*));
        int* inputfileint=(int*)malloc(numberofelement * sizeof(int));

        // for(int i = 0; i < 10000; i++) {
        //         inputfilestring[i] ="NULL";
        // }
       // int inputfileint[10000];
        char word[100];
        int len1=0;
       
         
         if (in_file == NULL){
                printf("Can't open %s for reading.\n", "input.txt");
         }else
        {
               
                // printf("%s\n","-----------");
                while (fscanf(in_file, "%s", word) != EOF)
                {
              
                        int temp=exist1(inputfilestring, len1, word);
                        // inputfilestring[len1]= word;
                        // inputfileint[len1]=1;
                        // len1=len1+1;
                        // printf("%s %d\n", word, len1);
                        if(temp==-1){
                                inputfilestring[len1]=(char*)malloc(strlen(word+1) * sizeof(char));
                                strcpy(inputfilestring[len1], word);
                                inputfileint[len1]=1;
                                len1=len1+1;
                                 printf("%s %s\n","-----------", word);
                        }else{
                                inputfileint[temp]=inputfileint[temp]+1;
                        //  printf("%d\n", inputfileint[temp]);
                        }
                // printf("%s\n", "executing");
                //printf("%s\n", orderIds[k]);
            
                }
                fclose(in_file);
        }
        printf("%s %d\n","8888888888888888888888888888888888888888888888", len1);
        
        for(int i=0;i<len1;i++){
                printf("%s %d\n", inputfilestring[i], inputfileint[i]);
        }
      printf("%s\n","8888888888888888888888888888888888888888888888");
        double similiarity=vector_angle(inputfilestring,inputfileint,len1);

       // printf("%s--->%lf\n","Similiarity" ,similiarity);
       // int size = sizeof inputfilestring / sizeof inputfilestring[0];
       // printf("%d %d\n", size, k);

       
//         for(int i = 0; i < numberofelement; i++) {
//                 free(inputfilestring[i]);
//         }
        

//         free(inputfilestring);
//         free(inputfileint);

        printf("%s\n","execution completed");




        return similiarity;
}


int exist(char* input[], int l, char* elemet)
{
        // printf("%s\n","=============");
        // printf("%s %d %s\n", "exist", l, elemet);
        if(l==0){
                return -1;
        }
        for(int i=0;i<l;i++){
               // printf("%s %s\n", input[i], elemet);
                if(strcmp(input[i], elemet)==0){
                        return i;
                }
        }
        return -1;
}
int exist1(char** input, int l, char* elemet)
{
        // printf("%s\n","=============");
        // printf("%s %d %s\n", "exist", l, elemet);
        for(int i=0;i<l;i++){
               // printf("%s %s\n", input[i], elemet);
                if(strcmp(input[i], elemet)==0){
                        return i;
                }
        }
        return -1;
}


int dotproduct(char* input1[],int D1[], int len1, char* input2[],int D2[], int len2){  //first arg is for testfile.
        int result=0;
        for(int i=0;i<len1;i++){
                char* str=input1[i];
                int temp=exist(input2, len2 , str );
                if(temp!=-1){
                        result= result+(D2[temp]*D1[i]);
                       // printf("%s--->%d\n", "result", result);
                }
        }
        return result;
}

double vector_angle(char* input2[],int D2[], int len2){
       // printf("%d %d\n",len2, len);
        int numerator= dotproduct(testfilestring, testfilesint, len,input2,D2,len2);
        double denominator= sqrt(dotproduct(testfilestring, testfilesint, len,testfilestring, testfilesint, len)* dotproduct(input2,D2,len2,input2,D2,len2));
        double temp=((double)numerator)/denominator;
        double temp2=PI/180;
        printf("%s %lf\n", "temp", temp);
        printf("%s %d\n", "numera", numerator);
        printf("%s %lf\n", "deno", denominator);
        double a= acos(temp)*180/PI;
       //  printf("%s %lf\n", "aa", a);
        return (100-(a/90)*100);
       // return 0.0;
}