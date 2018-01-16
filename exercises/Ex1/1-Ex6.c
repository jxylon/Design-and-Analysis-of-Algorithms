#include<stdio.h>
#include<time.h>
//斐波那契数
long fibonacci(long n,int * count)
{
	//n=0或者n=1的时候退出递归
	if(n==0)
		return 0;
	else if(n==1)
		return 1;
	else
	{
		//基本操作次数
		(*count)++;
		return fibonacci(n-2,count)+fibonacci(n-1,count);
	}
}
int main(void)
{
	long i,count,result;
	int begin,end;
	printf("input n:\n");
	for(i=0;i<=40;i+=2)
	{
		//计算运行时间
		count=0;
		begin=clock();
		result=fibonacci(i,&count);
		end=clock();
		printf("n=%ld,result=%ld,time=%dms,count=%d\n",i,result,end-begin,count);
	}
}