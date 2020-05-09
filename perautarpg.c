#include <gb/gb.h> 
#include <stdio.h>

#include "border.h"
#include "window.h"

#include "map1.h"
#include "tileset1.h"

#define MAX_X_LIMITATION 160
#define MIN_X_LIMITATION 16
#define MAX_Y_LIMITATION 152
#define MIN_Y_LIMITATION 24
#define SCROLL_MOVE 8

void main() {
	
	int spriteX = 16, spriteY = 24;
	int mapX = 152, mapY = 144;
	int windowActive = 0;
	
	DISPLAY_OFF;
	
	SPRITES_8x8;
	set_sprite_data(0,tileset1Len,tileset1);
	set_sprite_tile(0,14);
	move_sprite(0,spriteX,spriteY);
	
	set_bkg_data(0, tileset1Len, tileset1);
	set_bkg_tiles(0, 0, map1Width, map1Height, map1);
	
	set_win_data(tileset1Len, borderLen, border);
	set_win_tiles(0, 0, windowWidth, windowHeight, window);
	
	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	
	while(1) {
		if (joypad() == J_RIGHT) {
			if (spriteX < MAX_X_LIMITATION) {
				spriteX += SCROLL_MOVE;
				move_sprite(0, spriteX, spriteY);
			} else {
				if (mapX < ((map1Width - 1) * 8)) {
					mapX += SCROLL_MOVE;
					scroll_bkg(SCROLL_MOVE, 0);
				}
			}
		}
		if (joypad() == J_LEFT) {
			if(spriteX > MIN_X_LIMITATION) {
				spriteX -= SCROLL_MOVE;
				move_sprite(0, spriteX, spriteY);
			} else {
				if (mapX > 160) {
					mapX -= SCROLL_MOVE;
					scroll_bkg(-SCROLL_MOVE, 0);
				}
			}
		}
		if (joypad() == J_UP) {
			if(spriteY > MIN_Y_LIMITATION) {
				spriteY -= SCROLL_MOVE;
				move_sprite(0, spriteX, spriteY);
			} else {
				if(mapY > 152) {
					mapY -= SCROLL_MOVE;
					scroll_bkg(0, -SCROLL_MOVE);
				}
			}
		}
		if (joypad() == J_DOWN) {
			if(spriteY < MAX_Y_LIMITATION) {
				spriteY += SCROLL_MOVE;
				move_sprite(0, spriteX, spriteY);
			} else {
				if(mapY < (map1Height * SCROLL_MOVE)) {
					mapY += SCROLL_MOVE;
					scroll_bkg(0, SCROLL_MOVE);
				}
			}
		}
		if (joypad() == J_START) {
			if(windowActive == 0) {
				windowActive = 1;
				move_win(7,112);
				SHOW_WIN;
			} else {
				windowActive = 0;
				HIDE_WIN;
			}
		}
		delay(100);
	}

}