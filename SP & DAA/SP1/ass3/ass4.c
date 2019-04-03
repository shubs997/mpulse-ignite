#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char term1[28][7]={"(",")","{","}","=",";","+","-","*","/","%","<",">","&","|","==","+=","-=","*=","<=",">=","&&","||","void","int","if","printf","scanf"};

char operator[10]={'+','-','=','*','/','<','>','%','&','|'};

char token[20][20];
FILE *fp1,*fp2;
typedef struct table
{
	int id;
	char nm[20];
}table;

table sym[10];
int si,li;
table lit[10];

void reset()
{	
	int i;
	for(i=0;i<20;i++)
		strcpy(token[i],"\0");
}

int opr(char buff[],int i)
{
	int j,k;
	for(j=0;j<10;j++)
	{
		if(operator[j]==buff[i])
		{
			for(k=0;k<10;k++)
			{
				if(operator[k]==buff[i+1])
					return 1;
			}
			break;
		}
	}
	return 0;
}

int symser(char tok[])
{
	int i,j,k;
	i=0;
	while(i<=si)
	{
		j=strcmp(sym[i].nm,tok);
		if(j==0)
			return (sym[i].id);
		i++;
	}	
	
	sym[si].id=i;
	strcpy(sym[si].nm,tok);
	k=si;
	si++;
	return(sym[k].id);
}

int litser(char tok[])
{
	int k;
	lit[li].id=li+1;
	strcpy(lit[li].nm,tok);
	k=li;
	li++;
	return(lit[k].id);
}

void searcht(int k)
{
	int i,j,flg,m,n;-
	flg=0;
	for(i=0;i<k;i++)
	{
		flg=0;
		for(j=0;j<28;j++)
		{
			if((strcmp(token[i],term1[j]))==0)
			{
				flg=1;
				fprintf(fp2," TERM\t\t%d\t\t%s\n",(j+1),token[i]);
				break;
			}
		}
		if( isdigit(token[i][0]) || token[i][0] =='"' )
		{
			flg=1;
			n=litser(token[i]);
			fprintf(fp2," LITR\t\t%d\t\t%s\n",n,token[i]);
		}
		else if( flg!=1 )
		{
			m=symser(token[i]);
			fprintf(fp2," SYMB\t\t%d\t\t%s\n",m,token[i]);
			printf("\n\tSymbol: %d",m);
		}
	}
}

int main()
{
	//FILE *fp1,*fp2;
	char buff[30],temp[30];
	int i,j,n,ti,k;
	fp1=fopen("in.txt","r");
	fp2=fopen("UST.txt","w");
	
	while(fgets(buff,30,fp1))
	{
		reset();
		ti=0,j=0;
		n=strlen(buff);
		printf("\n\n");
		for(i=0;i<n;i++)
		{
			
			if( isalnum(buff[i]) || buff[i]=='"' )
			{	
				if(buff[i]=='"')
				{

					do{
						temp[j]=buff[i];
						i++;
						j++;
					}while(buff[i]!='"');
					temp[j++]=buff[i];
					i=i+1;
				}
				else
				{
					while(isalnum(buff[i]))
					{
						temp[j]=buff[i];
						i++;
						j++;
					}
				}
				temp[j]='\0';
				if(buff[i]==' ' || !isalnum(buff[i]))
				{
					strcpy(token[ti++],temp);
					printf("afhasahf %d: %s\n",ti-1,token[ti-1]);
					j=0;
				}
				i=i-1;
			}
			else if(buff[i]!=' ' && buff[i]!=',' && buff[i]!='\n')
			{
				if(ispunct(buff[i]))
				{
					temp[j++]=buff[i];
					if(opr(buff,i))
					{
						temp[j++]=buff[i+1];
						i++;
					}
				}
				temp[j]='\0';
				strcpy(token[ti++],temp);
				printf("afhasahf %d: %s\n",ti-1,token[ti-1]);
				j=0;
			}
			k=ti;
		}
		//printf("\nbdgdgdgh:%d",k);
		searcht(k);
		
	}	
	
		printf("\n\tSYMBOL TABLE:\n\tId\t\tName\n");
		for(i=0;i<si;i++)
		{
			printf("\t%d\t\t%s\n",sym[i].id,sym[i].nm);
		}
		
		printf("\n\tLITERAL TABLE:\n\tId\t\tName\n");
		for(i=0;i<li;i++)
		{
			printf("\t%d\t\t%s\n",lit[i].id,lit[i].nm);
		}
			
}
