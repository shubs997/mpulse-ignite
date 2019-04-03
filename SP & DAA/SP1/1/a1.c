#include<stdio.h>
#include<string.h>

char MOT[][10]={"MOVER","MOVEM","ADD","SUB","MUL","DIV","PRINT","READ","BC","COMP"};
char POT[][10]={"START","END","ORIGIN","EQU","LTORG","DS","DC"};
char REG[][10]={"AREG","BREG","CREG","DREG"};
char CBC[][10]={"LT","GT","LE","GE"};
int symcount=0;
int poolcnt=0;
int litcnt=0;
int pooltab[5];


 struct symtable
{
	int index;
	char name[10];
	int addr;
};
struct symtable table[10];

struct littable
{
	int index;
	char name[10];
	int addr;
};
struct littable table1[10];

int search_mot(char str[10])
{
	int i,r;
	char str1[10];
	for(i=0;i<9;i++)
	{
		if((strcmp(MOT[i],str))==0)
		   	return i;
	}
				return -1;
}


int search_pot(char str[10])
{
	int i,r;
	char str1[10];
	for(i=0;i<7;i++)
	{
		if((strcmp(POT[i],str))==0)
		   	return i;
	}
	return -1;
}


int search_reg(char str[10])
{
	int i,r;
	char str1[10];
	for(i=0;i<4;i++)
	{
		r=strcmp(REG[i],str);
		if(r==0)
		   	return i;
	}
		return -1;
}
int search_cbc(char str[10])
{
	int i,r;
	char str1[10];
	for(i=0;i<4;i++)
	{
		r=strcmp(CBC[i],str);
		if(r==0)
		   	return i;
	}
		return -1;
}

int search_sym(char str[10])
{
	int i,r;
	char str1[10];
	for(i=0;i<10;i++)
	{
		if((strcmp(table[i].name,str))==0)
		   	return i;
	}
	return -1;
}

int search_lit(char str[10])
{
	int i,r;
	char str1[10];
	for(i=pooltab[poolcnt];i<litcnt;i++)
	{
		if((strcmp(table1[i].name,str))==0)
		   	return i;
	}
	return -1;
}



