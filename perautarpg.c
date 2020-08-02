#include <gb/gb.h> 
#include <gb/cgb.h> 
#include <stdlib.h>
#include <string.h>

#include "palettes.h"
#include "./assets/mapList.h"

#include "assets/tilesets/sprites_01.h"
#include "assets/tilesets/exterior_01.h"
#include "assets/tilesets/interior_01.h"
#include "assets/maps/town_01.h"
#include "assets/maps/house_01.h"
#include "assets/border.h"
#include "assets/window.h"

#define MAX_X_LIMITATION 160
#define MIN_X_LIMITATION 16
#define MAX_Y_LIMITATION 152
#define MIN_Y_LIMITATION 24
#define SCROLL_MOVE 8

#define PLAYER_POSITION_X 0
#define PLAYER_POSITION_Y 1

int player[2];
char teste[3];

int mapX = 152, mapY = 144, end;
int i = 0, spriteBackupX = 0, spriteBackupY = 0;

UBYTE mapaAtual = 0;
UBYTE menuPos = 0;
UBYTE currentKey;

void init();
void captureInput();
char checkColision(int x, int y);
void loadMap(int mapId);
void mostrarPosicaoSprite();
void player_pos_to_map_tile(unsigned char *tiles, int posicao);
void render_map_info(int mapId);

void main() {	
	init();
	
	while(1) {
		captureInput();
		delay(100);
		mostrarPosicaoSprite();
		wait_vbl_done();
	}
}

