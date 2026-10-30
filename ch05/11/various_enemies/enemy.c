#include "msxgl.h"
#include "math.h"
#include "enemy.h"
#include "background.h"
#include "sprite_scroll.h"

#define ENEMY_FIRST_SPRITE 9

#define ENEMY_COUNT 4

#define ENEMY_SPEED 1

#define ENEMY_SPAWN_INTERVAL 60

#define SCREEN_HEIGHT 212

#define ENEMY_TYPE_BASIC   0
#define ENEMY_TYPE_ZIGZAG  1
#define ENEMY_TYPE_CHASER  2
#define ENEMY_TYPE_SHOOTER 3
#define ENEMY_TYPE_COUNT   4

static const u8 g_EnemyPatterns[4][32] =
{
    // Basic
    {
        0x00, 0x03, 0x0F, 0x1F,
        0x3F, 0x39, 0x7F, 0x7F,
        0x7F, 0x3F, 0x1F, 0x0C,
        0x18, 0x30, 0x00, 0x00,
        0x00, 0xC0, 0xF0, 0xF8,
        0xFC, 0x9C, 0xFE, 0xFE,
        0xFE, 0xFC, 0xF8, 0x30,
        0x18, 0x0C, 0x00, 0x00
    },

    // Zigzag
    {
        0x00, 0x03, 0x07, 0x0F,
        0xEF, 0xF7, 0xFB, 0xFF,
        0x3F, 0x1F, 0x0E, 0x1C,
        0x38, 0x70, 0x00, 0x00,
        0x00, 0xC0, 0xE0, 0xF0,
        0xF7, 0xEF, 0xDF, 0xFF,
        0xFC, 0xF8, 0x70, 0x38,
        0x1C, 0x0E, 0x00, 0x00
    },
    
    // Chaser
    {
        0x00, 0x01, 0x03, 0x07,
        0xCF, 0xEF, 0x7F, 0x3F,
        0x1F, 0x0F, 0x07, 0x07,
        0x03, 0x03, 0x01, 0x00,

        0x00, 0x80, 0xC0, 0xE0,
        0xF3, 0xF7, 0xFE, 0xFC,
        0xF8, 0xF0, 0xE0, 0xE0,
        0xC0, 0xC0, 0x80, 0x00
    },

    // Shooter
    {
        0x00, 0x0F, 0x1F, 0x3F,
        0x3F, 0x38, 0x3F, 0x7F,
        0x7F, 0x7F, 0x3F, 0x07,
        0x03, 0x03, 0x03, 0x00,
        0x00, 0xF0, 0xF8, 0xFC,
        0xFC, 0x1C, 0xFC, 0xFE,
        0xFE, 0xFE, 0xFC, 0xE0,
        0xC0, 0xC0, 0xC0, 0x00
    }
};

static const u8 g_EnemyNormalPattern[ENEMY_TYPE_COUNT] =
{
    8, 24, 32, 40
};

static const u8 g_EnemyShiftedPattern[ENEMY_TYPE_COUNT] =
{
    20, 28, 36, 44
};

static const u8 g_EnemyColor[ENEMY_TYPE_COUNT] =
{
    11,  // Basic
    3,  // Zigzag
    5,  // Chaser
    9   // Shooter
};

static Enemy g_Enemies[ENEMY_COUNT];

static u8 g_SpawnCounter = 0;

static u8 g_NextEnemyType = ENEMY_TYPE_BASIC;

static void Enemy_LoadPatterns()
{
    u8 i;
    for(i = 0; i < ENEMY_TYPE_COUNT; i++)
    {
        VDP_LoadSpritePattern(
            g_EnemyPatterns[i],
            g_EnemyNormalPattern[i],
            4
        );

        SpriteScroll_LoadShiftedPattern(
            g_EnemyPatterns[i],
            g_EnemyShiftedPattern[i]
        );
    }
}

static void Enemy_MoveZigzag(Enemy* enemy)
{
    if(enemy->moveTimer > 0)
    {
        enemy->moveTimer--;
        if(enemy->moveTimer == 0)
        {
            enemy->direction ^= 1;
            enemy->moveTimer = 24;
        }
    }

    if(enemy->x == 0)
    {
        enemy->direction = 1;
    }
    else if(enemy->x >= 240)
    {
        enemy->direction = 0;
    }

    if(enemy->direction == 1)
    {
        enemy->x++;
    }
    else
    {
        enemy->x--;
    }
}

static void Enemy_MoveChase(
    Enemy* enemy, 
    u8 playerX
)
{
    if(enemy->x < playerX)
    {
        if(enemy->x < 240)
        {
            enemy->x++;
        }
    }
    else if(enemy->x > playerX)
    {
        if(enemy->x > 0)
        {
            enemy->x--;
        }
    }
}

static void Enemy_MoveHorizontal(
    Enemy* enemy, 
    u8 playerX
)
{
    switch(enemy->type)
    {
    case ENEMY_TYPE_ZIGZAG:
        Enemy_MoveZigzag(enemy);
        break;

    case ENEMY_TYPE_CHASER:
        Enemy_MoveChase(enemy, playerX);
        break;

    case ENEMY_TYPE_BASIC:
    case ENEMY_TYPE_SHOOTER:
    default:
        break;
    }
}

void Enemy_Init()
{    
    Enemy_LoadPatterns();

    u8 i;
    for (i = 0; i < ENEMY_COUNT; i++)
    {
        g_Enemies[i].active = FALSE;

        VDP_SetSpriteExUniColor(
            ENEMY_FIRST_SPRITE + i, 
            0, 
            0, 
            g_EnemyNormalPattern[ENEMY_TYPE_BASIC],
            0
        );
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
            g_Enemies[i].type = g_NextEnemyType;
            g_Enemies[i].direction 
                = (g_Enemies[i].x < 120) ? 1 : 0;
            g_Enemies[i].moveTimer = 24;
            g_Enemies[i].fireTimer = 60;

            g_NextEnemyType++;
            if(g_NextEnemyType >= ENEMY_TYPE_COUNT)
            {
                g_NextEnemyType = ENEMY_TYPE_BASIC;
            }

            VDP_SetSpriteUniColor(
                ENEMY_FIRST_SPRITE + i,
                g_EnemyColor[g_Enemies[i].type]
            );

            SpriteScroll_SetPosition(
                ENEMY_FIRST_SPRITE + i,
                g_Enemies[i].x,
                g_Enemies[i].y,
                g_EnemyNormalPattern[g_Enemies[i].type],
                g_EnemyShiftedPattern[g_Enemies[i].type]
            );

            return;
        }
    }
}

void Enemy_Update(u8 playerX)
{
    u8 i = 0;
    for (i = 0; i < ENEMY_COUNT; i++)
    {
        if (g_Enemies[i].active)
        {
            if (g_Enemies[i].y 
                < SCREEN_HEIGHT - ENEMY_SPEED)
            {
                Enemy_MoveHorizontal(
                    &g_Enemies[i], playerX
                );

                g_Enemies[i].y += ENEMY_SPEED;

                SpriteScroll_SetPosition(
                    ENEMY_FIRST_SPRITE + i,
                    g_Enemies[i].x,
                    g_Enemies[i].y,
                    g_EnemyNormalPattern[g_Enemies[i].type],
                    g_EnemyShiftedPattern[g_Enemies[i].type]
                );
            }
            else
            {
                Enemy_Deactivate(i);
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

    VDP_SetSpriteUniColor(
        ENEMY_FIRST_SPRITE + index, 
        0
    );
}