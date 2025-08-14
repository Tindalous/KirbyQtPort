/* Main.c
 * Processor: PIC18F45K22
 * Compiler:  MPLAB XC8
 */

#include "mainOG.h"





unsigned char fullImage[640]; //8*80

unsigned char getBuffer(int x, int y) {
    return readByte(y,x); //Page y Y(horizontal)
}
unsigned char tileMap[80];

int camX = 0;

const byte *screenStartP;
int screenEnd;
const byte *entitiesStartP;
int entitiesEnd;
const byte *tpDataP;
const byte *tpAreaP;
const byte *tpXP;
const byte *tpYP;
const byte *tpCamP;
byte screenType;
int cEntity = 0;

//Current level data
int cLvlStartScreen;
int cLvlMapDataOffset;
int cLvlEntityDataOffset;
int cLvlTpDataOffset;
char cLvl = 1;
char cScreen = 0;
char holdingItem = 0;
int cScreenWidth = 0;
int cHeight = 0;


byte timer = 0;

byte gameState = 0; //0 = Gameplay, 1 = Animation, 2 = Animation end, 3 = Lock

int debugOut;

//Controller data
int charX = 0;
int charY = 0;

int spY = 0;
int accY = 2;
int grounded = 0;
int charSpr = 0;
int charFlip = 0;
int realCamX = 0;
int jumpPressed = 0;
int actPressed = 0;
int state = 0; // 0 = normal 1 = floating 2 = absorv 3 = full
int invincibility = 0;
byte HP = 6;
byte BOSS = 6;
int tempFormula = 0;
int dutyreal = 0;

byte suckTimer = 0;

int spitX = 0;
byte spitY = 0;
signed char spitDir = 0;//

//Tema entidades
int entityDat[] = {0,0,0,128,0,0,0,-1, //Primera columna X, segunda columna Y, tercera columna id de enemigo, ,4a columna sprite data, las otras 3 son variables de enemigo
                   0,0,0,128,0,0,0,-1,
                   0,0,0,128,0,0,0,-1,
                   0,0,0,128,0,0,0,-1};
byte bossMode = 0;

const char * s1 = "L7A Projecte\n\r";
const char * s2 = "Dani Mejias\n\r";
const char * s3 = "Biel Perez\n\r";
const char * kirbtxt = "Kirby\n\r";
const char * bosstxt = "Boss\n\r";
const char * gameovertxt = "Game Over\n\r";
const char * theendtxt = "The End\n\r";

const unsigned char kirbysplash [1024] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 64, 64, 32, 16, 12, 74, 138, 44, 216, 32, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 2, 6, 8, 112, 112, 241, 240, 120, 124, 3, 0, 0, 128, 128, 128, 192, 64, 64, 64, 64, 64, 192, 128, 128, 192, 64, 64, 64, 96, 32, 32, 32, 96, 64, 192, 128, 128, 128, 192, 96, 32, 192, 128, 0, 0, 128, 192, 64, 126, 193, 1, 1, 7, 252, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 124, 196, 2, 2, 6, 60, 224, 252, 6, 3, 1, 241, 31, 0, 252, 132, 4, 4, 12, 56, 238, 27, 17, 240, 0, 0, 24, 120, 120, 120, 0, 128, 193, 99, 62, 24, 240, 0, 0, 0, 60, 60, 24, 0, 192, 192, 35, 63, 62, 224, 128, 0, 7, 12, 6, 131, 96, 48, 12, 7, 253, 7, 3, 1, 1, 241, 97, 193, 131, 198, 124, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 126, 192, 0, 0, 3, 1, 64, 192, 0, 1, 31, 48, 96, 199, 252, 0, 0, 0, 3, 30, 112, 255, 0, 0, 0, 0, 252, 28, 112, 193, 129, 7, 12, 248, 143, 0, 0, 0, 30, 30, 14, 0, 0, 1, 131, 230, 60, 120, 207, 0, 0, 128, 254, 19, 124, 196, 4, 12, 56, 35, 60, 0, 0, 135, 252, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 252, 128, 0, 0, 143, 255, 4, 12, 24, 48, 32, 33, 47, 60, 136, 136, 136, 136, 15, 2, 196, 36, 36, 231, 128, 0, 0, 193, 98, 35, 225, 129, 227, 18, 98, 194, 2, 2, 2, 2, 243, 9, 4, 4, 248, 1, 3, 2, 3, 192, 112, 16, 17, 51, 230, 4, 4, 12, 8, 12, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 128, 128, 128, 128, 0, 128, 240, 17, 9, 9, 9, 204, 196, 4, 12, 24, 248, 126, 3, 1, 57, 44, 164, 231, 128, 254, 1, 112, 56, 112, 7, 28, 252, 3, 0, 224, 225, 3, 192, 240, 128, 15, 248, 128, 0, 224, 255, 0, 0, 255, 192, 112, 24, 12, 7, 129, 156, 159, 0, 0, 7, 248, 6, 3, 7, 28, 48, 126, 1, 2, 252, 0, 252, 2, 6, 196, 204, 152, 144, 112, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 15, 8, 48, 224, 128, 24, 120, 248, 249, 241, 226, 4, 24, 224, 0, 1, 1, 112, 224, 199, 143, 28, 240, 192, 128, 135, 68, 68, 71, 56, 16, 8, 6, 2, 4, 4, 15, 8, 6, 3, 1, 2, 3, 0, 3, 6, 6, 3, 0, 63, 65, 128, 128, 143, 143, 136, 120, 12, 6, 3, 0, 1, 31, 16, 24, 15, 112, 128, 128, 124, 24, 112, 192, 128, 255, 254, 1, 0, 30, 31, 31, 135, 195, 112, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 60, 96, 193, 135, 71, 97, 24, 12, 7, 3, 6, 4, 6, 3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};





