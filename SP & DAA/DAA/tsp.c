
/* Travelling Salesperson Problem to find optimal path and cost */

#include<stdio.h>
#define INFINITY 999
#define NEWLINE printf("\n");

int n;
int pos=0;

void print_graph(int graph[][n])
{
 int i,j;
 for(i=0;i<n;i++)
 {
  for(j=0;j<n;j++)
  {
   printf("%d\t",graph[i][j]);
  }NEWLINE
 }
}

int row_minimization(int graph[][n], int flag)
{
 int i,j,k;
 int row_min,rm=0;
 for(i=0;i<n;i++)
 {
  row_min=INFINITY;
  for(j=0;j<n;j++)
  {
   if(graph[i][j]<row_min)
     row_min=graph[i][j];
  }
  if(row_min==INFINITY)
    row_min=0;
  if(flag==1)
  {
   for(k=0;k<n;k++)
   {
    if(graph[i][k]!=INFINITY)
      graph[i][k]-=row_min;
   }
  }
  rm+=row_min;
 }
 return(rm);
}

int col_minimization(int graph[][n], int flag)
{
 int i,j,k;
 int col_min,cm=0;
 for(i=0;i<n;i++)
 {
  col_min=INFINITY;
  for(j=0;j<n;j++)
  {
   if(graph[j][i]<col_min)
     col_min=graph[j][i];
  }
  if(col_min==INFINITY)
    col_min=0;
  if(flag==1)
  {
   for(k=0;k<n;k++)
   {
    if(graph[k][i]!=INFINITY)
      graph[k][i]-=col_min;
   }
  }
  cm+=col_min;
 }
 return(cm);
}

int visited(int path[], int k)
{
 int i;
 for(i=0;i<pos;i++)
 {
  if(k==path[i])
    return 1;
 }
 return 0;
}

void copy(int a[][n], int b[][n])
{
 int i,j;
 for(i=0;i<n;i++)
 {
  for(j=0;j<n;j++)
  {
   a[i][j]=b[i][j];
  }
 }
}

void select_row(int matrix[][n], int prev_node)
{
 int i;
 for(i=0;i<n;i++)
 {
  matrix[prev_node][i]=INFINITY;
 }
}

void select_col(int matrix[][n], int prev_node)
{
 int i;
 for(i=0;i<n;i++)
 {
  matrix[i][prev_node]=INFINITY;
 }
}

void set_infinity(int matrix[][n], int path[])
{
 int i;
 for(i=1;i<pos;i++)
 {
  matrix[path[i]][0]=INFINITY;
 }
}

void main()
{
 int i,j;
 int rm,cm,cost,opt_cost,temp_cost;
 int prev_node,node;
 printf("Enter number of vertices: ");
 scanf("%d",&n);
 int graph[n][n], matrix[n][n], temp_mat[n][n];
 int path[n];
 printf("Enter graph:\n");
 for(i=0;i<n;i++)
 {
  for(j=0;j<n;j++)
  {
   scanf("%d",&graph[i][j]);
  }
 }
 printf("Entered graph:\n");
 print_graph(graph);
 rm=row_minimization(graph,1);
 cm=col_minimization(graph,1);
 /*printf("Fully reduced graph:\n");
 print_graph(graph);*/
 opt_cost=rm+cm;
 pos=0;
 path[pos]=0;
 pos++;
 prev_node=0;
 copy(matrix,graph);
 while(1)
 {
  cost=INFINITY;
  for(i=1;i<n;i++)
  {
   select_row(matrix,prev_node);	//row of visited node is made infinity
   if(!visited(path,i))
   {
    select_col(matrix,i);	//column of current node is made infinity
    set_infinity(matrix,path);
    rm=row_minimization(matrix,0);
    cm=col_minimization(matrix,0);
    temp_cost=opt_cost+rm+cm+graph[prev_node][i];	//calculate cost
    if(temp_cost<cost)
    {
     cost=temp_cost;		//minimum cost
     node=i;			//next node to be visited
     copy(temp_mat,matrix);
    }
	
    copy(matrix,graph);
   }
  }

  path[pos]=node;
  pos++;
  opt_cost=cost;
  prev_node=node;
  if(pos==n)
    break;
  copy(graph,temp_mat);
 }
printf("Fully reduced graph:\n");
 print_graph(graph);
 printf("Optimal path is:\n");
 for(i=0;i<pos;i++)
 {
  printf("%d->",path[i]);
 }
 printf("%d\n",path[0]);
 printf("Optimal Cost is %d\n",opt_cost);
}

/* Output:
amita@ubuntu:~/TE/SEM-II/DAA$ gcc tsp.c
amita@ubuntu:~/TE/SEM-II/DAA$ ./a.out
Enter number of vertices: 5
Enter graph:
999	 20	 30	 10	 11
15	 999	 16	 4	 2 
3	 5	 999	 2	 4 
19	 6	 18	 999	 3
16	 4	 7	 16	 999
Entered graph:
999	20	30	10	11	
15	999	16	4	2	
3	5	999	2	4	
19	6	18	999	3	
16	4	7	16	999	
Fully reduced graph:
999	10	17	0	1	
12	999	11	2	0	
0	3	999	0	2	
15	3	12	999	0	
11	0	0	12	999	
Optimal path is:
0->3->1->4->2->0
Optimal Cost is 28
 */
