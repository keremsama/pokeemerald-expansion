#include "global.h"
#include "main.h"
#include "bg.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "item.h"
#include "malloc.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "pokedex.h"
#include "randomizer.h"
#include "randomizer_nuzlocke_menu.h"
#include "scanline_effect.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/items.h"
#include "constants/party_menu.h"
#include "constants/region_map_sections.h"
#include "constants/rgb.h"
#include "constants/songs.h"

enum
{
    WIN_TOP,
    WIN_OPTIONS,
    WIN_DESCRIPTION,
};

enum
{
    PAGE_RANDOMIZER,
    PAGE_NUZLOCKE,
    PAGE_COUNT,
};

enum
{
    RANDOMIZER_ENABLED,
    RANDOMIZER_WILD,
    RANDOMIZER_STARTER,
    RANDOMIZER_TRAINER,
    RANDOMIZER_TYPE_THEMED,
    RANDOMIZER_STATIC,
    RANDOMIZER_EGG,
    RANDOMIZER_ABILITIES,
    RANDOMIZER_FIELD_ITEMS,
    RANDOMIZER_SPECIES_MODE,
    RANDOMIZER_SAVE,
    RANDOMIZER_COUNT,
};

enum
{
    NUZLOCKE_MODE,
    NUZLOCKE_SPECIES_CLAUSE,
    NUZLOCKE_SHINY_CLAUSE,
    NUZLOCKE_NICKNAMING,
    NUZLOCKE_DELETION,
    NUZLOCKE_SAVE,
    NUZLOCKE_COUNT,
};

enum
{
    NUZLOCKE_MODE_OFF,
    NUZLOCKE_MODE_EASY,
    NUZLOCKE_MODE_NORMAL,
    NUZLOCKE_MODE_HARD,
};

struct RandomizerNuzlockeMenu
{
    u8 page;
    u8 cursor[PAGE_COUNT];
    u8 top[PAGE_COUNT];
    u8 randomizer[RANDOMIZER_COUNT];
    u8 nuzlocke[NUZLOCKE_COUNT];
    u8 arrowTaskId;
};

static EWRAM_DATA struct RandomizerNuzlockeMenu *sMenu = NULL;

static EWRAM_DATA u8 sPendingRandomizer[RANDOMIZER_COUNT] = {0};
static EWRAM_DATA u8 sPendingNuzlocke[NUZLOCKE_COUNT] = {0};
static EWRAM_DATA bool8 sPendingSettingsInitialized = FALSE;

static void MainCB2(void);
static void VBlankCB(void);
static void InitPendingSettings(void);
static void Task_FadeIn(u8 taskId);
static void Task_ProcessInput(u8 taskId);
static void Task_FadeOut(u8 taskId);
static void DrawTopBar(void);
static void DrawMenu(void);
static void DrawDescription(void);
static void DrawCursor(void);
static void DrawBgWindowFrames(void);
static void SaveSelections(void);
static u8 GetCurrentPageItemCount(void);
static bool8 CurrentItemIsSave(void);
static bool8 IsCurrentItemActive(u8 cursor);
static const u8 *GetCurrentItemDescription(void);
static void ChangeSelection(s8 delta);
static void RefreshScrollArrows(void);
static u16 GetNuzlockeMapSecId(u16 mapsec);
static u16 GetSpeciesFamilyBase(u16 species);
static bool8 IsSpeciesFamilyCaught(u16 species);

static void InitPendingSettings(void)
{
    if (sPendingSettingsInitialized)
        return;

    sPendingNuzlocke[NUZLOCKE_SPECIES_CLAUSE] = TRUE;
    sPendingNuzlocke[NUZLOCKE_SHINY_CLAUSE] = TRUE;
    sPendingNuzlocke[NUZLOCKE_NICKNAMING] = TRUE;
    sPendingSettingsInitialized = TRUE;
}

static const struct WindowTemplate sWinTemplates[] =
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

static const struct BgTemplate sBgTemplates[] =
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

static const u16 sBgPal[] = {RGB(17, 18, 31)};
static const u16 sTextPal[] = INCBIN_U16("graphics/interface/option_menu_text_custom.gbapal");

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

static const u8 sTextTopPrevious[] = _("{L_BUTTON}PREVIOUS");
static const u8 sTextTopNext[] = _("{R_BUTTON}NEXT");
static const u8 sTextRandomizerTitle[] = _("RANDOMIZER");
static const u8 sTextNuzlockeTitle[] = _("NUZLOCKE");
static const u8 sTextOff[] = _("OFF");
static const u8 sTextOn[] = _("ON");
static const u8 sTextSave[] = _("SAVE");
static const u8 sTextModeEasy[] = _("EASY");
static const u8 sTextModeHard[] = _("HARD");
static const u8 sTextModeNorm[] = _("NORM");
static const u8 sTextFaintCemetery[] = _("CEMETERY");
static const u8 sTextFaintRelease[] = _("RELEASE");

