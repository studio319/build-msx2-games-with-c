#include "msxgl.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "collision.h"
#include "enemy_bullet.h"
#include "explosion.h"
#include "score.h"

#define BULLET_HITBOX_X 7
#define BULLET_HITBOX_Y 5
#define BULLET_HITBOX_WIDTH 2
#define BULLET_HITBOX_HEIGHT 6

#define ENEMY_HITBOX_SIZE 16

#define PLAYER_HITBOX_SIZE 16

#define IS_OVERLAP(ax, ay, aw, ah, bx, by, bw, bh) \
    ( ax < bx + bw && ax + aw > bx \
    && ay < by + bh && ay + ah > by )

void Collision_Update()
{
    const Bullet* bullets = Bullet_GetBullets();
    const Enemy* enemies = Enemy_GetEnemies();
    u8 bulletCount = Bullet_GetCount();
    u8 enemyCount = Enemy_GetCount();
    
    u8 bulletIndex;
    for (bulletIndex = 0; bulletIndex < bulletCount; bulletIndex++)
    {
        if (!bullets[bulletIndex].active)
        {
            continue;
        }

        u8 bulletX = bullets[bulletIndex].x + BULLET_HITBOX_X;
        u8 bulletY = bullets[bulletIndex].y + BULLET_HITBOX_Y;

        u8 enemyIndex;
        for (enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++)
        {
            if (!enemies[enemyIndex].active)
            {
                continue;
            }

            if (IS_OVERLAP(
                bulletX,
                bulletY,
                BULLET_HITBOX_WIDTH,
                BULLET_HITBOX_HEIGHT,
                enemies[enemyIndex].x,
                enemies[enemyIndex].y,
                ENEMY_HITBOX_SIZE,
                ENEMY_HITBOX_SIZE
            ))
            {
                Bullet_Deactivate(bulletIndex);
                Enemy_Deactivate(enemyIndex);

                Explosion_Spawn(
                    enemies[enemyIndex].x, 
                    enemies[enemyIndex].y
                );

                Score_Add(100);
                
                break;
            }
        }
    }
}

u8 Collision_CheckPlayerEnemy()
{
    const Enemy* enemies = Enemy_GetEnemies();
    u8 enemyCount = Enemy_GetCount();
    
    u8 g_PlayerX = Player_GetX();
    u8 g_PlayerY = Player_GetY();
    
    u8 enemyIndex;
    for (enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++)
    {
        if (!enemies[enemyIndex].active)
        {
            continue;
        }

        if (IS_OVERLAP(
            g_PlayerX,
            g_PlayerY,
            PLAYER_HITBOX_SIZE,
            PLAYER_HITBOX_SIZE,
            enemies[enemyIndex].x,
            enemies[enemyIndex].y,
            ENEMY_HITBOX_SIZE,
            ENEMY_HITBOX_SIZE
        ))
        {
            Enemy_Deactivate(enemyIndex);

            return TRUE;
        }
    }

    return FALSE;
}

u8 Collision_CheckPlayerEnemyBullet()
{
    const EnemyBullet* bullets = EnemyBullet_GetBullets();
    u8 bulletCount = EnemyBullet_GetCount();

    u8 playerX = Player_GetX();
    u8 playerY = Player_GetY();

    u8 bulletIndex;
    for(bulletIndex = 0; bulletIndex < bulletCount; bulletIndex++)
    {
        if(!bullets[bulletIndex].active)
        {
            continue;
        }

        u8 bulletX = bullets[bulletIndex].x + BULLET_HITBOX_X;
        u8 bulletY = bullets[bulletIndex].y + BULLET_HITBOX_Y;

        if(IS_OVERLAP(bulletX,
            bulletY,
            BULLET_HITBOX_WIDTH,
            BULLET_HITBOX_HEIGHT,
            playerX,
            playerY,
            PLAYER_HITBOX_SIZE,
            PLAYER_HITBOX_SIZE))
        {
            EnemyBullet_Deactivate(bulletIndex);

            return TRUE;
        }
    }

    return FALSE;
}