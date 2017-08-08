#include "../inc/show_bmp.h"

char *init_lcd(struct fb_var_screeninfo *pvinfo)
{
	int lcd = open("/dev/fb0", O_RDWR);
	if(lcd == -1)
	{
		perror("open lcd failed");
		exit(0);
	}

	bzero(pvinfo, sizeof(struct fb_var_screeninfo));
	ioctl(lcd, FBIOGET_VSCREENINFO, pvinfo);

	char *fbmemy = mmap(NULL, pvinfo->xres * pvinfo->yres * pvinfo->bits_per_pixel/8,
			    PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);

	if(fbmemy == MAP_FAILED)
	{
		perror("mmap failed");
		exit(0);
	}

	return fbmemy;
}

char *load_bmp(char *bmpfile, struct image_info *pimgfo)
{
	struct header head;
	struct info info;
	int img = open(bmpfile, O_RDONLY);
	if(img == -1)
	{
		perror("open bmp failed");
		exit(0);
	}

	if(read(img, &head, sizeof(struct header)) == -1)
	{
		perror("read head failed");
		exit(0);
	}
	
	if(read(img, &info, sizeof(struct info)) == -1)
	{
		perror("read info failed");
		exit(0);
	}

	if(info.compression)
	{
		printf("not support.\n");
		exit(0);
	}

	pimgfo->height = info.height;
	pimgfo->width  = info.width;
	pimgfo->bpp    = info.bit_count; 

	char *imgdata = calloc(1, head.size-head.offbits);
	char *tmp = imgdata;
	int n, btyes_to_read = head.size-head.offbits;

	while(btyes_to_read > 0)
	{
	 	n = read(img, tmp, btyes_to_read);
		btyes_to_read -= n;
		tmp += n;
	}

	return imgdata;
	
}

void display_bmp(char *fbmemy, struct fb_var_screeninfo *pvinfo, char *imgdata,
		struct image_info *pimgfo, int xoffset, int yoffset)
{
	int pad = (4-(pimgfo->width * pimgfo->bpp/8) % 4)% 4;

	fbmemy += (yoffset * pvinfo->xres + xoffset) * pvinfo->bits_per_pixel/8;
	imgdata += (pimgfo->width * pimgfo->bpp/8 + pad) * (pimgfo->height-1);

	int i, j;
	for(j=0; j<pimgfo->height && j<pvinfo->yres-yoffset; j++)
	{
		long fb_offset, ig_offset;
		for(i=0; i<pimgfo->width && i<pvinfo->xres-xoffset; i++)
		{
			fb_offset = (j*pvinfo->xres + i)*(pvinfo->bits_per_pixel/8);
			ig_offset = i*pimgfo->bpp/8;

			memcpy(fbmemy+fb_offset+pvinfo->red.offset/8, ig_offset+imgdata+RED, 1);
			memcpy(fbmemy+fb_offset+pvinfo->green.offset/8, ig_offset+imgdata+GREEN, 1);
			memcpy(fbmemy+fb_offset+pvinfo->blue.offset/8, ig_offset+imgdata+BLUE, 1);
		}

		imgdata -= pimgfo->width*pimgfo->bpp/8 + pad;
	}
}



int main(int argc, char **argv)
{
	struct fb_var_screeninfo vinfo;
	char *fbmemy = init_lcd(&vinfo);

	struct image_info imgfo1;
	char *imgdata1 = load_bmp("../pic/background.bmp", &imgfo1);

	struct image_info imgfo2;
	char *imgdata2 = load_bmp("../pic/bar.bmp", &imgfo2);
	
	struct image_info imgfo3;
	char *imgdata3 = load_bmp("../pic/key_on.bmp", &imgfo3);
	
	struct image_info imgfo4;
	char *imgdata4 = load_bmp("../pic/logo.bmp", &imgfo4);

	display_bmp(fbmemy, &vinfo, imgdata1, &imgfo1, 0, 0);
	display_bmp(fbmemy, &vinfo, imgdata2, &imgfo2, 0, 0);
	int i;
	for(i=0; i<12; i++)
	{
		display_bmp(fbmemy, &vinfo, imgdata3, &imgfo3, 10+i*65, 47);
	}
	display_bmp(fbmemy, &vinfo, imgdata4, &imgfo4, 229, 327);

	return 0;
}
