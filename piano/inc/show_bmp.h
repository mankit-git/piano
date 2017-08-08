#ifndef __SHOW_BMP_H__
#define __SHOW_BMP_H__

#include <stdio.h>
#include <linux/fb.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/ioctl.h>

#define RED   2
#define GREEN 1
#define BLUE  0

struct image_info
{
	int height;
	int width;
	int bpp;
};

struct header
{
	int16_t type;
	int32_t size;
	int16_t reserved1;
	int16_t reserved2;
	int32_t offbits;
}__attribute__((packed));

struct info
{
	int32_t size;
	int32_t width;
	int32_t height;
	int16_t planes;

	int16_t bit_count;
	int32_t compression;
	int32_t size_img;
	int32_t X_pel;
	int32_t Y_pel;
	int32_t clrused;
	int32_t clrImportant;
}__attribute__((packed));


#endif 
