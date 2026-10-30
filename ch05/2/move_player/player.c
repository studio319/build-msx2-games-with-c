#include "msxgl.h"
#include "player.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 212

#define PLAYER_SIZE 16
#define PLAYER_SPRITE 0
#define PLAYER_PATTERN 0

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

    VDP_SetSpriteExUniColor(
        PLAYER_SPRITE, 
        g_PlayerX, 
        g_PlayerY, 
        PLAYER_PATTERN, 
        COLOR_WHITE
    );
}

void Player_Update()
{
    u8 row8 = Keyboard_Read(8);

    if (IS_KEY_PRESSED(row8, KEY_LEFT))
    {
        g_PlayerX--;
    }

    if (IS_KEY_PRESSED(row8, KEY_RIGHT))
    {
        g_PlayerX++;
    }

    if (IS_KEY_PRESSED(row8, KEY_UP))
    {
        g_PlayerY--;
    }

    if (IS_KEY_PRESSED(row8, KEY_DOWN))
    {
        g_PlayerY++;
    }

    VDP_SetSpritePosition(
        PLAYER_SPRITE, 
        g_PlayerX, 
        g_PlayerY
    );
}