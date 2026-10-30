#include "msxgl.h"
#include "math.h"
#include "print.h"
#include "font/font_mgl_sample6.h"
#include "block_data.h"
#include "board.h"
#include "sound.h"

#define START_FALL_INTERVAL 30

#define LINES_PER_LEVEL 5

#define FALL_INTERVAL_STEP 3
#define MIN_FALL_INTERVAL 6

#define SCORE_PER_LINE 100

#define UI_X 184
#define UI_SCORE_Y 32
#define UI_LEVEL_Y 48
#define UI_LINES_Y 64

typedef struct
{
    i8 blockX;
    i8 blockY;
    u8 currentBlockType;
    u8 currentRotation;

    u8 prevRow5;
    u8 fallCounter;
    u8 fallInterval;

    u16 score;
    u16 totalLines;
    u16 level;

    u8 gameOver;
} GameState;

GameState g_Game;

u8 GetFallInterval(u16 level)
{
    u16 decrease = (level - 1) * FALL_INTERVAL_STEP;

    if (decrease >= START_FALL_INTERVAL - MIN_FALL_INTERVAL)
    {
        return MIN_FALL_INTERVAL;
    }

    return START_FALL_INTERVAL - decrease;
}

void DrawUI(u16 score, u16 level, u16 totalLines)
{
    Print_SetPosition(UI_X, UI_SCORE_Y);
    Print_DrawFormat("SCORE %u", score);

    Print_SetPosition(UI_X, UI_LEVEL_Y);
    Print_DrawFormat("LEVEL %u", level);

    Print_SetPosition(UI_X, UI_LINES_Y);
    Print_DrawFormat("LINES %u", totalLines);
}

void ShowTitleScreen()
{
    VDP_ClearVRAM();

    Print_SetPosition(86, 80);
    Print_DrawText("FALLING BLOCKS");

    Print_SetPosition(68, 112);
    Print_DrawText("PRESS SPACE TO START");
}

void WaitForSpacePress()
{
    u8 row8;

    do
    {
        row8 = Keyboard_Read(8);

        Halt();
    }
    while (!IS_KEY_PRESSED(row8, KEY_SPACE));
}

void StartNewGame()
{
    g_Game.blockX = BLOCK_START_X;
    g_Game.blockY = BLOCK_START_Y;

    g_Game.currentBlockType = BLOCK_T;
    g_Game.currentRotation = 0;

    g_Game.fallCounter = 0;
    g_Game.fallInterval = START_FALL_INTERVAL;

    g_Game.score = 0;
    g_Game.totalLines = 0;
    g_Game.level = 1;
    g_Game.gameOver = FALSE;
    g_Game.prevRow5 = 0xFF;

    VDP_ClearVRAM();

    ClearBoard();
    DrawBoard();
    DrawUI(g_Game.score, g_Game.level, g_Game.totalLines);
    DrawBlockShape(
        g_Game.blockX, 
        g_Game.blockY, 
        g_Game.currentBlockType, 
        g_Game.currentRotation, BLOCK_COLOR
    );
}

void ShowGameOver()
{
    Print_SetPosition(101, 96);
    Print_DrawText("GAME OVER");

    Print_SetPosition(62, 112);
    Print_DrawText("PRESS SPACE TO RESTART");
}

