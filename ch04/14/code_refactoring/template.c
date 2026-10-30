#include "msxgl.h"
#include "math.h"
#include "print.h"
#include "font/font_mgl_sample6.h"
#include "block_data.h"
#include "board.h"

#define START_FALL_INTERVAL 30

#define LINES_PER_LEVEL 5

#define FALL_INTERVAL_STEP 3
#define MIN_FALL_INTERVAL 6

#define SCORE_PER_LINE 100

#define UI_X 184
#define UI_SCORE_Y 32
#define UI_LEVEL_Y 48
#define UI_LINES_Y 64

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

void main()
{
    VDP_SetMode(VDP_MODE_SCREEN5);
    VDP_SetColor(COLOR_BLACK);
    VDP_EnableVBlank(TRUE);
    VDP_ClearVRAM();
    
    Print_SetBitmapFont(g_Font_MGL_Sample6);
    Print_SetColor(COLOR_WHITE, COLOR_BLACK);

    ClearBoard();
    DrawBoard();

    u16 totalLines = 0;
    u16 level = 1;
    u16 score = 0;

    DrawUI(score, level, totalLines);

    i8 blockX = BLOCK_START_X;
    i8 blockY = BLOCK_START_Y;
    u8 currentBlockType = Math_GetRandomMax8(BLOCK_TYPE_COUNT);
    u8 currentRotation = 0;    

    DrawBlockShape(
        blockX, 
        blockY, 
        currentBlockType, 
        currentRotation, 
        BLOCK_COLOR
    );

    u8 prevRow5 = 0xFF;
    u8 fallCounter = 0;
    u8 fallInterval = START_FALL_INTERVAL;    
    u8 gameOver = FALSE;    
    while (!gameOver)
    {
        u8 row8 = Keyboard_Read(8);
        u8 row5 = Keyboard_Read(5);

        if(IS_KEY_PRESSED(row8, KEY_LEFT))
        {
            if(CanMoveBlock(
                blockX - 1, 
                blockY, 
                currentBlockType, 
                currentRotation
            ))
            {
                DrawBlockShape(
                    blockX, 
                    blockY, 
                    currentBlockType, 
                    currentRotation, 
                    EMPTY_COLOR
                );

                blockX--;

                DrawBlockShape(
                    blockX, 
                    blockY, 
                    currentBlockType, 
                    currentRotation, 
                    BLOCK_COLOR
                );
            }
        }

        if(IS_KEY_PRESSED(row8, KEY_RIGHT))
        {
            if(CanMoveBlock(
                blockX + 1, 
                blockY, 
                currentBlockType, 
                currentRotation
            ))
            {
                DrawBlockShape(
                    blockX, 
                    blockY, 
                    currentBlockType, 
                    currentRotation, 
                    EMPTY_COLOR
                );

                blockX++;

                DrawBlockShape(
                    blockX, 
                    blockY, 
                    currentBlockType, 
                    currentRotation, 
                    BLOCK_COLOR
                );
            }
        }

        if(IS_KEY_PRESSED(row8, KEY_DOWN))
        {
            if(CanMoveBlock(
                blockX, 
                blockY + 1, 
                currentBlockType, 
                currentRotation
            ))
            {
                DrawBlockShape(
                    blockX, 
                    blockY, 
                    currentBlockType, 
                    currentRotation, 
                    EMPTY_COLOR);

                blockY++;

                DrawBlockShape(
                    blockX, 
                    blockY, 
                    currentBlockType, 
                    currentRotation, 
                    BLOCK_COLOR
                );

                fallCounter = 0;
            }
        }

        if(IS_KEY_PRESSED(row5, KEY_X) &&
            !IS_KEY_PRESSED(prevRow5, KEY_X))
        {
            u8 nextRotation = currentRotation + 1;
            if(nextRotation >= BLOCK_ROTATION_COUNT)
            {
                nextRotation = 0;
            }

            if(CanMoveBlock(
                blockX,
                blockY,
                currentBlockType,
                nextRotation
            ))
            {
                DrawBlockShape(
                    blockX,
                    blockY,
                    currentBlockType,
                    currentRotation,
                    EMPTY_COLOR
                );

                currentRotation = nextRotation;

                DrawBlockShape(
                    blockX,
                    blockY,
                    currentBlockType,
                    currentRotation,
                    BLOCK_COLOR
                );
            }
        }
        else if(IS_KEY_PRESSED(row5, KEY_Z) &&
            !IS_KEY_PRESSED(prevRow5, KEY_Z))
        {
            u8 nextRotation;
            if(currentRotation == 0)
            {
                nextRotation =
                    BLOCK_ROTATION_COUNT - 1;
            }
            else
            {
                nextRotation =
                    currentRotation - 1;
            }

            if(CanMoveBlock(
                blockX,
                blockY,
                currentBlockType,
                nextRotation
            ))
            {
                DrawBlockShape(
                    blockX,
                    blockY,
                    currentBlockType,
                    currentRotation,
                    EMPTY_COLOR
                );

                currentRotation = nextRotation;

                DrawBlockShape(
                    blockX,
                    blockY,
                    currentBlockType,
                    currentRotation,
                    BLOCK_COLOR
                );
            }
        }

        fallCounter++;
        
        if(fallCounter >= fallInterval)
        {
            fallCounter = 0;

            if(CanMoveBlock(
                blockX, 
                blockY + 1, 
                currentBlockType, 
                currentRotation
            ))
            {
                DrawBlockShape(
                    blockX, 
                    blockY, 
                    currentBlockType, 
                    currentRotation, 
                    EMPTY_COLOR
                );

                blockY++;

                DrawBlockShape(
                    blockX, 
                    blockY, 
                    currentBlockType, 
                    currentRotation, 
                    BLOCK_COLOR
                );
            }
            else
            {
                FixBlock(
                    blockX, 
                    blockY, 
                    currentBlockType, 
                    currentRotation
                );

                u8 clearedLines = ClearCompletedLines();

                if (clearedLines > 0)
                {
                    totalLines += clearedLines;
                    u16 newLevel = totalLines / LINES_PER_LEVEL + 1;

                    if (newLevel != level)
                    {
                        level = newLevel;
                        fallInterval = GetFallInterval(level);
                    }

                    score += clearedLines * SCORE_PER_LINE + (level - 1);

                    DrawBoard();
                    DrawUI(score, level, totalLines);
                }

                currentBlockType 
                    = Math_GetRandomMax8(BLOCK_TYPE_COUNT);
                currentRotation = 0;

                blockX = BLOCK_START_X;
                blockY = BLOCK_START_Y;

                if(CanMoveBlock(
                    blockX, 
                    blockY, 
                    currentBlockType, 
                    currentRotation 
                ))
                {
                    DrawBlockShape(
                        blockX, 
                        blockY, 
                        currentBlockType, 
                        currentRotation, 
                        BLOCK_COLOR
                    );
                }
                else
                {
                    gameOver = TRUE;
                }
            }
        }

        prevRow5 = row5;

        Halt();
    }

    Print_SetPosition(101, 100);
    Print_DrawText("GAME OVER");

    while(1)
    {
        Halt();
    }
}