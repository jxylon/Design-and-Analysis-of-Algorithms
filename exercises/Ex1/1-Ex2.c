#include<stdio.h>
//欧几里得算法，递归实现
long gcd(long m,long n)
{
	long r;
	if(n==0)
		return m;
	else
	{
		r=m%n;
		m=n;
		n=r;
		gcd(m,n);
	}
}
int main(void)
{
	long m,n,result,t;
	printf("input m & n\n");
	scanf("%ld %ld",&m,&n);
	result=gcd(m,n);
	printf("%ld\n",result);
	return 0;
}