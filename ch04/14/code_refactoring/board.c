#include "msxgl.h"
#include "draw.h"
#include "block_data.h"
#include "board.h"

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