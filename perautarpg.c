#include <gb/gb.h> 
#include <gb/cgb.h> 
#include <stdio.h>

#include "palettes.h"

#include "assets/tilesets/exterior_01.h"
#include "assets/tilesets/interior_01.h"
#include "assets/maps/town_01.h"
#include "assets/maps/house_01.h"

#define MAX_X_LIMITATION 160
#define MIN_X_LIMITATION 16
#define MAX_Y_LIMITATION 152
#define MIN_Y_LIMITATION 24
#define SCROLL_MOVE 8

#define PLAYER_POSITION_X 0
#define PLAYER_POSITION_Y 1

unsigned char colisionTest[400] = { 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
 };

int player[2];

int mapX = 152, mapY = 144, end;
int i = 0, spriteBackupX = 0, spriteBackupY = 0;

UBYTE activeMap = 0;
UBYTE menuPos = 0;
UBYTE currentKey;

void init();
void captureInput();
char checkColision(int x, int y);
void loadMap();

void main() {
	
	init();
	
	while(1) {
		captureInput();
		delay(100);
		wait_vbl_done();
	}
}

void captureInput() {
			
	currentKey = joypad();
		
	if (currentKey & J_RIGHT) {
		if (player[PLAYER_POSITION_X] < MAX_X_LIMITATION) {
			if(!checkColision(player[PLAYER_POSITION_X] + 8, player[PLAYER_POSITION_Y]) ) {
				player[PLAYER_POSITION_X] += SCROLL_MOVE;
				move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
			}
		} else {
			if (mapX < ((town_01Width - 1) * 8)) {
				mapX += SCROLL_MOVE;
				scroll_bkg(SCROLL_MOVE, 0);
			}
		}
	}
	if (currentKey & J_LEFT) {
		if(player[PLAYER_POSITION_X] > MIN_X_LIMITATION) {
			if(!checkColision(player[PLAYER_POSITION_X] - 8, player[PLAYER_POSITION_Y]) ) {
				player[PLAYER_POSITION_X] -= SCROLL_MOVE;
				move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
			}
		} else {
			if (mapX > 160) {
				mapX -= SCROLL_MOVE;
				scroll_bkg(-SCROLL_MOVE, 0);
			}
		}
	}
	if (currentKey & J_UP) {
		if(player[PLAYER_POSITION_Y] > MIN_Y_LIMITATION) {
			if(!checkColision(player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y] - 8) ) {
				player[PLAYER_POSITION_Y] -= SCROLL_MOVE;
				move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
			}
		} else {
			if(mapY > 152) {
				mapY -= SCROLL_MOVE;
				scroll_bkg(0, -SCROLL_MOVE);
			}
		}
	}
	if (currentKey & J_DOWN) {
		if(player[PLAYER_POSITION_Y] < MAX_Y_LIMITATION) {
			if(!checkColision(player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y] + 8) ) {
				player[PLAYER_POSITION_Y] += SCROLL_MOVE;
				move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
			}
		} else {
			if(mapY < (town_01Height * SCROLL_MOVE)) {
				mapY += SCROLL_MOVE;
				scroll_bkg(0, SCROLL_MOVE);
			}
		}
	}
	
	//Arrumar depois (Diego)
	if (currentKey & J_START) {
		
			if (activeMap == 0) {
				activeMap = 1;
			} else {
				activeMap = 0;
			}
			
			loadMap();
			
			//spriteBackupX = player[PLAYER_POSITION_X];
			//spriteBackupY = player[PLAYER_POSITION_X];
			
			//set_sprite_data(0, borderLen, border);
			//set_sprite_tile(0, 35);
			
			//player[PLAYER_POSITION_X] = 16;
			//player[PLAYER_POSITION_Y] = 136;
			
			//move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
			
			//move_win(7,112);
			//SHOW_WIN;
			
			delay(1000);
			
			/* while(1) {
				currentKey = joypad();
				if(currentKey & J_START) {
					menuPos = 0;
					player[PLAYER_POSITION_X] = spriteBackupX;
					player[PLAYER_POSITION_Y] = spriteBackupY;
					
					set_sprite_data(0, tileset1Len, tileset1);
					set_sprite_tile(0, 14);
					move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
					
					spriteBackupX = 0;
					spriteBackupY = 0;
					
					HIDE_WIN;
					break;
				}
				
				if( (currentKey & J_DOWN) || (currentKey & J_UP) ) {
					switch(menuPos) {
						case 0:
							player[PLAYER_POSITION_Y] += 8;
							menuPos = 2;
							move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
							break;
						case 1:
							player[PLAYER_POSITION_Y] += 8;
							menuPos = 3;
							move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
							break;
						case 2:
							player[PLAYER_POSITION_Y] -= 8;
							menuPos = 0;
							move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
							break;
						case 3:
							player[PLAYER_POSITION_Y] -= 8;
							menuPos = 1;
							move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
							break;
					}
				}
				
				if( (currentKey & J_RIGHT) || (currentKey & J_LEFT)) {
					switch(menuPos) {
						case 0:
							player[PLAYER_POSITION_X] += 72;
							menuPos = 1;
							move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
							break;
						case 1:
							player[PLAYER_POSITION_X] -= 72;
							menuPos = 0;
							move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
							break;
						case 2:
							player[PLAYER_POSITION_X] += 72;
							menuPos = 3;
							move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
							break;
						case 3:
							player[PLAYER_POSITION_X] -= 72;
							menuPos = 2;
							move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
							break;
					}
					
				}
				delay(150);
			} */

		} 
}

void init() {
	
	player[PLAYER_POSITION_X] = 70;
	player[PLAYER_POSITION_Y] = 100;
	
	loadMap();
	
	DISPLAY_OFF;
	
/* 	while(i < (windowWidth * windowHeight)) {
		window[i] += exterior_01Len;
		i++;
	}
	set_win_data(tileset1Len, borderLen, border);
	set_win_tiles(0, 0, windowWidth, windowHeight, window); */
	
	SPRITES_8x8;
	set_sprite_palette(0, 8, exterior_01_palettes);
	set_sprite_data(0, exterior_01Len, exterior_01);
	set_sprite_tile(0, 1);
	move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
	
	
	SHOW_SPRITES;
	DISPLAY_ON;
}

char checkColision(int x, int y) {
	end = (((y / 8) * 20) + (x / 8));
	
	return colisionTest[end];
}

void loadMap() {
	DISPLAY_OFF;
	HIDE_BKG;
	
	switch(activeMap) {
		
		default:
		case 0:
			set_bkg_palette(0, 8, exterior_01_palettes);
			set_bkg_data(0, exterior_01Len, exterior_01);
			VBK_REG = 1;
			set_bkg_tiles(0, 0, town_01Width, town_01Height, town_01_attributes);
			VBK_REG = 0;
			set_bkg_tiles(0, 0, town_01Width, town_01Height, town_01_tiledata);
			break;
			
		case 1:
			set_bkg_palette(0, 8, interior_01_palettes);
			set_bkg_data(0, interior_01Len, interior_01);
			VBK_REG = 1;
			set_bkg_tiles(0, 0, house_01Width, house_01Height, house_01_attributes);
			VBK_REG = 0;
			set_bkg_tiles(0, 0, house_01Width, house_01Height, house_01_tiledata);
			break;
	} 
	
	SHOW_BKG;
	DISPLAY_ON;
	wait_vbl_done();
}