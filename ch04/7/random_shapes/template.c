#include "msxgl.h"
#include "draw.h"
#include "math.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

#define CELL_SIZE 8

#define BOARD_X 88
#define BOARD_Y 24

#define CELL_EMPTY 0
#define CELL_BLOCK 1

#define EMPTY_COLOR 4
#define BLOCK_COLOR 15

#define BLOCK_SIZE 4

#define BLOCK_START_X 3
#define BLOCK_START_Y 2

#define FALL_INTERVAL 30

#define BLOCK_T 0
#define BLOCK_I 1
#define BLOCK_O 2
#define BLOCK_L 3
#define BLOCK_J 4
#define BLOCK_S 5
#define BLOCK_Z 6
#define BLOCK_TYPE_COUNT 7

u8 g_Board[BOARD_HEIGHT][BOARD_WIDTH];

const u8 g_BlockShapes[BLOCK_TYPE_COUNT][BLOCK_SIZE][BLOCK_SIZE] =
{
    {
        { 0, 1, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 0, 0, 0 },
        { 1, 1, 1, 1 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 0, 1, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 1, 0, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 0 },
        { 1, 1, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 1, 1, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    }
};

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

void DrawBlockShape(i8 blockX, i8 blockY, u8 blockType, u8 color)
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
            if(g_BlockShapes[blockType][y][x] == 1)
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

u8 CanMoveBlock(i8 newX, i8 newY, u8 blockType)
{
    u8 y;
    for(y = 0; y < BLOCK_SIZE; y++)
    {
        i8 boardY = newY + y;

        u8 x;
        for(x = 0; x < BLOCK_SIZE; x++)
        {
            if(g_BlockShapes[blockType][y][x] == 1)
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

void FixBlock(i8 blockX, i8 blockY, u8 blockType)
{    
    u8 y;
    for(y = 0; y < BLOCK_SIZE; y++)
    {        
        i8 boardY = blockY + y;

        u8 x;    
        for(x = 0; x < BLOCK_SIZE; x++)
        {
            if(g_BlockShapes[blockType][y][x] == 1)
            {
                i8 boardX = blockX + x;

                g_Board[boardY][boardX] = CELL_BLOCK;
            }
        }
    }
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
    DrawBlockShape(blockX, blockY, currentBlockType, BLOCK_COLOR);

    u8 fallCounter = 0;
    while (1)
    {
        u8 row8 = Keyboard_Read(8);

        if(IS_KEY_PRESSED(row8, KEY_LEFT))
        {
            if(CanMoveBlock(blockX - 1, blockY, currentBlockType))
            {
                DrawBlockShape(blockX, blockY, currentBlockType, EMPTY_COLOR);

                blockX--;

                DrawBlockShape(blockX, blockY, currentBlockType, BLOCK_COLOR);
            }
        }

        if(IS_KEY_PRESSED(row8, KEY_RIGHT))
        {
            if(CanMoveBlock(blockX + 1, blockY, currentBlockType))
            {
                DrawBlockShape(blockX, blockY, currentBlockType, EMPTY_COLOR);

                blockX++;

                DrawBlockShape(blockX, blockY, currentBlockType, BLOCK_COLOR);
            }
        }

        fallCounter++;
        
        if(fallCounter >= FALL_INTERVAL)
        {
            fallCounter = 0;

            if(CanMoveBlock(blockX, blockY + 1, currentBlockType))
            {
                DrawBlockShape(blockX, blockY, currentBlockType, EMPTY_COLOR);

                blockY++;

                DrawBlockShape(blockX, blockY, currentBlockType, BLOCK_COLOR);
            }
            else
            {
                FixBlock(blockX, blockY,currentBlockType);

                currentBlockType = Math_GetRandomMax8(BLOCK_TYPE_COUNT);

                blockX = BLOCK_START_X;
                blockY = BLOCK_START_Y;

                DrawBlockShape(blockX, blockY, currentBlockType, BLOCK_COLOR);
            }
        }

        Halt();
    }
}