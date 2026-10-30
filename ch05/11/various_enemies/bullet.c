#include "msxgl.h"
#include "bullet.h"
#include "background.h"
#include "sprite_scroll.h"

#define BULLET_FIRST_SPRITE 1
#define BULLET_PATTERN 4
#define BULLET_PATTERN_SHIFTED 16

#define BULLET_SPEED 2
#define BULLET_START_OFFSET 8

#define BULLET_COUNT 8

static const u8 g_BulletPattern[] =
{
    /* 왼쪽 위 8×8 */
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x01, 0x01,

    /* 왼쪽 아래 8×8 */
    0x01, 0x01, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00,

    /* 오른쪽 위 8×8 */
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x80, 0x80,

    /* 오른쪽 아래 8×8 */
    0x80, 0x80, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00
};

static Bullet g_Bullets[BULLET_COUNT];

void Bullet_Init()
{
    VDP_LoadSpritePattern(
        g_BulletPattern, 
        BULLET_PATTERN, 
        4
    );
    SpriteScroll_LoadShiftedPattern(
        g_BulletPattern,
        BULLET_PATTERN_SHIFTED
    );

    u8 i;
    for (i = 0; i < BULLET_COUNT; i++)
    {
        g_Bullets[i].active = FALSE;

        VDP_SetSpriteExUniColor(
            BULLET_FIRST_SPRITE + i,
            0,
            0,
            BULLET_PATTERN,
            0
        );
    }
}

void Bullet_Fire(u8 x, u8 y)
{
    u8 i;
    for (i = 0; i < BULLET_COUNT; i++)
    {
        if (!g_Bullets[i].active)
        {
            g_Bullets[i].x = x;

            if (y >= BULLET_START_OFFSET)
            {
                g_Bullets[i].y 
                    = y - BULLET_START_OFFSET;
            }
            else
            {
                g_Bullets[i].y = 0;
            }

            g_Bullets[i].active = TRUE;

            VDP_SetSpriteUniColor(
                BULLET_FIRST_SPRITE + i,
                COLOR_WHITE
            );
            
            SpriteScroll_SetPosition(
                BULLET_FIRST_SPRITE + i,
                g_Bullets[i].x,
                g_Bullets[i].y,
                BULLET_PATTERN,
                BULLET_PATTERN_SHIFTED
            );

            return;
        }
    }
}

void Bullet_Update()
{
    u8 i;
    for (i = 0; i < BULLET_COUNT; i++)
    {
        if (g_Bullets[i].active)
        {
            if (g_Bullets[i].y >= BULLET_SPEED)
            {
                g_Bullets[i].y -= BULLET_SPEED;
                
                SpriteScroll_SetPosition(
                    BULLET_FIRST_SPRITE + i,
                    g_Bullets[i].x,
                    g_Bullets[i].y,
                    BULLET_PATTERN,
                    BULLET_PATTERN_SHIFTED
                );
            }
            else
            {
                Bullet_Deactivate(i);
            }
        }
    }
}

const Bullet* Bullet_GetBullets()
{
    return g_Bullets;
}

u8 Bullet_GetCount()
{
    return BULLET_COUNT;
}

void Bullet_Deactivate(u8 index)
{
    g_Bullets[index].active = FALSE;

    VDP_SetSpriteUniColor(
        BULLET_FIRST_SPRITE + index, 
        0
    );
}