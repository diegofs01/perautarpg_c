#include "border.h"
#include "window.h"

#include "map1.h"
#include "tileset1.h"

UINT16 spritePalette[] = {
	tileset1CGBPal7c0, tileset1CGBPal7c1, tileset1CGBPal7c2, tileset1CGBPal7c3
};

UINT16 map1Palette[] = {
	tileset1CGBPal0c0, tileset1CGBPal0c1, tileset1CGBPal0c2, tileset1CGBPal0c3,
	tileset1CGBPal1c0, tileset1CGBPal1c1, tileset1CGBPal1c2, tileset1CGBPal1c3,
	tileset1CGBPal2c0, tileset1CGBPal2c1, tileset1CGBPal2c2, tileset1CGBPal2c3,
	tileset1CGBPal3c0, tileset1CGBPal3c1, tileset1CGBPal3c2, tileset1CGBPal3c3,
	tileset1CGBPal4c0, tileset1CGBPal4c1, tileset1CGBPal4c2, tileset1CGBPal4c3,
	tileset1CGBPal5c0, tileset1CGBPal5c1, tileset1CGBPal5c2, tileset1CGBPal5c3,
	tileset1CGBPal6c0, tileset1CGBPal6c1, tileset1CGBPal6c2, tileset1CGBPal6c3,
	tileset1CGBPal7c0, tileset1CGBPal7c1, tileset1CGBPal7c2, tileset1CGBPal7c3
};

UINT16 borderPalette[] = {
	borderCGBPal0c0, borderCGBPal0c1, borderCGBPal0c2, borderCGBPal0c3,
	borderCGBPal1c0, borderCGBPal1c1, borderCGBPal1c2, borderCGBPal1c3,
	borderCGBPal2c0, borderCGBPal2c1, borderCGBPal2c2, borderCGBPal2c3,
	borderCGBPal3c0, borderCGBPal3c1, borderCGBPal3c2, borderCGBPal3c3,
	borderCGBPal4c0, borderCGBPal4c1, borderCGBPal4c2, borderCGBPal4c3,
	borderCGBPal5c0, borderCGBPal5c1, borderCGBPal5c2, borderCGBPal5c3,
	borderCGBPal6c0, borderCGBPal6c1, borderCGBPal6c2, borderCGBPal6c3,
	borderCGBPal7c0, borderCGBPal7c1, borderCGBPal7c2, borderCGBPal7c3
};