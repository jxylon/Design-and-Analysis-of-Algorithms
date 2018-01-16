#include<stdio.h>
#include<stdlib.h>
#define MAX 1000
struct node
{
	int lcost;
	int cc;
	int rcost;
	int s;
	int *x;
	struct node *next;
};
int n,** edge,cc,bestc;
node* head,* lq,* fq;
int del_min(node*&ee)
{
	node* tmp=NULL;
	tmp=fq;
	ee=fq;
	if(ee==NULL)
		return 0;
	head->next=fq->next;
	fq=fq->next;
	return 0;
}
int insert_node(node* hn)
{
	if(head->next==NULL)
	{
		head->next=hn;
		fq=lq=head->next;
	}
	else  
	{
		node *tmp=NULL;
		tmp=fq;
		if(tmp->cc>hn->cc)
		{
			hn->next=tmp;
			head->next=hn;
			fq=head->next;
		}
		else  
		{
			while(tmp!=NULL)
			{
				if(tmp->next != NULL && tmp->cc>hn->cc)
				{
					hn->next=tmp->next;
					tmp->next=hn;
					break;
				}  
				tmp=tmp->next;
			}
		}
		if(tmp==NULL)
		{
			lq->next=hn;
			lq=lq->next;
		}
	}
	return 0;
}
int TSP(int v[])
{
	int i,j;
	head=(node*)malloc(sizeof(node));
	head->cc=0;
	head->x=0;
	head->lcost=0;
	head->next=NULL;
	head->rcost=0;
	head->s=0;
	int *MinOut=new int[n+1];
	int MinSum=0;
	for(i=1;i<=n;i++)
	{
		int Min=MAX;
		for(j=1;j<=n;j++)
			if(edge[i][j] != MAX&&(edge[i][j]<Min || Min==MAX))
				Min=edge[i][j];
		if(Min==MAX)
			return MAX;
		MinOut[i]=Min;
		MinSum += Min;
	}  
	node *ee=0;
	ee=(node*)malloc(sizeof(node));
	ee->x=new int[n];
	for(i=0;i<n;i++)
		ee->x[i]=i+1;
	ee->s=0;
	ee->cc=0;
	ee->rcost=MinSum;
	ee->next=0; 
	int bestc=MAX;
	while(ee->s<n-1)
	{  
		if(ee->s==n-2)
		{
			if(edge[ee->x[n-2]][ee->x[n-1]] != MAX &&
				edge[ee->x[n-1]][1] != MAX &&
				(ee->cc+edge[ee->x[n-2]][ee->x[n-1]]+edge[ee->x[n-1]][1]<bestc
				|| bestc==MAX))
			{
				bestc=ee->cc+edge[ee->x[n-2]][ee->x[n-1]]+edge[ee->x[n-1]][1];
				ee->cc=bestc;
				ee->lcost=bestc;
				ee->s++;
				ee->next=NULL;
				insert_node(ee);
			}
			else  
				free(ee->x); 
		}
		else  
		{
			for(int i=ee->s+1;i<n;i++)
				if(edge[ee->x[ee->s]][ee->x[i]] != MAX)
				{
					int cc=ee->cc+edge[ee->x[ee->s]][ee->x[i]];
					int rcost=ee->rcost-MinOut[ee->x[ee->s]];
					int b=cc+rcost;
					if(b<bestc || bestc==MAX)
					{
						node*N;
						N=(node*)malloc(sizeof(node));
						N->x=new int[n];
						for(int j=0;j<n;j++)
							N->x[j]=ee->x[j];
						N->x[ee->s+1]=ee->x[i];
						N->x[i]=ee->x[ee->s+1];
						N->cc=cc;
						N->s=ee->s+1;
						N->lcost=b;
						N->rcost=rcost;
						N->next=NULL;
						insert_node(N);
					}
				}
				free(ee->x);
		}
		del_min(ee);
		if(ee==NULL)
			break;
	}  
	if(bestc==MAX)
		return MAX;
	for(i=0;i<n;i++)
		v[i+1]=ee->x[i];
	while(true)
	{
		free(ee->x);
		del_min(ee);
		if(ee==NULL)
			break;
	}
	return bestc;
}
int main(void)
{
	n=0;
	int i=0;
	n=4;
	edge=(int**)malloc(sizeof(int*)*(n+1));
	for(i=1;i<=n;i++)
	{
		edge[i]=(int*)malloc(sizeof(int)*(n+1));
	}
	edge[1][1]=0;edge[1][2]=2;edge[1][3]=5;edge[1][4]=7;
	edge[2][1]=2;edge[2][2]=0;edge[2][3]=8;edge[2][4]=3;
	edge[3][1]=5;edge[3][2]=8;edge[3][3]=0;edge[3][4]=1;
	edge[4][1]=7;edge[4][2]=3;edge[4][3]=1;edge[4][4]=0;
	int * v=(int *)malloc(sizeof(int)*(n+1));
	for(i=1;i<=n;i++)
		v[i]=0;
	bestc=TSP(v);
	printf("最佳路径：\n");
	for(i=1;i<=n;i++)
		printf("%c->",v[i]+96);
	printf("a\n");
	printf("路径花费：\n");
	printf("%d\n", bestc);
	return 0;
}