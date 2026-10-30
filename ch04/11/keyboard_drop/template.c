#include "msxgl.h"
#include "draw.h"
#include "math.h"
#include "block_data.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

#define CELL_SIZE 8

#define BOARD_X 88
#define BOARD_Y 24

#define CELL_EMPTY 0
#define CELL_BLOCK 1

#define EMPTY_COLOR 4
#define BLOCK_COLOR 15

#define BLOCK_START_X 3
#define BLOCK_START_Y 0

#define FALL_INTERVAL 30

u8 g_Board[BOARD_HEIGHT][BOARD_WIDTH];

void ClearBoard()
{
    u8 y;
    for(y = 0; y < BOARD_HEIGHT; y++)
    {
        u8 x;
        for(x = 0; x < BOARD_WIDTH; x++)
        {
            g_Board[y][x] = CELL_EMPTY;
        }
    }
}

void DrawBoard()
{
    u8 y;    
    for(y = 0; y < BOARD_HEIGHT; y++)
    {
        u16 screenY = BOARD_Y + y * CELL_SIZE;

        u8 x;
        for(x = 0; x < BOARD_WIDTH; x++)
        {
            u8 color;

            if(g_Board[y][x] == CELL_BLOCK)
            {
                color = BLOCK_COLOR;
            }
            else
            {
                color = EMPTY_COLOR;
            }

            u16 screenX = BOARD_X + x * CELL_SIZE;            

            Draw_FillBox(
                screenX,
                screenY,
                screenX + CELL_SIZE - 2,
                screenY + CELL_SIZE - 2,
                color,
                VDP_OP_IMP
            );
        }
    }
}

void DrawBlockShape(
    i8 blockX,
    i8 blockY,
    u8 blockType,
    u8 rotation,
    u8 color
)
{
    u8 y;
    for(y = 0; y < BLOCK_SIZE; y++)
    {
        u16 screenY =
            BOARD_Y +
            (blockY + y) * CELL_SIZE;

        u8 x;
        for(x = 0; x < BLOCK_SIZE; x++)
        {
            if(g_BlockShapes[blockType][rotation][y][x] == 1)
            {
                u16 screenX =
                    BOARD_X +
                    (blockX + x) * CELL_SIZE;

                Draw_FillBox(
                    screenX,
                    screenY,
                    screenX + CELL_SIZE - 2,
                    screenY + CELL_SIZE - 2,
                    color,
                    VDP_OP_IMP
                );
            }
        }
    }
}

u8 CanMoveBlock(i8 newX, i8 newY, u8 blockType, u8 rotation)
{
    u8 y;
    for(y = 0; y < BLOCK_SIZE; y++)
    {
        i8 boardY = newY + y;

        u8 x;
        for(x = 0; x < BLOCK_SIZE; x++)
        {
            if(g_BlockShapes[blockType][rotation][y][x] == 1)
            {
                i8 boardX = newX + x;                

                if(boardX < 0 ||
                    boardX >= BOARD_WIDTH ||
                    boardY < 0 ||
                    boardY >= BOARD_HEIGHT)
                {
                    return FALSE;
                }

                if(g_Board[boardY][boardX] != CELL_EMPTY)
                {
                    return FALSE;
                }
            }
        }
    }
    
    return TRUE;
}

void FixBlock(i8 blockX, i8 blockY, u8 blockType, u8 rotation)
{    
    u8 y;
    for(y = 0; y < BLOCK_SIZE; y++)
    {        
        i8 boardY = blockY + y;

        u8 x;    
        for(x = 0; x < BLOCK_SIZE; x++)
        {
            if(g_BlockShapes[blockType][rotation][y][x] == 1)
            {
                i8 boardX = blockX + x;

                g_Board[boardY][boardX] = CELL_BLOCK;
            }
        }
    }
}

u8 IsLineFull(u8 lineY)
{
    u8 x;
    for(x = 0; x < BOARD_WIDTH; x++)
    {
        if(g_Board[lineY][x] == CELL_EMPTY)
        {
            return FALSE;
        }
    }

    return TRUE;
}

void RemoveLine(u8 lineY)
{    
    u8 y;
    u8 x;

    for(y = lineY; y > 0; y--)
    {        
        for(x = 0; x < BOARD_WIDTH; x++)
        {
            g_Board[y][x] =
                g_Board[y - 1][x];
        }
    }

    for(x = 0; x < BOARD_WIDTH; x++)
    {
        g_Board[0][x] = CELL_EMPTY;
    }
}

u8 ClearCompletedLines()
{
    u8 y = BOARD_HEIGHT - 1;
    u8 clearedLines = 0;

    while(1)
    {
        if(IsLineFull(y))
        {
            RemoveLine(y);

            clearedLines++;
        }
        else
        {
            if(y == 0)
            {
                break;
            }

            y--;
        }
    }

    return clearedLines;
}

void main()
{
    VDP_SetMode(VDP_MODE_SCREEN5);
    VDP_SetColor(COLOR_BLACK);
    VDP_EnableVBlank(TRUE);
    VDP_ClearVRAM();
    
    ClearBoard();
    DrawBoard();

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
        
        if(fallCounter >= FALL_INTERVAL)
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

                if(ClearCompletedLines() > 0)
                {
                    DrawBoard();
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

    while(1)
    {
        Halt();
    }
}