#include "msxgl.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "collision.h"
#include "background.h"
#include "sprite_scroll.h"
#include "enemy_bullet.h"
#include "explosion.h"

#define SPRITE_ATTRIBUTE_TABLE 0xF600
#define SPRITE_PATTERN_TABLE   0xF800

void main()
{
    VDP_SetMode(VDP_MODE_SCREEN5);
    VDP_SetColor(COLOR_BLACK);
    VDP_EnableVBlank(TRUE);
    VDP_ClearVRAM();

    VDP_SetSpriteAttributeTable(
        SPRITE_ATTRIBUTE_TABLE
    );
    VDP_SetSpritePatternTable(
        SPRITE_PATTERN_TABLE
    );

    VDP_SetSpriteFlag(
        VDP_SPRITE_SIZE_16 | VDP_SPRITE_SCALE_1
    );
    VDP_EnableSprite(TRUE);

    Background_Init();
    SpriteScroll_Init();
    Player_Init();
    Bullet_Init();
    Enemy_Init();
    EnemyBullet_Init();
    Explosion_Init();

    u8 gameOver = FALSE;
    while (!gameOver)
    {
        Background_Update();
        Player_Update();
        Bullet_Update();
        Enemy_Update(Player_GetX());        
        EnemyBullet_Update();
        Explosion_Update();
        Collision_Update();

        if(Collision_CheckPlayerEnemy() ||
            Collision_CheckPlayerEnemyBullet())
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