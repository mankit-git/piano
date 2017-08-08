#include <stdio.h>
#include "sum.h" // 首先在当前目录下找，找不到再去系统标准路径找(/usr/include)

int main(void)
{
	int a=1, b=2;

	int m = sum_int(a, b);
	printf("m: %d\n", m);

	return 0;
}


