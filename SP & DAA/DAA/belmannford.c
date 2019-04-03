#include<stdio.h>
int flag=0;
int dist[10],parent[10];
int belmannford(int weight[10][10],int v,int edge[10][2],int k)
{
	int i,s,j;
	int x,y;
	for(i=0;i<=v;i++)
	{
		dist[i]=1111;
		parent[i]=-1;
	}
	printf("\nEnter the Source Vertex");
	scanf("%d",&s);
	dist[s]=0;
	for(i=0;i<v;i++)
	{
		for(j=0;j<k;j++)
		{
			x=edge[j][0];
			y=edge[j][1];
			if(dist[y]>(dist[x]+weight[x][y]))
			{
				dist[y]=(dist[x]+weight[x][y]);
				parent[y]=x;
			}					
		}
	}
	for(j=0;j<k;j++)
	{
		x=edge[j][0];
		y=edge[j][1];
		if(dist[y]>(dist[x]+weight[x][y]))
		{
			flag=1;
			return flag;
		}					
	}
}
int main()
{
	int v,i,j,k=0,edge[10][2],weight[10][10];
	printf("\nEnter The No Of Vertices");
	scanf("%d",&v);
	for(i=0;i<v;i++)
	{
		for(j=0;j<v;j++)
		{
			if(i!=j)
			{
				printf("\nEnter The Weight of (%d , %d)",i,j);
				scanf("%d",&weight[i][j]);
				if(weight[i][j]!=0)				
				{
					edge[k][0]=i;
					edge[k++][1]=j;
				}
			}
			else
			{
				weight[i][j]=0;
			}
		}
	}
	flag=belmannford(weight,v,edge,k);
	if(flag==1)
	{
		printf("\nNegative Weight Exists");
	}
	else
	{
		printf("\nNegative Weight doesnt Exists\n\n\n");
		printf("\n------MATRIX-----");		
		for(i=0;i<=v;i++)
		{
			printf("\n");
			for(j=0;j<=v;j++)
			{
				printf("\t");
				printf("%d",weight[i][j]);
			}		
		}		
		printf("\n------EDGES----");
		for(i=0;i<k;i++)
		{
			printf("\n");
			for(j=0;j<2;j++)
			{
				printf("(%d)",edge[i][j]);									
			}		
		}
		printf("\n");
		printf("\nVertex\tWeight\tParent\n");
		for(i=0;i<=v;i++)
		{
			printf("\n%d\t%d\t%d",i,dist[i],parent[i]);
		}
	}
	printf("\n");
}
