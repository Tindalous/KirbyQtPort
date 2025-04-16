
/*
 * GLCD (Graphic Liquid Crystal Display)
 */

//#include <xc.h>
#include "GLCD.h"
#include "ascii.h"

// D'us intern
void GLCDBusyWait(byte CS);
byte readByteReal(byte, byte, byte);

int glcdCursorPos = 0;

byte glcdScreenBuffer[1024];


void spWB(byte data)
{
    glcdScreenBuffer[glcdCursorPos] = data;
    glcdCursorPos++;
}


// Send command  to GLCD
//
void sendGLCDCommand(byte val, byte CS)
{

}

// Selecciona linea de inici (z= 0 a 63)
//
void setStartLine(byte z)
{
}

// Set Page Address  X -row- (x= 0 a 7)
//
void setXAddress(byte page)
{
}

// Set Y address Y -column- (y= 0 a 127)
//
void setYAddress(byte y)
{
    if (y < 64) // Part esquerra
    {
    } else { // Part dreta
    }
}

//Posiciona el cursor
// x [0:7] y [0:127]
void setAddress(byte page, byte y)
{
}

// Init GLCD
//
void GLCDinit()
{
    for (int i = 0; i < sizeof(glcdScreenBuffer); i++) {
        glcdScreenBuffer[i] = 0;
    }
}

// Write data on GLCD at position (p,y)(Page p= 0 a 7) (y= 0 a 127)
//
void writeByte(byte p, byte y, byte data)
{
    glcdScreenBuffer[p*128 + y] = data;
    glcdCursorPos = p*128 + y + 1;
}



byte readByteReal(byte p, byte y, byte first)
{
    return glcdScreenBuffer[p*128 + y];
}

// Read the GLCD RAM at position (x,y) (Page p= 0 a 7) (y= 0 a 127)
//
// Two acces are required to read data
// 1st is a dummy access. 2nd is RAM value
byte readByte(byte p, byte y)
{
    byte aux;
    readByteReal(p, y, 1);
    aux=readByteReal(p, y, 1);
    return(aux);
}

//  Clear all pixels in ri to re pages and ci to ce columns
// ri,re [0:7] ci,ce [0:127]
void clearGLCD(byte ri, byte re, byte ci, byte ce)
{
    GLCDinit();
}

// Encen el pixel a la posicio (x,y), (x [0:63]) (y [0:127])
void SetDot(byte x, byte y)
{

}
// Apaga el pixel a la posicio (x,y), (x [0:63]) (y [0:127])
void ClearDot(byte x, byte y)
{

}

// Escriu el caracter c en la posicio (p,y) (pagina p= 0 a 7) (character column y= 0 a 24)
// Els caracters estan definits en la taula font5x7[], al fitxer ascii.h
void putchGLCD(byte p, byte y, char c)
{
    int fontPos = (c-' ')*5;
    int i;
    y = y*5;
    int aux;
    for (i = 0; i < 5; ++i)
    {
        aux = font5x7[fontPos];
        writeByte (p, y, aux);
        ++y;
        ++fontPos;
    }
}

// Escriu el nombre enter i en la posicio (p,y) (page p= 0 a 7) (character column y= 0 a 24)
// Cal fer la conversió de INT to ASCII
// Els caracters estan definits en la taula font5x7[], al fitxer ascii.h
void writeNum (byte p, byte y, int i) {
    //int page = 0;
    //int y = 0;
    int aux;
    char arr[32];
    if (i <0)
    {
        putchGLCD (p, y, '-');
        ++y;
        i*= -1;
    }
    int j = 0;
    if (i == 0) {arr[0] = '0';++j;}
    while (i > 0)
    {
        arr[j] = i%10+'0';
        ++j;
        i/=10;
    }
    while (j > 0)
    {
        j--;
        i = arr[j];
        putchGLCD (p, y, i);
        ++y;
        if (y > 127) ++p, y = 0;
    }
}
