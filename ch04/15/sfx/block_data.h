#ifndef BLOCK_DATA_H
#define BLOCK_DATA_H

#include "msxgl.h"

#define BLOCK_SIZE 4

#define BLOCK_ROTATION_COUNT 4

#define BLOCK_T 0
#define BLOCK_I 1
#define BLOCK_O 2
#define BLOCK_L 3
#define BLOCK_J 4
#define BLOCK_S 5
#define BLOCK_Z 6
#define BLOCK_TYPE_COUNT 7


extern const u8 g_BlockShapes
    [BLOCK_TYPE_COUNT]
    [BLOCK_ROTATION_COUNT]
    [BLOCK_SIZE]
    [BLOCK_SIZE];

#endif