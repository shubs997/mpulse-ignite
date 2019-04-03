#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char t1[10],t2[10],t3[10],t4[10];
int lc,error;

char POT[][10]={"START","END","ORIGIN","EQU","LTORG","DS","DC"};
char MOT[][10]={"MOVER","MOVEM","ADD","SUB","MUL","DIV","PRINT","READ","COMP","BC"};
char REG[][10]={"AREG","BREG","CREG","DREG"};
char CMP[][10]={"LT","LTE","GT","GTE"};

typedef struct table
{
	int no;
	char name[8];
	int addr;
	
}table;

table symbol[10];
table literal[10];
int pool[10];
int pool_ind;
int ind;
int lno;

int searchPOT( char a[10])
{
	int i,j;
	for(i=0;i<8;i++)
    {
       j=strcmp(POT[i],a);
        if(j==0)
        return (i+1);
     } 
     return(-1);  

}

int searchMOT( char a[10])
{
	int i,j;
	for(i=0;i<=10;i++)
     {
       j=strcmp(MOT[i],a);
        if(j==0)
        return (i+1);
     } 
     return(-1);  

}

int searchCMP( char a[10])
{
	int i,j;
	for(i=0;i<=7;i++)
     {
       j=strcmp(CMP[i],a);
        if(j==0)
        return (i+1);
     } 
     return(-1);  

}


int searchREG( char a[10])
{
	int i,j;
	for(i=0;i<5;i++)
     {
       j=strcmp(REG[i],a);
        if(j==0)
        {
        
        return (i+1);
        }
     } 
     return(-1);  

}


int insert_symbol(char a[10])
{
	
	int j;
	symbol[ind].no=ind+1;
	strcpy(symbol[ind].name,a);
	j=symbol[ind].no;
	if(a==t1)				//eg t1=LOOP,LABEL
	{
		symbol[ind].addr=lc;
	}
	ind++;
	return(j);
}


int searchSymbol(char a[10],int status)
{
	int i,chk,flag,j;
	flag=0;
	for(i=0; i<=ind ;i++)
	{
		chk=strcmp(symbol[i].name,a);
		if(chk==0)
		{
			
			flag=1;
			j=symbol[i].no;
			return(j);
			
		}
		
	}
	if(flag != 1 && status==0)
	{
		
		return 0;
	}
	if(flag != 1 && status==1)
	{
		
		j=insert_symbol(a);	
		return(j);
	}

}

char *getLiteral(char a[10])
{
	int t,i,k;
	char tkn[10];
	k=0;
	t=strlen(a);
	a[t]='\0';
	for(i=1;a[i]!='\0';i++,k++)
	{
		tkn[k]=a[i];
	}
	tkn[k]='\0';
	return (char *)tkn;
}

int searchLiteral(char a[10],int status)
{
	int i,j,flag,chk,k;
	flag=0;
	for(i=pool[pool_ind];i<=lno;i++)
	{
		chk=strcmp(literal[i].name,a);
		if(chk==0)
		{
			flag=1;
			j=literal[i].no;
			return(j);
		}
	}
	
	if(flag!=1 && status==1)		//to insert literal status=1
	{
		literal[lno].no=lno+1;
		strcpy(literal[lno].name,a);
		j=literal[lno].no;
		lno++;
	return(j);

	}
	
}