static const u8 sTextRandomizer[] = _("RANDOMIZER");
static const u8 sTextWild[] = _("WILD POKEMON");
static const u8 sTextStarter[] = _("STARTER POKEMON");
static const u8 sTextTrainer[] = _("TRAINER");
static const u8 sTextTypeThemed[] = _("TYPE THEMED");
static const u8 sTextStatic[] = _("STATIC POKEMON");
static const u8 sTextEgg[] = _("EGG POKEMON");
static const u8 sTextAbilities[] = _("ABILITIES");
static const u8 sTextFieldItems[] = _("FIELD ITEMS");
static const u8 sTextSpeciesMode[] = _("SPECIES MODE");

static const u8 sTextNuzlocke[] = _("NUZLOCKE");
static const u8 sTextSpeciesClause[] = _("DUPES CLAUSE");
static const u8 sTextShinyClause[] = _("SHINY CLAUSE");
static const u8 sTextNicknaming[] = _("NICKNAMES");
static const u8 sTextDeletion[] = _("FAINTING");

static const u8 sTextSpeciesRandom[] = _("RANDOM");
static const u8 sTextSpeciesLegend[] = _("LEGEND");
static const u8 sTextSpeciesBst[] = _("BST");
static const u8 sTextSpeciesEvolution[] = _("EVOLVE");

static const u8 *const sRandomizerNames[RANDOMIZER_COUNT] =
{
    [RANDOMIZER_ENABLED] = sTextRandomizer,
    [RANDOMIZER_WILD] = sTextWild,
    [RANDOMIZER_STARTER] = sTextStarter,
    [RANDOMIZER_TRAINER] = sTextTrainer,
    [RANDOMIZER_TYPE_THEMED] = sTextTypeThemed,
    [RANDOMIZER_STATIC] = sTextStatic,
    [RANDOMIZER_EGG] = sTextEgg,
    [RANDOMIZER_ABILITIES] = sTextAbilities,
    [RANDOMIZER_FIELD_ITEMS] = sTextFieldItems,
    [RANDOMIZER_SPECIES_MODE] = sTextSpeciesMode,
    [RANDOMIZER_SAVE] = sTextSave,
};

static const u8 *const sNuzlockeNames[NUZLOCKE_COUNT] =
{
    [NUZLOCKE_MODE] = sTextNuzlocke,
    [NUZLOCKE_SPECIES_CLAUSE] = sTextSpeciesClause,
    [NUZLOCKE_SHINY_CLAUSE] = sTextShinyClause,
    [NUZLOCKE_NICKNAMING] = sTextNicknaming,
    [NUZLOCKE_DELETION] = sTextDeletion,
    [NUZLOCKE_SAVE] = sTextSave,
};

static const u8 *const sSpeciesModeTexts[] =
{
    [MON_RANDOM] = sTextSpeciesRandom,
    [MON_RANDOM_LEGEND_AWARE] = sTextSpeciesLegend,
    [MON_RANDOM_BST] = sTextSpeciesBst,
    [MON_EVOLUTION] = sTextSpeciesEvolution,
};

static const u8 sTextDescDisabledRandomizer[] = _("Only usable when RANDOMIZER is ON.");
static const u8 sTextDescDisabledNuzlocke[] = _("Only usable with NUZLOCKE\nenabled.");
static const u8 sTextDescDisabledTrainer[] = _("Only usable with random TRAINER\nPOKEMON.");
static const u8 sTextDescSave[] = _("Save choices and continue...");

static const u8 sTextDescRandomizerOff[] = _("Game will not be randomized.");
static const u8 sTextDescRandomizerOn[] = _("Play the game randomized.\nSettings below!");
static const u8 sTextDescWildOff[] = _("Same wild encounters as in the\nbase game.");
static const u8 sTextDescWildOn[] = _("Randomize wild POKEMON.");
static const u8 sTextDescStarterOff[] = _("Standard starter POKEMON.");
static const u8 sTextDescStarterOn[] = _("Randomize starter POKEMON.");
static const u8 sTextDescTrainerOff[] = _("Trainers will have their expected\nparties.");
static const u8 sTextDescTrainerOn[] = _("Randomize enemy trainer parties.");
static const u8 sTextDescTypeThemedOff[] = _("Important battles are fully\nrandomized.");
static const u8 sTextDescTypeThemedOn[] = _("Gyms, Elite Four and Champion\nkeep their POKEMON type themes.");
static const u8 sTextDescStaticOff[] = _("Static encounters stay the same.");
static const u8 sTextDescStaticOn[] = _("Randomize static encounters.");
static const u8 sTextDescEggOff[] = _("Egg POKEMON stay the same.");
static const u8 sTextDescEggOn[] = _("Randomize Egg POKEMON.");
static const u8 sTextDescAbilitiesOff[] = _("POKEMON abilities stay the same.");
static const u8 sTextDescAbilitiesOn[] = _("Randomize POKEMON abilities.");
static const u8 sTextDescItemsOff[] = _("Field items stay the same.");
static const u8 sTextDescItemsOn[] = _("Randomize field items.");
static const u8 sTextDescSpeciesRandom[] = _("Random replacements can be any\nvalid POKEMON.");
static const u8 sTextDescSpeciesLegend[] = _("Legendary status is respected\nwhen replacing species.");
static const u8 sTextDescSpeciesBst[] = _("Replacements are picked near the\nsame base stat total.");
static const u8 sTextDescSpeciesEvolution[] = _("Species are replaced by members\nof evolution families.");

