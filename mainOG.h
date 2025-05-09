#ifndef MAINOG_H
#define MAINOG_H

#include <string.h>
#include <stdio.h>
#include <math.h>
#include "GLCD.h"
#include "gamedata.h"
#include "picengine.h"
#include "animation.h"
#include "tilememory.h"
#define _XTAL_FREQ 8000000

void frame(int ctrlL, int ctrlR, int ctrlA, int ctrlB);

void initFrame();
void initGame();

unsigned char getBuffer(int x, int y);


#endif // MAINOG_H
