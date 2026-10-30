#ifndef SCORE_H
#define SCORE_H

void Score_Init();

void Score_Add(u16 points);

void Score_GetText(char* text);

u8 Score_TakeChanged();

#endif