static const u8 sTextDescNuzlockeOff[] = _("Nuzlocke mode is disabled.");
static const u8 sTextDescNuzlockeEasy[] = _("Fainted POKEMON can't be used\nanymore.");
static const u8 sTextDescNuzlockeNormal[] = _("One catch per route! Fainted\nPOKEMON can't be used anymore.");
static const u8 sTextDescNuzlockeHard[] = _("Same rules as NORMAL with\nhardcore mode enabled.");
static const u8 sTextDescSpeciesClauseOff[] = _("Only the first POKEMON per area\ncan be caught.");
static const u8 sTextDescSpeciesClauseOn[] = _("Already caught evolution lines\nwill not count as first encounter.");
static const u8 sTextDescShinyClauseOff[] = _("Shiny POKEMON still follow the\nfirst encounter rule.");
static const u8 sTextDescShinyClauseOn[] = _("Shiny POKEMON can always be\ncaught.");
static const u8 sTextDescNicknamesOff[] = _("Nicknames are optional.");
static const u8 sTextDescNicknamesOn[] = _("Forces a nickname for every\ncaught POKEMON.");
static const u8 sTextDescFaintCemetery[] = _("Fainted POKEMON are sent to the\nPC after battle.");
static const u8 sTextDescFaintRelease[] = _("Fainted POKEMON are released\nafter battle.");

static const u8 *const sRandomizerDescriptions[RANDOMIZER_COUNT][4] =
{
    [RANDOMIZER_ENABLED] = {sTextDescRandomizerOff, sTextDescRandomizerOn},
    [RANDOMIZER_WILD] = {sTextDescWildOff, sTextDescWildOn},
    [RANDOMIZER_STARTER] = {sTextDescStarterOff, sTextDescStarterOn},
    [RANDOMIZER_TRAINER] = {sTextDescTrainerOff, sTextDescTrainerOn},
    [RANDOMIZER_TYPE_THEMED] = {sTextDescTypeThemedOff, sTextDescTypeThemedOn},
    [RANDOMIZER_STATIC] = {sTextDescStaticOff, sTextDescStaticOn},
    [RANDOMIZER_EGG] = {sTextDescEggOff, sTextDescEggOn},
    [RANDOMIZER_ABILITIES] = {sTextDescAbilitiesOff, sTextDescAbilitiesOn},
    [RANDOMIZER_FIELD_ITEMS] = {sTextDescItemsOff, sTextDescItemsOn},
    [RANDOMIZER_SPECIES_MODE] = {sTextDescSpeciesRandom, sTextDescSpeciesLegend, sTextDescSpeciesBst, sTextDescSpeciesEvolution},
    [RANDOMIZER_SAVE] = {sTextDescSave},
};

