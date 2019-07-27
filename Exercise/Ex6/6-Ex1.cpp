#include<stdio.h>
#include<stdlib.h>
#define MAX 9999
typedef struct package
{
	float weight;
	float value;
	float wvalue;
}package;
typedef struct node
{
	float w;
	float v;
	float ub;
	int level;
	int left;
}node;
typedef struct queue
{
	int front;
	int rear;
	node data[MAX];
}queue;
int W,select[MAX];
package pack[MAX];
void init_queue(queue * q)
{
	q->front=q->rear=-1;
}
void push(queue * q,node num)
{
	if(q->rear==MAX)
		printf("队满\n");
	else
		q->data[++q->rear]=num;
}
node pop(queue * q)
{
	node x;
	x.ub=0;
	if(q->front==q->rear)
	{
		printf("队空\n");
	}
	else
	{
		x=q->data[++q->front];
	}
	return x;
}
int queue_empty(queue * q)
{
	if(q->front==q->rear)
		return 1;
	else
		return 0;
}
node sort_queue(queue * q)
{
	node m;
	int i,j;
	float max=0;
	for(i=q->front+1;i<q->rear+1;i++)
	{
		if(q->data[i].ub>max)
		{
			max=q->data[i].ub;
			j=i;
		}
	}
	m=q->data[j];
	//删掉最大的结点
	for(i=j;i<q->rear;i++)
	{
		q->data[i]=q->data[i+1];
	}
	//最大的结点放到队头
	q->rear--;
	for(i=q->rear;i>q->front;i--)
	{
		q->data[i+1]=q->data[i];
	}
	q->data[q->front+1]=m;
	q->rear++;
	return m;
}
int init_package()
{
	int n,i;
	printf("input MAX WEIGHT\n");
	scanf("%d",&W);
	printf("input stuff number\n");
	scanf("%d",&n);
	printf("input weight value\n");
	for(i=0;i<n;i++)
	{
		scanf("%f %f",&pack[i].weight,&pack[i].value);
		pack[i].wvalue=pack[i].value/pack[i].weight;
	}
	return n;
}
void sort_package(int n)
{
	int i,j;
	float temp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(pack[j].wvalue<pack[j+1].wvalue)
			{
				temp=pack[j+1].wvalue;
				pack[j+1].wvalue=pack[j].wvalue;
				pack[j].wvalue=temp;
				temp=pack[j+1].weight;
				pack[j].weight=temp;
				pack[j+1].weight=pack[j].weight;
				temp=pack[j+1].value;
				pack[j+1].value=pack[j].value;
				pack[j].value=temp;
			}
		}
	}
}
void prin_package(int n)
{
	int i;
	printf("stuff\tweight\tvalue\twvalue\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t%.1f\t%.1f\t%.1f\n",i+1,pack[i].weight,pack[i].value,pack[i].wvalue);
	}
}
void package(int n)
{
	int i;
	queue * q;
	node head,next,left,right,m;
	q=(queue *)malloc(sizeof(queue));
	init_queue(q);
	head.v=0;
	head.w=0;
	head.ub=(W-head.w)*pack[0].wvalue+head.v;
	head.level=0;
	push(q,head);
	next.level=0;
	while(next.level!=n)
	{
		next=pop(q);
		if((W-next.w)>=pack[next.level].weight)
		{
			left.v=next.v+pack[next.level].value;
			left.w=next.w+pack[next.level].weight;
			left.level=next.level+1;
			left.ub=(W-left.w)*pack[next.level+1].wvalue+left.v;
			left.left=1;
		}
		else
		{
			left.ub=0;
		}
		right.level=next.level+1;
		right.v=next.v;
		right.w=next.w;
		right.ub=(W-right.w)*pack[next.level+1].wvalue+right.v;
		right.left=0;
		if(left.ub!=0)
			push(q,left);
		push(q,right);
		m=sort_queue(q);
		select[m.level-1]=m.left;
	}
	for(i=0;i<n;i++)
	{
		if(select[i])
			printf("物品%d √\n",i);
		else
			printf("物品%d ×\n",i);
	}
	m=q->data[q->front+1];
	printf("背包最大价值为%.1f\n",m.v);
}
int main(void)
{
	int n;
	n=init_package();
	sort_package(n);
	prin_package(n);
	package(n);
	return 0;
}