void writeTxt(byte page, byte y, const char * s) {
    int i=0;
    while (*s!='\n' && *s!='\0' && *s!='\r')
    {
        putchGLCD(page, y+i, *(s++));
        ++i;
    }
}





byte getCol(int x, int y) {
    x /= 8;
    x %= 10;
    y /= 8;
    y %= 8;
    return tileMap[x*8 + y];
}

byte isCol(int x, int y) {
    byte c = getCol(x,y);
    if (c == 1 || c == 12) return 1;
    return 0;
}

void doItem(char n) {
    if (n == 14) {
        HP += 2;
        if (HP >= 6) HP = 6;
        writeNum(2,21,HP);
        state = 0;
        holdingItem = 0;
    }
    if (n == 15) {
        HP = 6;
        writeNum(2,21,HP);
        state = 0;
        holdingItem = 0;
    }
}

void setMetaTile(int x, int y, int t, int realX) { //Mover al main
    t *= 4;
    byte *tm = &tileMap[x*16 + y*2];//Aquí se ponen los tiles
    char offX = 0;
    char offY = 0;
    for (int i = 0; i < 4; i++) {
        offX = i >>1;
        offY = i &0x01;
        unsigned char tile = metaTileSet[t+i];
        *tm = tile;
        tile &= 0x7F;
        if (tile == 12) {
            unsigned char check1 = checkStarBlock(realX*2 + offX,y*2 + offY);
            if (check1 == 1) *tm = 0;
            else if (check1 == 2) addStarBlock(realX*2 + offX, y*2 + offY);
        }
        if (tile >= 13 && tile < 21) {
            unsigned char check2 = checkItemTile(realX*2 + offX,y*2 + offY, cScreen);
            if (check2 == 1) *tm = 0;
            else if (check2 == 2) addItemTile(realX*2 + offX, y*2 + offY, cScreen);
        }
        tm++;
        if (i == 1) tm += 6;

    }

    drawTile(x*2, y*2);
    drawTile(x*2+1, y*2);
    drawTile(x*2, y*2+1);
    drawTile(x*2+1, y*2+1);
}

void loadNewColumn(byte imgX, byte lvlX) {
    const byte *c = &screenStartP[lvlX];
    int colId = *c * 4;
    const byte *p = &columnSheet[colId];
    imgX %=5;
    for (int i = 0; i < 4; i++) {
        setMetaTile(imgX,i, *p, lvlX);
        p++;
    }

}

void loadLvl(int lvl) {
    lvl *= 4;
    cLvlStartScreen = lvlInfo[lvl];
    cLvlMapDataOffset = lvlInfo[lvl + 1];
    cLvlEntityDataOffset = lvlInfo[lvl + 2];
    cLvlTpDataOffset = lvlInfo[lvl + 3];
    clearStarBlocks();

}

byte spawnEntity(const byte *p, const byte id, byte *link) {
    for (int i = 0; i < 32; i+=8) {
        if (entityDat[i + 3] == 128) {
            entityDat[i] = realCamX + p[1];
            entityDat[i+1] = p[2];
            entityDat[i+2] = p[3]; //Tipo de entidad
            entityDat[i+3] = 0;
            entityDat[i+4] = 0;
            entityDat[i+5] = 0;
            entityDat[i+6] = 0;
            entityDat[i+7] = id; //Se usa en zona comentada con "entityID" para no respawnear enemigos al moverse adelante y atrás

            if (p[3] == 7 || p[3] == 22) {
                entityDat[i+6] = *link;
            }
            //A partir de la id 20 los enemigos son tipo boss
            if (p[3] >= 70 && p[3] < 80) {
                bossMode = 1;
            }
            *link = i;
            return 1;
        }
    }
    return 0;
}

