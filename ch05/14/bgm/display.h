#ifndef DISPLAY_H
#define DISPLAY_H

extern volatile u8 g_VBlankCounter;

void Display_Init();

void Display_StartHUD();
void Display_StopHUD();

void Display_SetScroll(u8 offset);

#endif