static const u8 *const sNuzlockeDescriptions[NUZLOCKE_COUNT][4] =
{
    [NUZLOCKE_MODE] = {sTextDescNuzlockeOff, sTextDescNuzlockeEasy, sTextDescNuzlockeNormal, sTextDescNuzlockeHard},
    [NUZLOCKE_SPECIES_CLAUSE] = {sTextDescSpeciesClauseOff, sTextDescSpeciesClauseOn},
    [NUZLOCKE_SHINY_CLAUSE] = {sTextDescShinyClauseOff, sTextDescShinyClauseOn},
    [NUZLOCKE_NICKNAMING] = {sTextDescNicknamesOff, sTextDescNicknamesOn},
    [NUZLOCKE_DELETION] = {sTextDescFaintCemetery, sTextDescFaintRelease},
    [NUZLOCKE_SAVE] = {sTextDescSave},
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

void CB2_InitRandomizerNuzlockeMenu(void)
{
    u8 taskId;

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
        InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
        ResetBgPositions();
        InitWindows(sWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0 | WININ_WIN1_BG0 | WININ_WIN0_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_EFFECT_DARKEN | BLDCNT_TGT1_BG0);
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
        LoadPalette(sBgPal, BG_PLTT_ID(0), sizeof(sBgPal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        LoadPalette(sTextPal, BG_PLTT_ID(1), sizeof(sTextPal));
        InitPendingSettings();
        sMenu = AllocZeroed(sizeof(*sMenu));
        memcpy(sMenu->randomizer, sPendingRandomizer, sizeof(sPendingRandomizer));
        memcpy(sMenu->nuzlocke, sPendingNuzlocke, sizeof(sPendingNuzlocke));
        sMenu->arrowTaskId = TASK_NONE;
        gMain.state++;
        break;
    case 4:
        PutWindowTilemap(WIN_TOP);
        PutWindowTilemap(WIN_OPTIONS);
        PutWindowTilemap(WIN_DESCRIPTION);
        DrawTopBar();
        DrawMenu();
        DrawDescription();
        DrawCursor();
        DrawBgWindowFrames();
        RefreshScrollArrows();
        CopyWindowToVram(WIN_TOP, COPYWIN_FULL);
        CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
        CopyWindowToVram(WIN_DESCRIPTION, COPYWIN_FULL);
        taskId = CreateTask(Task_FadeIn, 0);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        gTasks[taskId].data[0] = 0;
        break;
    }
}

static void Task_FadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_ProcessInput;
}

static void Task_ProcessInput(u8 taskId)
{
    if (JOY_NEW(A_BUTTON) && CurrentItemIsSave())
    {
        PlaySE(SE_SELECT);
        SaveSelections();
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
        gTasks[taskId].func = Task_FadeOut;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        SaveSelections();
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
        gTasks[taskId].func = Task_FadeOut;
    }
    else if (JOY_NEW(R_BUTTON) && sMenu->page != PAGE_NUZLOCKE)
    {
        PlaySE(SE_SELECT);
        sMenu->page = PAGE_NUZLOCKE;
        DrawTopBar();
        DrawMenu();
        DrawDescription();
        DrawCursor();
        RefreshScrollArrows();
    }
    else if (JOY_NEW(L_BUTTON) && sMenu->page != PAGE_RANDOMIZER)
    {
        PlaySE(SE_SELECT);
        sMenu->page = PAGE_RANDOMIZER;
        DrawTopBar();
        DrawMenu();
        DrawDescription();
        DrawCursor();
        RefreshScrollArrows();
    }
    else if (JOY_NEW(DPAD_UP))
    {
        u8 count = GetCurrentPageItemCount();
        PlaySE(SE_SELECT);
        if (sMenu->cursor[sMenu->page] == 0)
            sMenu->cursor[sMenu->page] = count - 1;
        else
            sMenu->cursor[sMenu->page]--;
        if (count > OPTIONS_ON_SCREEN)
        {
            if (sMenu->cursor[sMenu->page] < sMenu->top[sMenu->page])
                sMenu->top[sMenu->page] = sMenu->cursor[sMenu->page];
            else if (sMenu->cursor[sMenu->page] >= sMenu->top[sMenu->page] + OPTIONS_ON_SCREEN)
                sMenu->top[sMenu->page] = count - OPTIONS_ON_SCREEN;
        }
        else
        {
            sMenu->top[sMenu->page] = 0;
        }
        DrawMenu();
        DrawDescription();
        DrawCursor();
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        u8 count = GetCurrentPageItemCount();
        PlaySE(SE_SELECT);
        sMenu->cursor[sMenu->page]++;
        if (sMenu->cursor[sMenu->page] >= count)
            sMenu->cursor[sMenu->page] = 0;
        if (count > OPTIONS_ON_SCREEN)
        {
            if (sMenu->cursor[sMenu->page] < sMenu->top[sMenu->page])
                sMenu->top[sMenu->page] = 0;
            else if (sMenu->cursor[sMenu->page] >= sMenu->top[sMenu->page] + OPTIONS_ON_SCREEN)
                sMenu->top[sMenu->page] = sMenu->cursor[sMenu->page] - OPTIONS_ON_SCREEN + 1;
        }
        else
        {
            sMenu->top[sMenu->page] = 0;
        }
        DrawMenu();
        DrawDescription();
        DrawCursor();
    }
    else if (JOY_NEW(DPAD_LEFT))
    {
        ChangeSelection(-1);
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        ChangeSelection(1);
    }
}

static void Task_FadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        if (sMenu->arrowTaskId != TASK_NONE)
            RemoveScrollIndicatorArrowPair(sMenu->arrowTaskId);
        FreeAllWindowBuffers();
        FREE_AND_SET_NULL(sMenu);
        SetMainCallback2(gMain.savedCallback);
    }
}

static void DrawTopBar(void)
{
    const u8 color[3] = {TEXT_DYNAMIC_COLOR_6, TEXT_COLOR_WHITE, TEXT_COLOR_OPTIONS_GRAY_FG};
    const u8 *title = sMenu->page == PAGE_RANDOMIZER ? sTextRandomizerTitle : sTextNuzlockeTitle;
    u8 titleX = 120 - GetStringWidth(FONT_SMALL, title, 0) / 2;
    u8 rightX = 240 - GetStringWidth(FONT_SMALL, sTextTopNext, 0) - 5;

    FillWindowPixelBuffer(WIN_TOP, PIXEL_FILL(15));
    if (sMenu->page == PAGE_NUZLOCKE)
        AddTextPrinterParameterized3(WIN_TOP, FONT_SMALL, 5, 1, color, TEXT_SKIP_DRAW, sTextTopPrevious);
    AddTextPrinterParameterized3(WIN_TOP, FONT_SMALL, titleX, 1, color, TEXT_SKIP_DRAW, title);
    if (sMenu->page == PAGE_RANDOMIZER)
        AddTextPrinterParameterized3(WIN_TOP, FONT_SMALL, rightX, 1, color, TEXT_SKIP_DRAW, sTextTopNext);
    CopyWindowToVram(WIN_TOP, COPYWIN_FULL);
}

