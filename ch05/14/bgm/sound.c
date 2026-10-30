#include "msxgl.h"
#include "psg.h"
#include "sound.h"

#define BGM_NOTE_FRAMES 24
#define BGM_NOTE_COUNT  16

static const u16 g_BgmMelody[BGM_NOTE_COUNT] =
{
    254, 214, 170, 214,
    285, 226, 190, 226,
    321, 254, 214, 254,
    339, 269, 226, 269
};

static const u16 g_BgmBass[8] =
{
    508, 678,
    571, 762,
    641, 856,
    678, 1017
};

static u8 g_BgmPlaying;
static u8 g_BgmStep;
static u8 g_BgmFrame;

void Sound_StartBGM()
{
    g_BgmPlaying = TRUE;
    g_BgmStep = 0;
    g_BgmFrame = 0;

    PSG_EnableTone(PSG_CHANNEL_A, TRUE);
    PSG_EnableNoise(PSG_CHANNEL_A, FALSE);

    PSG_EnableTone(PSG_CHANNEL_B, TRUE);
    PSG_EnableNoise(PSG_CHANNEL_B, FALSE);

    PSG_SetVolume(PSG_CHANNEL_A, 8);
    PSG_SetVolume(PSG_CHANNEL_B, 6);
}

void Sound_StopBGM()
{
    g_BgmPlaying = FALSE;

    PSG_SetVolume(PSG_CHANNEL_A, 0);
    PSG_SetVolume(PSG_CHANNEL_B, 0);

    PSG_EnableTone(PSG_CHANNEL_A, FALSE);
    PSG_EnableTone(PSG_CHANNEL_B, FALSE);
}

void Sound_Update()
{
    if(g_BgmPlaying)
    {
        if(g_BgmFrame == 0)
        {
            PSG_SetTone(
                PSG_CHANNEL_A, 
                g_BgmMelody[g_BgmStep]
            );

            if((g_BgmStep & 1) == 0)
            {
                PSG_SetTone(
                    PSG_CHANNEL_B, 
                    g_BgmBass[g_BgmStep >> 1]
                );
            }
        }

        g_BgmFrame++;

        if(g_BgmFrame >= BGM_NOTE_FRAMES)
        {
            g_BgmFrame = 0;
            g_BgmStep++;

            if(g_BgmStep >= BGM_NOTE_COUNT)
            {
                g_BgmStep = 0;
            }
        }
    }

    PSG_Apply();
}

void Sound_Init()
{
    g_BgmPlaying = FALSE;
    g_BgmStep = 0;
    g_BgmFrame = 0;

    PSG_Mute();
    PSG_Apply();
}

void Sound_Stop()
{
    Sound_Init();
}