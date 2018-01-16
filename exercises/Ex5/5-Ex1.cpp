#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int C[MAX]={0},row=1;
int judge(int n)
{
	int i,j;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i!=j && (C[i]!=0 && C[j] !=0) && (C[i]==C[j] || abs(C[i]-C[j])==abs(i-j)))
				return 0;
		}
	}
	return 1;
}
void queen(int n)
{
	while(row>0)
	{
		while(C[row]<n)
		{
			C[row]+=1;
			if(judge(n))
				row+=1;
			if(row==(n+1))
				break;
		}
		if(row==(n+1))
			break;
		else
		{
			C[row]=0;
			row=row-1;
		}
	}
}
int main(void)
{
	int n,i,j;
	printf("input N queen's scale\n");
	scanf("%d",&n);
	queen(n);
	printf("col:\t");
	for(i=0;i<n;i++)
		printf("%d\t",i+1);
	printf("\n");
	for(i=1;i<=n;i++)
	{
		printf("row%d:\t",i);
		for(j=0;j<C[i]-1;j++)
			printf("\t");
		printf("Q\n");
	}
	printf("\n");
	for(i=1;i<=n;i++)
	{
		printf("row%d's position:col:%d\n",i,C[i]);
	}
	return 0;
}