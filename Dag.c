#include <stdio.h>
#include <stdlib.h>

//structure for linked list
struct node
{
	int item;
	struct node* next;
};
typedef struct node* nodeptr;

//define visited,entry and exi,initially clock=0;
int visited[100000],entry[100000],exi[100000],pred[100000],clock=0;
nodeptr newelement=NULL;

void Push(int num)
{
	nodeptr newnode;
	//dynamically allot a newnode
	newnode=(struct node *) malloc (sizeof(struct node));
	//linking newnode at top of stack
	newnode->item=num;
	newnode->next=newelement;
	newelement=newnode;
}

void Pop()
{
	//create temp nodeptr
	nodeptr temp;
	//point head to temp
	temp=(newelement);
	//pop the top element of stack
	if(newelement !=NULL)
	{
		printf("%d\n",newelement->item);
		newelement=newelement->next;
		free(temp);
	}
}

//function for exploring adjacent vertices of v 
void Dfsexplore(nodeptr *head,int v,int n)
{
		//Take a note of entry times of v using global clock
		visited[v]=1;
		printf("%d ",v);
		entry[v]=clock;
		clock=clock+1;
		//declare temp and set head[v] to temp
		nodeptr temp;
		temp=head[v];
		//Check whether adjacent vertices are visited or not if not visit it via recursively calling Dfsexplore
		while(temp != NULL)
		{
			if(visited[(temp->item)] ==0)
			{
				//pred is not 
				pred[(temp->item)]=v;
				Dfsexplore(head,(temp->item),n);
			}
			temp=temp->next;
		}
		//Take a note of exit times of v using global clock
		//Push vertice v to the stack since first exitted element will be pushed first
		Push(v);
		exi[v]=clock;
		clock=clock+1;
}

void DepthFirstSearch(nodeptr *head,int n,int start)
{
	int i;
	//initialise visited,entry time,exit times such that no vertice is visited first
	clock=0;
	for(i=1;i<=n;i++)
	{
		visited[i]=0;
		pred[i]=-1;
		entry[i]=-1;
		exi[i]=-1;
	}
	//check start index's vertice whether is visited or not
	Dfsexplore(head,start,n);
	//Then check for all vertices
	for(i=1;i<=n;i++)
	{
		if(visited[i]==0)
		{
			Dfsexplore(head,i,n);
		}
	}
}

//creating function for Enqueue
void Enqueue(nodeptr *head,nodeptr *tail,int num)
{
	nodeptr newnode;
	newnode=(struct node *) malloc (sizeof(struct node));
	newnode->item=num;
	newnode->next=NULL;
	//linking newnode at tail of queue
	if(*head==NULL) //enqueuing first vertice
	{
		(*head)=newnode;
		(*tail)=newnode;
	}
	else
	{	
		(*tail)->next=newnode;
		(*tail)=newnode;
	}
}

int main()
{
	int n,i,x,y,start,flag=0,j;
	scanf("%d",&n);
	int arr[n][2];
	for(j=0;j<1;j++)
	{
		for(i=0;i<n;i++)
		{
			arr[i][j]=-1;
		}
	}
	j=0;
	//define array of linked lists
	nodeptr head[n],tail[n];
	//initialise it to NULL
	for(i=1;i<=n;i++)
	{
		head[i]=NULL;
		tail[i]=NULL;
	}
	i=1;
	//storing neighboring elements in adjacency list of that vertex until x is -1 and then increment i
	while(i<=n)
	{
		while(1)
		{
			scanf("%d",&x);
			if(x!=-1)
			{
				Enqueue(&head[i],&tail[i],x);
			}
			else
			{
				i++;
				break;
			}
		}
	}
	scanf("%d",&start);
	DepthFirstSearch(head,n,start);
	//for loop for checking whether a edge is back egde or not and if its a back edge stored in an array
	for(i=1;i<=n;i++)
	{
		while(head[i] != NULL)
		{
			if((entry[(head[i]->item)] < entry[i])&& (entry[i] < exi[i]) && (exi[i] < exi[(head[i]->item)]))
			{
				flag=1;
				arr[j][0]=i;
				arr[j][1]=head[i]->item;
				j++;
			}
			head[i]=head[i]->next;
		}
	}
	//print entry,exit,pred times of all vertices
	for(i=1;i<=n;i++)
	{
		printf("%d %d %d\n",entry[i],exi[i],pred[i]);
	}
	//if Directed cycle has back edge then it is not a Dag and viceversa
	if(flag != 1)
	{
		printf("DAG\n");
	}
	else
	{
		printf("Not a DAG\n");
	}
	j=0;
	//if it is a Dag,print the topological o0rdering of directed graph
	if(flag !=1)
	{
		for(i=0;i<n;i++)
		{
			Pop();
		}
	}
	//else print entry and exit times of vertices with back edges
	else
	{
		while(arr[j][0] != -1)
		{
			printf("%d %d %d %d\n",entry[arr[j][1]],entry[arr[j][0]],exi[arr[j][0]],exi[arr[j][1]]);
			j++;
		}
	}
	return 0;
}
