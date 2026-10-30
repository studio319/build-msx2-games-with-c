#include "msxgl.h"
#include "explosion.h"
#include "sprite_scroll.h"

#define EXPLOSION_FIRST_SPRITE 17
#define EXPLOSION_FRAME_COUNT 4
#define EXPLOSION_FRAME_DELAY 6
#define EXPLOSION_SPRITE_HEIGHT 16

#define EXPLOSION_COUNT 4

#define SCREEN_HEIGHT 212

static const u8 g_ExplosionPatterns[4][32] =
{
    // Frame 0
    {
        0x00, 0x00, 0x00, 0x00,
        0x01, 0x03, 0x07, 0x0F,
        0x0F, 0x07, 0x03, 0x01,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x80, 0xC0, 0xE0, 0xF0,
        0xF0, 0xE0, 0xC0, 0x80,
        0x00, 0x00, 0x00, 0x00
    },
    // Frame 1
    {
        0x00, 0x01, 0x01, 0x19,
        0x0F, 0x07, 0x3F, 0x7F,
        0x7F, 0x3F, 0x07, 0x0F,
        0x19, 0x01, 0x01, 0x00,
        0x00, 0x80, 0x80, 0x98,
        0xF0, 0xE0, 0xFC, 0xFE,
        0xFE, 0xFC, 0xE0, 0xF0,
        0x98, 0x80, 0x80, 0x00
    },
    // Frame 2
    {
        0x0C, 0x04, 0x23, 0x1C,
        0x10, 0x60, 0x80, 0x80,
        0x80, 0x60, 0x10, 0x1C,
        0x23, 0x04, 0x0C, 0x00,
        0x30, 0x20, 0xC4, 0x38,
        0x08, 0x06, 0x01, 0x01,
        0x01, 0x06, 0x08, 0x38,
        0xC4, 0x20, 0x30, 0x00
    },
    // Frame 3
    {
        0x00, 0x20, 0x00, 0x06,
        0x00, 0x40, 0x02, 0x10,
        0x10, 0x02, 0x40, 0x00,
        0x06, 0x00, 0x20, 0x00,
        0x00, 0x08, 0x00, 0x60,
        0x00, 0x02, 0x40, 0x08,
        0x08, 0x40, 0x02, 0x00,
        0x60, 0x00, 0x08, 0x00
    }
};

static const u8 
    g_ExplosionNormalPattern[EXPLOSION_FRAME_COUNT] =
{
    48, 52, 56, 60
};

static const u8 
    g_ExplosionShiftedPattern[EXPLOSION_FRAME_COUNT] =
{
    64, 68, 72, 76
};

static const u8 
    g_ExplosionColor[EXPLOSION_FRAME_COUNT] =
{
    15, 11, 9, 6
};

typedef struct
{
    u8 x;
    u8 y;
    u8 frame;
    u8 timer;
    u8 active;
} Explosion;

static Explosion g_Explosions[EXPLOSION_COUNT];

void Explosion_Init()
{
    u8 i;
    for(i = 0; i < EXPLOSION_FRAME_COUNT; i++)
    {
        VDP_LoadSpritePattern(
            g_ExplosionPatterns[i],
            g_ExplosionNormalPattern[i],
            4
        );

        SpriteScroll_LoadShiftedPattern(
            g_ExplosionPatterns[i],
            g_ExplosionShiftedPattern[i]
        );
    }

    Explosion_Reset();
}

void Explosion_Reset()
{
    u8 i;
    for(i = 0; i < EXPLOSION_COUNT; i++)
    {
        g_Explosions[i].x = 0;
        g_Explosions[i].y = 0;
        g_Explosions[i].frame = 0;
        g_Explosions[i].timer = 0;
        g_Explosions[i].active = FALSE;

        VDP_SetSpriteExUniColor(
            EXPLOSION_FIRST_SPRITE + i,
            0,
            0,
            g_ExplosionNormalPattern[0],
            0
        );
    }
}

void Explosion_Spawn(u8 x, u8 y)
{
    if(y > SCREEN_HEIGHT - EXPLOSION_SPRITE_HEIGHT)
    {
        y = SCREEN_HEIGHT - EXPLOSION_SPRITE_HEIGHT;
    }

    u8 i;
    for(i = 0; i < EXPLOSION_COUNT; i++)
    {
        if(!g_Explosions[i].active)
        {
            g_Explosions[i].x = x;
            g_Explosions[i].y = y;
            g_Explosions[i].frame = 0;
            g_Explosions[i].timer 
                = EXPLOSION_FRAME_DELAY;
            g_Explosions[i].active = TRUE;

            SpriteScroll_SetPosition(
                EXPLOSION_FIRST_SPRITE + i,
                g_Explosions[i].x,
                g_Explosions[i].y,
                g_ExplosionNormalPattern[0],
                g_ExplosionShiftedPattern[0]
            );

            VDP_SetSpriteUniColor(
                EXPLOSION_FIRST_SPRITE + i,
                g_ExplosionColor[0]
            );

            return;
        }
    }
}

static void Explosion_Deactivate(u8 index)
{
    g_Explosions[index].active = FALSE;

    VDP_SetSpriteUniColor(
        EXPLOSION_FIRST_SPRITE + index, 
        0
    );
}

void Explosion_Update()
{
    u8 i;
    for(i = 0; i < EXPLOSION_COUNT; i++)
    {
        if(g_Explosions[i].active)
        {
            u8 frame;

            if(g_Explosions[i].timer > 0)
            {
                g_Explosions[i].timer--;
            }

            if(g_Explosions[i].timer == 0)
            {
                g_Explosions[i].frame++;
                
                if(g_Explosions[i].frame 
                    >= EXPLOSION_FRAME_COUNT)
                {
                    Explosion_Deactivate(i);
                    continue;
                }

                g_Explosions[i].timer 
                    = EXPLOSION_FRAME_DELAY;

                frame = g_Explosions[i].frame;    
                VDP_SetSpriteUniColor(
                    EXPLOSION_FIRST_SPRITE + i,
                    g_ExplosionColor[frame]
                );
            }

            frame = g_Explosions[i].frame;
            SpriteScroll_SetPosition(
                EXPLOSION_FIRST_SPRITE + i,
                g_Explosions[i].x,
                g_Explosions[i].y,
                g_ExplosionNormalPattern[frame],
                g_ExplosionShiftedPattern[frame]
            );
        }
    }
}