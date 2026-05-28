#include "global.h"
#include "option_menu.h"
#include "bg.h"
#include "gpu_regs.h"
#include "heat_start_menu.h"
#include "international_string_util.h"
#include "list_menu.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "gba/m4a_internal.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define tMenuSelection       data[0]
#define tTextSpeed           data[1]
#define tBattleSceneOff      data[3]
#define tBattleStyle         data[4]
#define tTrainerBattleMode   data[5]
#define tSound               data[6]
#define tButtonMode          data[7]
#define tWindowFrameType     data[8]
#define tStartMenuPalette    data[9]
#define tTopOption           data[10]
#define tArrowTaskId         data[11]

enum
{
    MENUITEM_TEXTSPEED,
    MENUITEM_BATTLESCENE,
    MENUITEM_BATTLESTYLE,
    MENUITEM_TRAINERBATTLEMODE,
    MENUITEM_SOUND,
    MENUITEM_BUTTONMODE,
    MENUITEM_FRAMETYPE,
    MENUITEM_STARTMENUCOLOR,
    MENUITEM_CANCEL,
    MENUITEM_COUNT,
};

enum
{
    WIN_TOP,
    WIN_OPTIONS,
    WIN_DESCRIPTION,
};

#define Y_DIFF 16
#define OPTIONS_ON_SCREEN 5
#define CHOICE_LEFT_X 104
#define CHOICE_RIGHT_EDGE 198

#define TEXT_COLOR_OPTIONS_WHITE             1
#define TEXT_COLOR_OPTIONS_GRAY_FG           2
#define TEXT_COLOR_OPTIONS_GRAY_SHADOW       3
#define TEXT_COLOR_OPTIONS_GRAY_LIGHT_FG     4
#define TEXT_COLOR_OPTIONS_ORANGE_FG         5
#define TEXT_COLOR_OPTIONS_ORANGE_SHADOW     6
#define TEXT_COLOR_OPTIONS_RED_FG            8
#define TEXT_COLOR_OPTIONS_RED_SHADOW        7
#define TEXT_COLOR_OPTIONS_RED_DARK_FG       14
#define TEXT_COLOR_OPTIONS_RED_DARK_SHADOW   13

#define TILE_TOP_CORNER_L 0x1A2
#define TILE_TOP_EDGE     0x1A3
#define TILE_TOP_CORNER_R 0x1A4
#define TILE_LEFT_EDGE    0x1A5
#define TILE_RIGHT_EDGE   0x1A7
#define TILE_BOT_CORNER_L 0x1A8
#define TILE_BOT_EDGE     0x1A9
#define TILE_BOT_CORNER_R 0x1AA

static void MainCB2(void);
static void VBlankCB(void);
static void Task_OptionMenuFadeIn(u8 taskId);
static void Task_OptionMenuProcessInput(u8 taskId);
static void Task_OptionMenuSave(u8 taskId);
static void Task_OptionMenuFadeOut(u8 taskId);
static void InitOptionMenuTaskData(u8 taskId);
static void MoveOptionCursor(u8 taskId, s8 delta);
static bool8 ChangeSelection(u8 taskId, s8 delta);
static void DrawTopBar(void);
static void DrawMenu(u8 taskId);
static void DrawDescription(u8 taskId);
static void DrawCursor(u8 taskId);
static void DrawBgWindowFrames(void);
static void RefreshScrollArrows(u8 taskId);
static const u8 *GetOptionDescription(u8 item);
static u8 TextSpeed_ProcessInput(u8 selection, s8 delta);
static u8 SanitizeTextSpeedSelection(u8 selection);
static u8 GetBattleTextSpeedFromTextSpeed(u8 textSpeed);
static u8 BattleScene_ProcessInput(u8 selection, s8 delta);
static u8 SanitizeBattleSceneSelection(u8 selection);
static u8 Toggle_ProcessInput(u8 selection);
static u8 TrainerBattleMode_ProcessInput(u8 selection, s8 delta);
static u8 SanitizeButtonModeSelection(u8 selection);
static u8 SanitizeTrainerBattleModeSelection(u8 selection);
static u8 FrameType_ProcessInput(u8 selection, s8 delta);
static u8 StartMenuPalette_ProcessInput(u8 selection, s8 delta);
static u8 SanitizeStartMenuPaletteSelection(u8 selection);

