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

void main()
{
    VDP_SetMode(VDP_MODE_SCREEN5);
    VDP_SetColor(COLOR_BLACK);
    VDP_EnableVBlank(TRUE);
    VDP_ClearVRAM();
    
    ClearBoard();
    DrawBoard();

    while (1)
    {
        Halt();
    }
}