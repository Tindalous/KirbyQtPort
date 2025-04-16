#ifndef ANIMATION_H
#define ANIMATION_H

#include "GLCD.h"

void setAnim (byte a);
void chainAnim();
byte advAnim (byte *x, byte *y, byte *sprs, int *cam);

#endif // ANIMATION_H
