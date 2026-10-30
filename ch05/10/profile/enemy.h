#ifndef ENEMY_H
#define ENEMY_H

typedef struct
{
    u8 x;
    u8 y;
    u8 active;
} Enemy;

void Enemy_Init();

void Enemy_Update();

const Enemy* Enemy_GetEnemies();

u8 Enemy_GetCount();

void Enemy_Deactivate(u8 index);

#endif