%{
       #include<math.h>
       #include"y.tab.h"	//for left,right,up & down
%}
%%

[0-9]+|[0-9]*\.[0-9]+ {
                       yylval.p = atof(yytext);
                       return num;		//return nonterminal
                       }

sin {return SIN;}	//return token SIN to YACC
cos {return COS;}	//return token COS to YACC
cube {return CUBE;}
squre {return SQURE;}
ln {return LN;}
tan return TAN;		//return token TAN to YACC
log return LOG;		//return token LOG to YACC
sqrt return SQRT;	//return token SQRT to YACC*/
[\t];
\n      return 0;
.       return yytext[0];


%%
