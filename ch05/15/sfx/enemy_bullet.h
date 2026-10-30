#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

typedef struct
{
    u8 x;
    u8 y;
    u8 active;
} EnemyBullet;

void EnemyBullet_Init();
void EnemyBullet_Reset();

void EnemyBullet_Fire(u8 x, u8 y);

void EnemyBullet_Update();

const EnemyBullet* EnemyBullet_GetBullets();

u8 EnemyBullet_GetCount();

void EnemyBullet_Deactivate(u8 index);

#endif