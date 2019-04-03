%{

	#include<stdio.h>
	#include<math.h>

%}
%union
{double p;}
%token<p>num
%token SIN 

%left '+''-'
%left '*''/'
%nonassoc uminu
%type<p>exp
%%

ss:exp
{
	printf("=%g\n",$1);
}

exp:	exp'+'exp	{$$=$1+$3;}
	|exp'-'exp	{$$=$1-$3;}
	|exp'*'exp	{$$=$1*$3;}
	|exp'/'exp	{
				if($3==0)
				printf("Divide by zero exception");
				else
				$$=$1/$3;
			
			}
	|'-'exp		{$$=-$2;}
	|'('exp')'	{$$=$2;}
	|SIN'('exp')'	{$$=sin($3);}
	
	|exp'^'exp	{
				$$=power($1,$3);
			}
	|num;

%%
main()
{
	printf("\nEnter the expression:");
		yyparse();

}

int power(double a,double b)
{
	int i;
	double mul=1;
	for(i=0;i<b;i++)
		mul=mul*a;
	return mul;
}

yyerror(s)
char *s;
{
	printf("Error");
}

