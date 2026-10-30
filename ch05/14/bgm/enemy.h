#ifndef ENEMY_H
#define ENEMY_H

typedef struct
{
    u8 x;
    u8 y;
    u8 active;
    u8 type;
    u8 direction;
    u8 moveTimer;
    u8 fireTimer;
} Enemy;

void Enemy_Init();
void Enemy_Reset();

void Enemy_Update(u8 playerX);

const Enemy* Enemy_GetEnemies();

u8 Enemy_GetCount();

void Enemy_Deactivate(u8 index);

#endif