/* 
			RDP program
			
	Given Productions:
	E->E+T | E-T | T
	T->T*F | T/F | F
	F->(E) | id 
	
	It contains left recursion
	E-> TE'
	E'-> +TE' | -TE' | E
	T-> FT'
	T'-> *FT' | /FT' | E
	F -> (E) | id
*/

#include<stdio.h>
#include<math.h>

char str[20];
int ptr=0;
int flag=0;

void E();
void Edash();
void T();
void Tdash();
void F();

void F()
{
	if(str[ptr]=='(')
	{
		ptr++;
		E();
		if(str[ptr]==')')
		{
			ptr++;
		}
		else
		{
			printf("\nerror. Invalid statement");
			flag=1;
			
		}
	}
	else if(isalnum(str[ptr]))
	{
		ptr++;
	}
	else 
	{
		printf("\nerror. Invalid statement");
			flag=1;
			
	}
	
}

void Tdash()
{
	if(str[ptr]=='*' || str[ptr]=='/')
	{
		ptr++;
		F();
		Tdash();
	}
	else 
		return;
}


void T()
{
	F();
	Tdash();
}

void E()
{
	 T();
	Edash();
}



void Edash()
{	
	if(str[ptr]=='+' || str[ptr]=='-')
	{
		ptr++;
		T();
		Edash();
	}
	else
	 return;	
} 

void main()
{
	printf("\nEnter your expression:\t");
	scanf("%s",str);
	//printf("\n : %s",str);
	E();
	if(flag!= 1)
	printf("\nValid statement");
}
