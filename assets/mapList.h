#include <gb/gb.h>
#include "./bank2/maps/town01.h"
#include "./bank3/maps/house01.h"

typedef struct {
	int bankNumber; unsigned char data[64]; UWORD palletes[8*8]; UINT8 length;
} Tileset;
 
typedef struct {
	int bankNumber; UINT8 width; UINT8 height; unsigned char *tiledata; unsigned char *attributes; unsigned char *colision; int tilesetId;
} Mapa;

Mapa *mapas[2];
*mapas[0] = town01;
*mapas[1] = house01;