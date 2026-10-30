#include "msxgl.h"
#include "psg.h"
#include "sound.h"

#define LINE_SOUND_TONE1 800
#define LINE_SOUND_TONE2 600
#define LINE_SOUND_TONE3 400

#define LINE_SOUND_VOLUME1 12
#define LINE_SOUND_VOLUME2 9
#define LINE_SOUND_VOLUME3 6

u8 g_LineSoundPlaying = FALSE;
u8 g_LineSoundFrame = 0;

void Sound_Init()
{
    PSG_Mute();
    PSG_Apply();

    g_LineSoundPlaying = FALSE;
    g_LineSoundFrame = 0;
}

void Sound_PlayLineClear()
{
    g_LineSoundPlaying = TRUE;
    g_LineSoundFrame = 0;

    PSG_EnableTone(PSG_CHANNEL_A, TRUE);
    PSG_EnableNoise(PSG_CHANNEL_A, FALSE);
    PSG_SetTone(PSG_CHANNEL_A, LINE_SOUND_TONE1);
    PSG_SetVolume(PSG_CHANNEL_A, LINE_SOUND_VOLUME1);
    PSG_Apply();
}

void Sound_Update()
{
    if (g_LineSoundPlaying)
    {
        if (g_LineSoundFrame == 4)
        {
            PSG_SetTone(PSG_CHANNEL_A, LINE_SOUND_TONE2);
            PSG_SetVolume(PSG_CHANNEL_A, LINE_SOUND_VOLUME2);
            PSG_Apply();
        }
        else if (g_LineSoundFrame == 8)
        {
            PSG_SetTone(PSG_CHANNEL_A, LINE_SOUND_TONE3);
            PSG_SetVolume(PSG_CHANNEL_A, LINE_SOUND_VOLUME3);
            PSG_Apply();
        }
        else if (g_LineSoundFrame >= 12)
        {
            PSG_SetVolume(PSG_CHANNEL_A, 0);
            PSG_EnableTone(PSG_CHANNEL_A, FALSE);
            PSG_Apply();

            g_LineSoundPlaying = FALSE;
        }

        if (g_LineSoundPlaying)
        {
            g_LineSoundFrame++;
        }
    }
}

void Sound_Stop()
{
    PSG_Mute();
    PSG_Apply();

    g_LineSoundPlaying = FALSE;
    g_LineSoundFrame = 0;
}