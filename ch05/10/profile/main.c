#include "msxgl.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "collision.h"
#include "background.h"
#include "sprite_scroll.h"
#include "debug.h"

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

    u8 gameOver = FALSE;
    while (!gameOver)
    {
        PROFILE_SECTION_START(1, 1, "Background");
        Background_Update();
        PROFILE_SECTION_END(1, 1, "Background");

        PROFILE_SECTION_START(1, 2, "Player");
        Player_Update();
        PROFILE_SECTION_END(1, 2, "Player");

        PROFILE_SECTION_START(1, 3, "Bullet");
        Bullet_Update();
        PROFILE_SECTION_END(1, 3, "Bullet");

        PROFILE_SECTION_START(1, 4, "Enemy");
        Enemy_Update();
        PROFILE_SECTION_END(1, 4, "Enemy");

        PROFILE_SECTION_START(1, 5, "Collision");
        Collision_Update();
        PROFILE_SECTION_END(1, 5, "Collision");

        PROFILE_SECTION_START(1, 6, "PlayerHit");
        if(Collision_CheckPlayerEnemy())
        {
            gameOver = TRUE;
        }
        PROFILE_SECTION_END(1, 6, "PlayerHit");

        Halt();
    }

    Player_Hide();

    while (1)
    {
        Halt();
    }
}