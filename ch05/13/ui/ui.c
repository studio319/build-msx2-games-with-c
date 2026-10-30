#include "msxgl.h"
#include "print.h"
#include "ui.h"
#include "font/font_mgl_sample6.h"

#define HUD_PAGE_Y 256
#define HUD_TEXT_Y 12

void UI_Init()
{
    Print_SetBitmapFont(g_Font_MGL_Sample6);
    Print_SetColor(COLOR_WHITE, COLOR_BLACK);
}

void UI_ShowTitle()
{
    VDP_SetVerticalOffset(0);
    
    UI_ClearGamePage();

    Print_SetColor(COLOR_WHITE, COLOR_BLACK);

    Print_SetPosition(86, 70);
    Print_DrawText("STAR FIGHTER");

    Print_SetPosition(89, 120);
    Print_DrawText("PRESS ENTER");
}

void UI_ShowGameOver(const char* scoreText)
{
    VDP_SetVerticalOffset(0);
    
    UI_ClearGamePage();

    Print_SetColor(COLOR_WHITE, COLOR_BLACK);

    Print_SetPosition(98, 58);
    Print_DrawText("GAME OVER");

    Print_SetPosition(90, 95);
    Print_DrawText("FINAL SCORE");

    Print_SetPosition(110, 111);
    Print_DrawText(scoreText);

    Print_SetPosition(89, 155);
    Print_DrawText("PRESS ENTER");
}

void UI_PrepareHUD()
{
    Print_SetColor(COLOR_WHITE, COLOR_BLACK);

    Print_SetPosition(
        8, 
        HUD_PAGE_Y + HUD_TEXT_Y
    );
    Print_DrawText("SCORE");

    Print_SetPosition(
        196, 
        HUD_PAGE_Y + HUD_TEXT_Y
    );
    Print_DrawText("000000");
}

void UI_UpdateHUD(const char* scoreText)
{
    Print_SetColor(
        COLOR_LIGHT_YELLOW, 
        COLOR_BLACK
    );

    Print_SetPosition(
        196, 
        HUD_PAGE_Y + HUD_TEXT_Y
    );

    Print_DrawText(scoreText);
}

void UI_ClearGamePage()
{
    VDP_CommandWait();

    VDP_CommandLMMV(
        0, 0,
        256, 256,
        COLOR_BLACK,
        VDP_OP_IMP
    );

    VDP_CommandWait();
}

void UI_ClearHUD()
{
    VDP_CommandWait();

    VDP_CommandLMMV(
        0, 256,
        256, 32,
        COLOR_BLACK,
        VDP_OP_IMP
    );

    VDP_CommandWait();
}