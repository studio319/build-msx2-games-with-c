#include "msxgl.h"
#include "math.h"
#include "draw.h"
#include "background.h"

#define STAR_COUNT 32

static u8 g_ScrollOffset;

void Background_Init()
{
    g_ScrollOffset = 0;

    VDP_SetVerticalOffset(g_ScrollOffset);
    Math_SetRandomSeed16(0xACE1);

    u8 i;
    for(i = 0; i < STAR_COUNT; i++)
    {
        u16 value = Math_GetRandom16();

        u8 x = (u8)value;
        u8 y = (u8)(value >> 8);

        Draw_Point(
            x,
            y,
            COLOR_WHITE,
            VDP_OP_IMP
            );
    }
}

void Background_Update()
{
    g_ScrollOffset--;

    VDP_SetVerticalOffset(g_ScrollOffset);
}

u8 Background_GetSpriteY(u8 y)
{
    return (u8)(y + g_ScrollOffset);
}