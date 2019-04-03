#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct table
{
	int id;
	char name[5];
	int addr;
}table;

table symbol[10];
table literal[10];

char t1[10],t2[10],t3[10],t4[10],t5[10],t6[10];

int main()
{
	int l,s,i,j;
	FILE *fp1,*fp2;
	char buff[30];
	fp1=fopen("file1.txt","r");
	fp2=fopen("file2.txt","w");
	
	printf("\nEnter the no. of Literals in literal table:");
	scanf("%d",&l);
	
	if(l>=1)
	{
		printf("\nEnter the Literals in literal table:");
		for(i=0;i<l;i++)
		{
			printf("\nEnter Literal index %d : ",i+1);
			printf("\nEnter Literal name :");
			scanf("%s",literal[i].name);
			printf("\nEnter Literal address :");
			scanf("%d",&literal[i].addr);
			literal[i].id=i+1;
		}
	}
	else
		printf("\nNot valid no. of literals");
	
	
	printf("\nEnter the no. of Symbols in Symbol table:");
	scanf("%d",&s);
	
	if(s>=1)
	{
		printf("\nEnter the Symbols in Symbol table:");
		for(i=0;i<s;i++)
		{
			printf("\nEnter Symbol index %d : ",i+1);
			printf("\nEnter Symbol name :");
			scanf("%s",symbol[i].name);
			printf("\nEnter Symbol address :");
			scanf("%d",&symbol[i].addr);
			symbol[i].id=i+1;
		}	
	}
	else
		printf("\nNot valid no. of Symbols");

	if(l>=1)	
	{
		printf("\n\tLiteral table:");
		printf("\n\nIndex\t\tName\t\tAddress");
		for(i=0;i<l;i++)
		{
			printf("\n%d\t\t\t%s\t\t\t%d",literal[i].id,literal[i].name,literal[i].addr);
		}
	}		
	
	if(s>=1)	
	{
		printf("\n\tSymbol table:");
		printf("\n\nIndex\t\tName\t\tAddress");
		for(i=0;i<s;i++)
		{
			printf("\n%d\t\t\t%s\t\t\t%d\n",symbol[i].id,symbol[i].name,symbol[i].addr);
		}
	}
	
	while(fgets(buff,30,fp1))
	{
		sscanf(buff,"%s%s%s%s%s%s",t1,t2,t3,t4,t5,t6);
		
		if(strcmp(t1,"(AD,")==0)
		{
			t2[strlen(t2)-1]='\0';
			t5[strlen(t5)-1]='\0';
			fprintf(fp2,"\n %s   %s   %s",t2,t3,t5);
		}
		
		if(strcmp(t2,"(IS,")==0)
		{
			t3[strlen(t3)-1]='\0';
			t6[strlen(t6)-1]='\0';
					
			if(strcmp(t5,"(S,")==0)
			{
				fprintf(fp2,"\n %s   %s    %s   %d",t1,t3,t4,symbol[atoi(t6)-1].addr);
			}
			else if(strcmp(t5,"(L,")==0)
			{
				fprintf(fp2,"\n %s   %s    %s   %d",t1,t3,t4,literal[atoi(t6)-1].addr);
			}
		}
		
		if(strcmp(t2,"(AD,")==0)
		{
			t3[strlen(t3)-1]='\0';
			
			if( atoi(t3)==5 || atoi(t3)==2 || atoi(t3)==7 )	//5=LTORG 2=END 7=DC
			{
				fprintf(fp2,"\n %s   -    -   %s",t1,t5);	
			}
			else if(atoi(t3)==6)			// 6=DS
			{
				fprintf(fp2,"\n %s   -    -   -",t1);	
			}
		}
	}
	
	return 0;
}
