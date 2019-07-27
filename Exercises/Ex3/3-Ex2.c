#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 5000
#define MAXV 99999;
int F[MAX],C[MAX];
int FF[MAX];
int CC[6]={1,5,10,20,50,100};
int max(int a,int b)
{
	return a>b?a:b;
}
int min(int a,int b)
{
	return a<b?a:b;
}
void initCoin(int n)
{
	int i;
	srand(0);
	for(i=0;i<n;i++)
	{
		C[i]=rand()%20+1;
	}
}
int coinRow(int n)
{
	int count=0;
	F[0]=0;
	F[1]=C[0];
	for(int i=2;i<=n;i++)
	{
		F[i]=max(C[i-1]+F[i-1],F[i-1]);
		count++;
	}
	return count;
}
int coinRow_recursion(int n)
{
	if(n==0)
		return 0;
	else if(n==1)
		return 0;
	else
	{
		return coinRow_recursion(n-2)+coinRow_recursion(n-1)+1;
	}
}
int ChangeMaking(int n)
{
	int count=0,temp,i,j;
	FF[0]=0;
	for(i=0;i<=n;i++)
	{
		temp=MAXV;
		j=0;
		while(j<6&&i>=CC[j])
		{
			temp=min(FF[i-CC[j]],temp);
			count++;
			j++;
		}
		FF[i]=temp+1;
	}
	return count;
}
int ChangeMaking_recursion(int n)
{
	int i=0,all=0;
	if(n==0)
		return 0;
	else
	{
		while(i<6&&n>=CC[i])
		{
			all+=ChangeMaking_recursion(n-CC[i]);
			i++;
		}
		return all+i;
	}
}
int main(void)
{
	int countMax1,countMax2,i;
	int start,end;
	printf("最大币值问题\n");
	for(i=0;i<=40;i+=2)
	{
		initCoin(i);
		printf("scale=%d\n",i);
		start=clock();
		countMax1=coinRow(i);
		end=clock();
		printf("Not recursion:count=%d,time=%dms\n",countMax1,end-start);
		start=clock();
		countMax2=coinRow_recursion(i);
		end=clock();
		printf("recursion:count=%d,time=%dms\n",countMax2,end-start);
		printf("\n");
	}
	printf("找零问题\n");
	for(i=0;i<=70;i+=5)
	{
		printf("scale=%d\n",i);
		start=clock();
		countMax1=ChangeMaking(i);
		end=clock();
		printf("Not recursion:count=%d,time=%dms\n",countMax1,end-start);
		start=clock();
		countMax2=ChangeMaking_recursion(i);
		end=clock();
		printf("recursion:count=%d,time=%dms\n",countMax2,end-start);
		printf("\n");
	}
	return 0;
}