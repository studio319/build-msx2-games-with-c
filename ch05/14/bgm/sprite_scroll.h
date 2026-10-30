#ifndef SPRITE_SCROLL_H
#define SPRITE_SCROLL_H

void SpriteScroll_Init();

void SpriteScroll_LoadShiftedPattern(
    const u8* pattern,
    u8 shiftedPattern
    );

void SpriteScroll_SetPosition(
    u8 index,
    u8 x,
    u8 y,
    u8 normalPattern,
    u8 shiftedPattern
    );

#endif