void main()
{
    VDP_SetMode(VDP_MODE_SCREEN5);
    VDP_SetColor(COLOR_BLACK);
    VDP_EnableVBlank(TRUE);
    VDP_ClearVRAM();
    
    Print_SetBitmapFont(g_Font_MGL_Sample6);
    Print_SetColor(COLOR_WHITE, COLOR_BLACK);

    Sound_Init();

    ShowTitleScreen();
    WaitForSpacePress();
       
    while (1)
    {
        StartNewGame();

        while(!g_Game.gameOver)
        {
            u8 row8 = Keyboard_Read(8);
            u8 row5 = Keyboard_Read(5);

            if(IS_KEY_PRESSED(row8, KEY_LEFT))
            {
                if(CanMoveBlock(
                    g_Game.blockX - 1, 
                    g_Game.blockY, 
                    g_Game.currentBlockType, 
                    g_Game.currentRotation
                ))
                {
                    DrawBlockShape(
                        g_Game.blockX, 
                        g_Game.blockY, 
                        g_Game.currentBlockType, 
                        g_Game.currentRotation, 
                        EMPTY_COLOR
                    );

                    g_Game.blockX--;

                    DrawBlockShape(
                        g_Game.blockX, 
                        g_Game.blockY, 
                        g_Game.currentBlockType, 
                        g_Game.currentRotation, 
                        BLOCK_COLOR
                    );
                }
            }

            if(IS_KEY_PRESSED(row8, KEY_RIGHT))
            {
                if(CanMoveBlock(
                    g_Game.blockX + 1, 
                    g_Game.blockY, 
                    g_Game.currentBlockType, 
                    g_Game.currentRotation
                ))
                {
                    DrawBlockShape(
                        g_Game.blockX, 
                        g_Game.blockY, 
                        g_Game.currentBlockType, 
                        g_Game.currentRotation, 
                        EMPTY_COLOR
                    );

                    g_Game.blockX++;

                    DrawBlockShape(
                        g_Game.blockX, 
                        g_Game.blockY, 
                        g_Game.currentBlockType, 
                        g_Game.currentRotation, 
                        BLOCK_COLOR
                    );
                }
            }

            if(IS_KEY_PRESSED(row8, KEY_DOWN))
            {
                if(CanMoveBlock(
                    g_Game.blockX, 
                    g_Game.blockY + 1, 
                    g_Game.currentBlockType, 
                    g_Game.currentRotation
                ))
                {
                    DrawBlockShape(
                        g_Game.blockX, 
                        g_Game.blockY, 
                        g_Game.currentBlockType, 
                        g_Game.currentRotation, 
                        EMPTY_COLOR);

                    g_Game.blockY++;

                    DrawBlockShape(
                        g_Game.blockX, 
                        g_Game.blockY, 
                        g_Game.currentBlockType, 
                        g_Game.currentRotation, 
                        BLOCK_COLOR
                    );

                    g_Game.fallCounter = 0;
                }
            }

            if(IS_KEY_PRESSED(row5, KEY_X) &&
                !IS_KEY_PRESSED(g_Game.prevRow5, KEY_X))
            {
                u8 nextRotation = g_Game.currentRotation + 1;
                if(nextRotation >= BLOCK_ROTATION_COUNT)
                {
                    nextRotation = 0;
                }

                if(CanMoveBlock(
                    g_Game.blockX,
                    g_Game.blockY,
                    g_Game.currentBlockType,
                    nextRotation
                ))
                {
                    DrawBlockShape(
                        g_Game.blockX,
                        g_Game.blockY,
                        g_Game.currentBlockType,
                        g_Game.currentRotation,
                        EMPTY_COLOR
                    );

                    g_Game.currentRotation = nextRotation;

                    DrawBlockShape(
                        g_Game.blockX,
                        g_Game.blockY,
                        g_Game.currentBlockType,
                        g_Game.currentRotation,
                        BLOCK_COLOR
                    );
                }
            }
            else if(IS_KEY_PRESSED(row5, KEY_Z) &&
                !IS_KEY_PRESSED(g_Game.prevRow5, KEY_Z))
            {
                u8 nextRotation;
                if(g_Game.currentRotation == 0)
                {
                    nextRotation =
                        BLOCK_ROTATION_COUNT - 1;
                }
                else
                {
                    nextRotation =
                        g_Game.currentRotation - 1;
                }

                if(CanMoveBlock(
                    g_Game.blockX,
                    g_Game.blockY,
                    g_Game.currentBlockType,
                    nextRotation
                ))
                {
                    DrawBlockShape(
                        g_Game.blockX,
                        g_Game.blockY,
                        g_Game.currentBlockType,
                        g_Game.currentRotation,
                        EMPTY_COLOR
                    );

                    g_Game.currentRotation = nextRotation;

                    DrawBlockShape(
                        g_Game.blockX,
                        g_Game.blockY,
                        g_Game.currentBlockType,
                        g_Game.currentRotation,
                        BLOCK_COLOR
                    );
                }
            }

            g_Game.fallCounter++;
            
            if(g_Game.fallCounter >= g_Game.fallInterval)
            {
                g_Game.fallCounter = 0;

                if(CanMoveBlock(
                    g_Game.blockX, 
                    g_Game.blockY + 1, 
                    g_Game.currentBlockType, 
                    g_Game.currentRotation
                ))
                {
                    DrawBlockShape(
                        g_Game.blockX, 
                        g_Game.blockY, 
                        g_Game.currentBlockType, 
                        g_Game.currentRotation, 
                        EMPTY_COLOR
                    );

                    g_Game.blockY++;

                    DrawBlockShape(
                        g_Game.blockX, 
                        g_Game.blockY, 
                        g_Game.currentBlockType, 
                        g_Game.currentRotation, 
                        BLOCK_COLOR
                    );
                }
                else
                {
                    FixBlock(
                        g_Game.blockX, 
                        g_Game.blockY, 
                        g_Game.currentBlockType, 
                        g_Game.currentRotation
                    );

                    u8 clearedLines 
                        = ClearCompletedLines();

                    if (clearedLines > 0)
                    {
                        g_Game.totalLines 
                            += clearedLines;
                        u16 newLevel 
                            = g_Game.totalLines / LINES_PER_LEVEL + 1;

                        if (newLevel != g_Game.level)
                        {
                            g_Game.level = newLevel;
                            g_Game.fallInterval 
                                = GetFallInterval(g_Game.level);
                        }

                        g_Game.score 
                            += clearedLines * SCORE_PER_LINE 
                                + (g_Game.level - 1);

                        DrawBoard();
                        DrawUI(
                            g_Game.score, 
                            g_Game.level, 
                            g_Game.totalLines);

                        Sound_PlayLineClear();
                    }

                    g_Game.currentBlockType 
                        = Math_GetRandomMax8(BLOCK_TYPE_COUNT);
                    g_Game.currentRotation = 0;

                    g_Game.blockX = BLOCK_START_X;
                    g_Game.blockY = BLOCK_START_Y;

                    if(CanMoveBlock(
                        g_Game.blockX, 
                        g_Game.blockY, 
                        g_Game.currentBlockType, 
                        g_Game.currentRotation 
                    ))
                    {
                        DrawBlockShape(
                            g_Game.blockX, 
                            g_Game.blockY, 
                            g_Game.currentBlockType, 
                            g_Game.currentRotation, 
                            BLOCK_COLOR
                        );
                    }
                    else
                    {
                        g_Game.gameOver = TRUE;
                    }
                }
            }

            g_Game.prevRow5 = row5;

            Sound_Update();

            Halt();
        }

        Sound_Stop();    
        ShowGameOver();
        WaitForSpacePress();
    }
}