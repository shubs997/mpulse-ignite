%{
       #include<stdio.h>
       #include<math.h>
	
%}

				//to define possible symbol types
			//to define possible symbol types
%union{	double p;}


/*Defining the Precedence and Associativity*/
%left '+''-'			//lowest precedence
%left '*''/'			//highest precedenc
%nonassoc uminu			//no associativity
%type<p>exp			//Sets the type for non - terminal
%token<p>num
%%

/* for storing the answer */
ss: exp {printf("=%g\n",$1);}

/* for binary arithmatic operators */
exp :   exp'+'exp      { $$=$1+$3; }
       |exp'-'exp      { $$=$1-$3; }
       |exp'*'exp      { $$=$1*$3; }
       |exp'/'exp      {
                               if($3==0)
                               {
                                       printf("Divide By Zero");
																}
												}

       |num;
%%

/* extern FILE *yyin; */
main()
{
       do
       {
               yyparse();	/* repeatedly tries to parse the sentence until the i/p runs out */
       }while(1);

}

yyerror(s)			/* used to print the error message when an error is parsing of i/p */

char *s;
{
       printf("ERROR");
}

