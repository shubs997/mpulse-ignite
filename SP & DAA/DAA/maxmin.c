#include<stdio.h>
int a[10],max=0,min=999;
#define exit 0
void MaxMin(int i,int j)
{
	int mid;
	if(i==j)
	{
		if(a[i]>max)
		{
			max=a[i];
		}	
		if(a[i]<min)
		{
			min=a[i];
		}	
	}
	else
	{
		mid=(i+j)/2;
		MaxMin(i,mid);
		MaxMin(mid+1,j);	
	}
}

int main()
{
	int m,n;
	printf("\nSize Of Array\n");
	scanf("%d",&n);
	if(n==0)
	{
		printf("\nNot a valid array\n");
		exit;
	}
	else
	{
		printf("\nEnter the %d values of array \n",n);
		for(m=0;m<n;m++)
		scanf("%d",&a[m]);
	}
	MaxMin(0,n-1);
	printf("\nThe Max no. in array is : %d\n",max);
	printf("\nThe Min no. in array is : %d\n",min);

}




