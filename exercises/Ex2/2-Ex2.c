#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
long LomutoPartition(long * array,long l,long r)
{
	long p,s,i,t;
	p=array[l];
	s=l;
	for(i=l+1;i<=r;i++)
		if(array[i]<p)
		{
			s=s+1;
			t=array[s];
			array[s]=array[i];
			array[i]=t;
		}
	t=array[l];
	array[l]=array[s];
	array[s]=t;
	return s;
}
void quicksort(long * array,long l,long r)
{
	long p,i,j,t;
	p=array[l];
	i=l;
	j=r+1;
	do
	{
		do
		{
			i=i+1;
		}while(array[i]<p);
		do
		{
			j=j-1;
		}while(array[j]>p);
		if(i>=j)
			break;
		else
		{
			t=array[i];
			array[i]=array[j];
			array[j]=t;
		}
	}while(i<j);
	t=array[l];
	array[l]=array[j];
	array[j]=t;
	if(l<j-1)
		quicksort(array,l,j-1);
	if(j+1<r)
		quicksort(array,j+1,r);
}
long Quickselect(long * array,long l,long r,long k)
{
	long s;
	s=LomutoPartition(array,l,r);
	if(s==(l+k-1))
		return array[s];
	else if(s>(l+k-1))
		Quickselect(array,l,s-1,k);
	else
		Quickselect(array,s+1,r,l+k-1-s);
}
int main(void)
{
	long length,i,k;
	long * array;
	srand(time(0));
	printf("input array's length\n");
	scanf("%ld",&length);
	array=(long *)malloc(length*sizeof(long));
	for(i=0;i<length;i++)
	{
		array[i]=rand()%length+1;
	}
	quicksort(array,0,length-1);
	for(i=1;i<=length;i++)
	{
		printf("%d ",array[i-1]);
		if(i%40==0)
			printf("\n");
	}
	printf("\n");
	printf("input k\n");
	scanf("%ld",&k);
	if(k>length)
		printf("k不能比数组长度大\n");
	else
		printf("第%ld个最小的元素是 %ld\n",k,Quickselect(array,0,length-1,k));
	printf("\n");
	return 0;
}
