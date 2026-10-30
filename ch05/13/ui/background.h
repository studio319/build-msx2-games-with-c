#ifndef BACKGROUND_H
#define BACKGROUND_H

void Background_Init();
void Background_Reset();

void Background_Update();

u8 Background_GetSpriteY(u8 y);

u8 Background_GetScrollOffset();

#endif