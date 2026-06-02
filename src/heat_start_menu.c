#include "option_menu.h"
#include "heat_start_menu.h"
#include "global.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "battle_pyramid_bag.h"
#include "bg.h"
#include "decompress.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_object_lock.h"
#include "event_scripts.h"
#include "fieldmap.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "field_specials.h"
#include "field_weather.h"
#include "field_screen_effect.h"
#include "frontier_pass.h"
#include "frontier_util.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "item_menu.h"
#include "link.h"
#include "load_save.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "new_game.h"
#include "option_menu.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokenav.h"
#include "safari_zone.h"
#include "save.h"
#include "scanline_effect.h"
#include "script.h"
#include "sprite.h"
#include "sound.h"
#include "start_menu.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "trainer_card.h"
#include "window.h"
#include "union_room.h"
#include "constants/battle_frontier.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/weather.h"
#include "rtc.h"
#include "event_object_movement.h"
#include "gba/isagbprint.h"

/* CALLBACKS */
static void SpriteCB_IconPoketch(struct Sprite* sprite);
static void SpriteCB_IconPokedex(struct Sprite* sprite);
static void SpriteCB_IconParty(struct Sprite* sprite);
static void SpriteCB_IconBag(struct Sprite* sprite);
static void SpriteCB_IconTrainerCard(struct Sprite* sprite);
static void SpriteCB_IconSave(struct Sprite* sprite);
static void SpriteCB_IconOptions(struct Sprite* sprite);
static void SpriteCB_IconFlag(struct Sprite* sprite);

/* TASKs */
static void Task_HeatStartMenu_HandleMainInput(u8 taskId);
static void Task_HeatStartMenu_SafariZone_HandleMainInput(u8 taskId);
static void Task_HandleSave(u8 taskId);

/* OTHER FUNCTIONS */
static void HeatStartMenu_LoadSprites(void);
static void HeatStartMenu_CreateSprites(void);
static void HeatStartMenu_SafariZone_CreateSprites(void);
static void HeatStartMenu_LoadBgGfx(void);
static void HeatStartMenu_ShowTimeWindow(void);
static void HeatStartMenu_UpdateClockDisplay(void);
static void HeatStartMenu_UpdateMenuName(void);
static void HeatStartMenu_LoadIconPalette(void);
static bool8 HeatStartMenu_IsFlashWindowActive(void);
static void HeatStartMenu_EnableFlashIconWindows(void);
static void HeatStartMenu_DestroyInputTask(void);
static u32 HeatStartMenu_CreateIconSprite(const struct SpriteTemplate *template, s16 x, s16 y, u32 *windowSpriteId);
static void HeatStartMenu_DestroyIconSprite(u32 *spriteId);
static void HeatStartMenu_RestoreFlashIconWindows(void);
static void HeatStartMenu_UpdateIconSelection(struct Sprite* sprite, u8 menuId);
static u8 RunSaveCallback(void);
static u8 SaveDoSaveCallback(void);
static void HideSaveInfoWindow(void);
static void HideSaveMessageWindow(void);
static u8 SaveOverwriteInputCallback(void);
static u8 SaveConfirmOverwriteDefaultNoCallback(void);
static void ShowSaveMessage(const u8 *message, u8 (*saveCallback)(void));
static u8 SaveFileExistsCallback(void);
static u8 SaveSavingMessageCallback(void);
static u8 SaveConfirmInputCallback(void);
static u8 SaveYesNoCallback(void);
static void ShowSaveInfoWindow(void);
static u8 SaveConfirmSaveCallback(void);
static void InitSave(void);
static bool8 HeatStartMenu_IsFadeActive(void);
static bool8 HeatStartMenu_IsWeatherFadeActive(void);

/* ENUMs */
enum MENU {
  MENU_POKEDEX,
  MENU_PARTY,
  MENU_BAG,
  MENU_POKETCH,
  MENU_TRAINER_CARD,
  MENU_SAVE,
  MENU_OPTIONS,
  MENU_FLAG,
};

#define MENU_SELECTED_NONE 255

enum FLAG_VALUES {
  FLAG_VALUE_NOT_SET,
  FLAG_VALUE_SET,
};

enum SAVE_STATES {
  SAVE_IN_PROGRESS,
  SAVE_SUCCESS,
  SAVE_CANCELED,
  SAVE_ERROR
};

/* STRUCTs */
struct HeatStartMenu {
  MainCallback savedCallback;
  u32 loadState;
  u32 sStartClockWindowId;
  u32 sMenuNameWindowId;
  u32 sSafariBallsWindowId;
  u32 clockSecond;
  u16 savedDispcnt;
  u16 savedWinOut;
  u32 flag:1; // some u32 holding values for controlling the sprite anims and lifetime
  u32 unlockAndUnfreeze:1;
  u32 iconPaletteNeedsReload:1;
  u32 hasFlashIconWindows:1;
  u32 padding:28;
  
  u32 spriteIdPoketch;
  u32 spriteIdPoketchWindow;
  u32 spriteIdPokedex;
  u32 spriteIdPokedexWindow;
  u32 spriteIdParty;
  u32 spriteIdPartyWindow;
  u32 spriteIdBag;
  u32 spriteIdBagWindow;
  u32 spriteIdTrainerCard;
  u32 spriteIdTrainerCardWindow;
  u32 spriteIdSave;
  u32 spriteIdSaveWindow;
  u32 spriteIdOptions;
  u32 spriteIdOptionsWindow;
  u32 spriteIdFlag;
  u32 spriteIdFlagWindow;
};

static EWRAM_DATA struct HeatStartMenu *sHeatStartMenu = NULL;
static EWRAM_DATA u8 menuSelected = 0;
static EWRAM_DATA bool8 sMenuSelectedInitialized = FALSE;
static EWRAM_DATA u8 (*sSaveDialogCallback)(void) = NULL;
static EWRAM_DATA u8 sSaveDialogTimer = 0;
static EWRAM_DATA u8 sSaveInfoWindowId = 0;

// --BG-GFX--
static const u32 sStartMenuTiles[] = INCBIN_U32("graphics/heat_start_menu/bg.4bpp.lz");
static const u32 sStartMenuTilemap[] = INCBIN_U32("graphics/heat_start_menu/bg.bin.lz");
static const u32 sStartMenuTilemapSafari[] = INCBIN_U32("graphics/heat_start_menu/bg_safari.bin.lz");
static const u16 sStartMenuPalettes[MENU_PAL_COUNT][16] =
{
  INCBIN_U16("graphics/heat_start_menu/bg.gbapal"),
  INCBIN_U16("graphics/heat_start_menu/bg1.gbapal"),
  INCBIN_U16("graphics/heat_start_menu/bg2.gbapal"),
  INCBIN_U16("graphics/heat_start_menu/bg3.gbapal"),
};

const u16 *GetStartMenuPalette(u8 id)
{
  if (id >= MENU_PAL_COUNT)
    id = DEFAULT_START_MENU_PALETTE;
  return sStartMenuPalettes[id];
}
//--SPRITE-GFX--
#define TAG_ICON_GFX 1234
#define TAG_ICON_PAL 0x4654

static const u32 sIconGfx[] = INCBIN_U32("graphics/heat_start_menu/icons.4bpp.lz");
static const u16 sIconPal[] = INCBIN_U16("graphics/heat_start_menu/icons.gbapal");

static const struct WindowTemplate sSaveInfoWindowTemplate = {
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 14,
    .height = 10,
    .paletteNum = 15,
    .baseBlock = 8
};

static const struct WindowTemplate sWindowTemplate_StartClock = {
  .bg = 0, 
  .tilemapLeft = 2, 
  .tilemapTop = 17, 
  .width = 12, // If you want to shorten the dates to Sat., Sun., etc., change this to 9
  .height = 2, 
  .paletteNum = 15,
  .baseBlock = 0x30
};

static const struct WindowTemplate sWindowTemplate_MenuName = {
  .bg = 0, 
  .tilemapLeft = 16, 
  .tilemapTop = 17, 
  .width = 7, 
  .height = 2, 
  .paletteNum = 15,
  .baseBlock = 0x30 + (12*2)
};

