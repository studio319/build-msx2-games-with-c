#include "msxgl.h"
#include "background.h"
#include "sprite_scroll.h"

#define SPRITE_COUNT 32

static u8 g_CurrentPattern[SPRITE_COUNT];

void SpriteScroll_Init()
{
    u8 i;
    for(i = 0; i < SPRITE_COUNT; i++)
    {
        g_CurrentPattern[i] = 0xFF;
    }
}

void SpriteScroll_LoadShiftedPattern(
    const u8* pattern,
    u8 shiftedPattern)
{    
    u8 shiftedData[32];
    shiftedData[0] = 0;
    shiftedData[16] = 0;

    u8 i;
    for(i = 1; i < 16; i++)
    {
        shiftedData[i] = pattern[i - 1];
        shiftedData[i + 16] = pattern[i + 15];
    }

    VDP_LoadSpritePattern(shiftedData,
        shiftedPattern,
        4);
}

void SpriteScroll_SetPosition(
    u8 index,
    u8 x,
    u8 y,
    u8 normalPattern,
    u8 shiftedPattern)
{
    u8 pattern = normalPattern;

    u8 spriteY = Background_GetSpriteY(y);

    if(spriteY == VDP_SPRITE_DISABLE_SM2)
    {
        spriteY = 215;
        pattern = shiftedPattern;
    }

    if(g_CurrentPattern[index] != pattern)
    {
        VDP_SetSpritePattern(index, pattern);
        g_CurrentPattern[index] = pattern;
    }
    
    VDP_SetSpritePosition(index, x, spriteY);
}