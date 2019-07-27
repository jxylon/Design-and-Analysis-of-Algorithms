#include<stdio.h>
#include<stdlib.h>
#define Max 100
#define Maxv 99999
typedef char datatype;
typedef struct
{
	datatype vers[Max+1];
	int edges[Max+1][Max+1];
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
void Dijkstra(graph * g,int v)
{
	int dist[Max],s[Max],rear[Max];
	int q[Max][Max];
	int i,j,k,m,min;
	//初始化s,rear
	for(i=1;i<=g->n;i++)
	{
		s[i]=0;
		rear[i]=-1;
	}
	//初始化dist,如果直接达到则入队
	for(i=1;i<=g->n;i++)
	{
		dist[i]=g->edges[v][i];
		if(dist[i]<Maxv)
		{
			q[i][++rear[i]]=v;
			q[i][++rear[i]]=i;
		}
	}
	// v源点入队
	s[v]=1;
	//找到n-1个点加入集合
	for(k=0;k<g->n-1;k++)
	{
		min=Maxv;
		j=v;
		//找到最小的dist
		for(i=1;i<=g->n;i++)
		{
			if(s[i] == 0 &&dist[i]<min)
			{
				j=i;
				min=dist[i];
			}
		}
		//调整距离dist
		if(j!=i)
		{
			s[j]=1;
			printf("\nthe %c 's shortest distance is %d:route is ",g->vers[j],dist[j]);
			for(i=0;i<=rear[j];i++)
			{
				if(i==rear[j])
					printf("%c",g->vers[q[j][i]]);
				else
					printf("%c->",g->vers[q[j][i]]);
			}
			printf("\n");
			for(i=1;i<=g->n;i++)
			{
				//如果该点未加入集合且经过j的间接距离距离比直接距离小，则最小距离调整为间接距离
				if(s[i] == 0&&((dist[j]+g->edges[j][i]<dist[i])))
				{
					dist[i]=dist[j]+g->edges[j][i];
					//队列调整为j
					for(m=0;m<=rear[j];m++)
						q[i][m]=q[j][m];
					rear[i]=rear[j];
					//i加入队列
					q[i][++rear[i]]=i;
				}
			}
		}
	}
}
void changeGraph(graph * g)
{
	int i,j;
	for(i=1;i<=g->n;i++)
	{
		for(j=1;j<=g->n;j++)
			if(g->edges[i][j]==0)
				g->edges[i][j]=Maxv;
	}
}
int main(void)
{
	int n;
	char * filename;
	filename=(char *)malloc(sizeof(char)*20);
	graph * g=NULL;
	printf("1:9.3-2b\n");
	printf("2:9.3-2a\n");
	scanf("%d",&n);
	switch(n)
	{
	case 1:filename="data1.txt";break;
	case 2:filename="data2.txt";break;
	}
	g=create(filename);
	prinGraph(g);
	changeGraph(g);
	Dijkstra(g,1);
	return 0;
}