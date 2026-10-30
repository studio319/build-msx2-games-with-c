#include "msxgl.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "collision.h"
#include "background.h"
#include "sprite_scroll.h"
#include "enemy_bullet.h"
#include "explosion.h"
#include "display.h"
#include "ui.h"
#include "score.h"

#define SPRITE_ATTRIBUTE_TABLE 0xF600
#define SPRITE_PATTERN_TABLE   0xF800

#define GAME_STATE_TITLE      0
#define GAME_STATE_PLAY       1
#define GAME_STATE_GAME_OVER  2

static void Game_Start()
{
    Display_StopHUD();

    VDP_EnableVBlank(FALSE);
    VDP_EnableDisplay(FALSE);

    UI_ClearGamePage();
    UI_ClearHUD();

    Background_Reset();
    Player_Reset();
    Bullet_Reset();
    EnemyBullet_Reset();
    Enemy_Reset();
    Explosion_Reset();
    Score_Init();

    UI_PrepareHUD();

    Display_StartHUD();

    Display_SetScroll(Background_GetScrollOffset());

    VDP_EnableVBlank(TRUE);
    VDP_EnableDisplay(TRUE);
}

void main()
{
    VDP_SetMode(VDP_MODE_SCREEN5);
    VDP_SetColor(COLOR_BLACK);

    VDP_EnableVBlank(FALSE);
    VDP_EnableDisplay(FALSE);

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

    Display_Init();
    UI_Init();
    Background_Init();
    SpriteScroll_Init();
    Player_Init();
    Bullet_Init();
    Enemy_Init();
    EnemyBullet_Init();
    Explosion_Init();

    UI_ShowTitle();

    VDP_EnableVBlank(TRUE);
    VDP_EnableDisplay(TRUE);

    u8 gameState = GAME_STATE_TITLE;
    u8 previousFrame = g_VBlankCounter;
    while (TRUE)
    {
        u8 enterPressed = Keyboard_IsKeyPressed(KEY_RETURN);
        static u8 wasEnterPressed = FALSE;

        switch(gameState)
        {
        case GAME_STATE_TITLE:
            if(enterPressed && !wasEnterPressed)
            {
                Game_Start();
                gameState = GAME_STATE_PLAY;
            }
            break;

        case GAME_STATE_PLAY:
            Background_Update();
            Display_SetScroll(
                Background_GetScrollOffset()
            );
            Player_Update();
            Bullet_Update();
            Enemy_Update(Player_GetX());        
            EnemyBullet_Update();
            Explosion_Update();
            Collision_Update();

            char scoreText[7];
            if(Score_TakeChanged())
            {
                Score_GetText(scoreText);
                UI_UpdateHUD(scoreText);
            }

            if(Collision_CheckPlayerEnemy() ||
                Collision_CheckPlayerEnemyBullet())
            {
                Score_GetText(scoreText);

                VDP_EnableVBlank(FALSE);
                VDP_EnableDisplay(FALSE);

                Display_StopHUD();

                UI_ShowGameOver(scoreText);

                gameState = GAME_STATE_GAME_OVER;

                VDP_EnableVBlank(TRUE);
                VDP_EnableDisplay(TRUE);
            }
            break;

        case GAME_STATE_GAME_OVER:
            if(enterPressed && !wasEnterPressed)
            {
                Game_Start();
                gameState = GAME_STATE_PLAY;
            }
            break;
        }

        while(previousFrame == g_VBlankCounter)
        {
            Halt();
        }

        previousFrame = g_VBlankCounter;
        
        wasEnterPressed = enterPressed;
    }
}