static const u8 sTextOptionsTitle[] = _("OPTIONS");
static const u8 sTextMid[] = _("MID");
static const u8 sTextFast[] = _("FAST");
static const u8 sTextInstant[] = _("INST");
static const u8 sTextBattleScene1x[] = _("1x");
static const u8 sTextBattleScene2x[] = _("2x");
static const u8 sTextBattleScene3x[] = _("3x");
static const u8 sTextBattleScene4x[] = _("4x");
static const u8 sTextBattleSceneOffPlain[] = _("OFF");
static const u8 sTextShift[] = _("SHIFT");
static const u8 sTextSet[] = _("SET");
static const u8 sTextBattleMode[] = _("BATTLE MODE");
static const u8 sTextMixed[] = _("MIXED");
static const u8 sText1v1[] = _("1v1");
static const u8 sText2v2[] = _("2v2");
static const u8 sTextMono[] = _("MONO");
static const u8 sTextStereo[] = _("STEREO");
static const u8 sTextNormal[] = _("NORMAL");
static const u8 sTextLR[] = _("LR");
static const u8 sTextType[] = _("TYPE");
static const u8 sTextColor[] = _("COLOR");
static const u8 sTextStartMenuColor[] = _("MENU COLOR");
static const u8 sTextSave[] = _("SAVE");

static const u8 sTextDescTextSpeed[] = _("Choose how fast regular text\nprints in dialogue boxes.");
static const u8 sTextDescBattleScene[] = _("Set battle animation speed, or\nturn battle animations off.");
static const u8 sTextDescBattleStyle[] = _("SHIFT asks before switching.\nSET keeps battling without prompts.");
static const u8 sTextDescTrainerBattleMode[] = _("MIXED keeps original battles.\n1v1 or 2v2 force when valid.");
static const u8 sTextDescSound[] = _("Choose MONO or STEREO sound.");
static const u8 sTextDescButtonMode[] = _("NORMAL keeps default controls.\nLR lets L/R act like left/right.");
static const u8 sTextDescFrameType[] = _("Choose the textbox frame style.");
static const u8 sTextDescStartMenuColor[] = _("Choose the Start Menu background\ncolor palette.");
static const u8 sTextDescCancel[] = _("Save options and return.");

static const u8 sTextSpeedOrder[] =
{
    OPTIONS_TEXT_SPEED_MID,
    OPTIONS_TEXT_SPEED_FAST,
    OPTIONS_TEXT_SPEED_INSTANT,
};

static const u8 sBattleSceneOrder[] =
{
    OPTIONS_BATTLE_SCENE_1X,
    OPTIONS_BATTLE_SCENE_2X,
    OPTIONS_BATTLE_SCENE_3X,
    OPTIONS_BATTLE_SCENE_4X,
    OPTIONS_BATTLE_SCENE_OFF,
};

static const u8 *const sOptionMenuItemsNames[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]       = gText_TextSpeed,
    [MENUITEM_BATTLESCENE]     = gText_BattleScene,
    [MENUITEM_BATTLESTYLE]     = gText_BattleStyle,
    [MENUITEM_TRAINERBATTLEMODE] = sTextBattleMode,
    [MENUITEM_SOUND]           = gText_Sound,
    [MENUITEM_BUTTONMODE]      = gText_ButtonMode,
    [MENUITEM_FRAMETYPE]       = gText_Frame,
    [MENUITEM_STARTMENUCOLOR]  = sTextStartMenuColor,
    [MENUITEM_CANCEL]          = sTextSave,
};

static const u16 sOptionMenuBg_Pal[] = {RGB(17, 18, 31)};
static const u16 sOptionMenuText_Pal[] = INCBIN_U16("graphics/interface/option_menu_text_custom.gbapal");
static const u8 sEqualSignGfx[] = INCBIN_U8("graphics/interface/option_menu_equals_sign.4bpp");

