#include "msxgl.h"
#include "draw.h"

// Fonts data
#include "font/font_mgl_sample6.h"

// Animation characters
const u8 g_ChrAnim[] = { '-', '/', '|', '\\' };

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
    
	Print_DrawText("Draw_Line()");	

	// 선
	Draw_Line(20, 30, 200, 30, 15, VDP_OP_IMP);

    u8 count = 0;
    while (!Keyboard_IsKeyPressed(KEY_ESC))
    {
        Halt();
        Print_SetPosition(255-8, 0);
        Print_DrawChar(g_ChrAnim[count++ % 4]);
    }

    BIOS_Exit(0);
}