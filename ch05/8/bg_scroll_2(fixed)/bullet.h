#ifndef BULLET_H
#define BULLET_H

typedef struct
{
    u8 x;
    u8 y;
    u8 active;
} Bullet;

void Bullet_Init();

void Bullet_Fire(u8 x, u8 y);

void Bullet_Update();

const Bullet* Bullet_GetBullets();

u8 Bullet_GetCount();

void Bullet_Deactivate(u8 index);

#endif