static const struct WindowTemplate sOptionMenuWinTemplates[] =
{
    [WIN_TOP] = {
        .bg = 1,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2,
    },
    [WIN_OPTIONS] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 26,
        .height = 10,
        .paletteNum = 1,
        .baseBlock = 62,
    },
    [WIN_DESCRIPTION] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 1,
        .baseBlock = 500,
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sOptionMenuBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
};

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_InitOptionMenu(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sOptionMenuBgTemplates, ARRAY_COUNT(sOptionMenuBgTemplates));
        ResetBgPositions();
        InitWindows(sOptionMenuWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0 | WININ_WIN1_BG0 | WININ_WIN0_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_DARKEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        LoadPalette(sOptionMenuBg_Pal, BG_PLTT_ID(0), sizeof(sOptionMenuBg_Pal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        LoadPalette(sOptionMenuText_Pal, BG_PLTT_ID(1), sizeof(sOptionMenuText_Pal));
        gMain.state++;
        break;
    case 4:
    {
        u8 taskId = CreateTask(Task_OptionMenuFadeIn, 0);

        InitOptionMenuTaskData(taskId);
        PutWindowTilemap(WIN_TOP);
        PutWindowTilemap(WIN_OPTIONS);
        PutWindowTilemap(WIN_DESCRIPTION);
        DrawTopBar();
        DrawMenu(taskId);
        DrawDescription(taskId);
        DrawCursor(taskId);
        DrawBgWindowFrames();
        RefreshScrollArrows(taskId);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        break;
    }
    }
}

static void InitOptionMenuTaskData(u8 taskId)
{
    gTasks[taskId].tMenuSelection = 0;
    gTasks[taskId].tTopOption = 0;
    gTasks[taskId].tTextSpeed = SanitizeTextSpeedSelection(gSaveBlock2Ptr->optionsTextSpeed);
    gTasks[taskId].tBattleSceneOff = SanitizeBattleSceneSelection(gSaveBlock2Ptr->optionsBattleSceneOff);
    gTasks[taskId].tBattleStyle = gSaveBlock2Ptr->optionsBattleStyle;
    gTasks[taskId].tTrainerBattleMode = SanitizeTrainerBattleModeSelection(gSaveBlock2Ptr->optionsTrainerBattleMode);
    gTasks[taskId].tSound = gSaveBlock2Ptr->optionsSound;
    gTasks[taskId].tButtonMode = SanitizeButtonModeSelection(gSaveBlock2Ptr->optionsButtonMode);
    gTasks[taskId].tWindowFrameType = gSaveBlock2Ptr->optionsWindowFrameType;
    gTasks[taskId].tStartMenuPalette = SanitizeStartMenuPaletteSelection(gSaveBlock2Ptr->optionsStartMenuPalette);
    gTasks[taskId].tArrowTaskId = TASK_NONE;
}

static void Task_OptionMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_OptionMenuProcessInput;
}

static void Task_OptionMenuProcessInput(u8 taskId)
{
    if (JOY_NEW(A_BUTTON))
    {
        if (gTasks[taskId].tMenuSelection == MENUITEM_CANCEL)
            gTasks[taskId].func = Task_OptionMenuSave;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        gTasks[taskId].func = Task_OptionMenuSave;
    }
    else if (JOY_NEW(DPAD_UP))
    {
        PlaySE(SE_SELECT);
        MoveOptionCursor(taskId, -1);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        PlaySE(SE_SELECT);
        MoveOptionCursor(taskId, 1);
    }
    else if (JOY_NEW(DPAD_LEFT))
    {
        if (ChangeSelection(taskId, -1))
        {
            PlaySE(SE_SELECT);
            DrawMenu(taskId);
            DrawDescription(taskId);
            DrawCursor(taskId);
        }
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        if (ChangeSelection(taskId, 1))
        {
            PlaySE(SE_SELECT);
            DrawMenu(taskId);
            DrawDescription(taskId);
            DrawCursor(taskId);
        }
    }
}

static void Task_OptionMenuSave(u8 taskId)
{
    gSaveBlock2Ptr->optionsTextSpeed = SanitizeTextSpeedSelection(gTasks[taskId].tTextSpeed);
    gSaveBlock2Ptr->optionsBattleTextSpeed = GetBattleTextSpeedFromTextSpeed(gSaveBlock2Ptr->optionsTextSpeed);
    gSaveBlock2Ptr->optionsBattleSceneOff = SanitizeBattleSceneSelection(gTasks[taskId].tBattleSceneOff);
    gSaveBlock2Ptr->optionsBattleStyle = gTasks[taskId].tBattleStyle;
    gSaveBlock2Ptr->optionsTrainerBattleMode = SanitizeTrainerBattleModeSelection(gTasks[taskId].tTrainerBattleMode);
    gSaveBlock2Ptr->optionsSound = gTasks[taskId].tSound;
    gSaveBlock2Ptr->optionsButtonMode = SanitizeButtonModeSelection(gTasks[taskId].tButtonMode);
    gSaveBlock2Ptr->optionsWindowFrameType = gTasks[taskId].tWindowFrameType;
    gSaveBlock2Ptr->optionsStartMenuPalette = SanitizeStartMenuPaletteSelection(gTasks[taskId].tStartMenuPalette);

    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    gTasks[taskId].func = Task_OptionMenuFadeOut;
}

