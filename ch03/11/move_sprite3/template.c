#include "msxgl.h"
#include "input.h"

// Fonts data
#include "font/font_mgl_sample6.h"

#define PLAYER_COLOR 15

typedef struct
{
    i16 x;
    i16 y;
    u8 speed;
    u8 spriteNo;
} Player;

const u8 g_SpritePattern[8] =
{
    0x18,
    0x3C,
    0x7E,
    0xDB,
    0xFF,
    0x24,
    0x24,
    0x66
};

// Program entry point
void main()
{
    Player player =
    {
        120,
        96,
        1,
        0
    };

    VDP_SetMode(VDP_MODE_SCREEN5);
    VDP_SetColor(COLOR_BLACK);
    VDP_EnableVBlank(TRUE);
    VDP_ClearVRAM();
    VDP_EnableSprite(TRUE);
    VDP_SetSpriteFlag(VDP_SPRITE_SIZE_8 | VDP_SPRITE_SCALE_1);
    VDP_LoadSpritePattern(g_SpritePattern, 0, 1);
    VDP_SetSpriteExUniColor(
            player.spriteNo,
            player.x,
            player.y,
            0,
            PLAYER_COLOR
        );
    VDP_DisableSpritesFrom(1);

    Print_SetBitmapFont(g_Font_MGL_Sample6);
    Print_SetColor(COLOR_WHITE, COLOR_BLACK);
    Print_SetPosition(0, 0);
    Print_DrawText("Move Sprite 3");

    while (!Keyboard_IsKeyPressed(KEY_ESC))
    {
        u8 row8 = Keyboard_Read(8);

        if(IS_KEY_PRESSED(row8, KEY_LEFT))
        {
            if(player.x > 0)
            {
                player.x -= player.speed;
            }
        }

        if(IS_KEY_PRESSED(row8, KEY_RIGHT))
        {
            if(player.x < 248)
            {
                player.x += player.speed;
            }
        }

        if(IS_KEY_PRESSED(row8, KEY_UP))
        {
            if(player.y > 0)
            {
                player.y -= player.speed;
            }
        }

        if(IS_KEY_PRESSED(row8, KEY_DOWN))
        {
            if(player.y < 204)
            {
                player.y += player.speed;
            }
        }

        VDP_SetSpritePosition(
                player.spriteNo,
                player.x,
                player.y
            );

        Halt();
    }

    BIOS_Exit(0);
}