void loadScreen(int screen, int posx, int posy, int newCam) {
    cScreen = screen;
    clearStarBlocks();
    spY = 0;
    cEntity = 0;
    state = 0;
    screen = screen*6;
    realCamX = 0;
    screenStartP = &fullLevel[screenInfo[screen] + cLvlMapDataOffset]; //Offset
    screenEnd = screenInfo[screen+1];
    entitiesStartP = &levelEntities[(screenInfo[screen+2]  + cLvlEntityDataOffset)*4]; //Offset
    entitiesEnd = screenInfo[screen+3];
    int tpIndex = screenInfo[screen+4] + cLvlTpDataOffset; //Offset
    tpDataP = &tpData[tpIndex];
    tpAreaP = &tpArea[tpIndex];
    tpXP = &tpPosX[tpIndex];
    tpYP = &tpPosY[tpIndex];
    tpCamP = &tpCamX[tpIndex];
    screenType = screenInfo[screen+5];
    if (screenType >= 4) {
        cScreenWidth = (screenType - 2)*64; //El minimo es 2
        screenType = 4;
        cHeight = (posx) / cScreenWidth;
    }
    charX = posx*10;
    charY = posy*10;
    realCamX = newCam;
    for (int i = 3; i < 32; i+=8) {
        entityDat[i] = 128;
    }

    for (int x = realCamX/16; x < 5 + realCamX/16; x++) {
        loadNewColumn(x,x);
    }

    byte linkId = -1;
    while (cEntity < entitiesEnd && entitiesStartP[cEntity*4]*16 <= realCamX) {
        if (entitiesStartP[cEntity*4]*16 == realCamX) {
            spawnEntity(&entitiesStartP[cEntity*4], cEntity, &linkId);
        }
        cEntity++;
    }
}

void findTPAndLoadScreen() {
    int tempx = charX/10;
    int i = 0;
    while (tpAreaP[i]*16 < tempx) i++;
    loadScreen(tpDataP[i] + cLvlStartScreen,tpXP[i],tpYP[i], tpCamP[i]);
}

void gameOver() {
    clearGLCD(0,7,0,127);
    writeTxt(3,8,gameovertxt);
    gameState = 3;
}

void gameEnd() {
    clearGLCD(0,7,0,127);
    writeTxt(3,8,theendtxt);
    gameState = 3;
}

void killEntity(byte e) {
    if (entityDat[e + 2] < 70) {
        entityDat[e + 3] = 128;
        entityDat[e + 7] = -1;
    } else {
        BOSS--;
        writeNum(5,21,BOSS);
        if (BOSS == 0) {
            if (entityDat[e + 2] < 80) gameEnd();
            else {
                entityDat[e + 3] = 128;
                entityDat[e + 7] = -1;
                findTPAndLoadScreen();
                BOSS = 6;
                writeNum(5,21,BOSS);
            }
        }
    }
}

byte getEntityCol(int x, int y) {
    int *p = &entityDat[0];
    for (int i = 0; i < 4; i++) {
        if (p[3] != 128) {
            if (x > p[0] && x < p[0] + 8 && y > p[1] && y < p[1] + 8) {
                return i*8;
            }
        }
        p += 8;
    }
    return 255;
}

void trySuck(byte entity, int charRoundX) {
    byte id = entityDat[entity+ 2];

    if (id <= 4) {
        suckTimer = 15;
        killEntity(entity);
        spitX = entityDat[entity] - charRoundX;
    }
    else if (id == 5) {
        suckTimer = 15;
        entityDat[entity+2] = 4;
        spitX = entityDat[entity] - charRoundX;
    } else if (id == 6) {
        suckTimer = 15;
        killEntity(entity);
        spitX = entityDat[entity] - charRoundX;
    } else if ((id >= 7 && id < 13) || (id >= 17 && id < 19) || (id > 19 && id < 70)) {
        suckTimer = 15;
        killEntity(entity);
        spitX = entityDat[entity] - charRoundX;
    }
}

void trySuckBlock(byte block, int charRoundX, int blockX, int blockY, int realBlockX) {
    spitX = realBlockX - charRoundX;

    realBlockX /= 8;
    blockX /= 8;
    blockX %= 10;
    blockY /= 8;
    blockY %= 8;
    suckTimer = 15;

    if (block == 12) destroyStarBlock(realBlockX, blockY);
    else if (block >= 13) {
        holdingItem = block;
        destroyItemTile(realBlockX, blockY, cScreen);
    }
    clearTile(blockX, blockY);
}