static void Task_OptionMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        if (gTasks[taskId].tArrowTaskId != TASK_NONE)
            RemoveScrollIndicatorArrowPair(gTasks[taskId].tArrowTaskId);
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}

static void MoveOptionCursor(u8 taskId, s8 delta)
{
    u8 cursor = gTasks[taskId].tMenuSelection;

    if (delta < 0)
        cursor = cursor == 0 ? MENUITEM_COUNT - 1 : cursor - 1;
    else
        cursor = cursor + 1 >= MENUITEM_COUNT ? 0 : cursor + 1;

    gTasks[taskId].tMenuSelection = cursor;

    if (MENUITEM_COUNT > OPTIONS_ON_SCREEN)
    {
        if (cursor < gTasks[taskId].tTopOption)
            gTasks[taskId].tTopOption = cursor;
        else if (cursor >= gTasks[taskId].tTopOption + OPTIONS_ON_SCREEN)
            gTasks[taskId].tTopOption = cursor - OPTIONS_ON_SCREEN + 1;
    }
    else
    {
        gTasks[taskId].tTopOption = 0;
    }

    DrawMenu(taskId);
    DrawDescription(taskId);
    DrawCursor(taskId);
}

static bool8 ChangeSelection(u8 taskId, s8 delta)
{
    u8 previousOption;

    switch (gTasks[taskId].tMenuSelection)
    {
    case MENUITEM_TEXTSPEED:
        previousOption = gTasks[taskId].tTextSpeed;
        gTasks[taskId].tTextSpeed = TextSpeed_ProcessInput(gTasks[taskId].tTextSpeed, delta);
        return previousOption != gTasks[taskId].tTextSpeed;
    case MENUITEM_BATTLESCENE:
        previousOption = gTasks[taskId].tBattleSceneOff;
        gTasks[taskId].tBattleSceneOff = BattleScene_ProcessInput(gTasks[taskId].tBattleSceneOff, delta);
        return previousOption != gTasks[taskId].tBattleSceneOff;
    case MENUITEM_BATTLESTYLE:
        previousOption = gTasks[taskId].tBattleStyle;
        gTasks[taskId].tBattleStyle = Toggle_ProcessInput(gTasks[taskId].tBattleStyle);
        return previousOption != gTasks[taskId].tBattleStyle;
    case MENUITEM_TRAINERBATTLEMODE:
        previousOption = gTasks[taskId].tTrainerBattleMode;
        gTasks[taskId].tTrainerBattleMode = TrainerBattleMode_ProcessInput(gTasks[taskId].tTrainerBattleMode, delta);
        return previousOption != gTasks[taskId].tTrainerBattleMode;
    case MENUITEM_SOUND:
        previousOption = gTasks[taskId].tSound;
        gTasks[taskId].tSound = Toggle_ProcessInput(gTasks[taskId].tSound);
        SetPokemonCryStereo(gTasks[taskId].tSound);
        return previousOption != gTasks[taskId].tSound;
    case MENUITEM_BUTTONMODE:
        previousOption = gTasks[taskId].tButtonMode;
        gTasks[taskId].tButtonMode = Toggle_ProcessInput(gTasks[taskId].tButtonMode);
        return previousOption != gTasks[taskId].tButtonMode;
    case MENUITEM_FRAMETYPE:
        previousOption = gTasks[taskId].tWindowFrameType;
        gTasks[taskId].tWindowFrameType = FrameType_ProcessInput(gTasks[taskId].tWindowFrameType, delta);
        if (previousOption != gTasks[taskId].tWindowFrameType)
            DrawBgWindowFrames();
        return previousOption != gTasks[taskId].tWindowFrameType;
    case MENUITEM_STARTMENUCOLOR:
        previousOption = gTasks[taskId].tStartMenuPalette;
        gTasks[taskId].tStartMenuPalette = StartMenuPalette_ProcessInput(gTasks[taskId].tStartMenuPalette, delta);
        return previousOption != gTasks[taskId].tStartMenuPalette;
    default:
        return FALSE;
    }
}

