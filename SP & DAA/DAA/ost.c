#include<stdio.h>

int n, sum=0, psum=0;
int L[10];
int RT[10];
int F,t,j,i;

void optimal();
void sort();

int main()
{
	optimal();
	return 0;

}

void optimal()
{
	printf("Enter the no. of programs: ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Program no %d size: ",i+1);
		scanf("%d",&L[i]);
	}
	int k=0, i;
	printf("\nOriginal program length: ->");
	for(i=0;i<n;i++)
		{
			printf("%d\t",L[i]);

		}
	sort();
	printf("\nSorted program length: ->");
	for(i=0;i<n;i++)
		{
			printf("%d\t",L[i]);

		}
	
	for(i=0;i<n;i++)
	{
		t=0;
		for(j=0;j<=i;j++)
		{
			t=t+L[j];
		}
		
		RT[i]=t;
	}
	
	F=0;
	for(i=0;i<n;i++)
	F=F+RT[i];
	

	
	printf("\nTotal retrieval time: -> %d", F);
	printf("\nMean retrieval time: -> %d", F/n);

	
}

void sort()
{
	int i, j, temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(L[j]>L[j+1])
			{
				temp=L[j];
				L[j]=L[j+1];
				L[j+1]=temp;

			}

		}

	}
}
