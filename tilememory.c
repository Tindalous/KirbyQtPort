#include "tilememory.h"

unsigned int starBlocksX[64];
unsigned char starBlocksY[64]; //bit 7 es aparecido/desapercido
unsigned char starBlocksLength = 0;

unsigned int itemPosX[20];
unsigned char itemPosY[20];
unsigned char itemScreen[20];
unsigned char itemsLength = 0;

unsigned char checkStarBlock(int x, int y) {
    for (int i = 0; i < starBlocksLength; i++) {
        if (starBlocksX[i] == x && (starBlocksY[i] & 0x7F) == y) {
            return (starBlocksY[i] & 0x80) == 0x80;
        }
    }
    return 2;
}

void addStarBlock(int x, int y) {
    starBlocksX[starBlocksLength] = x;
    starBlocksY[starBlocksLength] = y;
    starBlocksLength++;
}

void destroyStarBlock(int x, int y) {
    for (int i = 0; i < starBlocksLength; i++) {
        if (starBlocksX[i] == x && (starBlocksY[i] & 0x7F) == y) {
            starBlocksY[i] |= 0x80;
        }
    }
}

void clearStarBlocks() {
    for (int i = 0; i < starBlocksLength; i++) {
        starBlocksX[i] = 0;
        starBlocksY[i] = 0;
    }
    starBlocksLength = 0;
}

unsigned char checkItemTile(int x, int y, int screen) {
    for (int i = 0; i < itemsLength; i++) {
        if (itemPosX[i] == x && (itemPosY[i] & 0x7F) == y && itemScreen[i] == screen) {
            return (itemPosY[i] & 0x80) == 0x80;
        }
    }
    return 2;
}

void addItemTile(int x, int y, int screen) {
    itemPosX[itemsLength] = x;
    itemPosY[itemsLength] = y;
    itemScreen[itemsLength] = screen;
    itemsLength++;
}

void destroyItemTile(int x, int y, int screen) {
    for (int i = 0; i < itemsLength; i++) {
        if (itemPosX[i] == x && (itemPosY[i] & 0x7F) == y && itemScreen[i] == screen) {
            itemPosY[i] |= 0x80;
        }
    }
}

void clearItemTiles() {
    for (int i = 0; i < itemsLength; i++) {
        itemPosX[i] = 0;
        itemPosY[i] = 0;
        itemScreen[i] = 0;
    }
    itemsLength = 0;
}
