#include "sprite.h"
#include <string.h>

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef uint32 tile[16];
typedef tile tileBlock[256];

typedef struct objectAttributes
{
    uint16 attr0;
    uint16 attr1;
    uint16 attr2;
    uint16 pad;
} __attribute__((packed, aligned(4))) objectAttributes;

#define REG_DISPLAYCONTROL *((volatile uint16*)(0x04000000))

#define VIDEOMODE_0 0x0000
#define ENABLE_OBJECTS 0x1000
#define MAPPINGMODE_1D 0x0040

#define MEM_PALETTE ((uint16*) (0x05000200))
#define MEM_VRAM ((volatile uint16*) 0x6000000)
#define MEM_TILE ((tileBlock*) 0x6000000)

#define MEM_OAM ((volatile objectAttributes* ) 0x07000000)

#define REG_VCOUNT (*(volatile uint16*) 0x04000006)

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

void uploadPaletteMem(void)
{
    memcpy(MEM_PALETTE, spritePal, spritePalLen);
}

void uploadTileMem(void)
{
    memcpy(&MEM_TILE[4][1], spriteTiles, spriteTilesLen);
}

inline void vsync(void)
{
    while (REG_VCOUNT >= 160);
    while (REG_VCOUNT < 160);
}

int main(void)
{
    uploadPaletteMem();
    uploadTileMem();

    volatile objectAttributes *spriteAttribs = &MEM_OAM[0];
    spriteAttribs->attr0 = 0x2032;
    spriteAttribs->attr1 = 0x4064;
    spriteAttribs->attr2 = 2;

    REG_DISPLAYCONTROL = VIDEOMODE_0 | ENABLE_OBJECTS | MAPPINGMODE_1D;

    int x = 0;

    while(1)
    {
        vsync();
        x = (x + 1) % (SCREEN_WIDTH);
        spriteAttribs->attr1 = 0x4000 | (0x1FF & x);
    }
    return 0;
}