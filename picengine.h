#ifndef PICENGINE_H
#define PICENGINE_H

#include "GLCD.h"

void initialize_engine(byte *fi, const byte *mt, const byte *ts, byte *tm, const byte *spriteS, const byte *transS);

void renderImage(byte camX);

void drawTile(int x, int y);

void clearTile(int x, int y);

void resetTiles(byte x, byte y);

void ndrawSprite(byte x, byte y, byte spr, byte flip);



#endif // PICENGINE_H
