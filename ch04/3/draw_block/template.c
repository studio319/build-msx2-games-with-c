#include "msxgl.h"
#include "draw.h"

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

u8 g_Board[BOARD_HEIGHT][BOARD_WIDTH];

const u8 g_BlockShape[BLOCK_SIZE][BLOCK_SIZE] =
{
    { 0, 1, 0, 0 },
    { 1, 1, 1, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
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

void DrawBlockShape(i8 blockX, i8 blockY)
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
            if(g_BlockShape[y][x] == 1)
            {
                u16 screenX =
                    BOARD_X +
                    (blockX + x) * CELL_SIZE;

                Draw_FillBox(
                    screenX,
                    screenY,
                    screenX + CELL_SIZE - 2,
                    screenY + CELL_SIZE - 2,
                    BLOCK_COLOR,
                    VDP_OP_IMP
                );
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

    DrawBlockShape(3, 2);
    
    while (1)
    {
        Halt();
    }
}