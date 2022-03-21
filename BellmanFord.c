#include <stdio.h>
#include <stdlib.h>

//structure for linked list
struct node
{
    int item;
    struct node* next;
};
typedef struct node* nodeptr;
nodeptr newelement = NULL;

//function for pushing element to stack
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

//function for poping elements from stack
void Pop()
{
    //create temp nodeptr
    nodeptr temp;
    //point head to temp
    temp=(newelement);
    //pop the top element of stack
    if(newelement !=NULL)
    {
        printf("%d ",newelement->item);
        newelement=newelement->next;
        free(temp);
    }
}

//function for bellman ford algorithm
int Bellman(int s,int m,int w[m][3],int *d,int* pred,int n)
{
    int i,j,x,y,u,v,weight,update,prev;
    //set shortest distance of source as 0 and set update as zero
    update=0;
    d[s]=0;
    //run loop n-1 times
    for(i=1;i<n;i++)
    {
        update=0;
        for(j=1;j<=m;j++)
        {
            u=w[j][0];
            v=w[j][1];
            weight=w[j][2];
            //update d[v] if it is greater than d[u]+weight
            if(d[v] > d[u] + weight)
            {
                d[v] = d[u] +weight;
                pred[v]=u;
                update = 1;
            }
        }
        //if update is zero we need to break since there will not be any futher update
        if(update == 0)
        {
            break;
        }
    }
    //run loop for nth time
    for(j=1;j<=m;j++)
    {
        u=w[j][0];
        v=w[j][1];
        weight=w[j][2];
        //if there is any update,indicates there is negative edge cycle and store the first changed d[v] into an arrray
        if(d[v] > d[u] + weight)
        {
            d[v] = d[u] +weight;
            pred[v]=u;
            update = 1;
            prev = v;
            break;
        }
    }
        //if there is an update,there is negative edge cycle
        if(update==1)
        {
            //declare and initialise visited[n]
            int visited[n];
            for(i=1;i<=n;i++)
            {
                visited[i] = 0;
            }
            //now backtract the path of the first changed d[v] in last round till a particular vertex is appeared twice
            x = prev;
            while(visited[x] != 2)
            {
                Push(x);
                visited[x] = visited[x]+1;
                x=pred[x];
            }
            //Here x indicates  first one to encounter in negative edge edge while retracing the path predecessors from v
            return x;
        }
        
    return update;    
}
         
    
int main()
{
    int n,m,i,x,y,z,update,start;
    scanf("%d %d",&n,&m);
    int d[n+1];
    int w[m+1][3];
    int pred[n+1];
    for(i=1;i<=n;i++)
    {
        d[i] = 1000000;
        pred[i] = -1;
    }
    //initialise w[m][3] to zero
    for(i=1;i<=m;i++)
    {
        w[i][0]=0;
        w[i][1]=0;
        w[i][2]=0;
    }
    //scan and store x,y,z in w[i][0],w[i][1],w[i][2]
    for(i=1;i<=m;i++)
    {
        scanf("%d %d %d",&x,&y,&z);
        w[i][0]=x;
        w[i][1]=y;
        w[i][2]=z;
    }
    //scan for source vertex
    scanf("%d",&start);
    //call for bellmanford algorithm
    update = Bellman(start,m,w,d,pred,n);
    //condition of no negative edge cycle reachable from source
    if(update==0)
    {
        for(i=1;i<=n;i++)
        {
            //if there is no change in d value then its unreachable
            if(d[i]==1000000)
            {
                printf("Unreachable\n");
            }
            else
            {
                printf("%d %d\n",d[i],pred[i]);
            }
        }
    }
    else
    {
        //pop and print each element till first one to encounter while retracing the path predecessors from v
        while(newelement->item != update)
        {
            Pop();
        }
        //print first one to encounter while retracing the path predecessors from v
        printf("%d\n",newelement->item);
    }    
    return 0;
}