void main()
{
	FILE *fp,*fp1;
	int n=0,n1=0,n2=0,err=0,lc,k,j,k1,n3=0,i;
	fp=fopen("a.txt","r");
	fp1=fopen("Intfile.txt","w");
	char t1[10],t2[10],t3[10],t4[10],buf[180],a[10];
	pooltab[0]=0;
	while(fgets(buf,180,fp))
	{
		printf("%s",buf);
		n=sscanf(buf,"%s%s%s%s",t1,t2,t3,t4);
		switch(n)
		{
		
			case 1:
			n1=search_pot(t1);
			if(n1==0)	//start
			{
				lc=0;
				fprintf(fp1,"-) (AD,%d) - -\n",n1);
			}
			else if(n1==2)	//origin
			{
				lc=0;
			}
			else if(n1==1)	//end
			{
				if(litcnt==0)	//no literals
					 fprintf(fp1,"%d) (AD, %d) - - \n",lc,n1);
				else 
				{
				    	
					for(i=pooltab[poolcnt];i<litcnt;i++)
					{
					   table1[i].addr=lc;			   
					   fprintf(fp1,"%d) (AD, %d) - 0%s\n",lc,n1,table1[i].name);
					   lc++;
					} 
				}
			}
			else if(n1==4)	//ltrog
			{     
			        lc--;
					for(i=pooltab[poolcnt];i<litcnt;i++)
					{

					   table1[i].addr=lc;		   
					   fprintf(fp1,"%d) (AD, %d) - 0%s\n",lc,n1,table1[i].name);
					   lc++;
					}
					poolcnt++;
					pooltab[poolcnt]=litcnt;
					
			}
			else
			{
				fprintf(fp1,"\nAssembly directive error1");
				err++;
			}
			break;

			case 2:
			n1=search_pot(t1);
			if(n1==0)			//start
			{
				lc=atoi(t2);
				fprintf(fp1,"-) (AD, %d) - (C, %d)\n",n1,lc);
			}
			
			else if(n1==2)	//origin
			{
				
				n2=search_sym(t2);
				if(n2!=-1)
				lc=table[n2].addr;
				else
				lc=atoi(t2);
			}
			
			else			//read,print
			{
				n2=search_mot(t1);
				if(n2!=-1)
				{
					if(t2[0]=='=')	//literal
					{
						k1=search_lit(t2);
						if(k1==-1)
						{
							for(i=1,j=0;t2[i]!='\0';i++,j++)
								a[j]=t2[i];
							table1[litcnt].index=litcnt;
							strcpy(table1[litcnt].name,a);
							
							litcnt++;
						}
						k1=search_lit(a);
						fprintf(fp1,"%d) (IS,%d) - (L,%d)\n",lc,n2,k1);
						lc++;
					}
					else			//symbol table
					{
						k=search_sym(t2);
						if(k==-1)
						{
							table[symcount].index=symcount;
							strcpy(table[symcount].name,t2);
							symcount++;
						}
						k=search_sym(t2);
						fprintf(fp1,"%d) (IS, %d) - (S, %d)\n",lc,n2,k);
						lc++;
					
					
					}
					
				}
			}
			if(n1==-1 && n2==-1)
			{
				fprintf(fp1,"\nAssembly directive error2");
				err++;
			}
			break;

			case 3:
			n1=search_mot(t1); //mot
			if(n1!=-1)
			{
				
				n2=search_reg(t2);
				if(n2!=-1)
				{
					if(t3[0]=='=')	//literal
					{
						k1=search_lit(t3);
						if(k1==-1)
						{
							for(i=1,j=0;t3[i]!='\0';i++,j++)
								a[j]=t3[i];
							table1[litcnt].index=litcnt;
							strcpy(table1[litcnt].name,a);
							litcnt++;
						}
						k1=search_lit(a);
						fprintf(fp1,"%d) (IS, %d) - (L, %d)\n",lc,n1,k1);
						lc++;
					}
					else		//symbol
					{
						k=search_sym(t3);
						if(k==-1)
						{
							table[symcount].index=symcount;
							strcpy(table[symcount].name,t3);
							symcount++;
						}
						k=search_sym(t3);
						fprintf(fp1,"%d) (IS, %d) 0%d (S, %d)\n",lc,n1,n2,k);
						lc++;
					}
					
				}
				else
				{
					n3=search_cbc(t2);
					if(n3!=-1)
					{
						if(t3[0]=='=')	//literal
						{
							k1=search_lit(t3);
							if(k1==-1)
							{
								for(i=1,j=0;t3[i]!='\0';i++,j++)
									a[j]=t3[i];
								table1[litcnt].index=litcnt;
								strcpy(table1[litcnt].name,a);
								litcnt++;
							}
							k1=search_lit(a);
							fprintf(fp1,"%d) (IS, %d) %d (L, %d)\n",lc,n1,n3,k1);
							lc++;
						}
						else		//symbol
						{
							k=search_sym(t3);
							if(k==-1)
							{
								table[symcount].index=symcount;
								strcpy(table[symcount].name,t3);
								symcount++;
							}
							k=search_sym(t3);
							fprintf(fp1,"%d) (IS, %d) %d (S, %d)\n",lc,n1,n3,k);
							lc++;
						}
					}
				
				}
			}
			
			else if (n1==-1)	
			{
				k=search_sym(t1);
				if(k!=-1)	//without label
				{
					table[k].addr=lc;
					n2=search_pot(t2);	
					if(n2==5)	//DS
					{
						j=atoi(t3);
						fprintf(fp1,"%d) (AD, %d) - 0%d\n",lc,n2,j);
						lc=lc+j;
					}
					else if(n2==6)	//DC
					{
						j=atoi(t3);
						fprintf(fp1,"%d) (AD, %d) - 0%d\n",lc,n2,j);
						lc++;
					}	
				}
				
				else if(k==-1)		//label
				{
					table[symcount].index=symcount;
					strcpy(table[symcount].name,t1);
					table[symcount].addr=lc;
					symcount++;
				
					n2=search_mot(t2);			//mot
					lc++;
					if(n2!=-1)	//Read,print
					{
					    if(t3[0]=='=')	//literal
					    {
						    k1=search_lit(t3);
						    if(k1==-1)
						    {
							    for(i=1,j=0;t3[i]!='\0';i++,j++)
								    a[j]=t3[i];
							    table1[litcnt].index=litcnt;
							    strcpy(table1[litcnt].name,a);
							    litcnt++;
						    }
						    k1=search_lit(a);
						    fprintf(fp1,"%d) (IS, %d) - (L, %d)\n",lc,n2,k1);
						    lc++;
					    }
					    else		//symbol
					    {
					        k1=search_sym(t3);
						    if(k1==-1)
						    {
							    table[symcount].index=symcount;
							    strcpy(table[symcount].name,t3);
							    symcount++;
						    }
						    k1=search_sym(t3);
						    fprintf(fp1,"%d) (IS, %d) - (S, %d)\n",lc,n2,k1);
						    lc++;
					    }
						
					}
					
				}	
			}
			else
			{
			    	fprintf(fp1,"\nAssembly directive error");
				err++;
			}
			break;
			
			
			
			case 4:
			j=search_sym(t1);
			if(j==-1)
			{
				table[symcount].index=symcount;
				strcpy(table[symcount].name,t1);
				table[symcount].addr=lc;
				symcount++;
			}
			n1=search_mot(t2);
			if(n1!=-1)
			{
				n2=search_reg(t3);
				if(n2!=-1)
				{
					if(t4[0]=='=')	//literal
					{
						k1=search_lit(t4);
						if(k1==-1)
						{
							for(i=1,j=0;t4[i]!='\0';i++,j++)
								a[j]=t4[i];
							table1[litcnt].index=litcnt;
							strcpy(table1[litcnt].name,a);
							litcnt++;
						}
						k1=search_lit(a);
						fprintf(fp1,"%d) (IS, %d) 0%d (L, %d)\n",lc,n1,n2,k1);
						lc++;
					}
					else
					{
						k=search_sym(t4);
						if(k==-1)
						{
							table[symcount].index=symcount;
							strcpy(table[symcount].name,t4);
							symcount++;
						}
						k=search_sym(t4);
						fprintf(fp1,"%d) (IS, %d) 0%d (S, %d)\n",lc,n1,n2,k);
						lc++;
					
					}
				}
			}
			if(n1==-1 || n2==-1)
			{
			    	fprintf(fp1,"\nAssembly directive error");
				err++;
			}
			break;

		}
	}
	
	printf("\nSymbol Table");
	printf("\nIndex\tName\tAddress");
	for(i=0;i<symcount;i++)
		printf("\n%d\t %s\t\t%d",table[i].index,table[i].name,table[i].addr);
		
	printf("\nLiteral Table");
	printf("\nIndex\tName\tAddress");
	for(i=0;i<litcnt;i++)
		printf("\n%d\t =%s\t\t%d",table1[i].index,table1[i].name,table1[i].addr);
		
	printf("\nPool Table");
	for(i=0;i<poolcnt;i++)
		printf("\n%d\n",pooltab[i]);
	
	
}
