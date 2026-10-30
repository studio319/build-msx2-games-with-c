#include "msxgl.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "collision.h"

void main()
{
    VDP_SetMode(VDP_MODE_SCREEN5);
    VDP_SetColor(COLOR_BLACK);
    VDP_EnableVBlank(TRUE);
    VDP_ClearVRAM();

    VDP_SetSpriteFlag(
        VDP_SPRITE_SIZE_16 | VDP_SPRITE_SCALE_1
    );
    VDP_EnableSprite(TRUE);

    Player_Init();
    Bullet_Init();
    Enemy_Init();

    u8 gameOver = FALSE;
    while (!gameOver)
    {
        Player_Update();
        Bullet_Update();
        Enemy_Update();
        Collision_Update();

        if (Collision_CheckPlayerEnemy())
        {
            gameOver = TRUE;
        }

        Halt();
    }

    Player_Hide();

    while (1)
    {
        Halt();
    }
}