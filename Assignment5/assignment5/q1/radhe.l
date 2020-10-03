%{
   #include <stdio.h> 
   #include <string.h> 
   #include <stdbool.h>
   int crr_line=1;
   int commnets=0; 
   int start=0; 
   void handle_multiline(void);
   int handle_error(int);
   void count_line();
%}
%%

["][\/\*]*[^"]*                                                  {printf("%s",yytext);count_line();}
['][\/\*]*[^']*                                                  {printf("%s",yytext);count_line();}
["](([\\]([^y]|[y]))*[^\\\"]*[\/\*]*)*["]                               {printf("%s",yytext);count_line();}
['](([\\]([^x]|[x]))*[^\\\']*[\/\*]*)*[']                               {printf("%s",yytext);count_line();}
("/*"["/*"]*[^"*/"]*"*/")                                       {handle_multiline();}
[/][*][^"*/"]*[\"']*[^"*/"]*[\"']*                                                  {start=crr_line;handle_error(start);}
.                               ECHO;




%%
int yywrap(){}
void count_line(){
         int len=strlen(yytext);
        for(int i=0;i<len;i++){
                if(yytext[i]=='\n'){
                        crr_line++;
                }
        }
}
void handle_multiline(void){
        //printf("%s\n","kapil verma");
        int len=strlen(yytext);
        // /printf("%d\n",len);
        printf("%s"," ");
        for(int i=0;i<len;i++){
                if(yytext[i]=='\n'){
                        crr_line++;
                        printf("%s","\n");
                }
        }

}
int handle_error(int a){
        //printf("%s\n","kamli verma");
        int len=strlen(yytext);
        //printf("%d\n",len);
        printf("%s"," ");
        for(int i=0;i<len;i++){
                if(yytext[i]=='\n'){
                        printf("%s","\n");
                        crr_line++;
                }
        }
        fprintf(stderr,"Error: line %d unterminated commnets\n",a);
        return 0;
        exit(0);
}





int main(int argc, char* argv[]){
        // if(argc!=4){
        //         printf("Sufficient arguments are not given\n");
        //         exit(1);
        // }
        // extern FILE *yyin, *yyout, *stderr;
        // yyin=fopen(argv[1],"r");
        // yyout=fopen(argv[2],"w");
        // stderr= fopen(argv[3],"w");
        yylex();
      //  printf("%d\n ",commnets);
        return 0;
        }

