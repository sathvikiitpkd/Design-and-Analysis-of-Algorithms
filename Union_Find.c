#include <stdio.h>
#include <stdlib.h>

//creating structure of node
struct node
{
	int item;
	int parent;
	struct node * next;
};
typedef struct node *nodeptr;

//Globally initialise and declare head to NULL
nodeptr head=NULL;

//Function for making sets
void Makeset(int x,int parent[],int rank[])
{
	parent[x] = x;
	rank[x] = 0;
}

//Function to find x and return its Set Identifier
int Find(int x, int parent[], int rank[])
{
	int y,z,p;
	y = x;
	//run while loop till parent of y is itself
	while(parent[y] != y)
	{
		y = parent[y];
	}
	z = x;
	//Path Compression
	//setting parent of each element in the path from x to root(set identifier) to set identifier
	while(parent[z] != z)
	{
		p = parent[z];
		parent[z] = y;
		z = p;
	}
	return y;	
}

//Function for Union of set containing x and  set containing y
void Union(int x, int y,int parent[],int rank[])
{
	int p,q,a,b;
	//find for x,y if both are same set then nothing to do
	p = Find(x,parent,rank);
	q = Find(y,parent,rank);
	if(p == q)
	{
		return;
	}
	//if not in same set 
	else
	{
		a = rank[p];
		b = rank[q];
		//According to rank of set identifiers of set containing x and y ; set parent according
		//if rank of set identifiers of set containing x and y are same,then increment rank of set identifier of set containing x
		if(a == b)
		{
			parent[q] = p;
			rank[p] = rank[p] + 1;
		}
		else if(a < b)
		{
			parent[p] = q;
		}
		else
		{
			parent[q] = p;
		}
	}
}	
		

int main()
{
	int i,n,no,num,a,b,element;
	/*A positive integer n is taken as the first line of the input and it is assumed that the universal set contains elements 1 to n. After reading n,
	the program will create n singleton sets using Makeset operations.*/
	scanf("%d",&no);
	int parent[no],rank[no];
	for(i=0;i<no;i++)
	{
		Makeset(i+1,parent,rank);
	}
	while(1)
	{
		//depending on input function is menu driven
		scanf("%d",&n);
		if(n == 1)
		{
			scanf("%d",&num);
			element = Find(num,parent,rank);
			printf("%d\n",element);
		}
		if(n == 2)
		{
			scanf("%d%d",&a,&b);
			Union(a,b,parent,rank);
			element = Find(a,parent,rank);
			printf("%d %d\n",element,rank[element]);
		}
		if(n == 3)
		{
			for(i=0;i<no;i++)
			{
				element = Find(i+1,parent,rank);
				printf("%d %d\n",i+1,element);
			}
		}
		if(n == 4)
		{
			return 0;
		}
	}
	return 0;
}
