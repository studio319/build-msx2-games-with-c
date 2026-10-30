#include "msxgl.h"
#include "player.h"
#include "bullet.h"
#include "background.h"
#include "sprite_scroll.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 212

#define PLAYER_SIZE 16
#define PLAYER_SPRITE 0
#define PLAYER_PATTERN 0
#define PLAYER_PATTERN_SHIFTED 12

#define PLAYER_START_X 120
#define PLAYER_START_Y 180

static const u8 g_PlayerPattern[] =
{
    0x01, 0x03, 0x03, 0x07,
    0x07, 0x0F, 0x1F, 0x3F,

    0x7F, 0x1F, 0x1B, 0x19,
    0x19, 0x10, 0x10, 0x00,

    0x80, 0xC0, 0xC0, 0xE0,
    0xE0, 0xF0, 0xF8, 0xFC,

    0xFE, 0xF8, 0xD8, 0x98,
    0x98, 0x08, 0x08, 0x00
};

static u8 g_PlayerX;
static u8 g_PlayerY;

void Player_Init()
{
    g_PlayerX = PLAYER_START_X;
    g_PlayerY = PLAYER_START_Y;

    VDP_LoadSpritePattern(
        g_PlayerPattern, 
        PLAYER_PATTERN, 
        4
    );
    SpriteScroll_LoadShiftedPattern(
        g_PlayerPattern, 
        PLAYER_PATTERN_SHIFTED
    );

    VDP_SetSpriteExUniColor(
        PLAYER_SPRITE, 
        g_PlayerX, 
        g_PlayerY, 
        PLAYER_PATTERN, 
        COLOR_WHITE
    );

    SpriteScroll_SetPosition(
        PLAYER_SPRITE,
        g_PlayerX,
        g_PlayerY,
        PLAYER_PATTERN,
        PLAYER_PATTERN_SHIFTED
    );
}

void Player_Update()
{
    static u8 prevRow8 = 0xFF;
    u8 row8 = Keyboard_Read(8);

    if (IS_KEY_PRESSED(row8, KEY_LEFT))
    {
        if (g_PlayerX > 0)
        {
            g_PlayerX--;
        }
    }

    if (IS_KEY_PRESSED(row8, KEY_RIGHT))
    {
        if (g_PlayerX < SCREEN_WIDTH - PLAYER_SIZE)
        {
            g_PlayerX++;
        }
    }

    if (IS_KEY_PRESSED(row8, KEY_UP))
    {
        if (g_PlayerY > 0)
        {
            g_PlayerY--;
        }
    }

    if (IS_KEY_PRESSED(row8, KEY_DOWN))
    {
        if (g_PlayerY < SCREEN_HEIGHT - PLAYER_SIZE)
        {
            g_PlayerY++;
        }
    }

    if (IS_KEY_PRESSED(row8, KEY_SPACE) 
        && !IS_KEY_PRESSED(prevRow8, KEY_SPACE))
    {
        Bullet_Fire(g_PlayerX, g_PlayerY);
    }

    SpriteScroll_SetPosition(
        PLAYER_SPRITE,
        g_PlayerX,
        g_PlayerY,
        PLAYER_PATTERN,
        PLAYER_PATTERN_SHIFTED
    );

    prevRow8 = row8;
}

u8 Player_GetX()
{
    return g_PlayerX;
}

u8 Player_GetY()
{
    return g_PlayerY;
}

void Player_Hide()
{
    VDP_SetSpriteUniColor(PLAYER_SPRITE, 0);
}