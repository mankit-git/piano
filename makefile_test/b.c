#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

void foo(int x);

int main(void)
{
	open("alkdj", O_RDONLY);

	#ifdef DEBUG
	printf("[%s][%d] :%s\n", __FUNCTION__, __LINE__, strerror(errno));
	#endif
	
	int i, a[100];
	for(i=0; i<100000; i++)
	{
		foo(a[i]);
	}
		
	#ifdef DEBUG
	printf("[%s][%d] :%s\n", __FUNCTION__, __LINE__, strerror(errno));
	#endif
	
	return 0;
}

void foo(int x)
{

	int y = x;	
}	



