#include<stdio.h>
#include<time.h>
//取最小值
long min(long m,long n)
{
	return m<n?m:n;
}
//求最大公约数 递归实现
//m,n为所求的两个数，t为公约数
long gcd(long m,long n,long t)
{
	if(m%t==0)
	{
		if(n%t==0)
			return t;
		else
			gcd(m,n,t-1);
	}
	else
		gcd(m,n,t-1);
}
int main(void)
{
	time_t time_star,time_end;
	long m,n,result,t;
	printf("input m & n\n");
	scanf("%ld %ld",&m,&n);
	time_star=time(NULL);
	t=min(m,n);
	result=gcd(m,n,t);
	time_end=time(NULL);
	printf("gcd=%ld\ntime=%.1f\n",result,difftime(time_star,time_end));
	return 0;
}