int main()
{
	FILE *p1,*p2;
	p1= fopen("f1.txt","r");
	p2=fopen("f2.txt","w");
	
	char buffer[25];
	char *tkn;
	int n,k,k1,s,l,r,i,t,s1,c;
	lc=0;
	
	while(fgets(buffer,90,p1))
	{
		n=sscanf(buffer,"%s%s%s%s",t1,t2,t3,t4);
		switch(n)
		{
			case 1:
					k=searchPOT(t1);
					if(k==1)				//start
					{
						fprintf(p2,"(AD,1) - (C,0)\n");
						
					}
					
					if(k==3)				//origin
					{
						lc= 0;
					}
					
					if(k==2)				//end
					{
						for(i=pool[pool_ind];i<lno;i++)
						{
							literal[i].addr=lc;
							tkn=getLiteral(literal[i].name);
							fprintf(p2,"[%d]  (AD,2) - 00%s\n",lc,tkn);
							lc++;	
						}
						
					}
					if(k==5)				//LTORG
					{
						for(i=pool[pool_ind];i<lno;i++)
						{
							literal[i].addr=lc;
							tkn=getLiteral(literal[i].name);
							fprintf(p2,"[%d]  (AD,5) - 00%s\n",lc,tkn);
							lc++;	
						}
						pool[++pool_ind]=lno;
						
					}
					if(k==-1)
					{
						printf("\nSINGLE TOKEN ERROR:\tTOKEN NOT FOUND IN POT\n");
						fprintf(p2,"\n----------------------------------------------");
						fprintf(p2,"\nError : Token not found in POT at loc[%d]\n",lc);
						error++;
						
					}
					
					break;
					
			case 2:
				/* start with addr,origin with addr,origin with label,print,read */
					k=searchPOT(t1);
					k1=searchMOT(t1);
					
					if(k==1)				//start with addr
					{
						lc=atoi(t2);
						fprintf(p2,"(AD,1) - (C,%d)\n",lc);
						
						
					}
					
					if(k==3)				//origin with addr and label
					{
						if(atoi(t2)>=1)
							lc= atoi(t2);
						else
						{
							for(i=0; i<=ind ;i++)
							{
								c=searchSymbol(t2,0);
							
							}
						
							if(c==0)
								{
								printf("\nTWO TOKEN ERROR: \tSYMBOL NOT FOUND\n");
								fprintf(p2,"\n----------------------------------------------");
								fprintf(p2,"\nError : Two token error(Symbol not found) [%d]\n",lc);
								error++;
											
								}
						}

						
					}
					
					
					if(k1==7 || k1==8)		//print and read
					{
							if(t2[0] =='=')		//for literal
							{
							
								l=searchLiteral(t2,1);
								
								fprintf(p2,"[%d]  (IS,%d) - (L,%d)\n",lc,k1,l);
								lc=lc+1;
							}
							else
							{
										
							//for symbol
							s=searchSymbol(t2,1);
							fprintf(p2,"[%d]  (IS,%d) - (S,%d)\n",lc,k1,s); 
							lc=lc+1;
							}
					
					}
					if(k== -1 && k1== -1)
					{
						printf("\nTWO TOKEN ERROR:\tTOKEN NOT FOUND IN MOT & POT\n");
						fprintf(p2,"\n----------------------------------------------");
						fprintf(p2,"\n Two Token Error : Token not found in MOT and POT[%d]\n",lc);
						error++;
					}
					
					break;
					
				case 3:
					k1=searchMOT(t1);
					k=searchPOT(t2);
					//MOVER AREG B
					//ADD AREG A
					if(k1!=-1)
					{
						r=searchREG(t2);
						if(r!= -1)
						{
						
							//for literal
							if(t3[0] =='=')
							{
							
								l=searchLiteral(t3,1);
								fprintf(p2,"[%d]  (IS,%d) %d (L,%d)\n",lc,k1,r,l);
								lc=lc+1;
							}
							else
							{
								//for symbol
								s=searchSymbol(t3,1);
								fprintf(p2,"[%d]  (IS,%d) %d (S,%d)\n",lc,k1,r,s);
								lc=lc+1;
							}
						}
						
						if(k1==10)
						{
							//BC LT A
							c=searchCMP(t2);
							if(c==-1)
							{
							printf("\nTHREE TOKEN ERROR:\tREGISTER NOT FOUND(BC statement)\n");
							fprintf(p2,"\n----------------------------------------------");
							fprintf(p2,"\nError : Register not found(BC statement) at [%d]\n",lc);
							error++;
							}
							
							
							s=searchSymbol(t3,1);
							fprintf(p2,"[%d]  (IS,%d) %d (S,%d)\n",lc,k1,c,s);
							lc=lc+1;
						

						}
						if(r==-1 & k1!=10)
						{
							printf("\nTHREE TOKEN ERROR:\tREGISTER NOT FOUND\n");
							fprintf(p2,"\n----------------------------------------------");
							fprintf(p2,"\nThree Token Error: Register not found [%d]\n",lc);
							error++;
						}
					}
					
					else if(k != -1)
					{
						// A DC 5
						//C DS 6
					
						if(k==6)		// DS
						{
							s=searchSymbol(t1,0);
							if(s!= 0)
							{
								symbol[s-1].addr=lc;
								fprintf(p2,"[%d]  (AD,%d) - 00%d\n",lc,k,atoi(t3));
								lc=lc+atoi(t3);
							}
							else
							{
								printf("\nTHREE TOKEN ERROR: \tSYMBOL NOT FOUND(in DS)\n");
								fprintf(p2,"\n----------------------------------------------");
								fprintf(p2,"\nThree Token Error : Symbol not found(DS statement)[%d]\n",lc);
								error++;
							}
						}
						
						if(k==7)		// DC
						{
							s=searchSymbol(t1,0);
							if(s!=0)
							{
								symbol[s-1].addr=lc;
								fprintf(p2,"[%d]  (AD,%d) - 00%d\n",lc,k,atoi(t3));
								lc=lc+1;
							}
							else
							{
								printf("\nTHREE TOKEN ERROR:\t SYMBOL NOT FOUND(in DC)\n");
								fprintf(p2,"\n----------------------------------------------");
								fprintf(p2,"\nThree Token Error :Symbol not found(DC)[%d]\n",lc);
								error++;
							}
						}
						
						if(k==4)	//LABEL EQU A
						{
							s=searchSymbol(t1,1);
							s1=searchSymbol(t3,1);
							if(s1!=0)
							{
								symbol[s-1].addr=symbol[s1-1].addr;
							}
							else
							{
								printf("\nTHREE TOKEN ERROR: \tSYMBOL NOT FOUND(in EQU)\n");
								fprintf(p2,"\n----------------------------------------------");
								fprintf(p2,"\nThree Token Error :Symbol not found(in EQU)[%d]\n",lc);
								error++;
							}
						}

						
					
					}
					
					else
					{
						//LOOP PRINT A
						k1=searchMOT(t2);
						if(k1==7 || k1==8)
						{
							s=searchSymbol(t1,1);
							symbol[s-1].addr=lc;
										
							//for symbol
							s1=searchSymbol(t3,1);
							fprintf(p2,"[%d]  (IS,%d) - (S,%d)\n",lc,k1,s1); 
							lc=lc+1;
					
						}
						else if(k1 == -1)
						{
							printf("\nTHREE TOKEN ERROR:\tTOKEN NOT FOUND IN MOT\n");
							fprintf(p2,"\n----------------------------------------------");
							fprintf(p2,"\nThree Token Error :Token not found in MOT[%d]\n",lc);
							error++;
					
						}						
											
					}
					break;
				
			case 4:
				//LABEL SUB BREG ='5'
				s=searchSymbol(t1,1);
				k1=searchMOT(t2);
				r=searchREG(t3);
					//label BC LE A
					if(k1== 10)
					{
						c=searchCMP(t3);
						if(t4[0] =='=')
						{
							
							l=searchLiteral(t4,1);
							fprintf(p2,"[%d]  (IS,%d) %d (L,%d)\n",lc,k1,c,l);
							lc=lc+1;
						}
						else
						{
							s=searchSymbol(t4,1);
							fprintf(p2,"[%d]  (IS,%d) %d (S,%d)\n",lc,k1,c,s);
							lc=lc+1;
						}
						
					}
					else if(r==-1 && k1!=10)
					{
						printf("\nFOUR TOKEN ERROR:\tREGISTER NOT FOUND\n");
						fprintf(p2,"\n----------------------------------------------");
						fprintf(p2,"\nFour Token Error :Register not found[%d]\n",lc);
						error++;
					}
					else
					{
						//for literal
						if(t4[0] =='=')
						{
							
							l=searchLiteral(t4,1);
							fprintf(p2,"[%d]  (IS,%d) %d (L,%d)\n",lc,k1,r,l);
							lc=lc+1;
						}
						else
						{
							s=searchSymbol(t4,1);
							fprintf(p2,"[%d]  (IS,%d) %d (S,%d)\n",lc,k1,r,s);
							lc=lc+1;
						}
					
					}	
				
				
				break;
				
					
		}
	}
	
	for(i=0;i<ind;i++)
	{
		int chk;
		if(symbol[i].addr=='\0')
		{
			printf("\nERROR!!\tSYMBOL LEFT TO BE ADDRESSED\n");
			fprintf(p2,"\n----------------------------------------------");
			fprintf(p2,"\nERROR!!\tSYMBOL LEFT TO BE ADDRESSED\n");
			error++;
		}
	}
	
	printf("\n\n LITERAL TABLE\n");
	printf("LNO\t\tNAME\t\tADDRESS");
	for(i=0;i<lno;i++)
	{
		printf("\n%d\t\t%s\t\t%d",literal[i].no,literal[i].name,literal[i].addr);
	}
	

	printf("\n\n SYMBOL TABLE\n");
	printf("SNO\t\tNAME\t\tADDRESS");
	for(i=0;i<ind;i++)
	{
		printf("\n%d\t\t%s\t\t%d",symbol[i].no,symbol[i].name,symbol[i].addr);
	}
	
	printf("\n\nPOOLTABLE:");
	for(i=0;i<pool_ind;i++)
	{
		printf("\n%d",pool[i]);
	}
	printf("\n");
	

	printf("\nTotal number of errors:%d\n\n",error);
	return 0;

}
