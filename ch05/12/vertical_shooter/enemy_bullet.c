#include "msxgl.h"
#include "enemy_bullet.h"
#include "background.h"
#include "sprite_scroll.h"

#define ENEMY_BULLET_FIRST_SPRITE 13
#define ENEMY_BULLET_PATTERN 4
#define ENEMY_BULLET_PATTERN_SHIFTED 16
#define ENEMY_BULLET_SPRITE_HEIGHT 16

#define ENEMY_BULLET_SPEED 2
#define ENEMY_BULLET_COLOR 13

#define ENEMY_BULLET_COUNT 4

#define SCREEN_HEIGHT 212

static EnemyBullet g_EnemyBullets[ENEMY_BULLET_COUNT];

void EnemyBullet_Init()
{
    u8 i;
    for(i = 0; i < ENEMY_BULLET_COUNT; i++)
    {
        g_EnemyBullets[i].active = FALSE;

        VDP_SetSpriteExUniColor(
            ENEMY_BULLET_FIRST_SPRITE + i,
            0,
            0,
            ENEMY_BULLET_PATTERN,
            0
        );
    }
}

void EnemyBullet_Fire( u8 x, u8 y )
{
    if(y >= 180)
        return;

    u8 i;
    for(i = 0; i < ENEMY_BULLET_COUNT; i++)
    {
        if(!g_EnemyBullets[i].active)
        {
            g_EnemyBullets[i].x = x;
            g_EnemyBullets[i].y = y + 12;
            g_EnemyBullets[i].active = TRUE;

            VDP_SetSpriteUniColor(
                ENEMY_BULLET_FIRST_SPRITE + i,
                ENEMY_BULLET_COLOR
            );

            SpriteScroll_SetPosition(
                ENEMY_BULLET_FIRST_SPRITE + i,
                g_EnemyBullets[i].x,
                g_EnemyBullets[i].y,
                ENEMY_BULLET_PATTERN,
                ENEMY_BULLET_PATTERN_SHIFTED
            );

            return;
        }
    }
}

void EnemyBullet_Update()
{
    u8 i;
    for(i = 0; i < ENEMY_BULLET_COUNT; i++)
    {
        if(g_EnemyBullets[i].active)
        {
            if(g_EnemyBullets[i].y 
                >= ENEMY_BULLET_SPEED)
            {
                g_EnemyBullets[i].y 
                    += ENEMY_BULLET_SPEED;

                SpriteScroll_SetPosition(
                    ENEMY_BULLET_FIRST_SPRITE + i,
                    g_EnemyBullets[i].x,
                    g_EnemyBullets[i].y,
                    ENEMY_BULLET_PATTERN,
                    ENEMY_BULLET_PATTERN_SHIFTED
                );
            }
            else
            {
                EnemyBullet_Deactivate(i);
            }
        }
    }
}

void EnemyBullet_Deactivate( u8 index )
{
    g_EnemyBullets[index].active = FALSE;
    
    VDP_SetSpriteUniColor(
        ENEMY_BULLET_FIRST_SPRITE + index, 0
    );
}

u8 EnemyBullet_GetCount()
{
    return ENEMY_BULLET_COUNT;
}

const EnemyBullet* EnemyBullet_GetBullets()
{
    return g_EnemyBullets;
}