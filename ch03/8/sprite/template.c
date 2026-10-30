#include "msxgl.h"

// Fonts data
#include "font/font_mgl_sample6.h"

const u8 g_SpritePattern[] =
{
    0x18,
    0x3C,
    0x7E,
    0xFF,
    0xFF,
    0x7E,
    0x3C,
    0x18
};

// Program entry point
void main()
{
    VDP_SetMode(VDP_MODE_SCREEN5);
    VDP_SetColor(COLOR_BLACK);
    VDP_EnableVBlank(TRUE);
    VDP_ClearVRAM();
    VDP_EnableSprite(TRUE);
    VDP_SetSpriteFlag(VDP_SPRITE_SIZE_8 | VDP_SPRITE_SCALE_1);
    VDP_LoadSpritePattern(g_SpritePattern, 0, 1);
    VDP_SetSpriteExUniColor(0, 120, 98, 0, 15);
    VDP_DisableSpritesFrom(1);

    Print_SetBitmapFont(g_Font_MGL_Sample6);
    Print_SetColor(COLOR_WHITE, COLOR_BLACK);
    Print_SetPosition(0, 0);
    Print_DrawText("Sprite");

    while (!Keyboard_IsKeyPressed(KEY_ESC))
    {
        Halt();
    }

    BIOS_Exit(0);
}