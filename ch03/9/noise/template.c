#include "msxgl.h"
#include "psg.h"

void WaitFrames(u8 frames)
{
    while(frames > 0)
    {
        Halt();
        frames--;
    }
}

// Program entry point
void main()
{
    VDP_EnableVBlank(TRUE);
    
    PSG_EnableTone(PSG_CHANNEL_A, FALSE);
    PSG_EnableNoise(PSG_CHANNEL_A, TRUE);
    PSG_SetNoise(6);
    PSG_SetVolume(PSG_CHANNEL_A, 15);
    PSG_Apply();

    WaitFrames(30);

    PSG_SetVolume(PSG_CHANNEL_A, 0);
    PSG_Apply();

    while (!Keyboard_IsKeyPressed(KEY_ESC))
    {
        Halt();
    }

    BIOS_Exit(0);
}