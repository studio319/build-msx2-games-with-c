#include "msxgl.h"
#include "bullet.h"

#define BULLET_SPRITE 1
#define BULLET_PATTERN 4

#define BULLET_SPEED 2
#define BULLET_START_OFFSET 8

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

static u8 g_BulletX;
static u8 g_BulletY;

static u8 g_BulletActive;

void Bullet_Init()
{
    g_BulletActive = FALSE;

    VDP_LoadSpritePattern(
        g_BulletPattern, 
        BULLET_PATTERN, 
        4
    );

    VDP_SetSpriteExUniColor(
        BULLET_SPRITE, 
        0, 
        0, 
        BULLET_PATTERN, COLOR_WHITE
    );

    VDP_HideSprite(BULLET_SPRITE);
}

void Bullet_Fire(u8 x, u8 y)
{
    if (g_BulletActive)
        return;

    g_BulletX = x;

    if (y >= BULLET_START_OFFSET)
    {
        g_BulletY = y - BULLET_START_OFFSET;
    }
    else
    {
        g_BulletY = 0;
    }

    g_BulletActive = TRUE;

    VDP_SetSpritePosition(
        BULLET_SPRITE, 
        g_BulletX, 
        g_BulletY
    );
}

void Bullet_Update()
{
    if (!g_BulletActive)
        return;

    if (g_BulletY >= BULLET_SPEED)
    {
        g_BulletY -= BULLET_SPEED;
        VDP_SetSpritePosition(
            BULLET_SPRITE, 
            g_BulletX, 
            g_BulletY
        );
    }
    else
    {
        g_BulletActive = FALSE;
        VDP_HideSprite(BULLET_SPRITE);
    }
}