void charProcess(int ctrlL, int ctrlR, int ctrlA, int ctrlB) {

    int tempX = (charX/10)%80;
    int tempY = (charY/10)%64;
    int tempXtrue = charX/10;

    byte col = getEntityCol(tempXtrue +4, tempY + 4);
    if (col != 255) col = entityDat[col + 2];
    if (col != 255 && invincibility == 0) {
        invincibility = 30;
        spY = -20;
        HP--;
        writeNum(2,21,HP);
        if (HP == 0) gameOver();
    }
    if (invincibility != 0) invincibility--;

    //-----------------Vertical movement
    grounded = 0;
    int spX = 10;
    if (state != 0) spX = 5;
    spY += accY;
    if (isCol(tempX, tempY+8+(spY/10)) == 1 || isCol(tempX + 7, tempY+8+(spY/10)) == 1 ||
        isCol(tempX, tempY+(spY/10)) == 1 || isCol(tempX + 7, tempY+(spY/10)) == 1) {
        charY = ((charY + 70)/80)*80; //hacky af
        spY = 0;
        grounded = 1;
    }


    if (spY >= 40) spY = 40;
    charY += spY;
    tempY = (charY/10)%64;

    byte trans = 0;
    int starX = 0;
    int starY = 0;
    if (getCol(tempX + 4, tempY+4) == 8) {
        trans = 2;
        starX = ((charX/10)+4) & 0xFFFFFFF8;
        starY = ((charY/10)+4) & 0xFFFFFFF8;
    }
    if (ctrlB == 1) {
        if (jumpPressed == 0) {
            if (grounded && state != 1) {
                spY = -30;
            } else if (state < 2) {
                state = 1;
                spY = -20;
            }
            if (getCol(tempX + 4, tempY+4) == 6) {
                trans = 1;
            }

        }
        jumpPressed = 1;
    } else {
        jumpPressed = 0;
    }

    //-------------- Movimiento horizontal
    if ((ctrlR == 1) && state != 2) {
        if (isCol(tempX + 8, tempY+7) != 1 && isCol(tempX + 8, tempY) != 1) {
            charX+= spX;
        }
        charFlip = 0;
    }
    if ((ctrlL == 1) && state != 2) {
        if (isCol(tempX - 1, tempY+7) != 1 && isCol(tempX - 1, tempY) != 1) {
            charX-= spX;
        }
        charFlip = 1;
    }


    //----------------------Modo absorver
    if (state == 2) {

        if (suckTimer == 0) {
            int suckDir = charFlip? -7: 7;
            int col1 = getEntityCol(tempXtrue + 7+suckDir,tempY+4);
            int col2 = getEntityCol(tempXtrue + suckDir,tempY+4);
            int col3 = getCol(tempX + suckDir+4, tempY+4);
            if (col1 != 255) {
                trySuck(col1, tempXtrue);

            } else if (col2 != 255) {
                trySuck(col2, tempXtrue);
            } else if (col3 >= 12 && col3 <= 20) {
                trySuckBlock(col3, tempXtrue, tempX + suckDir + 4, tempY+4, tempXtrue + suckDir + 4);
            }
        }
    }

    //---------------------Entrar en modo absorver, escupir o dejar de flotar
    if (ctrlA == 1) {
        if (actPressed == 0) {
            if (state == 1) state = 0;
            else if (state == 0) state = 2;
            if (state == 3) {
                state = 0;
                spitX = charX/10;
                spitY = charY/10;
                spitDir = charFlip? -3: 3;
            }
        }
        actPressed = 1;
    } else {
        if (state == 2 && suckTimer == 0) state = 0;
        actPressed = 0;
    }

    if (suckTimer != 0) {
        suckTimer--;
        if (suckTimer == 0) {
            state = 3;
            doItem(holdingItem);
        }
    }


    if (trans == 1) {
        findTPAndLoadScreen();
    } else if (trans == 2) {
        //int temp = (charX + 40)/320;
        spitX = starX;
        spitY = starY - 8;
        charX = starX*10;
        charY = starY*10;
        gameState = 1;
        setAnim(cLvl<<1);
        tileMap[((tempX+4)/8)*8 + (tempY+4)/8] = 0;
    }



}



byte spawnTempEntity(byte x, byte y, byte type) {
    for (int i = 0; i < 32; i+=8) {
        if (entityDat[i + 3] == 128) {
            entityDat[i] = x; //Por chequear
            entityDat[i+1] = y;
            entityDat[i+2] = type;
            entityDat[i+3] = 0;
            entityDat[i+4] = 0;
            entityDat[i+5] = 0;
            entityDat[i+6] = 0;
            entityDat[i+7] = 255; //Porque
            return 1;
        }
    }
    return 0;
}

