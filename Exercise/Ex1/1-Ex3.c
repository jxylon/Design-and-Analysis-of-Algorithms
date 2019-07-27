#include<stdio.h>
//求0<m,n<10的最大除法次数
long gcd(long m,long n,long * count)
{
	long r;
	if(n==0)
		return m;
	else
	{
		r=m%n;
		(*count)++;
		m=n;
		n=r;
		gcd(m,n,count);
	}
}
int main(void)
{
	long m,n,result,t,count,max=0,maxn,maxm;
	for(n=1;n<=10;n++)
	{
			
		for(m=1;m<n;m++)
		{
			count=0;
			gcd(m,n,&count);
			if(max<count)
			{
				max=count;
				maxn=n;
				maxm=m;
			}
		}
	}
	printf("m=%ld n=%ld max_times=%ld\n",maxm,maxn,max);
	return 0;
}