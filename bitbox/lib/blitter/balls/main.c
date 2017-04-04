#include <math.h>
#include <bitbox.h>
#include "lib/blitter/blitter.h"

#if BITBOX_KERNEL != 0010 
#error must be compiled with kernel version v0.10 
#endif 

#include "bg.h"

#define SPRITE ball_small_spr
#define SPRITE_BIG ball_spr

extern const char SPRITE[];
extern const char SPRITE_BIG[];


// x and y  should be volatile since the vga thread must see the changes to x and y 
// which are runnin in the main thread 
#define NB_small 40
#define NB_big 3
#define NB (NB_small+NB_big)
#define MOVE_BALLS 1
#define ROTATE_BALLS 1
#define TILED_BG 0

object *ball[NB], *bg, *square;
int vx[NB],vy[NB];
const int ini_vy [8]= {-4, 3, 1,-6, 4,-7, 3,-5};
const int ini_vx [9]= {-2, 7, 1, 2, 4,-4, 3, 1 ,3};
const int ini_vz [8]= {-3,-5,-2,-2,-2, 3, 4, 5};
const int ini_y  [8]= {0,-50,100,-100,0,260,140,30};

uint32_t bgline(int l)
{
	return ((l/128)&1 ? RGB(100,100,100) : RGB(140,140,140))*0x10001;
}

void game_init() 
{
	blitter_init();

	if (TILED_BG)
		bg= tilemap_new (bg_tset, 64*16, 65535,bg_header,bg_tmap);
	else
		//bg= rect_new (0,0,VGA_H_PIXELS, VGA_H_PIXELS*3,200, RGB(100,100,100));
		bg=linegen_new(bgline);

	for (int i=0;i<NB_small;i++) {
		vx[i]=ini_vx[i%9];
		vy[i]=ini_vy[i%7];
		ball[i] = sprite_new((uint32_t *)&SPRITE, 0,ini_y[i%8], i);
		ball[i]->x = i*(VGA_H_PIXELS-ball[i]->w)/(NB_small+1); // fix X after the fact
	}

	for (int i=NB_small;i<NB;i++) {
		vx[i]=ini_vx[i%9];
		vy[i]=ini_vy[i%7]+10;
		ball[i] = sprite_new((uint32_t *)&SPRITE_BIG, 0,200+ini_y[i%8], 0);
		ball[i]->x = (i-NB_small)*(VGA_H_PIXELS-ball[i]->w)/(NB_big+1); // fix X after the fact
	}
}


void game_frame()
{
	if (MOVE_BALLS)	{
	    for (int i=0;i<NB;i++) {	

		    if (ball[i]->x + vx[i] >= (VGA_H_PIXELS-ball[i]->w) || ball[i]->x <0 )
		      	vx[i] = -vx[i];
		    
		    if ((ball[i]->y + vy[i]) > VGA_V_PIXELS-(int32_t)ball[i]->h )
		    	vy[i] = -vy[i]+1;


		    ball[i]->x += vx[i];
		    ball[i]->y += vy[i];
		    vy[i]+=1;
	    }
	}

	if (ROTATE_BALLS) {
		for (int i=0;i<NB;i++) {	
			ball[i]->fr = (vga_frame*ini_vz[i%8]/4)%8;
		}
	}
    
    uint32_t x = ((vga_frame%64)-32);
    bg->y = -x*x;
} 