void enemyProcess(int *enemyP, byte self) {
    byte id = enemyP[2];
    if (id == 0) {
        if (timer%2) enemyP[0]--;
        enemyP[3] = 71;
    }

    if (id == 1) {
        if (timer%2) {
            if (enemyP[4] == 1) {
                enemyP[3] = 8;
                enemyP[0]++;
            }
            else {
                enemyP[0]--;
                enemyP[3] = 72;
            }
            enemyP[5]++;
            if (enemyP[5] > 16) {
                enemyP[4] ^= 0x01;
                enemyP[5] = 0;
            }
        }

    }

    if (id == 2) {
        enemyP[3] = 13;
        enemyP[5]++;
        if (enemyP[5] <= 60) enemyP[3] = 13;
        else {
            enemyP[3] = 13 + (timer%4)/2;
            if (enemyP[5] <= 80) enemyP[1]--;
            else if (enemyP[5] > 100) enemyP[1]++;
        }
        if (enemyP[5] == 120) enemyP[5] = 0;
    }

    if (id == 3) {
        enemyP[5]++;
        if (enemyP[5] <= 30) enemyP[1]--;
        else {
            enemyP[1]++;
        }
        enemyP[3] = 71;
        if (enemyP[5] == 60) enemyP[5] = 0;
    }

    if (id == 4) {
        if (timer/8 == 0) {
            enemyP[3] = 15;
        } else {
            enemyP[3] = 79;
        }
    }

    if (id == 5) {
        if (timer/8 == 0) {
            enemyP[3] = 16;
        } else {
            enemyP[3] = 80;
        }
    }

    if (id == 6) {
        if (enemyP[6] == 0 && enemyP[5] < 8) {
            enemyP[1]++;
            enemyP[5]++;
        }
        byte temp = timer/8;
        if (temp == 0) enemyP[3] = 19;
        else if (temp == 1) enemyP[3] = 20;

        enemyP[4]++;
        if (enemyP[4] <= 20) enemyP[0]--;
        else {
            enemyP[0]++;
        }
        if (enemyP[4] == 40) enemyP[4] = 0;

        enemyP[6] = 0;
    }

    if (id == 7) {
        entityDat[enemyP[6]*8 + 6] = 1;
        byte temp = timer/4;
        if (temp == 0) enemyP[3] = 17;
        else if (temp == 1) enemyP[3] = 81;
        else if (temp == 2) enemyP[3] = 82;
        else if (temp == 3) enemyP[3] = 18;

        enemyP[5]++;
        if (enemyP[5] <= 20) enemyP[0]--;
        else {
            enemyP[0]++;
        }
        if (enemyP[5] == 40) enemyP[5] = 0;

    }

    if (id == 8) { //Bronto Burt bajando
        enemyP[3] = 71;
        if (enemyP[5] == 0) {
            enemyP[1]++;
            if (enemyP[1] > charY/10) enemyP[5] = 1;
        } else if (enemyP[5] < 20) enemyP[5]++;
        else {
            enemyP[0]--;
        }
    }

    if (id == 9) {
        enemyP[3] = 17;
        enemyP[4]++;
        if (enemyP[4] > 15) enemyP[1]+=2;
    }

    if (id == 10) {
        enemyP[3] = 25;
        enemyP[0]--;
    }

    if (id == 11) {
        enemyP[5]++;
        if (enemyP[5] <= 15) enemyP[1]--;
        else {
            enemyP[1]++;
        }
        enemyP[3] = 71;
        if (enemyP[5] == 30) enemyP[5] = 0;
    }
    if (id == 12) { //Bomba lanzada
        enemyP[3] = 26;
        enemyP[0]-= 2;
    }

    if (id == 13) { //Gordo horizontal
        enemyP[3] = 27;
        if (timer%2) {
            if (enemyP[4] == 1) {
                enemyP[0]++;
            }
            else {
                enemyP[0]--;
            }
            enemyP[5]++;
            if (enemyP[5] > 16) {
                enemyP[4] ^= 0x01;
                enemyP[5] = 0;
            }
        }
    }

    if (id == 14) { //Gordo vertical
        enemyP[3] = 27;
        if (timer%2) {
            if (enemyP[4] == 1) {
                enemyP[1]++;
            }
            else {
                enemyP[1]--;
            }
            enemyP[5]++;
            if (enemyP[5] > 16) {
                enemyP[4] ^= 0x01;
                enemyP[5] = 0;
            }
        }
    }

    if (id == 15) { //Cannon izq
        enemyP[3] = 29;

        enemyP[4]++;
        if (enemyP[4] >= 45) {
            spawnTempEntity(enemyP[0],enemyP[1],16);
            enemyP[4] = 0;
        }
    }

    if (id == 16) { //Cannonball izq
        enemyP[3] = 32;
        enemyP[0]-= 2;
    }

    if (id == 17) { //Booler 1
        enemyP[3] = 31 | (enemyP[5] << 6);
        if (timer%2) {
            enemyP[4]++;
            if (enemyP[5] == 0) enemyP[0]--;
            else enemyP[0]++;

            if (enemyP[4] < 3) enemyP[1]--;
            else if (enemyP[4] < 21) enemyP[1]++; //Baja 18 px
            else if (enemyP[4] < 25);
            else if (enemyP[4] < 43) enemyP[1]--;
            else if (enemyP[4] < 45) enemyP[1]++;
            else {
                enemyP[4] = 0;
                enemyP[5] = 0x01^enemyP[5];
            }
        }
    }

    if (id == 18) { //Booler 2
        enemyP[3] = 31;
        if (timer%2) {
            enemyP[4]++;
            enemyP[0]--;
            if (enemyP[4] < 15) enemyP[1]--;
            else if (enemyP[4] >= 20 && enemyP[4] < 35) enemyP[1]++;
            else if (enemyP[4] >= 40) enemyP[4] = 0;
        }
    }

    if (id == 19) { //Mumbie
        enemyP[3] = 28;
        if (timer%3 == 0) {
            if (enemyP[1] > charY/10) enemyP[1]--;
            else enemyP[1]++;
            if (enemyP[0] > charX/10) enemyP[0]--;
            else enemyP[0]++;
        }
    }

    if (id == 20) { //Caja R Slow
        enemyP[3] = 25;
        if (timer%2 == 0)
            enemyP[0]--;

        if (enemyP[0] < 4) enemyP[3] = 128;

    }

    if (id == 21) { //Caja L Slow
        enemyP[3] = 25;
        if (timer%2 == 0)
            enemyP[0]++;
        if (enemyP[0] > 60) enemyP[3] = 128;
    }

    if (id == 70) { //Whispy woods
        enemyP[3] = 21;
        enemyP[4]++;
        if (enemyP[4] > 60) {
            spawnTempEntity(rand()/585,4,9); //rand llega a 32767
            enemyP[4] = 0;
        }
    }

    if (id == 71) { //Lololo Local 4: 0 = Lololo izq lalala der 1 = viceversa / Local 5: 0 = hueco abajo libre 1 = hueco medio libre 2 = hueco arriba libre / Local 6: 0 = nada 1 = tpindicator

        //Main
        if (timer%2 == 0) {
            //Reset
            if (enemyP[6] >= 10) {
                enemyP[6] = 0;
                if (enemyP[5] == 2) enemyP[1] = 24;
                else enemyP[1] = 8;
                if (enemyP[4] == 1) {
                    enemyP[0] = 2;
                    spawnTempEntity(enemyP[0] + 8,enemyP[1],21);
                }
                else {
                    enemyP[0] = 56;
                    spawnTempEntity(enemyP[0] - 8,enemyP[1],20);
                }
            }

            if (enemyP[6] == 0) {
                //Anim
                if (timer >= 8) enemyP[3] = 22;
                else enemyP[3] = 23;

                if (enemyP[4] == 0) {
                    enemyP[0]--;
                    if (enemyP[0] < 2) enemyP[6] = 1;
                } else {
                    enemyP[0]++;
                    enemyP[3] = 0x40 | enemyP[3];
                    if (enemyP[0] > 56) enemyP[6] = 1;
                }
            }

            //Sumar
            if (enemyP[6] != 0) {
                enemyP[6]++;
                enemyP[0] = 64;
                enemyP[1] = 56;
            }
            if (enemyP[6] >= 10) {
                enemyP[4] = rand()/16384;
                enemyP[5] = rand()/10923;
            }

        }


    }

    if (id == 72) { //Lalala

        //Main
        if (timer%2 == 0) {

            if (entityDat[enemyP[6]*8 + 6] >= 10) {
                enemyP[4] = entityDat[enemyP[6]*8 + 4];
                if (entityDat[enemyP[6]*8 + 5] == 0) enemyP[1] = 24;
                else enemyP[1] = 40;
                if (enemyP[4] == 1) {
                    enemyP[0] = 56;
                    spawnTempEntity(enemyP[0] - 8,enemyP[1],20);
                }
                else {
                    enemyP[0] = 2;
                    spawnTempEntity(enemyP[0] + 8,enemyP[1],21);
                }
            }

            //Anim
            if (timer >= 8) enemyP[3] = 22;
            else enemyP[3] = 23;


            if (enemyP[4] == 0) {
                enemyP[0]++;
                enemyP[3] |= 0x40;
            } else {
                enemyP[0]--;
            }
            //Set random vars
            if (entityDat[enemyP[6]*8 + 6] > 0 && entityDat[enemyP[6]*8 + 6] < 10) {
                enemyP[0] = 64;
                enemyP[1] = 56;
            }

        }



    }

    if (id == 80) { //LololoMini
        if (enemyP[5] == 0) enemyP[5] = enemyP[1];
        if (enemyP[4] < 30) {
            enemyP[0]--;
            if (timer >= 8) enemyP[3] = 22;
            else enemyP[3] = 23;
        } else if (enemyP[4] < 45) {
            enemyP[3] = 24;
        } else if (enemyP[4] < 74) {
            if (timer >= 8) enemyP[3] = 86;
            else enemyP[3] = 87;
            enemyP[0]++;
        } else {
            byte newRow = (rand()/10923)*16;
            enemyP[1] = enemyP[5] - newRow;
            enemyP[4] = 0;
            spawnTempEntity(enemyP[0] - 8,enemyP[1],10);
        }

        enemyP[4]++;
    }



    if (id == 81) {
        enemyP[3] = 19;
        enemyP[5]++;
        if (enemyP[5] > 60) {
            spawnTempEntity(enemyP[0] - 8,enemyP[1],12);
            enemyP[5] = 0;
        }
    }

    //Enemy despawn
    signed char relPos = enemyP[0] - realCamX;

    if (relPos < -16 || relPos > 72 || enemyP[1] <= 0 || enemyP[1] > 56) {
        enemyP[3] = 128;
        enemyP[7] = -1;
    }
}