static void DrawTopBar(void)
{
    const u8 color[3] = {TEXT_DYNAMIC_COLOR_6, TEXT_COLOR_OPTIONS_WHITE, TEXT_COLOR_OPTIONS_GRAY_FG};
    u8 titleX = 120 - GetStringWidth(FONT_SMALL, sTextOptionsTitle, 0) / 2;

    FillWindowPixelBuffer(WIN_TOP, PIXEL_FILL(15));
    AddTextPrinterParameterized3(WIN_TOP, FONT_SMALL, titleX, 1, color, TEXT_SKIP_DRAW, sTextOptionsTitle);
    CopyWindowToVram(WIN_TOP, COPYWIN_FULL);
}

static void DrawOptionName(u8 item, int y)
{
    const u8 colorOrange[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_ORANGE_FG, TEXT_COLOR_OPTIONS_ORANGE_SHADOW};

    AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y, 0, 0, colorOrange, TEXT_SKIP_DRAW, sOptionMenuItemsNames[item]);
}

static void DrawOptionMenuChoice(const u8 *text, u8 x, u8 y, bool8 chosen)
{
    const u8 colorRed[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_RED_FG, TEXT_COLOR_OPTIONS_RED_SHADOW};
    const u8 colorGray[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_GRAY_FG, TEXT_COLOR_OPTIONS_GRAY_SHADOW};

    AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, x, y, 0, 0, chosen ? colorRed : colorGray, TEXT_SKIP_DRAW, text);
}

static void DrawTextSpeedChoices(u8 selection, int y)
{
    selection = SanitizeTextSpeedSelection(selection);
    DrawOptionMenuChoice(sTextMid, CHOICE_LEFT_X, y, selection == OPTIONS_TEXT_SPEED_MID);
    DrawOptionMenuChoice(sTextFast, 138, y, selection == OPTIONS_TEXT_SPEED_FAST);
    DrawOptionMenuChoice(sTextInstant, GetStringRightAlignXOffset(FONT_NORMAL, sTextInstant, CHOICE_RIGHT_EDGE), y, selection == OPTIONS_TEXT_SPEED_INSTANT);
}

static void DrawBattleSceneChoices(u8 selection, int y)
{
    selection = SanitizeBattleSceneSelection(selection);
    DrawOptionMenuChoice(sTextBattleScene1x, 103, y, selection == OPTIONS_BATTLE_SCENE_1X);
    DrawOptionMenuChoice(sTextBattleScene2x, 123, y, selection == OPTIONS_BATTLE_SCENE_2X);
    DrawOptionMenuChoice(sTextBattleScene3x, 143, y, selection == OPTIONS_BATTLE_SCENE_3X);
    DrawOptionMenuChoice(sTextBattleScene4x, 162, y, selection == OPTIONS_BATTLE_SCENE_4X);
    DrawOptionMenuChoice(sTextBattleSceneOffPlain, GetStringRightAlignXOffset(FONT_NORMAL, sTextBattleSceneOffPlain, CHOICE_RIGHT_EDGE), y, selection == OPTIONS_BATTLE_SCENE_OFF);
}

static void DrawTwoChoices(const u8 *left, const u8 *right, u8 selection, int y)
{
    DrawOptionMenuChoice(left, CHOICE_LEFT_X, y, selection == 0);
    DrawOptionMenuChoice(right, GetStringRightAlignXOffset(FONT_NORMAL, right, CHOICE_RIGHT_EDGE), y, selection == 1);
}

static void DrawNumberedChoice(const u8 *label, u8 selection, int y)
{
    u8 text[3];
    u8 n = selection + 1;

    DrawOptionMenuChoice(label, CHOICE_LEFT_X, y, FALSE);
    if (n >= 10)
    {
        text[0] = n / 10 + CHAR_0;
        text[1] = n % 10 + CHAR_0;
        text[2] = EOS;
    }
    else
    {
        text[0] = n % 10 + CHAR_0;
        text[1] = EOS;
    }
    DrawOptionMenuChoice(text, 134, y, TRUE);
}

