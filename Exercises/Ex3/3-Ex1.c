#include<stdio.h>
#define Max 100
int F[Max][Max];
int max(int n,int m)
{
	return (m>n?m:n);
}
void init_F(int n,int C)
{
	int i;
	for(i=0;i<n;i++)
		F[i][0]=0;
	for(i=0;i<C;i++)
		F[0][i]=0;
}
void prin_F(int n,int C)
{
	int i,j;
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=C;j++)
			printf("%d\t",F[i][j]);
		printf("\n");
	}
}
void bags(int v[],int w[],int C,int n)
{
	int i,j;
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=C;j++)
		{
			if(w[i-1]>j&&(i-1)>=0)
			{
				F[i][j]=F[i-1][j];
			}
			if(w[i-1]<=j&&(i-1)>=0)
			{
				F[i][j]=max(F[i-1][j],v[i-1]+F[i-1][j-w[i-1]]);
			}
		}
	}
}
void back(int n,int C,int w[],int v[])
{
	int i=n,j=C,count=0;
	int arr[Max];
	while(i>0&&j>0)
	{
		while(F[i][j]<=F[i-1][j])
		{
			i--;
		}
		arr[count++]=i;
		j=j-w[i-1];
		i--;
	}
	printf("最佳解决方案:\n");
	for(i=count-1;i>=0;i--)
	{
		printf("i=%d,w[%d]=%d,v[%d]=%d\n",arr[i],arr[i],w[arr[i]-1],arr[i],v[arr[i]-1]);
	}
	printf("背包最大价值:%d\n",F[n][C]);
}
void print_VW(int v[],int w[],int n)
{
	int i;
	printf("物品\t重量\t价值\t\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t\n",i,w[i],v[i]);
	}
}
int main(void)
{
	int C=6,n=5;
	int v[5]={25,20,15,40,50};
	int w[5]={3,2,1,4,5};
	printf("n=%d,C=%d\n",n,C);
	print_VW(v,w,n);
	init_F(n,C);
	bags(v,w,C,n);
	printf("动态规划表:\n");
	prin_F(n,C);
	back(n,C,w,v);
	return 0;
}