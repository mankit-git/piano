#include "push_key.h"
#include "show_bmp.h"

int push_key( int ts, struct coordinate *xyp)
{
	
	struct input_event buf;
	bzero(&buf, sizeof(buf));

	while(1)
	{
		read(ts, &buf, sizeof(buf));

		if(buf.type == EV_ABS)
		{	
			if(buf.code == ABS_X)
			{
				xyp->x = buf.value;
				printf("x: %d\n", xyp->x);
				//a = (buf.value-20)/65 * 65 + 10;
			}
			if(buf.code == ABS_Y)
			{
				xyp->y = buf.value;
				printf("y: %d\n", xyp->y);
			}
			
		}

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