void captureInput() {
			
	char colision;
	
	currentKey = joypad();
	
	if (currentKey & J_SELECT) {
		player[PLAYER_POSITION_X] = 0;
		player[PLAYER_POSITION_Y] = 0;
		move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
		move_sprite(1, player[PLAYER_POSITION_X] + 8, player[PLAYER_POSITION_Y]);
	}
	if (currentKey & J_RIGHT) {
		if (player[PLAYER_POSITION_X] < MAX_X_LIMITATION) {
			colision = checkColision(player[PLAYER_POSITION_X] + 8, player[PLAYER_POSITION_Y]);
			if(colision == 0) {
				player[PLAYER_POSITION_X] += SCROLL_MOVE;
				move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
				move_sprite(1, player[PLAYER_POSITION_X] + 8, player[PLAYER_POSITION_Y]);
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
			colision = checkColision(player[PLAYER_POSITION_X] - 8, player[PLAYER_POSITION_Y]);
			if(colision == 0) {
				player[PLAYER_POSITION_X] -= SCROLL_MOVE;
				move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
				move_sprite(1, player[PLAYER_POSITION_X] + 8, player[PLAYER_POSITION_Y]);
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
			colision = checkColision(player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y] - 8);
			if(colision == 0) {
				player[PLAYER_POSITION_Y] -= SCROLL_MOVE;
				move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
				move_sprite(1, player[PLAYER_POSITION_X] + 8, player[PLAYER_POSITION_Y]);
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
			colision = checkColision(player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y] + 8);
			if(colision == 0) {
				player[PLAYER_POSITION_Y] += SCROLL_MOVE;
				move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
				move_sprite(1, player[PLAYER_POSITION_X] + 8, player[PLAYER_POSITION_Y]);
			}
		} else {
			if(mapY < (town_01Height * SCROLL_MOVE)) {
				mapY += SCROLL_MOVE;
				scroll_bkg(0, SCROLL_MOVE);
			}
		}
	} 
}

void init() {
	
	player[PLAYER_POSITION_X] = 9*8;
	player[PLAYER_POSITION_Y] = 10*8;
	
	while(i < (windowWidth * windowHeight)) {
		window_tiledata[i] += 89;
		i++;
	}
	
	set_bkg_data(89, borderLen, border);
	
	loadMap(mapaAtual);
	
	DISPLAY_OFF;
	
	SPRITES_8x16;
	set_sprite_palette(0, 8, sprites_01_palettes);
	
	set_sprite_prop(0, sprites_01CGB[1]);
	set_sprite_prop(1, sprites_01CGB[2]);
	VBK_REG = 0;
	set_sprite_data(0, sprites_01Len * 2, sprites_01);
	set_sprite_tile(0, 2);
	set_sprite_tile(1, 4);
	move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
	move_sprite(1, player[PLAYER_POSITION_X] + 8, player[PLAYER_POSITION_Y]);
	
	SHOW_SPRITES;
	DISPLAY_ON;
}

char checkColision(int x, int y) {
	end = (((y / 8) * 20) + (x / 8));
	
	return colisionTest[end];
}

void loadMap(int mapId) {
	int tilesetId = mapas[mapId].tilesetId;
	
	DISPLAY_OFF;
	HIDE_BKG;
	
	set_bkg_palette(0, 7, tilesets[tilesetId].palletes);
	set_bkg_data(0, tilesets[tilesetId].length, tilesets[tilesetId].data); 
	
	/* set_bkg_palette(0, 7, exterior_01_palettes);
	set_bkg_data(0, exterior_01Len, exterior_01); */
	
	VBK_REG = 1;
	set_bkg_tiles(0, 0, mapas[mapId].width, mapas[mapId].height, mapas[mapId].attributes);
	
	VBK_REG = 0;
	set_bkg_tiles(0, 0, mapas[mapId].width, mapas[mapId].height, mapas[mapId].tiledata);
	
	//render_map_info(mapId);

	VBK_REG = 0;	
	set_bkg_tiles(0, 16, windowWidth, windowHeight, window_tiledata);
	
	SHOW_BKG;
	DISPLAY_ON;
	wait_vbl_done();
}

void mostrarPosicaoSprite() {
	
	//por algum motivo o gameboy/bgb odeia o numero 125 ://////////
	/* os tiles numerais começa no 116 (0x74)
	   logo pega a variavel/numero e adiciona 116
	   por exemplo: numero 1 = tile 117, 
	                numero 2 = tile 118, etc */
	
	// array pra armazenar os ids dos tiles e para nao bugar o set_bkg_tiles
	unsigned char tiles[3] = {125, 125, 125};
	
	// renderizar a posição X da sprite na 'barra de status'
	player_pos_to_map_tile(tiles, player[0]);
	set_bkg_tiles(8, 16, 3, 1, tiles);
	
	// renderizar a posição Y da sprite na 'barra de status'
	player_pos_to_map_tile(tiles, player[1]);
	set_bkg_tiles(8, 17, 3, 1, tiles);
}

void player_pos_to_map_tile(unsigned char *tiles, int posicao) {
	if(posicao >= 100) {
		tiles[2] = (posicao % 10) + 116;
		posicao /= 10;
		tiles[1] = (posicao % 10) + 116;
		posicao /= 10;
		tiles[0] = (posicao % 10) + 116;
	} else {
		if(posicao >= 10) {
			tiles[0] = 116;
			tiles[1] = (posicao / 10) + 116;
			tiles[2] = (posicao % 10) + 116;
		} else {
			tiles[0] = 116;
			tiles[1] = 116;
			tiles[2] = posicao + 116;
		}
	}
}

void render_map_info(int mapId) {
	unsigned char tiles[8] = {1, 1, 1, 1, 1, 1, 1, 1};
	int i;
	
	for(i = 0; i < strlen(mapas[mapId].mapName); i++) {
		tiles[i] = mapas[mapId].mapName[i] += 25;
	}
	set_bkg_tiles(12, 17, 8, 1, tiles);
}

//Arrumar depois (Diego)
/*if (currentKey & J_START) {
			
	//spriteBackupX = player[PLAYER_POSITION_X];
	//spriteBackupY = player[PLAYER_POSITION_X];
	
	//set_sprite_data(0, borderLen, border);
	//set_sprite_tile(0, 35);
	
	//player[PLAYER_POSITION_X] = 16;
	//player[PLAYER_POSITION_Y] = 136;
	
	//move_sprite(0, player[PLAYER_POSITION_X], player[PLAYER_POSITION_Y]);
	
	//move_win(7,112);
	//SHOW_WIN;
	
	//delay(1000);
	
	while(1) {
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
	}

} */

