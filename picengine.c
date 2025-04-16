#include "picengine.h"
#include "GLCD.h"

byte *pfullImage;
byte *pmetaTileSet;
byte *ptileSet;
byte *ptileMap;
byte *pspriteSheet;
byte *ptransSheet;

void initialize_engine(byte *fi, const byte *mt, const byte *ts, byte *tm, const byte *spriteS, const byte *transS) {
    pfullImage = fi;
    pmetaTileSet = mt;
    ptileSet = ts;
    ptileMap = tm;
    pspriteSheet = spriteS;
    ptransSheet = transS;
}



void renderImage(byte camX) {

    unsigned char *p;
    p = &pfullImage[camX*8];

    int portion = 80 - camX;
    //if (p >= &fullImage[576]) p = &fullImage;
    //int x = 0;
    int y = 0;

    int x = 1;
    while (y < 8) {
        writeByte(y,0,*p);
        byte *ptemp = p+8;
        x = 1;
        while (x < 64 && x < portion) {
            spWB(*ptemp);
            ptemp += 8;
            x++;
        }
        if (x != 64) ptemp = &pfullImage[0] + y;
        while (x < 64) {
            spWB(*ptemp);
            ptemp += 8;
            x++;
        }
        p++;
        y++;
    }
}





void drawTile(int x, int y) {
    unsigned char *p = &pfullImage[(y) + (x*64)];
    byte cTile = ptileMap[y + x*8];
    byte flip = cTile & 0x80;
    cTile &= 0x7F;
    int tPos = cTile*8;

    for (int i = 0; i < 8; i++) {
        if (!flip) *p = ptileSet[tPos + i];
        else *p = ptileSet[tPos + 7 - i];
        p+=8;
    }
}

void clearTile(int x, int y) {
    unsigned char *p = &pfullImage[(y) + (x*64)];
    ptileMap[y + x*8] = 0;
    for (int i = 0; i < 8; i++) {
        *p = 0;
        p+=8;
    }
}

void resetTiles(byte x, byte y) {

    drawTile(x,y);

    if (y < 7) drawTile(x,y+1);
    x++;
    if (x >= 10)x = 0;
    drawTile(x,y);
    if (y < 7) drawTile(x,y+1);
}

void ndrawSprite(byte x, byte y, byte spr, byte flip) {
    byte yDisp = y%8;
    byte yIni = y/8;
    byte *p = &pfullImage[(y/8) + x*8];
    int sprint = spr*8;
    byte spr1;
    byte spr2;
    byte trans1;
    byte trans2;
    for (int i = 0; i < 8; i++) {
        if (!flip) {
            trans1 = ptransSheet[sprint+i] << yDisp;
            trans2 = ptransSheet[sprint+i] >> (8-yDisp);
            spr1 = pspriteSheet[sprint+i] << yDisp;
            spr2 = pspriteSheet[sprint+i] >> (8-yDisp);
        } else {
            trans1 = ptransSheet[sprint+7-i] << yDisp;
            trans2 = ptransSheet[sprint+7-i] >> (8-yDisp);
            spr1 = pspriteSheet[sprint+7-i] << yDisp;
            spr2 = pspriteSheet[sprint+7-i] >> (8-yDisp);
        }
        byte temp = *p;
        temp = temp & ~trans1;
        temp = temp | spr1;
        *p = temp;
        p++;
        temp = *p;
        temp = temp & ~trans2;
        temp = temp | spr2;
        *p = temp;
        if (p >= &pfullImage[632]) p -= 640;
        p += 7;
    }
}
