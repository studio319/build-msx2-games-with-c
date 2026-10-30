#include "msxgl.h"
#include "psg.h"

#define TONE_C4 428
#define TONE_D4 381
#define TONE_E4 339
#define TONE_F4 320
#define TONE_G4 285
#define TONE_A4 254
#define NOTE_COUNT 7

const u16 g_Melody[NOTE_COUNT] =
{
    TONE_C4,
    TONE_C4,
    TONE_G4,
    TONE_G4,
    TONE_A4,
    TONE_A4,
    TONE_G4
};
const u8 g_Duration[NOTE_COUNT] =
{
    20,
    20,
    20,
    20,
    20,
    20,
    40
};

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

    u8 i;
    for(i = 0; i < NOTE_COUNT; i++)
    {
        PlayNote(g_Melody[i], g_Duration[i]);
    }

    while (!Keyboard_IsKeyPressed(KEY_ESC))
    {
        Halt();
    }

    BIOS_Exit(0);
}