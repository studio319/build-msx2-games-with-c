#ifndef UI_H
#define UI_H

void UI_Init();

void UI_ShowTitle();

void UI_ShowGameOver(const char* scoreText);

void UI_PrepareHUD();
void UI_UpdateHUD(const char* scoreText);

void UI_ClearGamePage();
void UI_ClearHUD();

#endif