static void DrawOptionName(u8 item, int y)
{
    const u8 colorOrange[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_ORANGE_FG, TEXT_COLOR_OPTIONS_ORANGE_SHADOW};
    const u8 colorGray[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_GRAY_LIGHT_FG, TEXT_COLOR_OPTIONS_GRAY_SHADOW};
    const u8 *text = sMenu->page == PAGE_RANDOMIZER ? sRandomizerNames[item] : sNuzlockeNames[item];
    const u8 *const color = IsCurrentItemActive(item) ? colorOrange : colorGray;

    AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y, 0, 0, color, TEXT_SKIP_DRAW, text);
}

static void DrawOptionChoice(const u8 *text, int x, int y, bool8 chosen, bool8 active)
{
    const u8 colorRed[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_RED_FG, TEXT_COLOR_OPTIONS_RED_SHADOW};
    const u8 colorGray[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_GRAY_FG, TEXT_COLOR_OPTIONS_GRAY_SHADOW};
    const u8 colorRedDark[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_RED_DARK_FG, TEXT_COLOR_OPTIONS_RED_DARK_SHADOW};
    const u8 colorGrayLight[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_GRAY_LIGHT_FG, TEXT_COLOR_OPTIONS_GRAY_SHADOW};
    const u8 *const color = chosen
        ? (active ? colorRed : colorRedDark)
        : (active ? colorGray : colorGrayLight);

    AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, x, y, 0, 0, color, TEXT_SKIP_DRAW, text);
}

static void DrawOptionChoiceSmall(const u8 *text, int x, int y, bool8 chosen, bool8 active)
{
    const u8 colorRed[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_RED_FG, TEXT_COLOR_OPTIONS_RED_SHADOW};
    const u8 colorGray[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_GRAY_FG, TEXT_COLOR_OPTIONS_GRAY_SHADOW};
    const u8 colorRedDark[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_RED_DARK_FG, TEXT_COLOR_OPTIONS_RED_DARK_SHADOW};
    const u8 colorGrayLight[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_GRAY_LIGHT_FG, TEXT_COLOR_OPTIONS_GRAY_SHADOW};
    const u8 *const color = chosen
        ? (active ? colorRed : colorRedDark)
        : (active ? colorGray : colorGrayLight);

    AddTextPrinterParameterized4(WIN_OPTIONS, FONT_SMALL, x, y, 0, 0, color, TEXT_SKIP_DRAW, text);
}

static void DrawTwoChoices(const u8 *left, const u8 *right, u8 selection, int y, bool8 active)
{
    DrawOptionChoice(left, CHOICE_LEFT_X, y, selection == 0, active);
    DrawOptionChoice(right, GetStringRightAlignXOffset(FONT_NORMAL, right, CHOICE_RIGHT_EDGE), y, selection == 1, active);
}

static void DrawOnOffChoices(u8 selection, int y, bool8 active)
{
    DrawTwoChoices(sTextOff, sTextOn, selection, y, active);
}

static void DrawOffRandomChoices(u8 selection, int y, bool8 active)
{
    DrawTwoChoices(sTextOff, sTextSpeciesRandom, selection, y, active);
}

static void DrawNuzlockeModeChoices(u8 selection, int y, bool8 active)
{
    DrawOptionChoiceSmall(sTextOff, CHOICE_LEFT_X, y + 2, selection == NUZLOCKE_MODE_OFF, active);
    DrawOptionChoiceSmall(sTextModeEasy, 128, y + 2, selection == NUZLOCKE_MODE_EASY, active);
    DrawOptionChoiceSmall(sTextModeNorm, 156, y + 2, selection == NUZLOCKE_MODE_NORMAL, active);
    DrawOptionChoiceSmall(sTextModeHard, GetStringRightAlignXOffset(FONT_SMALL, sTextModeHard, 206), y + 2, selection == NUZLOCKE_MODE_HARD, active);
}

static void DrawNuzlockeOnOffChoices(u8 selection, int y, bool8 active)
{
    DrawOptionChoice(sTextOn, CHOICE_LEFT_X, y, selection == TRUE, active);
    DrawOptionChoice(sTextOff, GetStringRightAlignXOffset(FONT_NORMAL, sTextOff, CHOICE_RIGHT_EDGE), y, selection == FALSE, active);
}

static void DrawFaintingChoices(u8 selection, int y, bool8 active)
{
    DrawOptionChoice(sTextFaintCemetery, CHOICE_LEFT_X, y, selection == FALSE, active);
    DrawOptionChoice(sTextFaintRelease, GetStringRightAlignXOffset(FONT_NORMAL, sTextFaintRelease, CHOICE_RIGHT_EDGE), y, selection == TRUE, active);
}

