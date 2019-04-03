#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char MOT[][15]= {"MOVER", "MOVEM", "ADD", "SUB", "MUL", "DIV", "PRINT", "READ", "COMP", "BC"}; //IS
char POT[][10]= {"START","END", "ORIGIN", "EQU", "LTORG","DS","DC"};  //AD
char REG[][10]={"AREG", "BREG", "CREG", "DREG"};
char BC[][5]={"LT","GT","GE","LE"};
typedef struct sym_table
{
	int index;
	char name[10];
	int addr;


}table;
table s1[10];


typedef struct lit_table
{
	int lit_no;
	char lit_name[10];
	int lit_addr; 

}l_table;
l_table l1[10];

int pool_tab[10];
int pool_cnt;
int flag;


int search_BC(char a[10])
{

  int i;
     flag=0;

	for(i=0;i<5;i++)
	{
		
		
	if(!strcmp(BC[i],a))
	{
	flag=1;
	printf("\nhi");
	return i; 
	
	}
	}		

	if(flag==0)
	return -1;

}
int search_sym(char a[10])
{

  int i;
     flag=0;

	for(i=0;i<7;i++)
	{
		
		
	if(!strcmp(s1[i].name,a))
	{flag=1;
	//printf("found!");
	return i; 
	
	}
}		

	if(flag==0)
	return -1;

}
int search_lit(char a[10])
{

  int i;
     flag=0;

	for(i=0;i<pool_cnt;i++)
	{
		
		
	if(!strcmp(l1[i].lit_name,a))
	{flag=1;
	printf("%s",l1[i].lit_name);
	return i; 
	
	}
}		

	if(flag==0)
	return -1;

}
int search_mot(char a[10])
{
     int i;
     flag=0;
	for(i=0;i<10;i++)
	{
		
		
	if(!strcmp(MOT[i],a))
	{flag=1;
	return i; 
	
	}
}
	if(flag==0)
	return -1;
}

int search_pot(char a[10])
{
     int i;
     flag=0;
	for(i=0;i<7;i++)
	{
		
		
	if(!strcmp(POT[i],a))
	{flag=1;
	return i; 
	
	}
}
	if(flag==0)
	return -1;
}


int search_reg(char a[10])
{
     int i;
     flag=0;
	for(i=0;i<7;i++)
	{
		
		
	if(!strcmp(REG[i],a))
	{flag=1;
	return i; 
	
	}
}
	if(flag==0)
	return -1;
}

