#include "msxgl.h"
#include "score.h"

#define SCORE_MAX 999999UL

static u32 g_Score;
static u8 g_ScoreChanged;

void Score_Init()
{
    g_Score = 0;
    g_ScoreChanged = TRUE;
}

void Score_Add(u16 points)
{
    if(points == 0 || g_Score >= SCORE_MAX)
    {
        return;
    }

    if(points >= SCORE_MAX - g_Score)
    {
        g_Score = SCORE_MAX;
    }
    else
    {
        g_Score += points;
    }

    g_ScoreChanged = TRUE;
}

u8 Score_TakeChanged()
{
    u8 changed = g_ScoreChanged;
    g_ScoreChanged = FALSE;

    return changed;
}

void Score_GetText(char* text)
{
    u32 value = g_Score;

    u8 i = 6;
    while(i > 0)
    {
        i--;

        text[i] = '0' + (u8)(value % 10);
        value /= 10;
    }

    text[6] = '\0';
}