static void DrawChoices(u8 item, int y)
{
    bool8 active = IsCurrentItemActive(item);

    if (sMenu->page == PAGE_RANDOMIZER)
    {
        if (item == RANDOMIZER_SAVE)
            return;
        if (item == RANDOMIZER_ENABLED)
            DrawOnOffChoices(sMenu->randomizer[item], y, active);
        else if (item == RANDOMIZER_SPECIES_MODE)
            DrawOptionChoice(sSpeciesModeTexts[sMenu->randomizer[item]], GetStringRightAlignXOffset(FONT_NORMAL, sSpeciesModeTexts[sMenu->randomizer[item]], CHOICE_RIGHT_EDGE), y, TRUE, active);
        else if (item == RANDOMIZER_TYPE_THEMED)
            DrawOnOffChoices(sMenu->randomizer[item], y, active);
        else
            DrawOffRandomChoices(sMenu->randomizer[item], y, active);
    }
    else
    {
        if (item == NUZLOCKE_SAVE)
            return;
        if (item == NUZLOCKE_MODE)
            DrawNuzlockeModeChoices(sMenu->nuzlocke[item], y, active);
        else if (item == NUZLOCKE_DELETION)
            DrawFaintingChoices(sMenu->nuzlocke[item], y, active);
        else
            DrawNuzlockeOnOffChoices(sMenu->nuzlocke[item], y, active);
    }
}

static void DrawMenu(void)
{
    u8 i;
    u8 count = GetCurrentPageItemCount();
    u8 first = sMenu->top[sMenu->page];

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < OPTIONS_ON_SCREEN && first + i < count; i++)
    {
        u8 item = first + i;
        int y = i * Y_DIFF + 1;
        DrawOptionName(item, y);
        DrawChoices(item, y);
    }
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

static void DrawDescription(void)
{
    const u8 colorGray[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_GRAY_FG, TEXT_COLOR_OPTIONS_GRAY_SHADOW};

    FillWindowPixelBuffer(WIN_DESCRIPTION, PIXEL_FILL(1));
    AddTextPrinterParameterized4(WIN_DESCRIPTION, FONT_NORMAL, 8, 1, 0, 0, colorGray, TEXT_SKIP_DRAW, GetCurrentItemDescription());
    CopyWindowToVram(WIN_DESCRIPTION, COPYWIN_FULL);
}

static void DrawCursor(void)
{
    u8 cursor = sMenu->cursor[sMenu->page] - sMenu->top[sMenu->page];

    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(Y_DIFF, 224));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(cursor * Y_DIFF + 24, cursor * Y_DIFF + 40));
}

static u8 GetCurrentPageItemCount(void)
{
    return sMenu->page == PAGE_RANDOMIZER ? RANDOMIZER_COUNT : NUZLOCKE_COUNT;
}

static bool8 CurrentItemIsSave(void)
{
    if (sMenu->page == PAGE_RANDOMIZER)
        return sMenu->cursor[PAGE_RANDOMIZER] == RANDOMIZER_SAVE;
    else
        return sMenu->cursor[PAGE_NUZLOCKE] == NUZLOCKE_SAVE;
}

static bool8 IsCurrentItemActive(u8 cursor)
{
    if (sMenu->page == PAGE_RANDOMIZER)
    {
        if (cursor == RANDOMIZER_ENABLED || cursor == RANDOMIZER_SAVE)
            return TRUE;
        if (!sMenu->randomizer[RANDOMIZER_ENABLED])
            return FALSE;
        if (cursor == RANDOMIZER_TYPE_THEMED)
            return sMenu->randomizer[RANDOMIZER_TRAINER];
        return TRUE;
    }
    else
    {
        if (cursor == NUZLOCKE_MODE || cursor == NUZLOCKE_SAVE)
            return TRUE;
        if (cursor == NUZLOCKE_DELETION)
            return sMenu->nuzlocke[NUZLOCKE_MODE] != NUZLOCKE_MODE_OFF;
        return sMenu->nuzlocke[NUZLOCKE_MODE] >= NUZLOCKE_MODE_NORMAL;
    }
}

static const u8 *GetCurrentItemDescription(void)
{
    u8 cursor = sMenu->cursor[sMenu->page];

    if (!IsCurrentItemActive(cursor))
    {
        if (sMenu->page == PAGE_RANDOMIZER && cursor == RANDOMIZER_TYPE_THEMED && sMenu->randomizer[RANDOMIZER_ENABLED])
            return sTextDescDisabledTrainer;
        if (sMenu->page == PAGE_RANDOMIZER)
            return sTextDescDisabledRandomizer;
        return sTextDescDisabledNuzlocke;
    }

    if (sMenu->page == PAGE_RANDOMIZER)
    {
        if (cursor == RANDOMIZER_SPECIES_MODE)
            return sRandomizerDescriptions[cursor][sMenu->randomizer[cursor]];
        return sRandomizerDescriptions[cursor][sMenu->randomizer[cursor] ? 1 : 0];
    }
    else
    {
        if (cursor == NUZLOCKE_MODE)
            return sNuzlockeDescriptions[cursor][sMenu->nuzlocke[cursor]];
        return sNuzlockeDescriptions[cursor][sMenu->nuzlocke[cursor] ? 1 : 0];
    }
}

