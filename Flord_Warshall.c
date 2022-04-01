#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n,i,j,x,k;
	scanf("%d",&n);	
	//declare arrays for shortest distances and predecessor
	int d[n+1][n+1];
	int pred[n+1][n+1];	
	//scan for shortest distances and set it predecessor
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			scanf("%d",&x);
			d[i][j] = x;
			if(x == 55555)
			{	
				pred[i][j] = -1;
			}
			else
			{
				pred[i][j] = i;
			}
		}
	}
	//Element with predecessor of same numbers is -1
	for(i=1;i<=n;i++)
	{
		pred[i][i] = -1;
	}
	//Floyd_Warshall
	//Pairwise Distance Matrix After Two Rounds
	printf("Pairwise Distance Matrix After Two Rounds\n");
	for(k=1;k<=2;k++)
	{	for(i=1;i<=n;i++)
		{	for(j=1;j<=n;j++)
			{
				if(d[i][j] > d[i][k] + d[k][j])
				{
					d[i][j] = d[i][k] + d[k][j];
					pred[i][j] = pred[k][j];
				}
			}
		}
	}
	for(i=1;i<=n;i++)
	{	for(j=1;j<n;j++)
		{
			printf("%d ",d[i][j]);
		}
		printf("%d\n",d[i][n]);
	}
	//Pairwise Predecessor Matrix After Two Rounds
	printf("Pairwise Predecessor Matrix After Two Rounds\n");
	for(i=1;i<=n;i++)
	{	for(j=1;j<n;j++)
		{
			if(pred[i][j] == -1)
			{
		    		printf("NIL ");
			}
			else
			{
				printf("%d ",pred[i][j]);
		    	}
		}
		if(pred[i][n] == -1)
		{
	         		printf("NIL\n");
		}
		else
		{
			printf("%d\n",pred[i][n]);
		}
	}
	//Final Pairwise Distance Matrix
	printf("Final Pairwise Distance Matrix\n");
	for(k=3;k<=n;k++)
	{	for(i=1;i<=n;i++)
		{	for(j=1;j<=n;j++)
			{
				if(d[i][j] > d[i][k] + d[k][j])
				{
					d[i][j] = d[i][k] + d[k][j];
					pred[i][j] = pred[k][j];
				}
			}
		}
	}
	for(i=1;i<=n;i++)
	{	for(j=1;j<n;j++)
		{
			printf("%d ",d[i][j]);
		}
		printf("%d\n",d[i][n]);
	}
	printf("Final Pairwise Predecessor Matrix\n");
	//Final Pairwise Predecessor Matrix
	for(i=1;i<=n;i++)
	{	for(j=1;j<n;j++)
		{
			if(pred[i][j] == -1)
		    	{
		        		printf("NIL ");
		    	}
		    	else
		    	{
				printf("%d ",pred[i][j]);
		    	}
		}
		if(pred[i][n] == -1)
		{
			printf("NIL\n");
		}
		else
		{
			printf("%d\n",pred[i][n]);
		}
	}
	return 0;
}
