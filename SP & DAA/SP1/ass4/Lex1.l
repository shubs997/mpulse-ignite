%{
       #include<math.h>
       #include"y.tab.h"	//for left,right,up & down
%}
%%

[0-9]+|[0-9]*\.[0-9]+ {
                       yylval.p = atof(yytext);
                       return num;		//return nonterminal
                       }
[\t];
\n      return 0;
.       return yytext[0];


%%