static void RefreshScrollArrows(void)
{
    if (sMenu->arrowTaskId != TASK_NONE)
    {
        RemoveScrollIndicatorArrowPair(sMenu->arrowTaskId);
        sMenu->arrowTaskId = TASK_NONE;
    }

    if (GetCurrentPageItemCount() > OPTIONS_ON_SCREEN)
        sMenu->arrowTaskId = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 240 / 2, 20, 110, GetCurrentPageItemCount() - 1, 110, 110, 0);
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

static void ChangeSelection(s8 delta)
{
    u8 cursor = sMenu->cursor[sMenu->page];

    if (CurrentItemIsSave() || !IsCurrentItemActive(cursor))
        return;

    PlaySE(SE_SELECT);
    if (sMenu->page == PAGE_RANDOMIZER)
    {
        if (cursor == RANDOMIZER_SPECIES_MODE)
            sMenu->randomizer[cursor] = (sMenu->randomizer[cursor] + MAX_MON_MODE + delta) % MAX_MON_MODE;
        else
            sMenu->randomizer[cursor] ^= 1;
    }
    else
    {
        if (cursor == NUZLOCKE_MODE)
            sMenu->nuzlocke[cursor] = (sMenu->nuzlocke[cursor] + 4 + delta) % 4;
        else
            sMenu->nuzlocke[cursor] ^= 1;
    }
    DrawMenu();
    DrawDescription();
    DrawCursor();
}

static void SaveSelections(void)
{
    memcpy(sPendingRandomizer, sMenu->randomizer, sizeof(sPendingRandomizer));
    memcpy(sPendingNuzlocke, sMenu->nuzlocke, sizeof(sPendingNuzlocke));
}

void ApplyNewGameRandomizerNuzlockeSettings(void)
{
    bool8 randomizerEnabled;

    InitPendingSettings();
    randomizerEnabled = sPendingRandomizer[RANDOMIZER_ENABLED];

    if (randomizerEnabled && sPendingRandomizer[RANDOMIZER_WILD])
        FlagSet(FLAG_RANDOM_WILD_MON);
    else
        FlagClear(FLAG_RANDOM_WILD_MON);

    if (randomizerEnabled && sPendingRandomizer[RANDOMIZER_STARTER])
        FlagSet(FLAG_RANDOM_STARTERS);
    else
        FlagClear(FLAG_RANDOM_STARTERS);

    if (randomizerEnabled && sPendingRandomizer[RANDOMIZER_TRAINER])
        FlagSet(FLAG_RANDOM_TRAINER_MON);
    else
        FlagClear(FLAG_RANDOM_TRAINER_MON);

    if (randomizerEnabled && sPendingRandomizer[RANDOMIZER_TRAINER] && sPendingRandomizer[RANDOMIZER_TYPE_THEMED])
        FlagSet(FLAG_RANDOM_TYPE_THEMED_ARENAS);
    else
        FlagClear(FLAG_RANDOM_TYPE_THEMED_ARENAS);

    if (randomizerEnabled && sPendingRandomizer[RANDOMIZER_STATIC])
        FlagSet(FLAG_RANDOM_FIXED_MON);
    else
        FlagClear(FLAG_RANDOM_FIXED_MON);

    if (randomizerEnabled && sPendingRandomizer[RANDOMIZER_EGG])
        FlagSet(FLAG_RANDOM_EGG_MON);
    else
        FlagClear(FLAG_RANDOM_EGG_MON);

    if (randomizerEnabled && sPendingRandomizer[RANDOMIZER_ABILITIES])
        FlagSet(FLAG_RANDOM_ABILITIES);
    else
        FlagClear(FLAG_RANDOM_ABILITIES);

    if (randomizerEnabled && sPendingRandomizer[RANDOMIZER_FIELD_ITEMS])
        FlagSet(FLAG_RANDOM_FIELD_ITEMS);
    else
        FlagClear(FLAG_RANDOM_FIELD_ITEMS);

    VarSet(VAR_RANDOM_SPECIES_MODE, sPendingRandomizer[RANDOMIZER_SPECIES_MODE]);

    gSaveBlock1Ptr->tx_Nuzlocke_EasyMode = sPendingNuzlocke[NUZLOCKE_MODE] == NUZLOCKE_MODE_EASY;
    gSaveBlock1Ptr->tx_Challenges_Nuzlocke = sPendingNuzlocke[NUZLOCKE_MODE] >= NUZLOCKE_MODE_NORMAL;
    gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore = sPendingNuzlocke[NUZLOCKE_MODE] == NUZLOCKE_MODE_HARD;
    gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause = gSaveBlock1Ptr->tx_Challenges_Nuzlocke && sPendingNuzlocke[NUZLOCKE_SPECIES_CLAUSE];
    gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause = gSaveBlock1Ptr->tx_Challenges_Nuzlocke && sPendingNuzlocke[NUZLOCKE_SHINY_CLAUSE];
    gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming = gSaveBlock1Ptr->tx_Challenges_Nuzlocke && sPendingNuzlocke[NUZLOCKE_NICKNAMING];
    gSaveBlock1Ptr->tx_Nuzlocke_Deletion = sPendingNuzlocke[NUZLOCKE_MODE] != NUZLOCKE_MODE_OFF && sPendingNuzlocke[NUZLOCKE_DELETION];
    memset(gSaveBlock1Ptr->nuzlockeEncounterFlags, 0, sizeof(gSaveBlock1Ptr->nuzlockeEncounterFlags));
}

