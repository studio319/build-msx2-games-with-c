#include "msxgl.h"
#include "psg.h"
#include "sound.h"

#define BGM_NOTE_FRAMES 24
#define BGM_NOTE_COUNT  16

#define SFX_NONE       0
#define SFX_SHOT       1
#define SFX_EXPLOSION  2
#define SFX_HIT        3

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

static u8 g_SfxType;
static u8 g_SfxFrame;

void Sound_PlayShot()
{
    if(g_SfxType != SFX_NONE)
    {
        return;
    }

    g_SfxType = SFX_SHOT;
    g_SfxFrame = 0;

    PSG_EnableTone(PSG_CHANNEL_C, TRUE);
    PSG_EnableNoise(PSG_CHANNEL_C, FALSE);

    PSG_SetTone(PSG_CHANNEL_C, 360);
    PSG_SetVolume(PSG_CHANNEL_C, 9);
}

void Sound_PlayExplosion()
{
    if(g_SfxType >= SFX_EXPLOSION)
    {
        return;
    }

    g_SfxType = SFX_EXPLOSION;
    g_SfxFrame = 0;

    PSG_EnableTone(PSG_CHANNEL_C, TRUE);
    PSG_EnableNoise(PSG_CHANNEL_C, FALSE);

    PSG_SetTone(PSG_CHANNEL_C, 220);
    PSG_SetVolume(PSG_CHANNEL_C, 12);
}

void Sound_PlayHit()
{
    g_SfxType = SFX_HIT;
    g_SfxFrame = 0;

    PSG_EnableTone(PSG_CHANNEL_C, TRUE);
    PSG_EnableNoise(PSG_CHANNEL_C, FALSE);

    PSG_SetTone(PSG_CHANNEL_C, 180);
    PSG_SetVolume(PSG_CHANNEL_C, 15);
}

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

    if(g_SfxType != SFX_NONE)
    {
        if(g_SfxType == SFX_SHOT)
        {
            if(g_SfxFrame == 2)
            {
                PSG_SetTone(PSG_CHANNEL_C, 520);
                PSG_SetVolume(PSG_CHANNEL_C, 5);
            }
            else if(g_SfxFrame >= 5)
            {
                PSG_SetVolume(PSG_CHANNEL_C, 0);
                PSG_EnableTone(PSG_CHANNEL_C, FALSE);

                g_SfxType = SFX_NONE;
            }
        }
        else if(g_SfxType == SFX_EXPLOSION)
        {
            if(g_SfxFrame == 4)
            {
                PSG_SetTone(PSG_CHANNEL_C, 440);
                PSG_SetVolume(PSG_CHANNEL_C, 9);
            }
            else if(g_SfxFrame == 8)
            {
                PSG_SetTone(PSG_CHANNEL_C, 740);
                PSG_SetVolume(PSG_CHANNEL_C, 5);
            }
            else if(g_SfxFrame >= 12)
            {
                PSG_SetVolume(PSG_CHANNEL_C, 0);
                PSG_EnableTone(PSG_CHANNEL_C, FALSE);

                g_SfxType = SFX_NONE;
            }
        }
        else if(g_SfxType == SFX_HIT)
        {
            if(g_SfxFrame == 5)
            {
                PSG_SetTone(PSG_CHANNEL_C, 450);
                PSG_SetVolume(PSG_CHANNEL_C, 12);
            }
            else if(g_SfxFrame == 10)
            {
                PSG_SetTone(PSG_CHANNEL_C, 700);
                PSG_SetVolume(PSG_CHANNEL_C, 9);
            }
            else if(g_SfxFrame == 16)
            {
                PSG_SetTone(PSG_CHANNEL_C, 1100);
                PSG_SetVolume(PSG_CHANNEL_C, 5);
            }
            else if(g_SfxFrame >= 24)
            {
                PSG_SetVolume(PSG_CHANNEL_C, 0);
                PSG_EnableTone(PSG_CHANNEL_C, FALSE);

                g_SfxType = SFX_NONE;
            }
        }

        if(g_SfxType != SFX_NONE)
        {
            g_SfxFrame++;
        }
    }


    PSG_Apply();
}

void Sound_Init()
{
    g_BgmPlaying = FALSE;
    g_BgmStep = 0;
    g_BgmFrame = 0;

    g_SfxType = SFX_NONE;
    g_SfxFrame = 0;
    
    PSG_Mute();
    PSG_Apply();
}

void Sound_Stop()
{
    Sound_Init();
}