int main()
{
	FILE *fp, *fp2;
	char t1[10], t2[10], t3[10],t4[10] ,buff[80],name[10];
	int n,k,p,l,i,d;
	int lc, n1,n2,n3,n4,s,r,sym_cnt,lit_cnt,b;	
	p=0;
	sym_cnt=0;
	lit_cnt=0;
	pool_cnt=0;
	
	fp=fopen("a.txt", "r");
		//printf("\n\n");
        fp2=fopen("b.txt", "w");
	while(fgets(buff,80, fp))
	{	/*
		t1[0]=NULL;
		t2[0]=NULL;
		t3[0]=NULL;
		*/		
		n=sscanf(buff, "%s%s%s%s", t1, t2, t3, t4);
		switch(n)
	{
		case 1: 

		
		
		n1=search_pot(t1);  //start
		
		if(n1==0)   //start with no constant
		{
		
		lc=0;
		fprintf(fp2,"\n  (AD, 00) - (C,0) ");
		
		}
		
		if(n1==2) //origin
		{
		
			lc=0;
			fprintf(fp2,"\n");
			
		
		}
		
		
		
		
		if(n1==4) //ltorg
		{	
			

			for(i=pool_tab[pool_cnt];i<lit_cnt;i++)
			{
				
				strcpy(name,&l1[i].lit_name[1]);
				fprintf(fp2,"\n %d) (AD, %d) - %d ",lc, n1, atoi(name));
				l1[i].lit_addr=lc;
				lc++;
				
			}
			//pool_cnt++;
			
			pool_tab[pool_cnt]=lit_cnt;
			//pool_tab[pool_cnt]=l1[lit_cnt--].lit_no;
			
			
		}
		if(n1==-1)
			printf("\nAssembly Directive does not exist");

		if(n1==1) //end
		{
			for(i=pool_tab[pool_cnt];i<lit_cnt;i++)
			{
				
				strcpy(name,&l1[i].lit_name[1]);
				fprintf(fp2,"\n %d) (AD, %d) - %d ",lc, n1, atoi(name));
				l1[i].lit_addr=lc;
				lc++;
				
			}
	printf("\nSymbol table");
printf("\nindex \t name  \taddr ");
	for(i=0;i<sym_cnt;i++)
	{
	
	printf("\n%d\t%s\t%d", s1[i].index,s1[i].name,s1[i].addr);
	}	

printf("\nLiteral table");
printf("\nindex \t name  \taddr ");
	for(i=0;i<lit_cnt;i++)
	{
	
	printf("\n%d\t%s\t%d", l1[i].lit_no,l1[i].lit_name,l1[i].lit_addr);
	}	
printf("\npool table");
for(i=0;i<pool_cnt;i++)
	{
	printf("\n%d",pool_tab[i]);}
		
		}
	

	break;

		
		
		
		
		case 2:

		n1=search_pot(t1);
		
		n2=search_mot(t1);
		
		
		
		if(n1!=-1)  //FOR POT
		{
			if(n1==0)
		{

		lc=atoi(t2);  //start with constant
		fprintf(fp2,"\n   (AD, %d) - (c, %d) ", n1,lc);
		

		}
		
		
		if(n1==2) //origin
		{
			k=search_sym(t2);
			if(k!=-1)
			{
			lc=s1[k].addr;
			
			}
			else
			{
			lc=atoi(t2);
			//fprintf(fp2,"\n");
			
			}
			
			
		
		}
		
		}
		
	else if(n2!=-1)
	{

		
		if(n2==06 || n2==07) 
		{
		
		if(t2[0]=='=')
		{
		
				l=search_lit(t2); 
				printf("%d",l);    //print/read with literal
				if(l==-1)
				{
				l1[lit_cnt].lit_no=lit_cnt;
				strcpy(l1[lit_cnt].lit_name,t2);
				//printf("%s",l1.lit_name);
				fprintf(fp2,"\n %d)(IS, %d) - (L, %d)", lc,n2,lit_cnt);
				lit_cnt++;
				lc++;
				//l=0;
			
			}
			else 
			{
							//printf("%s",l1.lit_name);
				fprintf(fp2,"\n %d)(IS, %d) - (L, %d)",lc, n2,l);
				//lit_cnt++;
				lc++;
			}	
		
		}
		
		else
		{
		
		

		k=search_sym(t2); 	//print/read with symbol
		
		
			if(k==-1)
			{
				s1[sym_cnt].index=sym_cnt;
				strcpy(s1[sym_cnt].name,t2);
                                s1[sym_cnt].addr=lc;
				fprintf(fp2,"\n %d)(IS, %d) - (s, %d)", lc,n2,sym_cnt);
				sym_cnt++;
				lc++;
			}
			
			else
			
			{	fprintf(fp2,"\n %d)(IS, %d) - (s, %d)",lc, n2,k);
				lc++;
			}	
		}
		}
		
	

	}	


else
		
		fprintf(fp2,"\nError! Immediate statement does not exists");
		
		break;
		
		
		case 3:
	
		
		n3=search_mot(t1);
		if(n3==9)
	{
		printf("\nIn BC");
		s=search_BC(t2);
		r=search_sym(t3);
		if(r!=-1)
		{
		
		fprintf(fp2,"\n %d)(IS, 9) %d (S, %d)",lc,s,sym_cnt);
				lc++;
		}
		else
		{
		s1[sym_cnt].index=sym_cnt;
		strcpy(s1[sym_cnt].name,t3);
                s1[sym_cnt].addr=lc;
		fprintf(fp2,"\n %d)(IS, 9) %d (S, %d)",lc,s,sym_cnt);
		sym_cnt++;
		lc++;

		}

	}
		
		
		if(n3==0 || n3==1 || n3==2 || n3==3 ||n3==4|| n3==8) //MOVER, MOVEM,ADD,SUB
		{
		r=search_reg(t2);
		if(r==-1)
		fprintf(fp2,"\nError! Register does not exists");
else
{
		k=search_sym(t2); 
		if(t3[0]=='=')
		{
		
				l=search_lit(t3); 
				//printf("%d",l);    //print/read with literal
				if(l==-1)
				{
				l1[lit_cnt].lit_no=lit_cnt;
				strcpy(l1[lit_cnt].lit_name,t3);
				//printf("%s",l1.lit_name);
				

				fprintf(fp2,"\n %d)(IS, %d) %d (L, %d)", lc,n3,r,lit_cnt);
				lit_cnt++;
				lc++;
				//l=0;
			
				}
			else 
			{
							//printf("%s",l1.lit_name);
											
				fprintf(fp2,"\n %d)(IS, %d) %d (L, %d)",lc, n3,r,l);
				//lit_cnt++;
				lc++;
			}	
		
		}
		
		else
		{
		
		

		k=search_sym(t3); 	//print/read with symbol
		
		
			if(k==-1)
			{
				s1[sym_cnt].index=sym_cnt;
				strcpy(s1[sym_cnt].name,t3);
                                 
				fprintf(fp2,"\n %d)(IS, %d) %d (S, %d)", lc,n3,r,sym_cnt);
				sym_cnt++;
				lc++;
			}
			
			else
			
			{				
			fprintf(fp2,"\n %d)(IS, %d) %d (S, %d)",lc, n3,r,k);
				lc++;
			}
			
		}
}
}

		d=search_pot(t2);
		

	if(d==5)                          // a ds 5
	{ 
		fprintf(fp2,"\n %d) -  -  -", lc);
		r=search_sym(t1);
		s1[r].addr=lc;
		k=atoi(t3);
		lc=lc+k;
		
	}
	if(d==6)
	{
		fprintf(fp2,"\n %d) -  -  -", lc);
		r=search_sym(t1);
		s1[r].addr=lc;
		lc++;

	}
	if(d==3)				//label equ loop
	{
		k=search_sym(t3);
		r=s1[k].addr;
		
				s1[sym_cnt].index=sym_cnt;
				strcpy(s1[sym_cnt].name,t1);
                                 s1[sym_cnt].addr=r;
				sym_cnt++;
			
			
					

	}

	n2=search_mot(t2);
	if(n2==6)					//loop print b
	{
		 s1[sym_cnt].index=sym_cnt;
		strcpy(s1[sym_cnt].name,t1);
                    s1[sym_cnt].addr=lc;
		sym_cnt++;
		fprintf(fp2,"\n %d)(IS, %d) - (S, %d)", lc,n2,sym_cnt);
		s1[sym_cnt].index=sym_cnt;
		strcpy(s1[sym_cnt].name,t3);

		sym_cnt++;
                    //s1[sym_cnt].addr=lc;


	}
		s=search_sym(t1);


	


                break;


        case 4:  
               
                n3=search_mot(t2);
		s=search_sym(t1);
		r=search_reg(t3);
        		
        		if(s==-1)
        		{
        		      s1[sym_cnt].index=sym_cnt;
				strcpy(s1[sym_cnt].name,t1);
                                 s1[sym_cnt].addr=lc;
				fprintf(fp2,"\n %d)(IS, %d) %d (S, %d)", lc,n3,r,sym_cnt);
				sym_cnt++;
				lc++;  
        		}
        		
			if(t4[0]=='=')
		{
		
				l=search_lit(t4); 
				//printf("%d",l);    //print/read with literal
				if(l==-1)            //not present then insert
				{
				l1[lit_cnt].lit_no=lit_cnt;
				strcpy(l1[lit_cnt].lit_name,t4);
				//printf("%s",l1.lit_name);
				
                                
				fprintf(fp2,"\n %d)(IS, %d) %d (L, %d)", lc,n3,r,lit_cnt);
				lit_cnt++;
				lc++;
				//l=0;
			
			        }
			else 
			{
							//printf("%s",l1.lit_name);
											
				fprintf(fp2,"\n %d)(IS, %d) %d (L, %d)",lc, n3,r,lit_cnt);
				//lit_cnt++;
				lc++;
			}	
		
		}
		
		else
		{
		
		

		k=search_sym(t1); 	//print/read with symbol
		
		
			if(k==-1)
			{
				s1[sym_cnt].index=sym_cnt;
				strcpy(s1[sym_cnt].name,t1);
                                 s1[sym_cnt].addr=lc;
				fprintf(fp2,"\n %d)(IS, %d) %d (S, %d)", lc,n3,r,sym_cnt);
				sym_cnt++;
				lc++;
			}
			
			else
			
			{				
			fprintf(fp2,"\n %d)(IS, %d) %d (S, %d)",lc, n3,r,sym_cnt);
				lc++;
			}	
		}

                break;
        }

	}
	
	
	
	}
	