static const struct WindowTemplate sWindowTemplate_SafariBalls = {
    .bg = 0,
    .tilemapLeft = 2,
    .tilemapTop = 1,
    .width = 7,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = (0x30 + (12*2)) + (7*2)
};

static const struct SpritePalette sSpritePal_Icon[] =
{
  {sIconPal, TAG_ICON_PAL},
  {NULL},
};

static const struct CompressedSpriteSheet sSpriteSheet_Icon[] = 
{
  {sIconGfx, 32*512/2 , TAG_ICON_GFX},
  {NULL},
};

static const struct OamData gOamIcon = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_DOUBLE,
    .objMode = 0,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
};

static const union AnimCmd gAnimCmdPoketch_NotSelected[] = {
    ANIMCMD_FRAME(112, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdPoketch_Selected[] = {
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconPoketchAnim[] = {
    gAnimCmdPoketch_NotSelected,
    gAnimCmdPoketch_Selected,
};

static const union AnimCmd gAnimCmdPokedex_NotSelected[] = {
    ANIMCMD_FRAME(128, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdPokedex_Selected[] = {
    ANIMCMD_FRAME(16, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconPokedexAnim[] = {
    gAnimCmdPokedex_NotSelected,
    gAnimCmdPokedex_Selected,
};

static const union AnimCmd gAnimCmdParty_NotSelected[] = {
    ANIMCMD_FRAME(144, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdParty_Selected[] = {
    ANIMCMD_FRAME(32, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconPartyAnim[] = {
    gAnimCmdParty_NotSelected,
    gAnimCmdParty_Selected,
};

static const union AnimCmd gAnimCmdBag_NotSelected[] = {
    ANIMCMD_FRAME(160, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdBag_Selected[] = {
    ANIMCMD_FRAME(48, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconBagAnim[] = {
    gAnimCmdBag_NotSelected,
    gAnimCmdBag_Selected,
};

static const union AnimCmd gAnimCmdTrainerCard_NotSelected[] = {
    ANIMCMD_FRAME(176, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdTrainerCard_Selected[] = {
    ANIMCMD_FRAME(64, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconTrainerCardAnim[] = {
    gAnimCmdTrainerCard_NotSelected,
    gAnimCmdTrainerCard_Selected,
};

static const union AnimCmd gAnimCmdSave_NotSelected[] = {
    ANIMCMD_FRAME(192, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdSave_Selected[] = {
    ANIMCMD_FRAME(80, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconSaveAnim[] = {
    gAnimCmdSave_NotSelected,
    gAnimCmdSave_Selected,
};

static const union AnimCmd gAnimCmdOptions_NotSelected[] = {
    ANIMCMD_FRAME(208, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdOptions_Selected[] = {
    ANIMCMD_FRAME(96, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconOptionsAnim[] = {
    gAnimCmdOptions_NotSelected,
    gAnimCmdOptions_Selected,
};

static const union AnimCmd gAnimCmdFlag_NotSelected[] = {
    ANIMCMD_FRAME(240, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gAnimCmdFlag_Selected[] = {
    ANIMCMD_FRAME(224, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gIconFlagAnim[] = {
    gAnimCmdFlag_NotSelected,
    gAnimCmdFlag_Selected,
};

static const union AffineAnimCmd sAffineAnimIcon_NoAnim[] =
{
  AFFINEANIMCMD_FRAME(0,0, 0, 60),
  AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnimIcon_Anim[] =
{
  AFFINEANIMCMD_FRAME(20, 20, 0, 5),    // Scale big
  AFFINEANIMCMD_FRAME(-10, -10, 0, 10), // Scale smol
  AFFINEANIMCMD_FRAME(0, 0, 1, 4),      // Begin rotating

  AFFINEANIMCMD_FRAME(0, 0, -1, 4),     // Loop starts from here ; Rotate/Tilt left 
  AFFINEANIMCMD_FRAME(0, 0, 0, 2),
  AFFINEANIMCMD_FRAME(0, 0, -1, 4),
  AFFINEANIMCMD_FRAME(0, 0, 0, 2),
  AFFINEANIMCMD_FRAME(0, 0, -1, 4),

  AFFINEANIMCMD_FRAME(0, 0, 1, 4),      // Rotate/Tilt Right
  AFFINEANIMCMD_FRAME(0, 0, 0, 2),
  AFFINEANIMCMD_FRAME(0, 0, 1, 4),
  AFFINEANIMCMD_FRAME(0, 0, 0, 2),
  AFFINEANIMCMD_FRAME(0, 0, 1, 4),

  AFFINEANIMCMD_JUMP(3),
};

static const union AffineAnimCmd *const sAffineAnimsIcon[] =
{   
    sAffineAnimIcon_NoAnim,
    sAffineAnimIcon_Anim,
};

static const struct SpriteTemplate gSpriteIconPoketch = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconPoketchAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconPoketch,
};

static const struct SpriteTemplate gSpriteIconPokedex = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconPokedexAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconPokedex,
};

static const struct SpriteTemplate gSpriteIconParty = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconPartyAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconParty,
};

static const struct SpriteTemplate gSpriteIconBag = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconBagAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconBag,
};

static const struct SpriteTemplate gSpriteIconTrainerCard = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconTrainerCardAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconTrainerCard,
};

static const struct SpriteTemplate gSpriteIconSave = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconSaveAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconSave,
};

static const struct SpriteTemplate gSpriteIconOptions = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconOptionsAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconOptions,
};

static const struct SpriteTemplate gSpriteIconFlag = {
    .tileTag = TAG_ICON_GFX,
    .paletteTag = TAG_ICON_PAL,
    .oam = &gOamIcon,
    .anims = gIconFlagAnim,
    .images = NULL,
    .affineAnims = sAffineAnimsIcon,
    .callback = SpriteCB_IconFlag,
};

static void SpriteCB_IconPoketch(struct Sprite* sprite) {
  HeatStartMenu_UpdateIconSelection(sprite, MENU_POKETCH);
}

static void SpriteCB_IconPokedex(struct Sprite* sprite) {
  HeatStartMenu_UpdateIconSelection(sprite, MENU_POKEDEX);
}

static void SpriteCB_IconParty(struct Sprite* sprite) {
  HeatStartMenu_UpdateIconSelection(sprite, MENU_PARTY);
}

static void SpriteCB_IconBag(struct Sprite* sprite) {
  HeatStartMenu_UpdateIconSelection(sprite, MENU_BAG);
}

static void SpriteCB_IconTrainerCard(struct Sprite* sprite) {
  HeatStartMenu_UpdateIconSelection(sprite, MENU_TRAINER_CARD);
}

static void SpriteCB_IconSave(struct Sprite* sprite) {
  HeatStartMenu_UpdateIconSelection(sprite, MENU_SAVE);
}

static void SpriteCB_IconOptions(struct Sprite* sprite) {
  HeatStartMenu_UpdateIconSelection(sprite, MENU_OPTIONS);
}

static void SpriteCB_IconFlag(struct Sprite* sprite) {
  HeatStartMenu_UpdateIconSelection(sprite, MENU_FLAG);
}

static void HeatStartMenu_UpdateIconSelection(struct Sprite* sprite, u8 menuId)
{
  if (menuSelected == menuId)
  {
    if (sprite->oam.objMode == ST_OAM_OBJ_WINDOW)
    {
      if (!sprite->data[0])
      {
        sprite->data[0] = TRUE;
        StartSpriteAnim(sprite, 1);
        StartSpriteAffineAnim(sprite, 1);
      }
    }
    else if (sHeatStartMenu->flag == FLAG_VALUE_NOT_SET)
    {
      sHeatStartMenu->flag = FLAG_VALUE_SET;
      sprite->data[0] = TRUE;
      StartSpriteAnim(sprite, 1);
      StartSpriteAffineAnim(sprite, 1);
    }
  }
  else
  {
    sprite->data[0] = FALSE;
    StartSpriteAnim(sprite, 0);
    StartSpriteAffineAnim(sprite, 0);
  }
}

// If you want to shorten the dates to Sat., Sun., etc., change this to 70
#define CLOCK_WINDOW_WIDTH 100

static const u8 gText_Friday[]    = _("Fri,");
static const u8 gText_Saturday[]  = _("Sat,");
static const u8 gText_Sunday[]    = _("Sun,");
static const u8 gText_Monday[]    = _("Mon,");
static const u8 gText_Tuesday[]   = _("Tue,");
static const u8 gText_Wednesday[] = _("Wed,");
static const u8 gText_Thursday[]  = _("Thu,");

static const u8 *const gDayNameStringsTable[] =
{
    gText_Friday,
    gText_Saturday,
    gText_Sunday,
    gText_Monday,
    gText_Tuesday,
    gText_Wednesday,
    gText_Thursday
};

static const u8 gText_CurrentTime[]      = _("  {STR_VAR_3} {CLEAR_TO 64}{STR_VAR_1}:{STR_VAR_2}");
static const u8 gText_CurrentTimeOff[]   = _("  {STR_VAR_3} {CLEAR_TO 64}{STR_VAR_1} {STR_VAR_2}");
static const u8 gText_CurrentTimeAM[]    = _("  {STR_VAR_3} {CLEAR_TO 51}{STR_VAR_1}:{STR_VAR_2} AM");
static const u8 gText_CurrentTimeAMOff[] = _("  {STR_VAR_3} {CLEAR_TO 51}{STR_VAR_1} {STR_VAR_2} AM");
static const u8 gText_CurrentTimePM[]    = _("  {STR_VAR_3} {CLEAR_TO 51}{STR_VAR_1}:{STR_VAR_2} PM");
static const u8 gText_CurrentTimePMOff[] = _("  {STR_VAR_3} {CLEAR_TO 51}{STR_VAR_1} {STR_VAR_2} PM");

static void SetSelectedMenu(void) {
  if (FlagGet(FLAG_SYS_POKENAV_GET) == TRUE) {
    menuSelected = MENU_POKETCH;
  } else if (FlagGet(FLAG_SYS_POKEDEX_GET) == TRUE) {
    menuSelected = MENU_POKEDEX;
  } else if (FlagGet(FLAG_SYS_POKEMON_GET) == TRUE) {
    menuSelected = MENU_PARTY;
  } else {
    menuSelected = MENU_BAG;
  }
}

static void ShowSafariBallsWindow(void)
{
    sHeatStartMenu->sSafariBallsWindowId = AddWindow(&sWindowTemplate_SafariBalls);
    FillWindowPixelBuffer(sHeatStartMenu->sSafariBallsWindowId, PIXEL_FILL(TEXT_COLOR_WHITE));
    PutWindowTilemap(sHeatStartMenu->sSafariBallsWindowId);
    ConvertIntToDecimalStringN(gStringVar1, gNumSafariBalls, STR_CONV_MODE_RIGHT_ALIGN, 2);
    StringExpandPlaceholders(gStringVar4, gText_SafariBallStock);
    AddTextPrinterParameterized(sHeatStartMenu->sSafariBallsWindowId, FONT_NARROW, gStringVar4, 0, 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(sHeatStartMenu->sSafariBallsWindowId, COPYWIN_GFX);
}

void HeatStartMenu_Init(void) {
  if (!IsOverworldLinkActive()) {
    FreezeObjectEvents();
    PlayerFreeze();
    StopPlayerAvatar();
  }

  LockPlayerFieldControls();

  if (sHeatStartMenu == NULL) {
    sHeatStartMenu = AllocZeroed(sizeof(struct HeatStartMenu));
  }

  if (sHeatStartMenu == NULL) {
    SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
    return;
  }

  sHeatStartMenu->savedCallback = CB2_ReturnToFieldWithOpenMenu;
  sHeatStartMenu->loadState = 0;
  sHeatStartMenu->sStartClockWindowId = 0;
  sHeatStartMenu->flag = 0;
  sHeatStartMenu->unlockAndUnfreeze = FALSE;
  sHeatStartMenu->iconPaletteNeedsReload = TRUE;
  sHeatStartMenu->hasFlashIconWindows = FALSE;
  sHeatStartMenu->clockSecond = 0xFF;
  sHeatStartMenu->spriteIdPoketch = MAX_SPRITES;
  sHeatStartMenu->spriteIdPoketchWindow = MAX_SPRITES;
  sHeatStartMenu->spriteIdPokedex = MAX_SPRITES;
  sHeatStartMenu->spriteIdPokedexWindow = MAX_SPRITES;
  sHeatStartMenu->spriteIdParty = MAX_SPRITES;
  sHeatStartMenu->spriteIdPartyWindow = MAX_SPRITES;
  sHeatStartMenu->spriteIdBag = MAX_SPRITES;
  sHeatStartMenu->spriteIdBagWindow = MAX_SPRITES;
  sHeatStartMenu->spriteIdTrainerCard = MAX_SPRITES;
  sHeatStartMenu->spriteIdTrainerCardWindow = MAX_SPRITES;
  sHeatStartMenu->spriteIdSave = MAX_SPRITES;
  sHeatStartMenu->spriteIdSaveWindow = MAX_SPRITES;
  sHeatStartMenu->spriteIdOptions = MAX_SPRITES;
  sHeatStartMenu->spriteIdOptionsWindow = MAX_SPRITES;
  sHeatStartMenu->spriteIdFlag = MAX_SPRITES;
  sHeatStartMenu->spriteIdFlagWindow = MAX_SPRITES;

  if (!sMenuSelectedInitialized) {
    menuSelected = MENU_SELECTED_NONE;
    sMenuSelectedInitialized = TRUE;
  }

  if (GetSafariZoneFlag() == FALSE) { 
    if (FlagGet(FLAG_SYS_POKENAV_GET) == FALSE && menuSelected == 0) {
      menuSelected = MENU_SELECTED_NONE;
    }

    if (menuSelected == MENU_FLAG) {
      menuSelected = MENU_POKEDEX;
    }

    if (menuSelected == MENU_SELECTED_NONE) {
      SetSelectedMenu();
    }
      
    HeatStartMenu_LoadSprites();
    HeatStartMenu_CreateSprites();
    HeatStartMenu_LoadBgGfx();
    HeatStartMenu_ShowTimeWindow();
    sHeatStartMenu->sMenuNameWindowId = AddWindow(&sWindowTemplate_MenuName);
    HeatStartMenu_UpdateMenuName();
    CreateTask(Task_HeatStartMenu_HandleMainInput, 0);
  } else {
    if (menuSelected == MENU_SELECTED_NONE || menuSelected == MENU_POKETCH || menuSelected == MENU_SAVE) {
      menuSelected = MENU_FLAG;
    }

    HeatStartMenu_LoadSprites();
    HeatStartMenu_SafariZone_CreateSprites();
    HeatStartMenu_LoadBgGfx();
    ShowSafariBallsWindow();
    HeatStartMenu_ShowTimeWindow();
    sHeatStartMenu->sMenuNameWindowId = AddWindow(&sWindowTemplate_MenuName);
    HeatStartMenu_UpdateMenuName();
    CreateTask(Task_HeatStartMenu_SafariZone_HandleMainInput, 0);
  }
}

static void HeatStartMenu_LoadSprites(void) {
  LoadSpritePalette(sSpritePal_Icon);
  HeatStartMenu_LoadIconPalette();
  LoadCompressedSpriteSheet(sSpriteSheet_Icon);
}

static void HeatStartMenu_LoadIconPalette(void)
{
  u32 index = IndexOfSpritePaletteTag(TAG_ICON_PAL);

  if (index != 0xFF)
    LoadPalette(sIconPal, OBJ_PLTT_ID(index), PLTT_SIZE_4BPP);
}

static bool8 HeatStartMenu_IsFlashWindowActive(void)
{
  return GetFlashLevel() > 0 || InBattlePyramid_();
}

static void HeatStartMenu_EnableFlashIconWindows(void)
{
  if (sHeatStartMenu->hasFlashIconWindows)
    return;

  sHeatStartMenu->savedDispcnt = GetGpuReg(REG_OFFSET_DISPCNT);
  sHeatStartMenu->savedWinOut = GetGpuReg(REG_OFFSET_WINOUT);
  SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
  SetGpuRegBits(REG_OFFSET_WINOUT, WINOUT_WINOBJ_OBJ);
  sHeatStartMenu->hasFlashIconWindows = TRUE;
}

static u32 HeatStartMenu_CreateIconSprite(const struct SpriteTemplate *template, s16 x, s16 y, u32 *windowSpriteId)
{
  u32 spriteId = CreateSprite(template, x, y, 0);

  *windowSpriteId = MAX_SPRITES;
  if (spriteId != MAX_SPRITES && HeatStartMenu_IsFlashWindowActive())
  {
    HeatStartMenu_EnableFlashIconWindows();
    *windowSpriteId = CreateSprite(template, x, y, 0);
    if (*windowSpriteId != MAX_SPRITES)
    {
      gSprites[*windowSpriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
      gSprites[*windowSpriteId].oam.priority = gSprites[spriteId].oam.priority;
    }
  }

  return spriteId;
}

static void HeatStartMenu_DestroyIconSprite(u32 *spriteId)
{
  if (*spriteId == MAX_SPRITES)
    return;

  FreeSpriteOamMatrix(&gSprites[*spriteId]);
  DestroySprite(&gSprites[*spriteId]);
  *spriteId = MAX_SPRITES;
}

static void HeatStartMenu_RestoreFlashIconWindows(void)
{
  if (!sHeatStartMenu->hasFlashIconWindows)
    return;

  SetGpuReg(REG_OFFSET_DISPCNT, sHeatStartMenu->savedDispcnt);
  SetGpuReg(REG_OFFSET_WINOUT, sHeatStartMenu->savedWinOut);
  sHeatStartMenu->hasFlashIconWindows = FALSE;
}

static bool8 HeatStartMenu_IsFadeActive(void)
{
  return gPaletteFade.active || HeatStartMenu_IsWeatherFadeActive();
}

static bool8 HeatStartMenu_IsWeatherFadeActive(void)
{
  switch (GetCurrentWeather())
  {
    case WEATHER_RAIN:
    case WEATHER_RAIN_THUNDERSTORM:
    case WEATHER_DOWNPOUR:
    case WEATHER_FOG_HORIZONTAL:
    case WEATHER_SHADE:
    case WEATHER_DROUGHT:
      return !IsWeatherNotFadingIn();
    default:
      return FALSE;
  }
}

static void HeatStartMenu_DestroyInputTask(void)
{
  u8 taskId = FindTaskIdByFunc(Task_HeatStartMenu_HandleMainInput);

  if (taskId != TASK_NONE)
  {
    DestroyTask(taskId);
    return;
  }

  taskId = FindTaskIdByFunc(Task_HeatStartMenu_SafariZone_HandleMainInput);
  if (taskId != TASK_NONE)
    DestroyTask(taskId);
}

static void HeatStartMenu_CreateSprites(void) {
  u32 x = 224;
  u32 y1 = 14;
  u32 y2 = 38;
  u32 y3 = 60;
  u32 y4 = 84;
  u32 y5 = 109;
  u32 y6 = 130;
  u32 y7 = 150;

  if (FlagGet(FLAG_SYS_POKENAV_GET) == TRUE) {
    sHeatStartMenu->spriteIdPokedex = HeatStartMenu_CreateIconSprite(&gSpriteIconPokedex, x-1, y1-2, &sHeatStartMenu->spriteIdPokedexWindow);
    sHeatStartMenu->spriteIdParty   = HeatStartMenu_CreateIconSprite(&gSpriteIconParty, x, y2-3, &sHeatStartMenu->spriteIdPartyWindow);
    sHeatStartMenu->spriteIdBag     = HeatStartMenu_CreateIconSprite(&gSpriteIconBag, x, y3-2, &sHeatStartMenu->spriteIdBagWindow);
    sHeatStartMenu->spriteIdPoketch = HeatStartMenu_CreateIconSprite(&gSpriteIconPoketch, x, y4+1, &sHeatStartMenu->spriteIdPoketchWindow);
    sHeatStartMenu->spriteIdTrainerCard = HeatStartMenu_CreateIconSprite(&gSpriteIconTrainerCard, x, y5, &sHeatStartMenu->spriteIdTrainerCardWindow);
    sHeatStartMenu->spriteIdSave    = HeatStartMenu_CreateIconSprite(&gSpriteIconSave, x, y6, &sHeatStartMenu->spriteIdSaveWindow);
    sHeatStartMenu->spriteIdOptions = HeatStartMenu_CreateIconSprite(&gSpriteIconOptions, x, y7, &sHeatStartMenu->spriteIdOptionsWindow);
    return;
  } else if (FlagGet(FLAG_SYS_POKEDEX_GET) == TRUE) {
    sHeatStartMenu->spriteIdPokedex = HeatStartMenu_CreateIconSprite(&gSpriteIconPokedex, x-1, y1, &sHeatStartMenu->spriteIdPokedexWindow);
    sHeatStartMenu->spriteIdParty = HeatStartMenu_CreateIconSprite(&gSpriteIconParty, x, y2-1, &sHeatStartMenu->spriteIdPartyWindow);
    sHeatStartMenu->spriteIdBag     = HeatStartMenu_CreateIconSprite(&gSpriteIconBag, x, y3+1, &sHeatStartMenu->spriteIdBagWindow);
    sHeatStartMenu->spriteIdTrainerCard = HeatStartMenu_CreateIconSprite(&gSpriteIconTrainerCard, x, y4 + 2, &sHeatStartMenu->spriteIdTrainerCardWindow);
    sHeatStartMenu->spriteIdSave    = HeatStartMenu_CreateIconSprite(&gSpriteIconSave, x, y5 - 1, &sHeatStartMenu->spriteIdSaveWindow);
    sHeatStartMenu->spriteIdOptions = HeatStartMenu_CreateIconSprite(&gSpriteIconOptions, x, y6-2, &sHeatStartMenu->spriteIdOptionsWindow);
    return;
  } else if (FlagGet(FLAG_SYS_POKEMON_GET) == TRUE) {
    sHeatStartMenu->spriteIdParty = HeatStartMenu_CreateIconSprite(&gSpriteIconParty, x, y1, &sHeatStartMenu->spriteIdPartyWindow);
    sHeatStartMenu->spriteIdBag     = HeatStartMenu_CreateIconSprite(&gSpriteIconBag, x, y2 + 1, &sHeatStartMenu->spriteIdBagWindow);
    sHeatStartMenu->spriteIdTrainerCard = HeatStartMenu_CreateIconSprite(&gSpriteIconTrainerCard, x, y3 + 3, &sHeatStartMenu->spriteIdTrainerCardWindow);
    sHeatStartMenu->spriteIdSave    = HeatStartMenu_CreateIconSprite(&gSpriteIconSave, x, y4 + 1, &sHeatStartMenu->spriteIdSaveWindow);
    sHeatStartMenu->spriteIdOptions = HeatStartMenu_CreateIconSprite(&gSpriteIconOptions, x, y5 - 4, &sHeatStartMenu->spriteIdOptionsWindow);
    return;
  } else {
    sHeatStartMenu->spriteIdBag     = HeatStartMenu_CreateIconSprite(&gSpriteIconBag, x, y1, &sHeatStartMenu->spriteIdBagWindow);
    sHeatStartMenu->spriteIdTrainerCard = HeatStartMenu_CreateIconSprite(&gSpriteIconTrainerCard, x, y2 + 1, &sHeatStartMenu->spriteIdTrainerCardWindow);
    sHeatStartMenu->spriteIdSave    = HeatStartMenu_CreateIconSprite(&gSpriteIconSave, x, y3 + 3, &sHeatStartMenu->spriteIdSaveWindow);
    sHeatStartMenu->spriteIdOptions = HeatStartMenu_CreateIconSprite(&gSpriteIconOptions, x, y4 + 1, &sHeatStartMenu->spriteIdOptionsWindow);
  }
}

static void HeatStartMenu_SafariZone_CreateSprites(void) {
  u32 x = 224;
  u32 y1 = 14;
  u32 y2 = 38;
  u32 y3 = 60;
  u32 y4 = 84;
  u32 y5 = 109;
  u32 y6 = 130;

  sHeatStartMenu->spriteIdFlag = HeatStartMenu_CreateIconSprite(&gSpriteIconFlag, x, y1, &sHeatStartMenu->spriteIdFlagWindow);
  sHeatStartMenu->spriteIdPokedex = HeatStartMenu_CreateIconSprite(&gSpriteIconPokedex, x-1, y2, &sHeatStartMenu->spriteIdPokedexWindow);
  sHeatStartMenu->spriteIdParty   = HeatStartMenu_CreateIconSprite(&gSpriteIconParty, x, y3, &sHeatStartMenu->spriteIdPartyWindow);
  sHeatStartMenu->spriteIdBag     = HeatStartMenu_CreateIconSprite(&gSpriteIconBag, x, y4, &sHeatStartMenu->spriteIdBagWindow);
  sHeatStartMenu->spriteIdTrainerCard = HeatStartMenu_CreateIconSprite(&gSpriteIconTrainerCard, x, y5, &sHeatStartMenu->spriteIdTrainerCardWindow);
  sHeatStartMenu->spriteIdOptions = HeatStartMenu_CreateIconSprite(&gSpriteIconOptions, x, y6, &sHeatStartMenu->spriteIdOptionsWindow);
}

static void HeatStartMenu_LoadBgGfx(void) {
  u8* buf;

  SetBgAttribute(0, BG_ATTR_CHARBASEINDEX, 2);
  SetBgAttribute(0, BG_ATTR_MAPBASEINDEX, 31);
  SetBgAttribute(0, BG_ATTR_PRIORITY, 0);
  ShowBg(0);
  ChangeBgX(0, 0, BG_COORD_SET);
  ChangeBgY(0, 0, BG_COORD_SET);

  if (gWindowBgTilemapBuffers[0] == NULL) {
    gWindowBgTilemapBuffers[0] = AllocZeroed(BG_SCREEN_SIZE);
    if (gWindowBgTilemapBuffers[0] == NULL)
      return;
  }

  SetBgTilemapBuffer(0, gWindowBgTilemapBuffers[0]);
  buf = gWindowBgTilemapBuffers[0];

  LoadBgTilemap(0, 0, 0, 0);
  ResetTempTileDataBuffers();
  DecompressAndCopyTileDataToVram(0, sStartMenuTiles, 0, 0, 0);
  while (FreeTempTileDataBuffersIfPossible())
    ;
  while (IsDma3ManagerBusyWithBgCopy())
    ;
  if (GetSafariZoneFlag() == FALSE) {
    LZDecompressWram(sStartMenuTilemap, buf);
  } else {
    LZDecompressWram(sStartMenuTilemapSafari, buf);
  }
  LoadPalette(gStandardMenuPalette, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
  LoadPalette(GetStartMenuPalette(gSaveBlock2Ptr->optionsStartMenuPalette), BG_PLTT_ID(14), PLTT_SIZE_4BPP);
  CopyBgTilemapBufferToVram(0);
  while (IsDma3ManagerBusyWithBgCopy())
    ;
}

static void HeatStartMenu_ShowTimeWindow(void)
{
    u8 analogHour;

	RtcCalcLocalTime();
      // print window
  sHeatStartMenu->sStartClockWindowId = AddWindow(&sWindowTemplate_StartClock);
  FillWindowPixelBuffer(sHeatStartMenu->sStartClockWindowId, PIXEL_FILL(TEXT_COLOR_WHITE));
  PutWindowTilemap(sHeatStartMenu->sStartClockWindowId);
	FlagSet(FLAG_TEMP_5);

    analogHour = (gLocalTime.hours >= 13 && gLocalTime.hours <= 24) ? gLocalTime.hours - 12 : gLocalTime.hours;

	StringCopy(gStringVar3, gDayNameStringsTable[(gLocalTime.days % 7)]);
    ConvertIntToDecimalStringN(gStringVar1, gLocalTime.hours, STR_CONV_MODE_LEADING_ZEROS, 2);
	ConvertIntToDecimalStringN(gStringVar2, gLocalTime.minutes, STR_CONV_MODE_LEADING_ZEROS, 2);
	    ConvertIntToDecimalStringN(gStringVar1, analogHour, STR_CONV_MODE_LEADING_ZEROS, 2);
    
	StringExpandPlaceholders(gStringVar4, gText_CurrentTime);
        if (gLocalTime.hours >= 13 && gLocalTime.hours <= 24)
            StringExpandPlaceholders(gStringVar4, gText_CurrentTimePM); 
        else
            StringExpandPlaceholders(gStringVar4, gText_CurrentTimeAM);  
    
	AddTextPrinterParameterized(sHeatStartMenu->sStartClockWindowId, 1, gStringVar4, 0, 1, 0xFF, NULL);
	CopyWindowToVram(sHeatStartMenu->sStartClockWindowId, COPYWIN_GFX);
    sHeatStartMenu->clockSecond = gLocalTime.seconds;
}

static void HeatStartMenu_UpdateClockDisplay(void)
{
    u8 analogHour;

	if (!FlagGet(FLAG_TEMP_5))
		return;
	RtcCalcLocalTime();
    if (sHeatStartMenu->clockSecond == gLocalTime.seconds)
        return;
    sHeatStartMenu->clockSecond = gLocalTime.seconds;

    analogHour = (gLocalTime.hours >= 13 && gLocalTime.hours <= 24) ? gLocalTime.hours - 12 : gLocalTime.hours;
    
	StringCopy(gStringVar3, gDayNameStringsTable[(gLocalTime.days % 7)]);
    ConvertIntToDecimalStringN(gStringVar1, gLocalTime.hours, STR_CONV_MODE_LEADING_ZEROS, 2);
	ConvertIntToDecimalStringN(gStringVar2, gLocalTime.minutes, STR_CONV_MODE_LEADING_ZEROS, 2);
	    ConvertIntToDecimalStringN(gStringVar1, analogHour, STR_CONV_MODE_LEADING_ZEROS, 2);
    if (gLocalTime.hours == 0)
		ConvertIntToDecimalStringN(gStringVar1, 12, STR_CONV_MODE_LEADING_ZEROS, 2);
    if (gLocalTime.hours == 12)
		ConvertIntToDecimalStringN(gStringVar1, 12, STR_CONV_MODE_LEADING_ZEROS, 2);

	if (gLocalTime.seconds % 2)
	{
        StringExpandPlaceholders(gStringVar4, gText_CurrentTime);
            if (gLocalTime.hours >= 12 && gLocalTime.hours <= 24)
                StringExpandPlaceholders(gStringVar4, gText_CurrentTimePM); 
            else
                StringExpandPlaceholders(gStringVar4, gText_CurrentTimeAM);  
    }
	else
	{
        StringExpandPlaceholders(gStringVar4, gText_CurrentTimeOff);
            if (gLocalTime.hours >= 12 && gLocalTime.hours <= 24)
                StringExpandPlaceholders(gStringVar4, gText_CurrentTimePMOff); 
            else
                StringExpandPlaceholders(gStringVar4, gText_CurrentTimeAMOff);  
    }
    
	AddTextPrinterParameterized(sHeatStartMenu->sStartClockWindowId, 1, gStringVar4, 0, 1, 0xFF, NULL);
	CopyWindowToVram(sHeatStartMenu->sStartClockWindowId, COPYWIN_GFX);
}

static const u8 gText_Poketch[] = _("  PokeNav");
static const u8 gText_Pokedex[] = _("  Pokédex");
static const u8 gText_Party[]   = _("    Party ");
static const u8 gText_Bag[]     = _("      Bag  ");
static const u8 gText_Trainer[] = _("   Trainer");
static const u8 gText_Save[]    = _("     Save  ");
static const u8 gText_Options[] = _("   Options");
static const u8 gText_Flag[]    = _("   Retire");

static void HeatStartMenu_UpdateMenuName(void) {
  
  FillWindowPixelBuffer(sHeatStartMenu->sMenuNameWindowId, PIXEL_FILL(TEXT_COLOR_WHITE));
  PutWindowTilemap(sHeatStartMenu->sMenuNameWindowId);

  switch(menuSelected) {
    case MENU_POKETCH:
      AddTextPrinterParameterized(sHeatStartMenu->sMenuNameWindowId, 1, gText_Poketch, 1, 0, 0xFF, NULL);
      break;
    case MENU_POKEDEX:
      AddTextPrinterParameterized(sHeatStartMenu->sMenuNameWindowId, 1, gText_Pokedex, 1, 0, 0xFF, NULL);
      break;
    case MENU_PARTY:
      AddTextPrinterParameterized(sHeatStartMenu->sMenuNameWindowId, 1, gText_Party, 1, 0, 0xFF, NULL);
      break;
    case MENU_BAG:
      AddTextPrinterParameterized(sHeatStartMenu->sMenuNameWindowId, 1, gText_Bag, 1, 0, 0xFF, NULL);
      break;
    case MENU_TRAINER_CARD:
      AddTextPrinterParameterized(sHeatStartMenu->sMenuNameWindowId, 1, gText_Trainer, 1, 0, 0xFF, NULL);
      break;
    case MENU_SAVE:
      AddTextPrinterParameterized(sHeatStartMenu->sMenuNameWindowId, 1, gText_Save, 1, 0, 0xFF, NULL);
      break;
    case MENU_OPTIONS:
      AddTextPrinterParameterized(sHeatStartMenu->sMenuNameWindowId, 1, gText_Options, 1, 0, 0xFF, NULL);
      break;
    case MENU_FLAG:
      AddTextPrinterParameterized(sHeatStartMenu->sMenuNameWindowId, 1, gText_Flag, 1, 0, 0xFF, NULL);
      break;
  }
  CopyWindowToVram(sHeatStartMenu->sMenuNameWindowId, COPYWIN_FULL);
}

static void HeatStartMenu_ExitAndClearTilemap(void) {
  u32 i;
  u8 *buf = GetBgTilemapBuffer(0);
 
  FillWindowPixelBuffer(sHeatStartMenu->sMenuNameWindowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
  FillWindowPixelBuffer(sHeatStartMenu->sStartClockWindowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

  ClearWindowTilemap(sHeatStartMenu->sMenuNameWindowId);
  ClearWindowTilemap(sHeatStartMenu->sStartClockWindowId);

  CopyWindowToVram(sHeatStartMenu->sMenuNameWindowId, COPYWIN_GFX);
  CopyWindowToVram(sHeatStartMenu->sStartClockWindowId, COPYWIN_GFX);

  RemoveWindow(sHeatStartMenu->sStartClockWindowId);
  RemoveWindow(sHeatStartMenu->sMenuNameWindowId);

  if (GetSafariZoneFlag() == TRUE) {
    FillWindowPixelBuffer(sHeatStartMenu->sSafariBallsWindowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    ClearWindowTilemap(sHeatStartMenu->sSafariBallsWindowId); 
    CopyWindowToVram(sHeatStartMenu->sSafariBallsWindowId, COPYWIN_GFX);
    RemoveWindow(sHeatStartMenu->sSafariBallsWindowId);
  }

  for(i=0; i<2048; i++) {
    buf[i] = 0;
  }
  ScheduleBgCopyTilemapToVram(0);

  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdPoketchWindow);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdPokedexWindow);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdPartyWindow);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdBagWindow);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdTrainerCardWindow);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdSaveWindow);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdOptionsWindow);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdFlagWindow);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdPoketch);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdPokedex);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdParty);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdBag);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdTrainerCard);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdSave);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdOptions);
  HeatStartMenu_DestroyIconSprite(&sHeatStartMenu->spriteIdFlag);
  HeatStartMenu_RestoreFlashIconWindows();

  
  if (sHeatStartMenu ->unlockAndUnfreeze)
  {
    ScriptUnfreezeObjectEvents();  
    UnlockPlayerFieldControls();
  }

  if (sHeatStartMenu != NULL) {
    FreeSpriteTilesByTag(TAG_ICON_GFX);  
    Free(sHeatStartMenu);
    sHeatStartMenu = NULL;
  }
}

static void DoCleanUpAndChangeCallback(MainCallback callback) {
  if (!HeatStartMenu_IsFadeActive()) {
    HeatStartMenu_DestroyInputTask();
    PlayRainStoppingSoundEffect();
    HeatStartMenu_ExitAndClearTilemap();
    CleanupOverworldWindowsAndTilemaps();
    SetMainCallback2(callback);
    gMain.savedCallback = CB2_ReturnToFieldWithOpenMenu;
  }
}

static void DoCleanUpAndOpenTrainerCard(void) {
  if (!HeatStartMenu_IsFadeActive()) {
    PlayRainStoppingSoundEffect();
    HeatStartMenu_ExitAndClearTilemap();
    CleanupOverworldWindowsAndTilemaps();
    if (IsOverworldLinkActive() || InUnionRoom()) {
      ShowPlayerTrainerCard(CB2_ReturnToFieldWithOpenMenu); // Display trainer card
      HeatStartMenu_DestroyInputTask();
    } else if (FlagGet(FLAG_SYS_FRONTIER_PASS)) {
      ShowFrontierPass(CB2_ReturnToFieldWithOpenMenu); // Display frontier pass
      HeatStartMenu_DestroyInputTask();
    } else {
      ShowPlayerTrainerCard(CB2_ReturnToFieldWithOpenMenu); // Display trainer card
      HeatStartMenu_DestroyInputTask();
    }
  }
}

static u8 RunSaveCallback(void)
{
    // True if text is still printing
    if (RunTextPrintersAndIsPrinter0Active() == TRUE)
    {
        return SAVE_IN_PROGRESS;
    }

    return sSaveDialogCallback();
}

static void SaveStartTimer(void)
{
    sSaveDialogTimer = 60;
}

static bool8 SaveSuccesTimer(void)
{
    sSaveDialogTimer--;


    if (JOY_HELD(A_BUTTON) || JOY_HELD(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        return TRUE;
    }
    if (sSaveDialogTimer == 0)
    {
        return TRUE;
    }

    return FALSE;
}

static bool8 SaveErrorTimer(void)
{
    if (sSaveDialogTimer != 0)
    {
        sSaveDialogTimer--;
    }
    else if (JOY_HELD(A_BUTTON))
    {
        return TRUE;
    }

    return FALSE;
}

static u8 SaveReturnSuccessCallback(void)
{
    if (!IsSEPlaying() && SaveSuccesTimer())
    {
        HideSaveInfoWindow();
        return SAVE_SUCCESS;
    }
    else
    {
        return SAVE_IN_PROGRESS;
    }
}

static u8 SaveSuccessCallback(void)
{
    if (!IsTextPrinterActive(0))
    {
        PlaySE(SE_SAVE);
        sSaveDialogCallback = SaveReturnSuccessCallback;
    }

    return SAVE_IN_PROGRESS;
}

static u8 SaveReturnErrorCallback(void)
{
    if (!SaveErrorTimer())
    {
        return SAVE_IN_PROGRESS;
    }
    else
    {
        HideSaveInfoWindow();
        return SAVE_ERROR;
    }
}

static u8 SaveErrorCallback(void)
{
    if (!IsTextPrinterActive(0))
    {
        PlaySE(SE_BOO);
        sSaveDialogCallback = SaveReturnErrorCallback;
    }

    return SAVE_IN_PROGRESS;
}

static u8 SaveDoSaveCallback(void)
{
    u8 saveStatus;

    IncrementGameStat(GAME_STAT_SAVED_GAME);
    PausePyramidChallenge();

    if (gDifferentSaveFile == TRUE)
    {
        saveStatus = TrySavingData(SAVE_OVERWRITE_DIFFERENT_FILE);
        gDifferentSaveFile = FALSE;
    }
    else
    {
        saveStatus = TrySavingData(SAVE_NORMAL);
    }

    if (saveStatus == SAVE_STATUS_OK)
        ShowSaveMessage(gText_PlayerSavedGame, SaveSuccessCallback);
    else
        ShowSaveMessage(gText_SaveError, SaveErrorCallback);

    SaveStartTimer();
    return SAVE_IN_PROGRESS;
}

static void HideSaveInfoWindow(void) {
  ClearStdWindowAndFrame(sSaveInfoWindowId, FALSE);
  RemoveWindow(sSaveInfoWindowId);
}

static void HideSaveMessageWindow(void) {
  ClearDialogWindowAndFrame(0, TRUE);
}

static u8 SaveOverwriteInputCallback(void)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0: // Yes
        sSaveDialogCallback = SaveSavingMessageCallback;
        return SAVE_IN_PROGRESS;
    case MENU_B_PRESSED:
    case 1: // No
        HideSaveInfoWindow();
        HideSaveMessageWindow();
        return SAVE_CANCELED;
    }

    return SAVE_IN_PROGRESS;
}

static u8 SaveConfirmOverwriteDefaultNoCallback(void)
{
    DisplayYesNoMenuWithDefault(1); // Show Yes/No menu (No selected as default)
    sSaveDialogCallback = SaveOverwriteInputCallback;
    return SAVE_IN_PROGRESS;
}

static void ShowSaveMessage(const u8 *message, u8 (*saveCallback)(void)) {
    StringExpandPlaceholders(gStringVar4, message);
    LoadMessageBoxAndFrameGfx(0, TRUE);
    AddTextPrinterForMessage_2(TRUE);
    sSaveDialogCallback = saveCallback;
}

static u8 SaveFileExistsCallback(void)
{
    if (gDifferentSaveFile == TRUE)
    {
        ShowSaveMessage(gText_DifferentSaveFile, SaveConfirmOverwriteDefaultNoCallback);
    }
    else
    {
        sSaveDialogCallback = SaveSavingMessageCallback;
    }

    return SAVE_IN_PROGRESS;
}

static u8 SaveSavingMessageCallback(void) {
  ShowSaveMessage(gText_SavingDontTurnOff, SaveDoSaveCallback);
  return SAVE_IN_PROGRESS;
}

static u8 SaveConfirmInputCallback(void)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0: // Yes
        switch (gSaveFileStatus)
        {
        case SAVE_STATUS_EMPTY:
        case SAVE_STATUS_CORRUPT:
            if (gDifferentSaveFile == FALSE)
            {
                sSaveDialogCallback = SaveFileExistsCallback;
                return SAVE_IN_PROGRESS;
            }

            sSaveDialogCallback = SaveSavingMessageCallback;
            return SAVE_IN_PROGRESS;
        default:
            sSaveDialogCallback = SaveFileExistsCallback;
            return SAVE_IN_PROGRESS;
        }
    case MENU_B_PRESSED: // No break, thats smart 
    case 1: // No
        HideSaveInfoWindow();
        HideSaveMessageWindow();
        return SAVE_CANCELED;
    }

    return SAVE_IN_PROGRESS;
}

static u8 SaveYesNoCallback(void) {
    DisplayYesNoMenuDefaultYes(); // Show Yes/No menu
    sSaveDialogCallback = SaveConfirmInputCallback;
    return SAVE_IN_PROGRESS;
}


static void ShowSaveInfoWindow(void) {
    struct WindowTemplate saveInfoWindow = sSaveInfoWindowTemplate;
    u8 gender;
    u8 color;
    u32 xOffset;
    u32 yOffset;

    if (!FlagGet(FLAG_SYS_POKEDEX_GET))
    {
        saveInfoWindow.height -= 2;
    }
    
    sSaveInfoWindowId = AddWindow(&saveInfoWindow);
    DrawStdWindowFrame(sSaveInfoWindowId, FALSE);

    gender = gSaveBlock2Ptr->playerGender;
    color = TEXT_COLOR_RED;  // Red when female, blue when male.

    if (gender == MALE)
    {
        color = TEXT_COLOR_BLUE;
    }

    // Print region name
    yOffset = 1;
    BufferSaveMenuText(SAVE_MENU_LOCATION, gStringVar4, TEXT_COLOR_GREEN);
    AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gStringVar4, 0, yOffset, TEXT_SKIP_DRAW, NULL);

    // Print player name
    yOffset += 16;
    AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gText_SavingPlayer, 0, yOffset, TEXT_SKIP_DRAW, NULL);
    BufferSaveMenuText(SAVE_MENU_NAME, gStringVar4, color);
    xOffset = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, 0x70);
    PrintPlayerNameOnWindow(sSaveInfoWindowId, gStringVar4, xOffset, yOffset);

    // Print badge count
    yOffset += 16;
    AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gText_SavingBadges, 0, yOffset, TEXT_SKIP_DRAW, NULL);
    BufferSaveMenuText(SAVE_MENU_BADGES, gStringVar4, color);
    xOffset = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, 0x70);
    AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gStringVar4, xOffset, yOffset, TEXT_SKIP_DRAW, NULL);

    if (FlagGet(FLAG_SYS_POKEDEX_GET) == TRUE)
    {
        // Print pokedex count
        yOffset += 16;
        AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gText_SavingPokedex, 0, yOffset, TEXT_SKIP_DRAW, NULL);
        BufferSaveMenuText(SAVE_MENU_CAUGHT, gStringVar4, color);
        xOffset = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, 0x70);
        AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gStringVar4, xOffset, yOffset, TEXT_SKIP_DRAW, NULL);
    }

    // Print play time
    yOffset += 16;
    AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gText_SavingTime, 0, yOffset, TEXT_SKIP_DRAW, NULL);
    BufferSaveMenuText(SAVE_MENU_PLAY_TIME, gStringVar4, color);
    xOffset = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar4, 0x70);
    AddTextPrinterParameterized(sSaveInfoWindowId, FONT_NORMAL, gStringVar4, xOffset, yOffset, TEXT_SKIP_DRAW, NULL);

    CopyWindowToVram(sSaveInfoWindowId, COPYWIN_GFX);
}

static u8 SaveConfirmSaveCallback(void) {
  ShowSaveInfoWindow();

  if (InBattlePyramid()) {
    ShowSaveMessage(gText_BattlePyramidConfirmRest, SaveYesNoCallback);
  } else {
    ShowSaveMessage(gText_ConfirmSave, SaveYesNoCallback);
  }
  return SAVE_IN_PROGRESS;
}

static void InitSave(void)
{
    SaveMapView();
    sSaveDialogCallback = SaveConfirmSaveCallback;
}

static void Task_HandleSave(u8 taskId) {
  switch (RunSaveCallback()) {
    case SAVE_IN_PROGRESS:
      break;
    case SAVE_SUCCESS:
    case SAVE_CANCELED: // Back to start menu
      ClearDialogWindowAndFrameToTransparent(0, TRUE);
      ScriptUnfreezeObjectEvents();  
      UnlockPlayerFieldControls();
      DestroyTask(taskId);
      break;
    case SAVE_ERROR:    // Close start menu
      ClearDialogWindowAndFrameToTransparent(0, TRUE);
      ScriptUnfreezeObjectEvents();
      UnlockPlayerFieldControls();
      SoftResetInBattlePyramid();
      DestroyTask(taskId);
      break;
  }
}

#define STD_WINDOW_BASE_TILE_NUM 0x214
#define STD_WINDOW_PALETTE_NUM 14

static void DoCleanUpAndStartSaveMenu(void) {
  if (!HeatStartMenu_IsFadeActive()) {
    HeatStartMenu_ExitAndClearTilemap();
    FreezeObjectEvents();
    LoadUserWindowBorderGfx(sSaveInfoWindowId, STD_WINDOW_BASE_TILE_NUM, BG_PLTT_ID(STD_WINDOW_PALETTE_NUM));
    LockPlayerFieldControls();
    HeatStartMenu_DestroyInputTask();
    InitSave();
    CreateTask(Task_HandleSave, 0x80);
  }
}

static void DoCleanUpAndStartSafariZoneRetire(void) {
  if (!HeatStartMenu_IsFadeActive()) {
    HeatStartMenu_ExitAndClearTilemap();
    FreezeObjectEvents();
    LockPlayerFieldControls();
    HeatStartMenu_DestroyInputTask();
    SafariZoneRetirePrompt();
  }
}
 
static void HeatStartMenu_OpenMenu(void) {
  switch (menuSelected) {
    case MENU_POKETCH:
      DoCleanUpAndChangeCallback(CB2_InitPokeNav);
      break;
    case MENU_POKEDEX:
      DoCleanUpAndChangeCallback(CB2_OpenPokedex);
      break;
    case MENU_PARTY: 
      DoCleanUpAndChangeCallback(CB2_PartyMenuFromStartMenu);
      break;
    case MENU_BAG: 
      DoCleanUpAndChangeCallback(CB2_BagMenuFromStartMenu);
      break;
    case MENU_TRAINER_CARD:
      DoCleanUpAndOpenTrainerCard();
      break;
    case MENU_OPTIONS:
      DoCleanUpAndChangeCallback(CB2_InitOptionMenu);
      break;
  }
}

void GoToHandleInput(void) {
  CreateTask(Task_HeatStartMenu_HandleMainInput, 80);
}

static void HeatStartMenu_HandleInput_DPADDOWN(void) {
  // Needs to be set to 0 so that the selected icons change in the frontend
  sHeatStartMenu->flag = 0;

  switch (menuSelected) {
    case MENU_OPTIONS:
      if (FlagGet(FLAG_SYS_POKEDEX_GET) == TRUE) {
        menuSelected = MENU_POKEDEX;
      } else if (FlagGet(FLAG_SYS_POKEMON_GET) == TRUE) {
        menuSelected = MENU_PARTY;
      } else {
        menuSelected = MENU_BAG;
      }
      break;
    default:
      menuSelected++;
      PlaySE(SE_SELECT);
      if (FlagGet(FLAG_SYS_POKENAV_GET) == FALSE && menuSelected == MENU_POKETCH) {
        menuSelected++;
      } else if (FlagGet(FLAG_SYS_POKEMON_GET) == FALSE && menuSelected == MENU_PARTY) {
        menuSelected++;
      }
      break;
  }
  HeatStartMenu_UpdateMenuName();
}

static void HeatStartMenu_HandleInput_DPADUP(void) {
  sHeatStartMenu->flag = 0;

  switch (menuSelected) {
    case MENU_POKEDEX:
      menuSelected = MENU_OPTIONS;
      break;
    default:
      PlaySE(SE_SELECT);
      if (FlagGet(FLAG_SYS_POKENAV_GET) == FALSE && menuSelected == MENU_TRAINER_CARD) {
        menuSelected -= 2;
      } else if ((FlagGet(FLAG_SYS_POKEMON_GET) == FALSE && menuSelected == MENU_BAG) || (FlagGet(FLAG_SYS_POKEDEX_GET) == FALSE && menuSelected == MENU_PARTY)) {
        menuSelected = MENU_OPTIONS;
        break;
      } else {
        menuSelected--;
      }
      break;
  }
  HeatStartMenu_UpdateMenuName();
}

static void Task_HeatStartMenu_HandleMainInput(u8 taskId) {
  bool8 fadeActive = HeatStartMenu_IsFadeActive();

  if (fadeActive)
    return;

  if (sHeatStartMenu->loadState == 0 && sHeatStartMenu->iconPaletteNeedsReload) {
    HeatStartMenu_LoadIconPalette();
    sHeatStartMenu->iconPaletteNeedsReload = FALSE;
  }

  HeatStartMenu_UpdateClockDisplay();

  if (JOY_NEW(A_BUTTON)) {
    if (sHeatStartMenu->loadState == 0) {
      if (menuSelected != MENU_SAVE) {
        FadeScreen(FADE_TO_BLACK, 0);
      }
      sHeatStartMenu->loadState = 1;
    }
  } else if (JOY_NEW(B_BUTTON) && sHeatStartMenu->loadState == 0) {
    PlaySE(SE_SELECT);
    sHeatStartMenu->unlockAndUnfreeze = TRUE;
    HeatStartMenu_ExitAndClearTilemap();  
    DestroyTask(taskId);
  } else if (gMain.newKeys & DPAD_DOWN && sHeatStartMenu->loadState == 0) {
    HeatStartMenu_HandleInput_DPADDOWN();
  } else if (gMain.newKeys & DPAD_UP && sHeatStartMenu->loadState == 0) {
    HeatStartMenu_HandleInput_DPADUP();
  } else if (sHeatStartMenu->loadState == 1) {
    if (menuSelected != MENU_SAVE) {
      HeatStartMenu_OpenMenu();
    } else {
      DoCleanUpAndStartSaveMenu();
    }
  }
}

static void HeatStartMenu_SafariZone_HandleInput_DPADDOWN(void) {
  sHeatStartMenu->flag = 0;

  switch (menuSelected) {
    case MENU_OPTIONS:
      menuSelected = MENU_FLAG;
      break;
    default:
      PlaySE(SE_SELECT);
      if (menuSelected == MENU_FLAG) {
        menuSelected = MENU_POKEDEX;
      } else if (menuSelected == MENU_BAG) {
        menuSelected = MENU_TRAINER_CARD;
      } else if (menuSelected == MENU_TRAINER_CARD) {
        menuSelected = MENU_OPTIONS;
      } else {
        menuSelected++;
      }
      break;
  }
  HeatStartMenu_UpdateMenuName();
}

static void HeatStartMenu_SafariZone_HandleInput_DPADUP(void) {
  sHeatStartMenu->flag = 0;

  switch (menuSelected) {
    case MENU_FLAG:
      menuSelected = MENU_OPTIONS;
      break;
    default:
      PlaySE(SE_SELECT);
      if (menuSelected == MENU_POKEDEX) {
        menuSelected = MENU_FLAG;
      } else if (menuSelected == MENU_OPTIONS) {
        menuSelected = MENU_TRAINER_CARD;
      } else if (menuSelected == MENU_TRAINER_CARD) {
        menuSelected = MENU_BAG;
      } else {
        menuSelected--;
      }
      break;
  }
  HeatStartMenu_UpdateMenuName();
}

static void Task_HeatStartMenu_SafariZone_HandleMainInput(u8 taskId) {
  bool8 fadeActive = HeatStartMenu_IsFadeActive();

  if (fadeActive)
    return;

  if (sHeatStartMenu->loadState == 0 && sHeatStartMenu->iconPaletteNeedsReload) {
    HeatStartMenu_LoadIconPalette();
    sHeatStartMenu->iconPaletteNeedsReload = FALSE;
  }

  HeatStartMenu_UpdateClockDisplay();

  if (JOY_NEW(A_BUTTON)) {
    if (sHeatStartMenu->loadState == 0) {
      if (menuSelected != MENU_FLAG) {
        FadeScreen(FADE_TO_BLACK, 0);
      }
      sHeatStartMenu->loadState = 1;
    }
  } else if (JOY_NEW(B_BUTTON) && sHeatStartMenu->loadState == 0) {
    PlaySE(SE_SELECT);
    sHeatStartMenu->unlockAndUnfreeze = TRUE;
    HeatStartMenu_ExitAndClearTilemap();  
    DestroyTask(taskId);
  } else if (gMain.newKeys & DPAD_DOWN && sHeatStartMenu->loadState == 0) {
    HeatStartMenu_SafariZone_HandleInput_DPADDOWN();
  } else if (gMain.newKeys & DPAD_UP && sHeatStartMenu->loadState == 0) {
    HeatStartMenu_SafariZone_HandleInput_DPADUP();
  } else if (sHeatStartMenu->loadState == 1) {
    if (menuSelected != MENU_FLAG) {
      HeatStartMenu_OpenMenu();
    } else {
      DoCleanUpAndStartSafariZoneRetire();
    }
  }
}