static void DrawChoices(u8 taskId, u8 item, int y)
{
    switch (item)
    {
    case MENUITEM_TEXTSPEED:
        DrawTextSpeedChoices(gTasks[taskId].tTextSpeed, y);
        break;
    case MENUITEM_BATTLESCENE:
        DrawBattleSceneChoices(gTasks[taskId].tBattleSceneOff, y);
        break;
    case MENUITEM_BATTLESTYLE:
        DrawTwoChoices(sTextShift, sTextSet, gTasks[taskId].tBattleStyle, y);
        break;
    case MENUITEM_TRAINERBATTLEMODE:
        DrawOptionMenuChoice(sTextMixed, 103, y, gTasks[taskId].tTrainerBattleMode == OPTIONS_TRAINER_BATTLE_MODE_MIXED);
        DrawOptionMenuChoice(sText1v1, 147, y, gTasks[taskId].tTrainerBattleMode == OPTIONS_TRAINER_BATTLE_MODE_SINGLE);
        DrawOptionMenuChoice(sText2v2, GetStringRightAlignXOffset(FONT_NORMAL, sText2v2, CHOICE_RIGHT_EDGE), y, gTasks[taskId].tTrainerBattleMode == OPTIONS_TRAINER_BATTLE_MODE_DOUBLE);
        break;
    case MENUITEM_SOUND:
        DrawTwoChoices(sTextMono, sTextStereo, gTasks[taskId].tSound, y);
        break;
    case MENUITEM_BUTTONMODE:
        DrawTwoChoices(sTextNormal, sTextLR, gTasks[taskId].tButtonMode, y);
        break;
    case MENUITEM_FRAMETYPE:
        DrawNumberedChoice(sTextType, gTasks[taskId].tWindowFrameType, y);
        break;
    case MENUITEM_STARTMENUCOLOR:
        DrawNumberedChoice(sTextColor, gTasks[taskId].tStartMenuPalette, y);
        break;
    }
}

static void DrawMenu(u8 taskId)
{
    u8 i;
    u8 first = gTasks[taskId].tTopOption;

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < OPTIONS_ON_SCREEN && first + i < MENUITEM_COUNT; i++)
    {
        u8 item = first + i;
        int y = i * Y_DIFF + 1;
        DrawOptionName(item, y);
        DrawChoices(taskId, item, y);
    }
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

static void DrawDescription(u8 taskId)
{
    const u8 colorGray[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_GRAY_FG, TEXT_COLOR_OPTIONS_GRAY_SHADOW};

    FillWindowPixelBuffer(WIN_DESCRIPTION, PIXEL_FILL(1));
    AddTextPrinterParameterized4(WIN_DESCRIPTION, FONT_NORMAL, 8, 1, 0, 0, colorGray, TEXT_SKIP_DRAW, GetOptionDescription(gTasks[taskId].tMenuSelection));
    CopyWindowToVram(WIN_DESCRIPTION, COPYWIN_FULL);
}

static void DrawCursor(u8 taskId)
{
    u8 cursor = gTasks[taskId].tMenuSelection - gTasks[taskId].tTopOption;

    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(Y_DIFF, 224));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(cursor * Y_DIFF + 24, cursor * Y_DIFF + 40));
}

static void RefreshScrollArrows(u8 taskId)
{
    if (gTasks[taskId].tArrowTaskId != TASK_NONE)
    {
        RemoveScrollIndicatorArrowPair(gTasks[taskId].tArrowTaskId);
        gTasks[taskId].tArrowTaskId = TASK_NONE;
    }

    if (MENUITEM_COUNT > OPTIONS_ON_SCREEN)
        gTasks[taskId].tArrowTaskId = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 120, 20, 110, MENUITEM_COUNT - OPTIONS_ON_SCREEN, 110, 110, (u16 *)&gTasks[taskId].tTopOption);
}

static const u8 *GetOptionDescription(u8 item)
{
    switch (item)
    {
    case MENUITEM_TEXTSPEED:
        return sTextDescTextSpeed;
    case MENUITEM_BATTLESCENE:
        return sTextDescBattleScene;
    case MENUITEM_BATTLESTYLE:
        return sTextDescBattleStyle;
    case MENUITEM_TRAINERBATTLEMODE:
        return sTextDescTrainerBattleMode;
    case MENUITEM_SOUND:
        return sTextDescSound;
    case MENUITEM_BUTTONMODE:
        return sTextDescButtonMode;
    case MENUITEM_FRAMETYPE:
        return sTextDescFrameType;
    case MENUITEM_STARTMENUCOLOR:
        return sTextDescStartMenuColor;
    default:
        return sTextDescCancel;
    }
}