void initFrame()
{



    GLCDinit();		   //Inicialitzem la pantalla
    clearGLCD(0,7,0,127);   //Esborrem pantalla
    setStartLine(0);        //Definim linia d'inici

    int temp = 0;
    for (int y = 0; y < 8; y ++) {
        for (int x = 0; x < 128; x++) {
            writeByte(y,x,kirbysplash[x + temp]);
        }
        temp += 128;
    }
    //__delay_ms(1000);




}

void initGame() {
    clearGLCD(0,7,0,127);


    initialize_engine(&fullImage[0], &metaTileSet[0], &tileSet[0], &tileMap[0], &spriteSheet[0], &transSheet[0]);

    loadLvl(cLvl);
    loadScreen(cLvlStartScreen,0,0,0);

    writeTxt(2,15,kirbtxt);
    writeTxt(5,16,bosstxt);
    writeNum(2,21,HP);
    writeNum(5,21,BOSS);
}

char sprY[] = {0,0,0,0,0,0};
byte sprX[] = 	{0,0,0,0,0,0};
byte sprDat[] = {0,128,128,128,128,128}; //Si el bit de mas peso (+128) es 1 el sprite es invisible, el segundo bit de mas peso (+64) decide el flip,  el resto se usa para determinar el sprite
byte eraseX;
byte eraseY;

