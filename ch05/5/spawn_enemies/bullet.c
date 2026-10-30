#include "msxgl.h"
#include "bullet.h"

#define BULLET_FIRST_SPRITE 1
#define BULLET_PATTERN 4

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

typedef struct
{
    u8 x;
    u8 y;
    u8 active;
} Bullet;

static Bullet g_Bullets[BULLET_COUNT];

void Bullet_Init()
{
    VDP_LoadSpritePattern(
        g_BulletPattern, 
        BULLET_PATTERN, 
        4
    );

    u8 i;
    for (i = 0; i < BULLET_COUNT; i++)
    {
        g_Bullets[i].active = FALSE;

        VDP_SetSpriteExUniColor(
            BULLET_FIRST_SPRITE + i, 
            0, 
            0, 
            BULLET_PATTERN, COLOR_WHITE
        );

        VDP_HideSprite(BULLET_FIRST_SPRITE + i);
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
            
            VDP_SetSpritePosition(
                BULLET_FIRST_SPRITE + i, 
                g_Bullets[i].x, 
                g_Bullets[i].y
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
                VDP_SetSpritePosition(
                    BULLET_FIRST_SPRITE + i, 
                    g_Bullets[i].x, 
                    g_Bullets[i].y
                );
            }
            else
            {
                g_Bullets[i].active = FALSE;

                VDP_HideSprite(
                    BULLET_FIRST_SPRITE + i
                );
            }
        }
    }
}