#ifndef BOARD_H
#define BOARD_H

#include "msxgl.h"

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

void ClearBoard();
void DrawBoard();
void DrawBlockShape(
    i8 blockX,
    i8 blockY,
    u8 blockType,
    u8 rotation,
    u8 color
);
u8 CanMoveBlock(i8 newX, i8 newY, u8 blockType, u8 rotation);
void FixBlock(i8 blockX, i8 blockY, u8 blockType, u8 rotation);
u8 ClearCompletedLines();

#endif