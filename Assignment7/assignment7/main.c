#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
// #include <malloc.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <math.h>
#include "all.h"
#define PI 3.14159265
char* waste_words[WASTE_WORD_COUNT] = {
	    "the", "of", "and", "a", "to", "in", "is", "you",
	    "that", "it", "he", "was", "for", "are", "as", "my"
	    "with", "his", "they", "i", "at", "be", "this", "have",
	    "from", "or", "one", "had", "by", "but", "were", "all",
	    "we", "your", "when", "can", "there", "an", "which", "she",
	    "do", "their", "if", "will", "up", "then", "these", "so",
	    "her", "his", "would", "him", "into", "has", "could", "may",
	    "get", "did", "its", "been", "than", "s"
	};
int present(char* a);
double executing(FILE* in_file, struct datafile *tf,struct datafile_freq *tf1 );
int exist(struct datafile *df, int len, char* elemet);
int exist1(struct datafile *tf, int len, char* elemet);
int stablise(FILE* in_file, struct datafile *tf,struct datafile_freq *tf1);
int dotproduct(struct datafile *tf,struct datafile_freq *tf1, int len1,struct datafile *df,struct datafile_freq *df1,int len2);
double vector_angle(struct datafile *df,struct datafile_freq *df1,int len2, struct datafile *tf, struct datafile_freq *tf1);
int reading(char* testfile, char* corpus_folder, struct datafile *tf, struct datafile_freq *tf1);
int len;
int present(char* a){
        for(int i=0;i<WASTE_WORD_COUNT;i++){
                if(strcmp(waste_words[i], a)==0){
                        return 1;
                }
        }
        return -1;
}

int main(int argc, char* argv[]){
        struct datafile *tf=calloc(sizeof(struct datafile),1);
        struct datafile_freq *tf1=calloc(sizeof(struct datafile_freq),1);
        char* testfile=argv[1];
        char* corpus_folder= argv[2];
        reading(argv[1],argv[2], tf,tf1);
        return 0;
}


int reading(char* testfile, char* corpus_folder, struct datafile *tf, struct datafile_freq *tf1){
       
        //char* matching_file[]= (char*)(malloc(10000, sizeof(STRING)));
        DIR* FD;
        struct dirent* in_file;
        FILE    *input1;
        FILE    *entry_file;
        char    buffer[BUFSIZ];

        struct datafile *df=calloc(sizeof(struct datafile),1);
        struct datafile_freq *df1=calloc(sizeof(struct datafile_freq),1);
        /* Openiing common file for writing */
        input1 = fopen(testfile, "r");

        stablise(input1, tf, tf1);
        fclose(input1);
        
       

        if (NULL == (FD = opendir (corpus_folder))) 
        {
                fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
                // fclose(input1);
                return 1;
        }
      

        while ((in_file = readdir(FD))) 
        {
                       
                char temp[200];
                strcpy(temp, corpus_folder);
                strcat(temp, "/");
                strcat(temp, in_file->d_name);
                 
                
                
                if (!strcmp (in_file->d_name, "."))
                        continue;
                if (!strcmp (in_file->d_name, ".."))    
                        continue;
                int temp_size = strlen(temp);
                if(!(temp[temp_size-1]=='t' && temp[temp_size-2]=='x' && temp[temp_size-3]=='t')){
                       
                        continue;
                }
                entry_file = fopen(temp, "r");

                if (entry_file == NULL)
                {
                        fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));
                        fclose(entry_file);
                        return 1;
                }
                double t_ = executing(entry_file, tf,tf1);
                printf("%s %lf\n", in_file->d_name, t_);
                fclose(entry_file);
        }

        fclose(input1);
        return 0; 
}


double executing(FILE* in_file, struct datafile *tf,struct datafile_freq *tf1){
        struct datafile *df=calloc(sizeof(struct datafile),1);
        struct datafile_freq *df1=calloc(sizeof(struct datafile_freq),1);
        char word[100];
        int len1=0;
       
         
        if (in_file == NULL){
                printf("Can't open %s for reading.\n", "input.txt");
        }
        else{   
                while (fscanf(in_file, "%s", word) != EOF)
                {       
                        if(present( word)==1){
                                continue;
                        }
                        int temp=exist(df, len1, word);
                        if(temp==-1){
                                strcpy(df->data[len1].word, word);
                                df1->data_[len1].fre=1;
                                len1=len1+1;
                        }else{
                               df1->data_[temp].fre=df1->data_[temp].fre+1;
                        }
            
                }
                fclose(in_file);
        } 
        double similiarity=vector_angle(df,df1,len1,tf,tf1);
        return similiarity;
}
int dotproduct(struct datafile *tf,struct datafile_freq *tf1, int len1,struct datafile *df,struct datafile_freq *df1,int len2){  //first arg is for testfile.
        int result=0;
        for(int i=0;i<len1;i++){
                char* str=tf->data[i].word;
                int temp=exist(df, len2 , str);
                if(temp!=-1){
                        result= result+(df1->data_[temp].fre*tf1->data_[i].fre);
                }
        }
        return result;
}

double vector_angle(struct datafile *df,struct datafile_freq *df1,int len2, struct datafile *tf, struct datafile_freq *tf1){
        int numerator= dotproduct(tf,tf1,len,df,df1,len2);
        double denominator= sqrt(dotproduct(tf,tf1, len,tf,tf1, len)* dotproduct(df,df1,len2,df,df1,len2));
        double temp=((double)numerator)/denominator;
        double temp2=PI/180;
        double a= acos(temp)*180/PI;
        return (100-(a/90)*100);
}

int stablise(FILE* in_file, struct datafile *tf, struct datafile_freq *tf1){
        char word[100];
        int k=0;
        if (in_file == NULL){
                printf("Can't open %s for reading.\n", "test file");
        }else
        {       
                while (fscanf(in_file, "%s", word) != EOF)
                {
                        if(present( word)==1){
                                continue;
                        }
                        int temp=exist1(tf,k, word);
                        if(temp==-1){
                                strcpy(tf->data[k].word, word);
                                tf1->data_[k].fre=1;
                                k++;
                        }else{
                                tf1->data_[temp].fre=tf1->data_[temp].fre+1;
                        }
                }
             
        }
        len=k;
        return 0;
}


int exist(struct datafile *df, int len, char* elemet){
        if(len==0){
                return -1;
        }
        for(int i=0;i<len;i++){
                if(strcmp(df->data[i].word, elemet)==0){
                        return i;
                }
        }
        return -1;
}  

int exist1(struct datafile *tf, int len, char* elemet){
        if(len==0){
                return -1;
        }
        for(int i=0;i<len;i++){
                if(strcmp(tf->data[i].word, elemet)==0){
                        return i;
                }
        }
        return -1;
}       
