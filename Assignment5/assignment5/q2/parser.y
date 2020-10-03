%{
         #define YYSTYPE int
        #include "lex.yy.c"
        #include <stdio.h>
        #include <stdlib.h>
        #include <stdbool.h>
        #include <ctype.h>
        #include <string.h>       
        extern char *yytext;
        void yyerror(char *);
        void push(void);
        void pop(void);
        char array[10000][10000];
        int top=0;
        int flag=0;
%}
%token id op space ENDLINE ferzi
%start Z
%%
Z : S ENDLINE Z 
   | S ENDLINE {yyterminate();}
    
S : E  { if(flag==0){fprintf(yyout,"%s ",array[top-1]);
        fprintf(yyout,"%d\n",$$);}else{
               
                flag=0;
        }
        }
      
     
E : E space E space op {
        pop();
      
        if(yytext[0]=='+'){
                $$=$1+$3;
        }else if(yytext[0]=='-'){
                $$=$1-$3;
        }else if(yytext[0]=='*'){
                $$=$1*$3;
        }else if(yytext[0]=='/'){
                $$=$1/$3;
        }else{

        }}
        |id {  push();$$=$1;}
        |E space E {flag=1;fprintf(yyout,"%s\n","invalid_input");}
        |E space op {flag=1;fprintf(yyout,"%s\n","invalid_input");}
       
        

%%
void yyerror(char *s){
        fprintf(stderr,"%s\n",s);
}
int main(int argc, char* argv[]){
        extern FILE *yyin, *yyout;
      //  printf("%s %s\n",argv[1],argv[2]);
        yyin=fopen(argv[1],"r");
        yyout=fopen(argv[2],"w");
        //printf("%s\n","Enter postfix expression:");
        yyparse();
        return 0;

}
void push(){
        int len=strlen(yytext);
        int i;
       for(i=0;i<len;i++){
               array[top][i]=yytext[i];
       }
      
      
       top++;
}
void pop(){
        char arr1[10000];
        char arr2[10000];
        top=top-1;
        int len1=strlen(array[top]);
        int i=0;
        for(i=0;i<len1;i++){
                arr1[i]=array[top][i];
        }
       
       
        top=top-1;
        int len2=strlen(array[top]);
        for(i=0;i<len2;i++){
                arr2[i]=array[top][i];
        }
        // arr2[i]='\n';
        char arr3[20002];
        arr3[0]=yytext[0];
        arr3[1]=' ';
        i=0;
        for(i=0;i<len2;i++){
                arr3[i+2]=arr2[i];
        }
        arr3[i+2]=' ';
        i=0;
        for(i=0;i<len1;i++){
                arr3[i+3+len2]=arr1[i];
        
        }
        arr3[len1+len2+3]='\0';
        int len3=strlen(arr3);
        i=0;
        for(i=0;i<len3;i++){
                array[top][i]=arr3[i];
        }
        // array[top][len3]='\n';
       
        top++;


}
