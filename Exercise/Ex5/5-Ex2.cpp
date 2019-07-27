#include<stdio.h>
#include<stdlib.h>
#define MAX 100
typedef char datatype;
typedef struct
{
	datatype vers[MAX+1];
	int edges[MAX+1][MAX+1];
	int n,e;
}graph;
graph * create(char * filename)
{
	graph * g=NULL;
	FILE *fp;
	int n,e,i,j;
	datatype ch,f,num;
	fp=fopen(filename,"r");
	g=(graph *)malloc(sizeof(graph));
	fscanf(fp,"%d %d",&n,&e);
	g->e=e;
	g->n=n;
	fscanf(fp,"%c",&ch);
	for(i=1;i<n+1;i++)
	{
		fscanf(fp,"%c",&num);
		g->vers[i]=num;
		fscanf(fp,"%c",&ch);
	}
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			fscanf(fp,"%d",&f);
			g->edges[i][j]=f;
			fscanf(fp,"%c",&ch);
		}
	}
	fclose(fp);
	return g;
}
void prinGraph(graph * g)
{
	int i,j;
	printf("%d个结点 %d条边\n",g->n,g->e);
	printf("结点为：\n");
	for(i=1;i<g->n+1;i++)
		printf("%c ",g->vers[i]);
	printf("\n邻接矩阵为:\n");
	for(i=1;i<g->n+1;i++)
	{
		for(j=1;j<g->n+1;j++)
			printf("%d ",g->edges[i][j]);
		printf("\n");
	}
}
void colormap(graph * g)
{
	int s[MAX+1];
	int i,j,k,m,count=0;
	s[1]=1;
	i=2;j=1;
	while(i<=g->n)
	{
		while((j<=3)&&i<=g->n)
		{
			k=1;
			while(k<i&&(s[k]*g->edges[i][k]!=j))
				k++;
			if(k<i)
				j++;
			else
			{
				s[i]=j;
				i++;
				j=1;
			}
			if(i==(g->n+1))
			{
				count++;
				for(m=1;m<=g->n;m++)
					printf("area:%d<->color:%d\n",m,s[m]);
				break;
			}
		}
		if(j>3)
		{
			i--;
			j=s[i]+1;
		}
	}
	printf("Totally %d answers\n",count);
}
int main(void)
{
	int n;
	char * filename;
	filename=(char *)malloc(sizeof(char)*20);
	graph * g=NULL;
	printf("1:12.3-a\n");
	printf("2:12.1-5\n");
	scanf("%d",&n);
	switch(n)
	{
	case 1:filename="data1.txt";break;
	case 2:filename="data2.txt";break;
	}
	g=create(filename);
	prinGraph(g);
	colormap(g);
	return 0;
}