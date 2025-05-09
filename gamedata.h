#ifndef GAMEDATA_H
#define GAMEDATA_H


const unsigned char tileSet[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0x00,0xC0,0x60,0x20,0x30,0x08,0x04,0x04,
    0x00,0x03,0x04,0x04,0x08,0x10,0x10,0x10,
    0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55, //32 4
    0xFC,0xFF,0xFC,0xF0,0xFC,0xFF,0xFC,0xF0,
    0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF, // puerta
    0xF0,0x0C,0x02,0x02,0x02,0x02,0x0C,0xF0,
    0x0C,0x74,0x42,0x21,0x21,0x42,0x74,0x0C, //Estrella
    0x80,0x80,0x80,0x40,0x40,0x20,0x18,0x07, //hoja
    0xFF,0xAA,0x00,0x00,0x00,0x00,0x00,0x00, //tronco 10
    0x8D,0x08,0x88,0x88,0xF8,0x80,0x08,0x88, //Ladrillos
    0xFF,0xF7,0xC7,0xE1,0xC7,0xF7,0xFF,0xFF, //StarBlock
    0x02,0x7F,0x7F,0x20,0x38,0xF8,0x28,0x38, //1up
    0x00,0x7C,0x97,0x95,0x97,0x7C,0x00,0x00, //bottle
    0x38,0x45,0xBA,0x93,0x92,0xBB,0x45,0x38, //maxitomato
    0x18,0x20,0xBE,0x69,0x69,0xBE,0x20,0x18, //micro
    0x30,0x58,0x7C,0x7C,0x64,0x64,0x58,0x30, //curry
    0xE0,0xBC,0xD6,0x6A,0x56,0x6B,0x3D,0x07, //leaf
    0xC0,0xA0,0x5C,0x32,0x21,0x21,0x12,0x0C, //piruleta invencible
    0x38,0x7C,0xF6,0xFE,0xFC,0x7A,0x35,0x01, //bomba
    0xFF,0xFB,0xFD,0xAD,0xF5,0xFB,0xFF,0xFF, //interrogante 1
    0xF0,0x90,0x4C,0x4A,0x29,0xFD,0x63,0x82, //Palmera superior
    0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00, //Palmera tronco
    0x04,0x08,0x10,0x10,0x20,0x20,0x40,0x40, //Agua
    0x07,0x38,0xC0,0x38,0x07,0x38,0xC0,0x38, //Pichos arriba
    0xE0,0x1C,0x03,0x1C,0xE0,0x1C,0x03,0x1C, //Pinchos abajo
    0x24,0x3E,0xE3,0x42,0x42,0xE3,0x3E,0x24, //Tierra fondo
    0x88,0x44,0x22,0xFF,0x22,0x44,0x88,0x88, //Cuerdas de fondo
    0x13,0x31,0x13,0x31,0x13,0x31,0x13,0x31, //Madera fondo
};

const unsigned char spriteSheet[] = {0xFC,0xC2,0xE1,0x99,0x81,0xD9,0xC2,0xFC, //quieto
    0x3C,0x42,0xE1,0xD9,0xC1,0xD9,0x42,0x3C, //caminar
    0xFF,0xC1,0x82,0x8D,0x81,0x8D,0x42,0x3C, //flotar
    0x0E,0x6A,0xF2,0xC1,0x41,0x47,0x59,0x66, //absorver
    0xFC,0xC2,0xF1,0x85,0xA1,0xC5,0xC2,0xFC, //quieto lleno
    0x3C,0x42,0xF1,0xC5,0xE1,0x85,0x42,0x3C, //caminar lleno 5
    0x0C,0x74,0x42,0x21,0x21,0x42,0x74,0x0C, //estrella
    0x0F,0x11,0x32,0x5C,0x84,0x94,0xB4,0x78, //enemigo volador
    0x3C,0x42,0xF2,0xDE,0xE1,0xED,0x63,0x3C, //Waddle dee
    0x0F,0x11,0x32,0x5C,0x84,0x94,0xB4,0x78,
    0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,//Estrella fondo 10
    0x0D,0x76,0x43,0x21,0x21,0x42,0x76,0x0D,//Estrella con kirby (1)
    0xE0,0x10,0x08,0x68,0x08,0x68,0x10,0xE0,
    0x08,0x16,0x35,0x41,0x41,0x4E,0x22,0x1C,//pajarete 13
    0x08,0x16,0x35,0x41,0xE1,0x8E,0x68,0x18,
    0x70,0x4E,0x8D,0xA1,0x8D,0xB5,0xD2,0x1E,//nochaminao 15
    0x1E,0x71,0x89,0x91,0x91,0xB9,0xD2,0x0C, //sichampinao
    0x3C,0x42,0x81,0x81,0x83,0x85,0x4A,0x3D, //manzana de balance
    0x3C,0x42,0x81,0x81,0xC1,0xA1,0x52,0xBC,
    0x1E,0x2B,0xE3,0xEB,0xE3,0x1F,0x07,0x0E,//Hombrecito de la manzana 19
    0x7E,0xEB,0xE3,0x2B,0x23,0xFF,0xE7,0x0E,
    0x7E,0xFF,0x7E,0x00,0x7E,0xFF,0x7E,0x00, //Whispy woods
    0x3C,0xDA,0xC2,0x5A,0xC2,0xCC,0x50,0x20, //lololo w1
    0x3C,0x5A,0xC2,0xDA,0xC2,0x4C,0x50,0x20, //lololo w2
    0x66,0xF9,0xC2,0x5A,0x42,0xDA,0xC2,0x3C, //lololo pose
    0x7E,0x81,0x81,0x81,0x81,0x81,0x81,0x7E, //caja 25
    0x38,0x7C,0xF6,0xFE,0xFC,0x7A,0x35,0x01,
    0x12,0xA4,0x5A,0x7F,0xDA,0x66,0x3D,0x48, //Gordo
    0x3C,0x52,0xB5,0xBD,0xA9,0xB9,0x5A,0x3C, //Mumbie
    0x3C,0x3C,0x18,0x3C,0x72,0x7A,0x7E,0x3C, //Canyon hor
    0x00,0x70,0xFB,0xFF,0xEF,0xCB,0x70,0x00, //Canyon up 30
    0x3E,0x4D,0xE1,0xED,0x81,0x82,0x5C,0x38, //Booler
    0x00,0x3C,0x72,0x7A,0x7E,0x7E,0x3C,0x00, //Cannon Ball
};

