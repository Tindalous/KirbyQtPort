#include "animation.h"

int cAnim;
int anim_t = 0;
int anim_pos = 0;
int anim_pos4 = 0;
const char directionsX[] = {0,0,0,0, -1,-1,0,0, 2,2,0,0, 1,1,0,0, 0,0,0,0, 1,0,0,0, 0,0,0,0,
                            -20,-20,0,0, 1,1,0,0, 0,0,0,0,
                            2,2,0,0, 0,0,0,0, 0,0,0,0, -4,-4,0,0, 4,4,0,0, 4,4,0,0 ,4,4,0,0 };

const char directionsY[] = {0,0,0,0, 0,0,0,0, -2,-2,0,0, 0,0,0,0, 0,0,0,0, 1,0,0,0, 0,0,0,0,
                            -32,-32,0,0, 2,2,0,0, 0,0,0,0,
                            4,4,0,0, 4,4,0,0, -4,-4,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 ,0,0,0,0 } ;

const char camDirs[] = {1,0,1,1,0,0,0,
                        0,0,0,
                        0,0,0,0,3,0,0};
const unsigned char sprites[] = {11,12,128,128, 11,12,128,128, 11,12,128,128, 128,128,128,128, 128,128,128,128, 10,128,128,128, 128,128,128,128,
                                 11,12,128,128, 11,12,128,128, 128,128,128,128,
                                 11,12,128,128, 11,12,128,128, 11,12,128,128, 11,12,128,128, 11,12,128,128, 11,12,128,128, 128,128,128,128};
const unsigned char timings[] = {32,10,8,20,30,30,255,
                                 1,20,255,
                                 2,5,7,7,20,3,10,255};
const int anims[] = {0,7,10,12};

void setAnim (byte a) {
    int c_anim = anims[a];
    anim_t = timings[c_anim];
    anim_pos = c_anim;
    anim_pos4 = c_anim*4;
    cAnim = a;
}

void chainAnim () {
    cAnim++;
    int c_anim = anims[cAnim];
    anim_t = timings[c_anim];
    anim_pos = c_anim;
    anim_pos4 = c_anim*4;
}

byte advAnim (byte *x, char *y, byte *sprs, int *cam) {
    for (int i = 0; i < 4; i++) {
        x[i] += directionsX[anim_pos4 + i];
        y[i] += directionsY[anim_pos4 + i];
        sprs[i] = sprites[anim_pos4 + i];
    }
    *cam += camDirs[anim_pos];
    anim_t--;
    if (anim_t == 0) {
        anim_pos++;
        anim_pos4 += 4;
        for (int i = 0; i < 4; i++) {
            sprs[i] = sprites[anim_pos4 + i];
        }
        if (timings[anim_pos] == 255) return 1;
        anim_t = timings[anim_pos];
    }
    return 0;
}