static u8 TextSpeed_ProcessInput(u8 selection, s8 delta)
{
    u8 i;

    selection = SanitizeTextSpeedSelection(selection);
    for (i = 0; i < ARRAY_COUNT(sTextSpeedOrder); i++)
    {
        if (selection == sTextSpeedOrder[i])
            break;
    }

    if (delta > 0)
        i = (i + 1) % ARRAY_COUNT(sTextSpeedOrder);
    else if (i == 0)
        i = ARRAY_COUNT(sTextSpeedOrder) - 1;
    else
        i--;

    return sTextSpeedOrder[i];
}

static u8 SanitizeTextSpeedSelection(u8 selection)
{
    if (selection == OPTIONS_TEXT_SPEED_SLOW || selection > OPTIONS_TEXT_SPEED_INSTANT)
        return OPTIONS_TEXT_SPEED_MID;

    return selection;
}

static u8 GetBattleTextSpeedFromTextSpeed(u8 textSpeed)
{
    textSpeed = SanitizeTextSpeedSelection(textSpeed);
    if (textSpeed == OPTIONS_TEXT_SPEED_MID)
        return OPTIONS_TEXT_SPEED_MID;

    return OPTIONS_TEXT_SPEED_FAST;
}

static u8 BattleScene_ProcessInput(u8 selection, s8 delta)
{
    u8 i;

    selection = SanitizeBattleSceneSelection(selection);
    for (i = 0; i < ARRAY_COUNT(sBattleSceneOrder); i++)
    {
        if (selection == sBattleSceneOrder[i])
            break;
    }

    if (delta > 0)
        i = (i + 1) % ARRAY_COUNT(sBattleSceneOrder);
    else if (i == 0)
        i = ARRAY_COUNT(sBattleSceneOrder) - 1;
    else
        i--;

    return sBattleSceneOrder[i];
}

static u8 SanitizeBattleSceneSelection(u8 selection)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(sBattleSceneOrder); i++)
    {
        if (selection == sBattleSceneOrder[i])
            return selection;
    }

    return OPTIONS_BATTLE_SCENE_1X;
}

static u8 Toggle_ProcessInput(u8 selection)
{
    return selection ^ 1;
}

static u8 TrainerBattleMode_ProcessInput(u8 selection, s8 delta)
{
    selection = SanitizeTrainerBattleModeSelection(selection);

    if (delta > 0)
        selection = (selection + 1) % OPTIONS_TRAINER_BATTLE_MODE_COUNT;
    else if (selection == 0)
        selection = OPTIONS_TRAINER_BATTLE_MODE_COUNT - 1;
    else
        selection--;

    return selection;
}

static u8 SanitizeButtonModeSelection(u8 selection)
{
    if (selection >= OPTIONS_BUTTON_MODE_COUNT)
        return OPTIONS_BUTTON_MODE_NORMAL;

    return selection;
}

static u8 SanitizeTrainerBattleModeSelection(u8 selection)
{
    if (selection >= OPTIONS_TRAINER_BATTLE_MODE_COUNT)
        return OPTIONS_TRAINER_BATTLE_MODE_MIXED;

    return selection;
}

static u8 FrameType_ProcessInput(u8 selection, s8 delta)
{
    if (delta > 0)
    {
        if (selection < WINDOW_FRAMES_COUNT - 1)
            selection++;
        else
            selection = 0;
    }
    else
    {
        if (selection != 0)
            selection--;
        else
            selection = WINDOW_FRAMES_COUNT - 1;
    }

    LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
    LoadPalette(GetWindowFrameTilesPal(selection)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
    return selection;
}

static u8 StartMenuPalette_ProcessInput(u8 selection, s8 delta)
{
    selection = SanitizeStartMenuPaletteSelection(selection);

    if (delta > 0)
        selection = (selection + 1) % MENU_PAL_COUNT;
    else if (selection == 0)
        selection = MENU_PAL_COUNT - 1;
    else
        selection--;

    return selection;
}

static u8 SanitizeStartMenuPaletteSelection(u8 selection)
{
    if (selection >= MENU_PAL_COUNT)
        return DEFAULT_START_MENU_PALETTE;

    return selection;
}

static void DrawBgWindowFrames(void)
{
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  2,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  2, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  2,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  3,  1, 16,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  3,  1, 16,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 13,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 13, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 13,  1,  1,  7);

    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1, 14,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2, 14, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28, 14,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1, 15,  1,  4,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28, 15,  1,  4,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 19,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 19, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 19,  1,  1,  7);

    CopyBgTilemapBufferToVram(1);
}
