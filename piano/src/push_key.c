#include "../inc/show.bmp.h"

void push_key()
{
	int ts = open("/dev/input/event0", O_RDONLY);
	if(ts == -1)
	{
		perror("open() failed");
		exit(0);
	}
	struct input_event buf;
	bzero(&buf, sizeof(buf));

	while(1)
	{
		read(ts, &buf, sizeof(buf));

		if(buf.type == EV_ABS)
		{
			if(buf.code == ABS_X && buf.value >=10 && buf.value <= 75)
			{
				printf("(%d, ", buf.value);
			}
			if()
		}
	}
}
