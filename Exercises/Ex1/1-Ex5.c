#include<stdio.h>
//求最小值
long min(long m,long n)
{
	return m<n?m:n;
}
//中学算法的改进
long gcd(long m,long n)
{
	long result=1,i,j;
	while(m!=1&&n!=1)
	{
		//从2开始取余
		for(i=2;i<=min(m,n);i++)
		{
			j=i;
			//如果都能除尽
			if(m%i==0&&n%i==0)
			{
				m=m/i;
				n=n/i;
				result*=i;
				break;
			}
		}
		//如果i从2到m,n的最小值都没有公约数，那么就已经没有公约数了，退出循环
		if(j==min(m,n))
			break;
	}
	return result;
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