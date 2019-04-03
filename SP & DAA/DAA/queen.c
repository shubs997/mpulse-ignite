#include<stdio.h>
#include<math.h>
int board[10],count;

void main()
{
	int n,i,j,exit=0;
	void queen(int row,int n);
	printf("\nEnter the no. of queens\n");
	scanf("%d",&n);
	if(n==2 || n==3)
	{	
		printf("\nNO Feasible solution\n");
		exit;
	}
	else
	queen(1,n);
	return;
}

void  print(int n)
{
	int i,j;	
	printf("\nSolution %d:\n",++count);
	for(i=1;i<=n;++i)
	printf("\t %d",i);
	for(i=1;i<=n;++i)
	{
		printf("\n%d",i);
		for(j=1;j<=n;++j)
		{
			if(board[i]==j)
			printf("\tQ");
			else
			printf("\t-");	
				
		}		
	}printf("\n\n");	
}

int place(int row,int column)
{
	int i;
	for(i=1;i<=row-1;++i)
	{
		if(board[i]==column)
		return 0;
		if(abs(board[i]-column)==abs(i-row))
		return 0;	
	}
	return 1;	
}

void queen(int row,int n)
{
	int column;
	for(column=1;column<=n;++column)
	{
		if(place(row,column))
		{
			board[row]=column;
			if(row==n)
			print(n);
			else
			queen(row+1,n);
		}		
	}

}

