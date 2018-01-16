#include<stdio.h>
//欧几里得算法的变形，取余数改为减一
long gcd(long m,long n)
{
	long r,result;
	if(n==0)
		return m;
	else
	{
		r=m-n;
		if(r<0)
			r=r*-1;
		m=n;
		n=r;
		result=gcd(m,n);
		return result;
	}
}
int main(void)
{
	long m,n,result;
	printf("input m & n\n");
	scanf("%ld %ld",&m,&n);
	result=gcd(m,n);
	printf("m=%ld n=%ld gcd=%ld\n",m,n,result);
	return 0;
}