bool8 IsNuzlockeActive(void)
{
    if (FlagGet(FLAG_IS_CHAMPION))
        return FALSE;

    return gSaveBlock1Ptr->tx_Challenges_Nuzlocke;
}

bool8 IsNuzlockeDeathRulesActive(void)
{
    if (FlagGet(FLAG_IS_CHAMPION))
        return FALSE;

    return gSaveBlock1Ptr->tx_Challenges_Nuzlocke || gSaveBlock1Ptr->tx_Nuzlocke_EasyMode;
}

bool8 IsNuzlockeNicknamingActive(void)
{
    if (!gSaveBlock1Ptr->tx_Challenges_Nuzlocke)
        return FALSE;
    if (FlagGet(FLAG_IS_CHAMPION))
        return FALSE;

    return gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming;
}

static u16 GetNuzlockeMapSecId(u16 mapsec)
{
    if (mapsec < ARRAY_COUNT(gSaveBlock1Ptr->nuzlockeEncounterFlags) * 8)
        return mapsec;
    return MAPSEC_DYNAMIC;
}

u8 NuzlockeFlagSet(u16 mapsec)
{
    u16 id = GetNuzlockeMapSecId(mapsec);
    gSaveBlock1Ptr->nuzlockeEncounterFlags[id / 8] |= 1 << (id & 7);
    return 0;
}

u8 NuzlockeFlagClear(u16 mapsec)
{
    u16 id = GetNuzlockeMapSecId(mapsec);
    gSaveBlock1Ptr->nuzlockeEncounterFlags[id / 8] &= ~(1 << (id & 7));
    return 0;
}

u8 NuzlockeFlagGet(u16 mapsec)
{
    u16 id = GetNuzlockeMapSecId(mapsec);
    return (gSaveBlock1Ptr->nuzlockeEncounterFlags[id / 8] >> (id & 7)) & 1;
}

static u16 GetSpeciesFamilyBase(u16 species)
{
    u16 preEvolution;

    species = GET_BASE_SPECIES_ID(species);
    while ((preEvolution = GetSpeciesPreEvolution(species)) != SPECIES_NONE)
        species = GET_BASE_SPECIES_ID(preEvolution);

    return species;
}

static bool8 IsSpeciesFamilyCaught(u16 species)
{
    u16 i;
    u16 baseSpecies = GetSpeciesFamilyBase(species);

    if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT))
        return 2;

    for (i = SPECIES_BULBASAUR; i < NUM_SPECIES; i++)
    {
        if (GetSpeciesFamilyBase(i) == baseSpecies
            && GetSetPokedexFlag(SpeciesToNationalPokedexNum(i), FLAG_GET_CAUGHT))
            return TRUE;
    }
    return FALSE;
}

bool8 IsNuzlockeCaptureBlocked(u16 species)
{
    if (!IsNuzlockeActive())
        return FALSE;

    if (gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause)
    {
        u8 speciesClause = IsSpeciesFamilyCaught(species);
        if (speciesClause)
            return speciesClause == 2 ? 3 : 2;
    }

    if (NuzlockeFlagGet(GetCurrentRegionMapSectionId()))
        return 1;

    return FALSE;
}

void NuzlockeDeleteFaintedPartyPokemon(void)
{
    u8 i;
    u16 itemNone = ITEM_NONE;
    u8 nuzlockeRibbon = TRUE;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        if (GetMonData(mon, MON_DATA_SANITY_HAS_SPECIES, NULL)
            && !GetMonData(mon, MON_DATA_IS_EGG, NULL)
            && GetMonAilment(mon) == AILMENT_FNT)
        {
            u16 heldItem = GetMonData(mon, MON_DATA_HELD_ITEM, NULL);
            if (heldItem != ITEM_NONE)
            {
                AddBagItem(heldItem, 1);
                SetMonData(mon, MON_DATA_HELD_ITEM, &itemNone);
            }
            SetMonData(mon, MON_DATA_NUZLOCKE_RIBBON, &nuzlockeRibbon);
            if (!gSaveBlock1Ptr->tx_Nuzlocke_Deletion)
                CopyMonToPC(mon);
            ZeroMonData(mon);
        }
    }
    CompactPartySlots();
}
