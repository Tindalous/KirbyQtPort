#ifndef TILEMEMORY_H
#define TILEMEMORY_H



unsigned char checkStarBlock(int x, int y);
void addStarBlock(int x, int y);
void destroyStarBlock(int x, int y);
void clearStarBlocks();

unsigned char checkItemTile(int x, int y, int screen);
void addItemTile(int x, int y, int screen);
void destroyItemTile(int x, int y, int screen);
void clearItemTiles();

#endif // TILEMEMORY_H
