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
    
	Print_DrawText("Draw Example");

	// 별
    Draw_Point(30, 25, 15, VDP_OP_IMP);
    Draw_Point(70, 40, 15, VDP_OP_IMP);
    Draw_Point(215, 30, 15, VDP_OP_IMP);

    // 달
    Draw_Circle(205, 45, 15, 15, VDP_OP_IMP);

    // 집 몸체
    Draw_FillBox(80, 105, 175, 180, 8, VDP_OP_IMP);

    // 지붕
    Draw_Line(65, 105, 127, 65, 15, VDP_OP_IMP);
    Draw_Line(127, 65, 190, 105, 15, VDP_OP_IMP);
    Draw_Line(65, 105, 190, 105, 15, VDP_OP_IMP);

    // 창문
    Draw_Box(95, 120, 115, 140, 15, VDP_OP_IMP);
    Draw_Box(142, 120, 162, 140, 15, VDP_OP_IMP);

    // 문
    Draw_FillBox(118, 145, 138, 180, 4, VDP_OP_IMP);

    // 땅
    Draw_Line(20, 181, 235, 181, 15, VDP_OP_IMP);

    u8 count = 0;
    while (!Keyboard_IsKeyPressed(KEY_ESC))
    {
        Halt();
        Print_SetPosition(255-8, 0);
        Print_DrawChar(g_ChrAnim[count++ % 4]);
    }

    BIOS_Exit(0);
}