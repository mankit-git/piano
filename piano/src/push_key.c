#include "push_key.h"
#include "show_bmp.h"

void cleanup(int sig)
{
	semctl(semid, 0, IPC_RMID);
	exit(0);
}

int push_key( int ts, struct coordinate *xyp)
{
	struct input_event buf;
	bzero(&buf, sizeof(buf));

	int flag1 = 0;
	int flag2 = 0;
	while(1)
	{
		read(ts, &buf, sizeof(buf));

		if(buf.type == EV_ABS)
		{	
			if(buf.code == ABS_X)
			{
				flag1 = 1;
				xyp->x = buf.value;
				printf("x: %d\n", xyp->x);
			}
			if(buf.code == ABS_Y)
			{
				flag2 = 1; 
				xyp->y = buf.value;
				printf("y: %d\n", xyp->y);
			}
			if(xyp->y <= 47 && xyp->x >= 740)
				return DEATH
		}

		if(flag1 ==1 && flag2 == 1)
			break;

		if(buf.type == EV_KEY)
		{
			if(buf.code == BTN_TOUCH)
			{
				xyp->press = buf.value;
				break;
			}		
		}
		
	}

}
