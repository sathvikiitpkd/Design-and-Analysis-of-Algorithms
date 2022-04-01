#include <stdio.h>
#include <stdlib.h>

//structure for linked list
struct node
{
	int item;
	int weight;
	struct node* next;
};
typedef struct node* nodeptr;

//structure of linked list storing vertices forming edge and its weight
struct nodestar
{
	int item;
	int value;
	int weight;
	struct nodestar* next;
};
typedef struct nodestar* Nodestar;

struct heaps
{
	int element;
	int shortest;
};
typedef struct heaps heap;

void Push(nodeptr *head,int num,int previous)
{
	nodeptr newnode;
	//dynamically allot a newnode
	newnode=(struct node *) malloc (sizeof(struct node));
	//linking newnode at top of stack
	newnode->item = num;
	newnode->weight = previous;
	newnode->next=*head;
	*head=newnode;
}
//return left child of i
int left(int i)
{
	return 2*i+1;
}

//return right child of i
int right(int i)
{
	return 2*i+2;
}

//return parent of i
int parent(int i)
{
	return (i-1)/2;
}

void minheapify(heap *H,int posn, int n)
{
	int l,r,small,temp,tempy;
	l=left(posn);
	r=right(posn);
	small=posn;
	//checking H[posn] and H[left] if H[posn] is larger then we need to swap it or either the index of left
	if(l<n && H[l].shortest <H[posn].shortest)
	{
		small=l;
	}
	//checking H[posn] and H[right] if H[posn] is larger then we need to swap it or either the index of right
	if(r<n && H[r].shortest < H[small].shortest)
	{
		small=r;
	}
	//if small is not equal to posn then swap element of index posn and small
	if(small != posn)
	{
		temp=H[posn].shortest;
		H[posn].shortest=H[small].shortest;
		H[small].shortest=temp;
		tempy=H[posn].element;
		H[posn].element=H[small].element;
		H[small].element=tempy;
		minheapify(H,small,n);
	}	
}

void siftup(heap *H,int pos)
{
	int temp;
	//if H[parent(pos)] is greater than H[pos] then swap its elements
	while(pos>0 && H[pos].shortest < H[parent(pos)].shortest)
	{
		temp=H[pos].shortest;
		H[pos].shortest=H[parent(pos)].shortest;
		H[parent(pos)].shortest=temp;
		temp=H[pos].element;
		H[pos].element=H[parent(pos)].element;
		H[parent(pos)].element=temp;
		pos=parent(pos);
	}
	return;
}

void Build_heap(heap *arr,int n)
{
	int i=parent(n);
	//we need to run while loop from parent(n) to 0
	while(i>=0)
	{
		minheapify(arr,i,n);
		i--;
	}
}

heap ExtractMin(heap *H,int *n) 		
{
	//swapping array with index 0 and last index
	heap temp;
	temp.element = H[0].element;
	temp.shortest = H[0].shortest;
	H[0].shortest=H[(*n)-1].shortest;
	H[0].element=H[(*n)-1].element;
	//removing last element from array 
	*n=(*n)-1;
	//minheapify for retaining min heap property
	minheapify(H,0,*n);
	return temp;
}

void Decreasekey(heap *H,int posn,int newval)
{
	/*if(posn == 3 && newval == 2)
	{
		for(int i=0;i<4;i++)
		{
			printf("%d\n",H[i].element);
		}
	}*/
	//if newval is greater than H[pos],we need not do anything
	if(H[posn].shortest <= newval)
	{	
		return;
	}
	//else siftup until it reaches correct posn
	
		H[posn].shortest = newval;
		siftup(H,posn);
	
}

void Enqueue(nodeptr *head,nodeptr *tail,int num,int weigh)
{
	nodeptr newnode;
	newnode=(struct node *) malloc (sizeof(struct node));
	newnode->item=num;
	newnode->weight = weigh;
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

void queue(Nodestar *head,Nodestar *tail,int num,int number,int weigh)
{
	//assigning data and link it with main linked list
	Nodestar newnode;
	newnode=(Nodestar) malloc (sizeof(struct node));
	newnode->item=num;
	newnode->value=number;
	newnode->weight = weigh;
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
	int i,t,weigh,n,x,y,source,index;
	scanf("%d",&n);
	//define array of linked lists
	nodeptr head[n+1],tail[n+1];
	//arrays for predecessor,cost,visited
	int pred[n+1],cost[n+1],visited[n+1];
	heap array[n-1],str;
	nodeptr temp,tempptr;
	Nodestar T=NULL,H=NULL;
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
				scanf("%d",&y);
				Enqueue(&head[i],&tail[i],x,y);
			}
			else if(x==-1)
			{
				i++;
				break;
			}
		}
	}
	scanf("%d",&source);
	//prim algorithm
	for(i=1;i<=n;i++)
	{
		visited[i] = 0;
	}
	visited[source] = 1;
	for(i=2;i<=n;i++)
	{
		cost[i] = 999999;
		pred[i] = -1;
	}
	temp=head[source];
	while(temp != NULL)
	{
		cost[temp->item] = temp->weight;
		pred[temp->item] = source;
		temp=temp->next;
	}
	//Build Queue Q with v1,v2...vsource-1 vsource+1 .....vn
	for(i=0;i<n-1;i++)
	{
		if(source <= i+1)
		{	
			array[i].element = i+2;
			array[i].shortest = cost[i+2];
		}
		if(source > i+1)
		{
			array[i].element = i+1;
			array[i].shortest = cost[i+1];
		}
	}
	Build_heap(array,n-1);
	n = n-1;
	//While Q not empty
	while(n != 0)
	{	
		index = -1;	
		str = ExtractMin(array,&(n));
		t = str.element;
		i = str.shortest;
		//add extracted element to S from S'
		visited[t] = 1;
		//T = T U {(t,prev(t))}
		queue(&T,&H,t,pred[t],i);
		tempptr = head[t];
		//for vj belongs to Adj(t)
		while(tempptr != NULL)
		{
			//initialise index to -1
			index = -1;
			//check for un-finalised vertices
			if(visited[tempptr->item] == 0)
			{
				//add lightest edge across t
				if(cost[tempptr->item] > tempptr->weight)
				{
					for(i=0;i<n;i++)
                    				{
                        				if (array[i].element == tempptr->item)
                        				{
                            					index = i;
                        				}
                        				if (index != -1)
                        				{
                            					break;
                        				}
                    				}
					cost[tempptr->item] = tempptr->weight;
					Decreasekey(array,index,tempptr->weight);
					//set its predecessor accordingly
					pred[(tempptr->item)] = t;
				}
			}
			tempptr = tempptr->next;
		}
	}
	//traverse and print the vertices and its weight
	while(T !=NULL)
	{
		printf("%d %d %d\n",T->value,T->item,T->weight);
		T = T->next;
	}
	return 0;
}