const unsigned char transSheet[] = {0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,//5
                                    0x00,0x08,0x7E,0x3F,0x3F,0x7E,0x08,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//10
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,//13
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,//15
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,//20
                                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,//25
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,//30
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
                                    };








//ScreenInfo
//screenStart, screenEnd, entitiesStart, entitiesEnd, tpDataStart, screenType 0 = horizontal 1 = vertical 2 = autoanim 3 = autoanim+autoexit 4 = rectangle, x,y
//LvlInfo
//Startscreen, tileinfostart, entityinfostart, tpinfostart,
//levelEntities
//camx posx posy id
const unsigned char fullLevel[] = {0,2,2,0,0,5,5,5,0,2,3,15,7,16,1,4,1,0,5,10,4,4,6,6,6,6,8,41,7,9,0,2,0,14,11,12,12,13,0,1,0,2,14,11,12,11,12,13,0,5,2,14,12,11,13,15,7,16,8,0,0,9,0,17,19,19,21,0,20,19,19,18,0,17,19,4,18,0,20,4,19,18,0,22,42,19,21,0,17,4,4,18,0,20,19,24,21,0,14,11,11,12,0,23,25,19,23,0,0,2,0,14,0,2,0,26,27,0,28,29,0,9,0,4,4,24,18,0,24,4,4,18,0,8,27,26,26,30,30,26,26,26,30,30,26,27,9,8,27,26,31,31,31,31,31,31,31,26,1,32,1,4,4,26,26,0,28,33,33,0,2,5,19,34,25,36,35,7,0,37,40,0,19,24,4,4,0,4,4,39,38,0,24,4,4,24,0,1,43,7,1,0,29,44,46,28,44,29,47,44,28,46,44,29,25,25,45,19,48,4,4,48,19,45,49,25,0,0,0,50,51,0,4,54,52,53,0,54,4,36,35,0,0,0,0,55,55,0,0,7,4,4,4,19,24,4,4,4,0,29,0,7,28,0,29,2,0,2,5,19,24,19,0,33,29,28,33,0,59,56,5,5,5,57,58,2,61,0,56,56,56,56,60,59,59,3,59,59,1,60,59,60,59,57,0,56,58,59,59,60,59,59,60,60,59,59,59,60,59,2,58,2,57,58,57,0,62,63,1,2,2,2,2,2,38,38,38,38,38,};
const byte levelEntities[] = {1,56,40,1,2,64,32,1,3,56,32,2,4,72,32,3,5,71,40,1,13,64,40,2,1,56,32,6,1,56,40,7,2,48,0,8,3,54,40,5,6,60,24,1,8,64,40,1,9,48,0,8,10,48,0,8,13,56,32,6,13,56,40,7,15,54,40,5,16,54,0,8,18,54,32,6,18,54,40,7,5,24,24,1,10,40,24,1,15,20,24,4,20,32,24,2,20,44,24,4,35,16,24,2,35,40,24,1,0,51,25,70,0,54,39,81,0,48,7,1,0,0,16,11,0,32,40,1,0,40,40,1,10,48,23,15,0,56,39,18,0,40,0,8,6,72,40,18,7,48,0,8,7,72,39,1,0,57,27,18,0,46,0,19,2,72,27,19,3,66,35,18,6,65,27,17,0,56,40,80,0,67,46,18,0,60,17,1,0,44,25,1,0,40,23,14,5,64,18,3,10,25,14,13,15,41,32,13,0,48,23,17,5,23,40,3,5,52,0,1,5,48,23,15,10,7,41,3,0,48,22,17,0,56,9,71,0,0,25,72,9,0,0,0,9,0,0,0,248,127,0,0,248,127,0,0,};
const int lvlInfo[] = {0,0,0,0,6,113,29,7,20,278,60,32,21,329,60,33,22,334,60,34,23,339,60,35,23,339,60,35,};
const int screenInfo[] =  {0,256,0,6,0,0,26,0,2,0,2,0,30,384,6,14,3,2,58,560,20,7,4,1,98,80,27,1,5,1,108,0,28,1,6,0,0,0,0,1,0,0,5,160,1,4,1,1,20,160,5,5,3,0,34,160,10,5,5,0,52,0,15,1,7,0,57,48,16,3,8,0,64,240,19,4,9,1,84,0,23,1,15,0,89,320,24,0,16,5,114,160,24,4,18,1,129,192,28,0,20,4,146,0,28,1,22,0,151,64,29,0,23,0,160,0,29,2,24,0,0,736,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
const unsigned char tpData[] = {1,5,0,3,4,0,2,1,2,7,1,8,8,4,10,6,5,6,6,6,6,12,1,9,3,8,3,5,11,10,13,3,0,0,0,};
const unsigned char tpArea[] = {13,255,255,255,255,255,255,255,8,255,4,255,4,255,255,255,1,4,7,14,16,255,255,12,255,8,255,9,255,255,255,255,255,255,255,};
const unsigned char tpCamX[] = {0,0,176,0,80,0,0,0,0,0,80,192,32,0,0,0,48,240,160,80,0,0,160,0,0,80,0,0,0,176,0,0,0,0,0,};
const unsigned char tpPosX[] = {36,20,190,36,90,0,20,7,18,32,120,193,35,0,0,0,95,240,208,97,48,0,160,48,16,97,16,0,32,193,20,16,0,0,0,};
const unsigned char tpPosY[] = {40,40,40,40,0,0,40,23,40,38,0,7,7,0,38,38,6,21,37,23,38,38,21,22,39,39,40,38,39,23,39,38,0,0,0,};
const unsigned char columnSheet[] = {0,0,0,1,0,0,1,1,2,0,0,1,0,1,1,1,0,0,0,0,0,0,3,1,0,0,5,4,0,0,6,1,7,7,7,1,8,8,8,1,0,9,1,1,12,0,0,1,12,13,13,1,10,0,0,1,11,0,0,1,14,14,14,1,15,15,15,1,7,7,1,7,8,8,1,8,0,0,16,0,7,7,7,7,8,8,8,8,7,1,1,7,0,16,16,0,0,6,16,0,0,16,0,0,17,17,17,1,17,17,18,1,0,0,16,1,0,16,0,1,17,0,0,1,17,19,17,1,0,9,0,0,0,16,16,1,0,3,0,0,18,16,17,17,17,16,17,17,0,0,8,1,0,3,6,16,0,0,8,0,0,3,6,1,0,0,21,1,0,22,16,0,2,0,17,1,0,23,13,1,0,23,13,13,13,13,13,1,0,16,6,1,0,0,0,16,6,16,0,0,1,1,0,1,1,6,0,1,24,17,25,24,24,17,25,26,2,0,0,0,0,27,27,1,28,29,30,1,28,29,29,1,0,28,29,1,0,0,0,32,0,2,0,32,0,0,31,1,0,33,33,1,0,33,34,1,};
const unsigned char metaTileSet[] = {0,0,0,0,1,1,1,1,2,3,130,131,0,1,0,1,4,4,4,4,5,4,5,4,7,6,0,0,1,1,0,0,0,0,1,1,8,0,0,0,0,9,9,0,137,0,0,137,0,9,0,137,10,10,138,138,10,10,0,0,0,0,138,138,1,0,1,0,11,11,11,11,7,6,11,11,11,11,0,0,12,12,12,12,0,14,0,0,1,15,1,12,1,10,1,138,11,1,11,1,1,11,1,11,11,1,19,1,1,12,1,12,0,22,0,150,23,23,151,151,23,1,151,1,0,12,0,12,0,152,0,24,27,27,27,27,7,6,27,27,1,1,1,1,};








const unsigned char screenStarAnim[] = {0,0,0,0,0};

#endif // GAMEDATA_H
