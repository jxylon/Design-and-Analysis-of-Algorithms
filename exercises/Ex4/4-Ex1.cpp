#include<stdio.h>
#include<stdlib.h>
#define Max 100
typedef char datatype;
typedef struct
{
	datatype vers[Max+1];
	int edges[Max+1][Max+1];
	int n,e;
}graph;
typedef struct edge
{
	int start,end,weight;
	edge * next;
}edge;
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
void change_edge(edge * e1,edge * e2)
{
	int i,j,k;
	i=e1->start;
	j=e1->end;
	k=e1->weight;
	e1->start=e2->start;
	e1->end=e2->end;
	e1->weight=e2->weight;
	e2->start=i;
	e2->end=j;
	e2->weight=k;
}
void sortedge(edge * edgeset[Max],int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(edgeset[j]->weight>edgeset[j+1]->weight)
			{
				change_edge(edgeset[j],edgeset[j+1]);
			}
		}
	}
}
void create_edgeset(graph * g,edge * edgeset[Max])
{
	edge * temp=NULL;
	int d=0;
	int i,j;
	for(i=1;i<=g->n;i++)
	{
		for(j=i+1;j<=g->n;j++)
		{
			if(g->edges[i][j]!=0)
			{
				edgeset[d]->start=i;
				edgeset[d]->end=j;
				edgeset[d]->weight=g->edges[i][j];
				d++;
			}
		}
	}
}
void kruskal(graph * g)
{
	edge * ge[Max],* c[Max],* p,* s[Max];
	int i;
	int k=1,d=0,m1,m2;
	for(i=0;i<Max;i++)
	{
		ge[i]=(edge *)malloc(sizeof(edge));
		c[i]=(edge *)malloc(sizeof(edge));
	}
	//创建邻边表
	create_edgeset(g,ge);
	//排序
	sortedge(ge,g->e);
	printf("边按权值大小排序:\n");
	for(i=0;i<g->e;i++)
	{
		printf("%c%c\t",g->vers[ge[i]->start],g->vers[ge[i]->end]);
	}
	printf("\n");
	for(i=0;i<g->e;i++)
	{
		printf("%d\t",ge[i]->weight);
	}
	printf("\n");
	for(i=0;i<g->n;i++)
	{
		p=(edge *)malloc(sizeof(edge));
		p->start=i+1;
		p->next=NULL;
		s[i]=p;
	}
	while(k<g->n)
	{
		for(i=0;i<g->n;i++)
		{
			p=s[i];
			while(p)
			{
				if(p->start == ge[d]->start)
					m1=i;
				if(p->start == ge[d]->end)
					m2=i;
				p=p->next;
			}
		}
		if(m1!=m2)
		{
			c[k-1]=ge[d];
			k++;
			p=s[m1];
			while(p->next!=NULL)
				p=p->next;
			p->next=s[m2];
			s[m2]=NULL;
		}
		d++;
	}
	for(i=0;i<g->n;i++)
	{
		p=s[i];
		while(p)
		{
			s[i]=p->next;
			free(p);
			p=s[i];
		}
	}
	printf("最小生成树:\n");
	for(i=0;i<g->n-1;i++)
	{
		printf("%c%c\t",g->vers[c[i]->start],g->vers[c[i]->end]);
	}
	printf("\n");
	for(i=0;i<g->n-1;i++)
	{
		printf("%d\t",c[i]->weight);
	}
	printf("\n");
}
int main(void)
{
	int n;
	char * filename;
	filename=(char *)malloc(sizeof(char)*20);
	graph * g=NULL;
	printf("1:9.2-1a\n");
	printf("2:9.2-1b\n");
	scanf("%d",&n);
	switch(n)
	{
	case 1:filename="data1.txt";break;
	case 2:filename="data2.txt";break;
	}
	g=create(filename);
	prinGraph(g);
	kruskal(g);
	return 0;
}