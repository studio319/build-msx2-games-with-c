#include "msxgl.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

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

    while(1)
    {
        Player_Update();
        Bullet_Update();
        Enemy_Update();
        
        Halt();
    }
}