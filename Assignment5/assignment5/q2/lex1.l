%{ 
  /* Definition section */
  #include <stdlib.h>
  #include "y.tab.h"
  
%} 
ALPHA [A-Za-z] 
DIGIT [0-9] 
OPERATOR [\+\-\*\/]
  
/* Rule Section */
%% 
[ \t]                                   {return space;}
([-]?{DIGIT}+)|([+]?{DIGIT}+)            {yylval= atof(yytext);return id; }
{OPERATOR}                                {return op;}
[\n]                                    {return ENDLINE;}
.                                       {return yytext[0];}                        
%% 
int yywrap(){
        return 1;
}