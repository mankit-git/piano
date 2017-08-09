#include "push_key.h"
#include "show_bmp.h"

int num;

int jugde(struct coordinate *xyp)
{	
	if(xyp->y < 47 || xyp->y >= 327)
			return -1;
	int i;
	for(i=0; i<12; i++)
	{	
		if(xyp->x >= 10+65*i && xyp->x <= 10+65*(i+1))
			break;
	}
	return i;
}

int main(int argc, char **argv)
{
	int ts = open("/dev/input/event0", O_RDONLY);
	if(ts == -1)
	{
		perror("open() failed");
		exit(0);
	}

	struct fb_var_screeninfo vinfo;
	char *fbmemy = init_lcd(&vinfo);

	struct image_info imgfo1;
	char *imgdata1 = load_bmp("../pic/background.bmp", &imgfo1);

	struct image_info imgfo2;
	char *imgdata2 = load_bmp("../pic/bar.bmp", &imgfo2);
	
	struct image_info imgfo3;
	char *imgdata3 = load_bmp("../pic/key_off.bmp", &imgfo3);
	
	struct image_info imgfo4;
	char *imgdata4 = load_bmp("../pic/key_on.bmp", &imgfo4);

	struct image_info imgfo5;
	char *imgdata5 = load_bmp("../pic/logo.bmp", &imgfo5);

	display_bmp(fbmemy, &vinfo, imgdata1, &imgfo1, 0, 0);
	display_bmp(fbmemy, &vinfo, imgdata2, &imgfo2, 0, 0);
	int i;
	for(i=0; i<12; i++)
	{
		display_bmp(fbmemy, &vinfo, imgdata3, &imgfo3, 10+i*65, 47);
	}
	display_bmp(fbmemy, &vinfo, imgdata5, &imgfo5, 229, 327);

	struct coordinate *xyp = calloc(1, sizeof(struct coordinate));

	int prev = 0;
	int last = 0;
	while(1)
	{
		int death = push_key(ts, xyp);

		
		if(num == -1)
			continue;
		last = (xyp->x-20)/65*65 + 10;
		printf("last: %d\n", last);

		if(xyp->press == 0 || prev != last)
		{
			//system("killall madplay");
			//last = (xyp->x-20)/65*65 + 10;
			//printf("last: %d\n", last);
			display_bmp(fbmemy, &vinfo, imgdata3, &imgfo3, prev, 47);
			printf("leave\n");
			//char buf[50];
			//bzero(buf, sizeof(buf));
			//num = jugde(xyp);
			//sprintf(buf, "./madplay ../snd/d%d.mp3 -a -10 &", num+1);
			//system(buf);
			
		}

		if(xyp->press == 1)
		{
			printf("on\n");
			prev = (xyp->x-20)/65*65 + 10;
			display_bmp(fbmemy, &vinfo, imgdata4, &imgfo4, prev, 47);
			printf("prev: %d\n", prev);
			//prev_num = num;
			//printf("prev num: %d\n", prev_num);
		}	
		
	}

	return 0;
}
