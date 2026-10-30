#include "msxgl.h"
#include "psg.h"

#define TONE_C4 428
#define TONE_D4 381
#define TONE_E4 339
#define TONE_F4 320
#define TONE_G4 285
#define TONE_A4 254

void WaitFrames(u8 frames)
{
    while(frames > 0)
    {
        Halt();
        frames--;
    }
}

void PlayNote(u16 tone, u8 frames)
{
    PSG_SetTone(PSG_CHANNEL_A, tone);
    PSG_SetVolume(PSG_CHANNEL_A, 12);
    PSG_Apply();

    WaitFrames(frames);

    PSG_SetVolume(PSG_CHANNEL_A, 0);
    PSG_Apply();

    WaitFrames(2);
}

// Program entry point
void main()
{
    VDP_EnableVBlank(TRUE);
    
    PSG_EnableTone(PSG_CHANNEL_A, TRUE);
    PSG_EnableNoise(PSG_CHANNEL_A, FALSE);
    PSG_Apply();

    // 도 도 솔 솔 라 라 솔
    PlayNote(TONE_C4, 20);
    PlayNote(TONE_C4, 20);
    PlayNote(TONE_G4, 20);
    PlayNote(TONE_G4, 20);
    PlayNote(TONE_A4, 20);
    PlayNote(TONE_A4, 20);
    PlayNote(TONE_G4, 40);

    // 파 파 미 미 레 레 도
    PlayNote(TONE_F4, 20);
    PlayNote(TONE_F4, 20);
    PlayNote(TONE_E4, 20);
    PlayNote(TONE_E4, 20);
    PlayNote(TONE_D4, 20);
    PlayNote(TONE_D4, 20);
    PlayNote(TONE_C4, 40);

    // 솔 솔 파 파 미 미 레
    PlayNote(TONE_G4, 20);
    PlayNote(TONE_G4, 20);
    PlayNote(TONE_F4, 20);
    PlayNote(TONE_F4, 20);
    PlayNote(TONE_E4, 20);
    PlayNote(TONE_E4, 20);
    PlayNote(TONE_D4, 40);

    // 솔 솔 파 파 미 미 레
    PlayNote(TONE_G4, 20);
    PlayNote(TONE_G4, 20);
    PlayNote(TONE_F4, 20);
    PlayNote(TONE_F4, 20);
    PlayNote(TONE_E4, 20);
    PlayNote(TONE_E4, 20);
    PlayNote(TONE_D4, 40);

    // 도 도 솔 솔 라 라 솔
    PlayNote(TONE_C4, 20);
    PlayNote(TONE_C4, 20);
    PlayNote(TONE_G4, 20);
    PlayNote(TONE_G4, 20);
    PlayNote(TONE_A4, 20);
    PlayNote(TONE_A4, 20);
    PlayNote(TONE_G4, 40);

    // 파 파 미 미 레 레 도
    PlayNote(TONE_F4, 20);
    PlayNote(TONE_F4, 20);
    PlayNote(TONE_E4, 20);
    PlayNote(TONE_E4, 20);
    PlayNote(TONE_D4, 20);
    PlayNote(TONE_D4, 20);
    PlayNote(TONE_C4, 40);

    while (!Keyboard_IsKeyPressed(KEY_ESC))
    {
        Halt();
    }

    BIOS_Exit(0);
}