char* frame(int ctrlL, int ctrlR, int ctrlA, int ctrlB) {
    if (gameState <= 2) {
        return gameProcess(ctrlL, ctrlR, ctrlA, ctrlB);
    }
    return "noFrame";
}

char* gameProcess(int ctrlL, int ctrlR, int ctrlA, int ctrlB) {
    //sprite erasing
    for (int i = 0; i < 6; i++) {
        eraseX = sprX[i] / 8;
        eraseY = sprY[i] / 8;
        if (sprY[i] >= 0)
            resetTiles(eraseX, eraseY);
    }
    int prevCamPos = realCamX/16;

    if (gameState == 0) {
        //animations
        timer++;
        if (timer > 15) timer = 0;
        if (state == 0) {
            sprDat[0] = timer/8;
        } else if (state == 1) sprDat[0] = 2;
        else if (state == 2) sprDat[0] = 3;
        else if (state == 3) sprDat[0] = timer/8 + 4;

        if (charFlip) sprDat[0] |= 0x40;
        else sprDat[0] &= 0xBF;


        if (invincibility != 0) {
            if (timer%2) sprDat[0] = 128;
        }



        //controller
        charProcess(ctrlL, ctrlR, ctrlA, ctrlB);

        //spit
        if (spitDir != 0) {
            spitX+= spitDir;
            sprDat[1] = 6;
            int col = getEntityCol(spitX+4,spitY+4);

            if (col != 255) {
                killEntity(col);
                spitDir = 0;
                sprDat[1] = 128;
            }

            int col2 = getCol(spitX+4,spitY+4);
            if (col2 == 12) {
                destroyStarBlock((spitX+4)/8, (spitY+4)/8);
                clearTile(((spitX+4)/8) % 80, (spitY+4)/8);
                spitDir = 0;
                sprDat[1] = 128;
            }
            if (spitX > realCamX + 64 || spitX < realCamX - 8) {
                spitDir = 0;
                sprDat[1] = 128;
            }

        }
        //suck
        if (suckTimer != 0) {
            int suckDir = charFlip? 1: -1;
            if (suckDir == 1 && spitX <= 0) spitX += suckDir;
            else if (suckDir == -1 && spitX >= 0) spitX += suckDir;
            sprX[1] = (sprX[0] + spitX)%80;
            sprY[1] = sprY[0];
            sprDat[1] = 6;
            if (suckTimer == 1)
                sprDat[1] = 128;
        } else {
            sprX[1] = spitX%80;
            sprY[1] = spitY;
        }

        //Procesado de enemigos
        int *enemyP = &entityDat[0];
        for (int i = 0; i < 4; i++) {
            if (enemyP[3] != 128) {
                enemyProcess(enemyP, i);
            }
            enemyP += 8;
        }

        //Mover camara
        int relPos = charX/10 - realCamX;
        //if (relPos < 0) relPos += 80; Maybe necessary
        //if (relPos < 0) relPos = 0;
        if (screenType != 1 && bossMode == 0) {
            if (relPos > 20) realCamX++;
            if (relPos < 10) realCamX--;
        }

        //Char limit
        if (realCamX < 0) realCamX = 0;

        if (relPos >= 56) charX = realCamX*10 + 550;
        if (relPos <= 0) charX = realCamX*10 + 20;
        if (charX < 10) charX = 10;

        if (screenType == 4) {
            int rectSpaceCamX = realCamX-(cHeight*cScreenWidth);

            if (rectSpaceCamX > cScreenWidth - 64) {
                realCamX = (cHeight+1)*cScreenWidth - 64;
            }

            if (rectSpaceCamX <= 0) {
                realCamX = cHeight*cScreenWidth;
            }
        }

        //Cam limit
        if (realCamX > screenEnd) {
            realCamX = screenEnd;
        }

        if (charX > screenEnd*10 + 560) {
            charX = screenEnd*10 + 560;
        }


        if (charY < 0) {
            if ((screenType != 1 && screenType != 4) || bossMode == 1) charY = 0;
            else if (screenType == 1) { //Camara vertical snap
                if (realCamX < screenEnd) {
                    charX += 800;
                    charY = 500;
                    realCamX += 80;
                    for (int x = 3; x < 32; x++) entityDat[x] = 128; //Arreglo para despawnear todos los enemigos de la pantalla anterior.
                    for (int x = realCamX/16; x < 5 + realCamX/16; x++) {
                        loadNewColumn(x,x);
                    }
                } else {
                    charY = 0;
                }

            } else if (screenType == 4) {
                if (realCamX < screenEnd) {
                    cHeight++;
                    charX += 10* cScreenWidth;
                    charY = 500;
                    realCamX += cScreenWidth;
                    for (int x = 3; x < 32; x++) entityDat[x] = 128; //Arreglo para despawnear todos los enemigos de la pantalla anterior.
                    for (int x = realCamX/16; x < 5 + realCamX/16; x++) {
                        loadNewColumn(x,x);
                    }
                } else {
                    charY = 0;
                }
            }
        }

        if (charY > 560) {
            if ((screenType != 1 && screenType != 4) || bossMode == 1) gameOver();
            else if (screenType == 1) {
                charX -= 800;
                charY = 60;
                realCamX -= 80;
                for (int x = realCamX/16; x < 5 + realCamX/16; x++) {
                    loadNewColumn(x,x);
                }

            } else if (screenType == 4) {
                cHeight--;
                charX -= 10* cScreenWidth;
                charY = 60;
                realCamX -= cScreenWidth;
                for (int x = realCamX/16; x < 5 + realCamX/16; x++) {
                    loadNewColumn(x,x);
                }
            }
        }


        sprY[0] = (charY/10)%64;
        sprX[0] = (charX/10)%80;

        byte eShown = 0;
        for (int i = 2; i < 6; i++) {
            sprX[i] = entityDat[eShown] % 80;
            if (sprX[i] > 128) sprX[i] = sprX[i] + 80;
            sprY[i] = entityDat[eShown + 1];
            sprDat[i] = entityDat[eShown + 3];
            eShown+=8;
        }


    } else if (gameState == 1) {
        if (advAnim(&sprX[0], &sprY[0], &sprDat[0], &realCamX) == 1) {
            findTPAndLoadScreen();
            if (screenType == 0) gameState = 0;
            sprDat[0] = 128;
            sprDat[1] = 128;
            if (screenType == 2) {
                sprX[0] = charX/10;
                sprY[0] = charY/10;
                sprX[1] = sprX[0];
                sprY[1] = sprY[0]-8;
                chainAnim();
                gameState = 2;
            }
        }
    } else if (gameState == 2) {
        if (advAnim(&sprX[0], &sprY[0], &sprDat[0], &realCamX) == 1) {
            if (screenType <= 2) gameState = 0;//Añadir el chain mapas
        }
    }

    if (gameState == 3) return "";

    camX = realCamX%80;

    //añadiendo de nuevas partes del mapa
    if (realCamX/16 > prevCamPos) {
        loadNewColumn(camX/16 + 4, realCamX/16 + 4);
        byte linkId = -1;
        while (entitiesStartP[cEntity*4]*16 <= realCamX && cEntity < entitiesEnd) {
            byte existsE = 0;
            for (int i = 7; i < 31; i+=8) {
                if (entityDat[i] == cEntity) existsE = 1; //Uso de entityID
            }
            if (existsE == 0 && entitiesStartP[cEntity*4]*16 == realCamX)
                spawnEntity(&entitiesStartP[cEntity*4], cEntity, &linkId);
            cEntity++;
        }
    }

    if (realCamX/16 < prevCamPos) {
        byte linkId = -1;
        loadNewColumn(camX/16, realCamX/16);
        while (entitiesStartP[cEntity*4 - 4]*16  >= realCamX + 1 && cEntity > 0) {

            cEntity--;
        }
        if (screenType == 1) {
            int temp = cEntity - 1;
            while (entitiesStartP[temp*4]*16 == realCamX && temp >= 0) {
                byte existsE = 0;
                for (int i = 7; i < 31; i+=8) {
                    if (entityDat[i] == temp) existsE = 1;
                }
                if (existsE == 0)
                    spawnEntity(&entitiesStartP[temp*4], temp, &linkId);
                temp--;
            }
        }
        if (cEntity < 0) cEntity = 0;
    }

    //Rendering
    for (int i = 0; i < 6; i++) {
        if (!(sprDat[i] & 0x80) && sprY[i] >= 0) {
            ndrawSprite(sprX[i],sprY[i],sprDat[i] & 0x3F, sprDat[i] & 0x40);
        }
    }


    if (camX > 79) camX = 0;
    if (camX < 0) camX = 79;
    for (int i = 0; i < 6; i++) {
        sprX[i] %= 80;
    }
    renderImage(camX);


    //DEBUG SHENANIGANS
    char* ret = malloc(100*sizeof(char));
    char outNum = sprX[1];
    ret[0] = outNum/16 +48;
    if (ret[0] > 48+9) ret[0] += -48+65-10;
    ret[1] = outNum%16 + 48;
    if (ret[1] > 48+9) ret[1] += -48+65-10;
    ret[2] = '\0';
    return ret;
}
