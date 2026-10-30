#include "msxgl.h"
#include "math.h"
#include "enemy.h"

#define ENEMY_PATTERN 8

#define ENEMY_FIRST_SPRITE 9

#define ENEMY_COUNT 4

#define ENEMY_SPEED 1

#define ENEMY_SPAWN_INTERVAL 60

#define SCREEN_HEIGHT 212

static const u8 g_EnemyPattern[] =
{
    /* 왼쪽 위 8×8 */
    0x18, 0x1C, 0x0F, 0x1F,
    0x3F, 0x7B, 0xFB, 0x33,

    /* 왼쪽 아래 8×8 */
    0x03, 0x07, 0x0D, 0x19,
    0x30, 0x00, 0x00, 0x00,

    /* 오른쪽 위 8×8 */
    0x18, 0x38, 0xF0, 0xF8,
    0xFC, 0xDE, 0xDF, 0xCC,

    /* 오른쪽 아래 8×8 */
    0xC0, 0xE0, 0xB0, 0x98,
    0x0C, 0x00, 0x00, 0x00
};

static Enemy g_Enemies[ENEMY_COUNT];

static u8 g_SpawnCounter = 0;

void Enemy_Init()
{    
    VDP_LoadSpritePattern(
        g_EnemyPattern, 
        ENEMY_PATTERN, 
        4
    );

    u8 i;
    for (i = 0; i < ENEMY_COUNT; i++)
    {
        g_Enemies[i].active = FALSE;

        VDP_SetSpriteExUniColor(
            ENEMY_FIRST_SPRITE + i, 
            0, 
            0, 
            ENEMY_PATTERN, COLOR_WHITE
        );

        VDP_HideSprite(ENEMY_FIRST_SPRITE + i);
    }
}

void Enemy_Spawn()
{
    u8 i;
    for (i = 0; i < ENEMY_COUNT; i++)
    {
        if (!g_Enemies[i].active)
        {
            g_Enemies[i].x 
                = Math_GetRandomMax8(241);
            g_Enemies[i].y = 0;
            g_Enemies[i].active = TRUE;

            VDP_SetSpritePosition(
                ENEMY_FIRST_SPRITE + i, 
                g_Enemies[i].x, 
                g_Enemies[i].y
            );

            return;
        }
    }
}

void Enemy_Update()
{
    u8 i = 0;
    for (i = 0; i < ENEMY_COUNT; i++)
    {
        if (g_Enemies[i].active)
        {
            if (g_Enemies[i].y 
                < SCREEN_HEIGHT - ENEMY_SPEED)
            {
                g_Enemies[i].y += ENEMY_SPEED;

                VDP_SetSpritePosition(
                    ENEMY_FIRST_SPRITE + i, 
                    g_Enemies[i].x, 
                    g_Enemies[i].y
                );
            }
            else
            {
                g_Enemies[i].active = FALSE;

                VDP_HideSprite(
                    ENEMY_FIRST_SPRITE + i
                );
            }
        }
    }

    g_SpawnCounter++;

    if (g_SpawnCounter >= ENEMY_SPAWN_INTERVAL)
    {
        g_SpawnCounter = 0;

        Enemy_Spawn();
    }
}

const Enemy* Enemy_GetEnemies()
{
    return g_Enemies;
}

u8 Enemy_GetCount()
{
    return ENEMY_COUNT;
}

void Enemy_Deactivate(u8 index)
{
    g_Enemies[index].active = FALSE;

    VDP_HideSprite(ENEMY_FIRST_SPRITE + index);
}