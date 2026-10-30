#include "msxgl.h"
#include "draw.h"
#include "input.h"

// Fonts data
#include "font/font_mgl_sample6.h"

// Program entry point
void main()
{
    VDP_SetMode(VDP_MODE_SCREEN5);
    VDP_SetColor(COLOR_BLACK);
    VDP_EnableVBlank(TRUE);
    VDP_ClearVRAM();

    Print_SetBitmapFont(g_Font_MGL_Sample6);
    Print_SetColor(COLOR_WHITE, COLOR_BLACK);
    Print_SetPosition(0, 0);
    Print_DrawText("Move Box");

    u8 x = 120;
    u8 y = 98;

    while (!Keyboard_IsKeyPressed(KEY_ESC))
    {
        u8 row8 = Keyboard_Read(8);

        if(IS_KEY_PRESSED(row8, KEY_LEFT))
        {
            x--;
        }

        if(IS_KEY_PRESSED(row8, KEY_RIGHT))
        {
            x++;
        }

        if(IS_KEY_PRESSED(row8, KEY_UP))
        {
            y--;
        }

        if(IS_KEY_PRESSED(row8, KEY_DOWN))
        {
            y++;
        }

        Draw_FillBox(x, y, x + 15, y + 15, 15, VDP_OP_IMP);

        Halt();
    }

    BIOS_Exit(0);
}