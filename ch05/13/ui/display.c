#include "msxgl.h"
#include "vdp.h"
#include "display.h"

#define HUD_HEIGHT      32
#define HUD_IRQ_LINE    (HUD_HEIGHT - 2)

#define GAME_PAGE_R2    0x1F
#define HUD_PAGE_R2     0x3F

#define VDP_STATUS_PORT 0x99
#define VDP_HR_BIT      0x20

__sfr __at(VDP_STATUS_PORT) VDP_ControlPort;

volatile u8 g_VBlankCounter;

static volatile u8 g_HudEnabled;
static volatile u8 g_PlayScroll;

void Display_Init()
{
    g_HudEnabled = FALSE;
    g_PlayScroll = 0;
    g_VBlankCounter = 0;

    VDP_EnableHBlank(FALSE);
    VDP_SetVerticalOffset(0);
    VDP_SetPage(0);
    VDP_EnableSprite(FALSE);
}

void Display_StartHUD()
{
    g_PlayScroll = 0;
    g_HudEnabled = TRUE;
}

void Display_StopHUD()
{
    g_HudEnabled = FALSE;

    VDP_EnableHBlank(FALSE);
    VDP_SetVerticalOffset(0);
    VDP_SetPage(0);
    VDP_EnableSprite(FALSE);
}

void Display_SetScroll(u8 offset)
{
    g_PlayScroll = offset;
}

void VDP_InterruptHandler()
{
    g_VBlankCounter++;

    if(g_HudEnabled)
    {
        VDP_EnableHBlank(FALSE);

        VDP_SetPage(1);
        VDP_SetVerticalOffset(0);
        VDP_EnableSprite(FALSE);

        VDP_SetHBlankLine(HUD_IRQ_LINE);
        VDP_EnableHBlank(TRUE);
    }
    else
    {
        VDP_EnableHBlank(FALSE);

        VDP_SetPage(0);
        VDP_SetVerticalOffset(0);
    }
}

void VDP_HBlankHandler()
{
    /* S#2 선택 */
    VDP_ControlPort = 2;
    VDP_ControlPort = 0x8F;

    /* 실제 화면 표시 구간이 시작될 때까지 대기 */
    while(VDP_ControlPort & VDP_HR_BIT)
    {
    }

    /* 해당 라인의 표시가 끝날 때까지 대기 */
    while(!(VDP_ControlPort & VDP_HR_BIT))
    {
    }

    /* R#2: 게임 페이지 선택 */
    VDP_ControlPort = GAME_PAGE_R2;
    VDP_ControlPort = 0x82;

    /* R#23: 게임 스크롤 적용 */
    VDP_ControlPort = g_PlayScroll;
    VDP_ControlPort = 0x97;

    /* 상태 레지스터 선택을 S#0으로 복원 */
    VDP_ControlPort = 0;
    VDP_ControlPort = 0x8F;

    /* 라인 인터럽트 비활성화 */
    VDP_EnableHBlank(FALSE);

    /* 게임 영역의 스프라이트 표시 */
    VDP_EnableSprite(TRUE);
}