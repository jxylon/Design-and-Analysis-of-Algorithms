#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
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
int main(void)
{
	long length,i;
	long * array;
	time_t c_start,c_end;
	srand(time(0));
	printf("input array's length\n");
	scanf("%ld",&length);
	array=(long *)malloc(length*sizeof(long));
	for(i=0;i<length;i++)
	{
		array[i]=rand()%length+1;
	}
	printf("Before sort\n");
	for(i=1;i<=length;i++)
	{
		printf("%d ",array[i-1]);
		if(i%40==0)
			printf("\n");
	}
	printf("\n");
	c_start = clock();
	quicksort(array,0,length-1);
	c_end = clock();
	printf("After sort\n");
	for(i=1;i<=length;i++)
	{
		printf("%d ",array[i-1]);
		if(i%40==0)
			printf("\n");
	}
	printf("\n");
	printf("The sorttime is %.2f ms\n",difftime(c_end,c_start));
	return 0;
}