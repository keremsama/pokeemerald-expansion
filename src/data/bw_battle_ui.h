// const data

// textbox
static const u32 sBWBattleUI_TextboxTiles[] = INCBIN_U32("graphics/battle_interface/bw/textbox.4bpp.lz");
static const u32 sBWBattleUI_TextboxPalette[] = INCBIN_U32("graphics/battle_interface/bw/textbox.gbapal.lz");
static const u16 sBWBattleUI_TextboxPaletteRaw[] = INCBIN_U16("graphics/battle_interface/bw/textbox.gbapal"); // used as sprite palette
static const u32 sBWBattleUI_TextboxTilemap[] = INCBIN_U32("graphics/battle_interface/bw/textbox.bin.lz");

// inputbox->actionbox
static const u8 sBWBattleUI_ActionBox[] = INCBIN_U8("graphics/battle_interface/bw/actionbox.4bpp");
static const u8 *const sBWBattleUI_ActionBoxFields[][BUI_ACTION_BOX_ENTRY_COUNT] =
{
    // left-top -> right-bottom
    { // default
        COMPOUND_STRING("FIGHT!"),  COMPOUND_STRING("BAG"),
        COMPOUND_STRING("POKÉMON"), COMPOUND_STRING("RUN"),
    },
    { // safari
        COMPOUND_STRING("BALL!"),    COMPOUND_STRING("{POKEBLOCK}"),
        COMPOUND_STRING("GO NEAR"),  COMPOUND_STRING("RUN"),
    },
};

// inputbox->movebox
static const u8 sBWBattleUI_MoveBoxGraphics[] = INCBIN_U8("graphics/battle_interface/bw/movebox.4bpp");
static const u8 sBWBattleUI_MoveBoxGraphicsZ[] = INCBIN_U8("graphics/battle_interface/bw/movebox_z.4bpp");
static const u16 sBWBattleUI_MoveBoxPalette[] = INCBIN_U16("graphics/battle_interface/bw/movebox.gbapal");
static const u16 sBWBattleUI_MoveBoxTypePalettes[] = INCBIN_U16("graphics/battle_interface/bw/movebox_types.gbapal");

// BW Battle UI uses one palette for both ball_status_bar and ball_display
static const u16 sBWBattleUI_PartySummaryBarPalette[] = INCBIN_U16("graphics/battle_interface/bw/ball_status_bar.gbapal");
static const u16 sBWBattleUI_StatusIconPalette[] = INCBIN_U16("graphics/battle_interface/bw/status.gbapal");

// healthbox
static const u32 sBWBattleUI_HPBarText[] = INCBIN_U32("graphics/battle_interface/bw/hpbar.4bpp");
static const u32 sBWBattleUI_HPBarAnims[] = INCBIN_U32("graphics/battle_interface/bw/hpbar_anims.4bpp");
static const u32 sBWBattleUI_HPBoxEndFrames[] = INCBIN_U32("graphics/battle_interface/bw/healthbox_end_frames.4bpp");
static const u32 sBWBattleUI_HPBoxCaughtIndicator[] = INCBIN_U32("graphics/battle_interface/bw/ball_caught_indicator.4bpp");
static const u32 sBWBattleUI_EXPBarAnims[] = INCBIN_U32("graphics/battle_interface/bw/expbar.4bpp");

// ability pop up
static const u32 sBWBattleUI_AbilityPopUpGfx[] = INCBIN_U32("graphics/battle_interface/bw/ability_pop_up.4bpp");

static const u32 *const sBWBattleUI_SpriteGraphics[NUM_BUI_SPRITE_GFX] =
{
    [BUI_SPRITE_GFX_CURSOR] = (const u32[])INCBIN_U32("graphics/battle_interface/bw/cursor.4bpp.lz"),

    [BUI_SPRITE_GFX_SUMMARY_BAR]  = (const u32[])INCBIN_U32("graphics/battle_interface/bw/ball_status_bar.4bpp.lz"),
    [BUI_SPRITE_GFX_SUMMARY_BALL] = (const u32[])INCBIN_U32("graphics/battle_interface/bw/ball_display.4bpp.lz"),

    [BUI_SPRITE_GFX_HPBOX_S_PLAYER]   = (const u32[])INCBIN_U32("graphics/battle_interface/bw/healthbox_singles_player.4bpp.lz"),
    [BUI_SPRITE_GFX_HPBOX_S_OPPONENT] = (const u32[])INCBIN_U32("graphics/battle_interface/bw/healthbox_singles_opponent.4bpp.lz"),
    [BUI_SPRITE_GFX_HPBOX_D_PLAYER]   = (const u32[])INCBIN_U32("graphics/battle_interface/bw/healthbox_doubles_player.4bpp.lz"),
    [BUI_SPRITE_GFX_HPBOX_D_OPPONENT] = (const u32[])INCBIN_U32("graphics/battle_interface/bw/healthbox_doubles_opponent.4bpp.lz"),
    [BUI_SPRITE_GFX_HPBOX_SAFARI]     = (const u32[])INCBIN_U32("graphics/battle_interface/bw/healthbox_safari.4bpp.lz"),

    [BUI_SPRITE_GFX_GIMMICK_TRIGGER_MEGA]     = (const u32[])INCBIN_U32("graphics/battle_interface/bw/mega_trigger.4bpp.lz"),
    [BUI_SPRITE_GFX_GIMMICK_TRIGGER_BURST]    = (const u32[])INCBIN_U32("graphics/battle_interface/bw/burst_trigger.4bpp.lz"),
    [BUI_SPRITE_GFX_GIMMICK_TRIGGER_Z_MOVE]   = (const u32[])INCBIN_U32("graphics/battle_interface/bw/z_move_trigger.4bpp.lz"),
    [BUI_SPRITE_GFX_GIMMICK_TRIGGER_DYNAMAX]  = (const u32[])INCBIN_U32("graphics/battle_interface/bw/dynamax_trigger.4bpp.lz"),
    [BUI_SPRITE_GFX_GIMMICK_TRIGGER_TERA]     = (const u32[])INCBIN_U32("graphics/battle_interface/bw/tera_trigger.4bpp.lz"),

    [BUI_SPRITE_GFX_MOVE_INFO_TRIGGER] = (B_MOVE_DESCRIPTION_BUTTON == R_BUTTON)
        ? (const u32[])INCBIN_U32("graphics/battle_interface/bw/move_info_r.4bpp.lz")
        : (const u32[])INCBIN_U32("graphics/battle_interface/bw/move_info_l.4bpp.lz"),
    [BUI_SPRITE_GFX_LAST_BALL_TRIGGER] = (B_LAST_USED_BALL_BUTTON == R_BUTTON)
        ? (const u32[])INCBIN_U32("graphics/battle_interface/bw/last_used_ball_r.4bpp.lz")
        : (const u32[])INCBIN_U32("graphics/battle_interface/bw/last_used_ball_l.4bpp.lz"),
};

static const u16 *const sBWBattleUI_SpritePalettes[NUM_BUI_SPRITE_PALS] =
{
    [BUI_SPRITE_PAL_CURSOR] = (const u16[])INCBIN_U16("graphics/battle_interface/bw/cursor.gbapal"),

    [BUI_SPRITE_PAL_SUMMARY_BAR]  = sBWBattleUI_PartySummaryBarPalette,
    [BUI_SPRITE_PAL_SUMMARY_BALL] = sBWBattleUI_PartySummaryBarPalette,

    [BUI_SPRITE_PAL_HEALTH_BOX]   = (const u16[])INCBIN_U16("graphics/battle_interface/bw/healthbox_singles_player.gbapal"),
    [BUI_SPRITE_PAL_HEALTH_BAR]   = (const u16[])INCBIN_U16("graphics/battle_interface/bw/hpbar.gbapal"),

    [BUI_SPRITE_PAL_ABILITY_POP_UP] = (const u16[])INCBIN_U16("graphics/battle_interface/bw/ability_pop_up.gbapal"),

    [BUI_SPRITE_PAL_GIMMICK_TRIGGER_MEGA]     = (const u16[])INCBIN_U16("graphics/battle_interface/bw/mega_trigger.gbapal"),
    [BUI_SPRITE_PAL_GIMMICK_TRIGGER_BURST]    = (const u16[])INCBIN_U16("graphics/battle_interface/bw/burst_trigger.gbapal"),
    [BUI_SPRITE_PAL_GIMMICK_TRIGGER_Z_MOVE]   = (const u16[])INCBIN_U16("graphics/battle_interface/bw/z_move_trigger.gbapal"),
    [BUI_SPRITE_PAL_GIMMICK_TRIGGER_DYNAMAX]  = (const u16[])INCBIN_U16("graphics/battle_interface/bw/dynamax_trigger.gbapal"),
    [BUI_SPRITE_PAL_GIMMICK_TRIGGER_TERA]     = (const u16[])INCBIN_U16("graphics/battle_interface/bw/tera_trigger.gbapal"),

    [BUI_SPRITE_PAL_TEXTBOX_0] = sBWBattleUI_TextboxPaletteRaw,
};

static const s16 sBWBattleUI_HealthboxCoords[BATTLE_COORDS_COUNT][MAX_BATTLERS_COUNT][2] =
{
    [BATTLE_COORDS_SINGLES] =
    {
        [B_POSITION_PLAYER_LEFT]    = { 128, 72  },
        [B_POSITION_OPPONENT_LEFT]  = { 0,   14  },
    },
    [BATTLE_COORDS_DOUBLES] =
    {
        [B_POSITION_PLAYER_LEFT]    = { 128, 56  },
        [B_POSITION_OPPONENT_LEFT]  = { 0,   0   },
        [B_POSITION_PLAYER_RIGHT]   = { 128, 82  },
        [B_POSITION_OPPONENT_RIGHT] = { 0,   26  },
    },
};

static const s16 sBWBattleUI_SafariPlayerHealthboxCoords[2] = { 128, 80 };

static const s16 sBWBattleUI_HealthbarCoords[BATTLE_COORDS_COUNT][MAX_BATTLERS_COUNT][2] =
{
    [BATTLE_COORDS_SINGLES] =
    {
        [B_POSITION_PLAYER_LEFT]    = { 164, 82  },
        [B_POSITION_OPPONENT_LEFT]  = { 28,  24  },
    },
    [BATTLE_COORDS_DOUBLES] =
    {
        [B_POSITION_PLAYER_LEFT]    = { 164, 66  },
        [B_POSITION_OPPONENT_LEFT]  = { 28,  10  },
        [B_POSITION_PLAYER_RIGHT]   = { 164, 92  },
        [B_POSITION_OPPONENT_RIGHT] = { 28,  36  },
    },
};

static const s16 sBWBattleUI_AbilityPopUpCoords[BATTLE_COORDS_COUNT][MAX_BATTLERS_COUNT][2] =
{
    [BATTLE_COORDS_SINGLES] =
    {
        [B_POSITION_PLAYER_LEFT]    = { 0,   80  },
        [B_POSITION_OPPONENT_LEFT]  = { 144, 32  },
    },
    [BATTLE_COORDS_DOUBLES] =
    {
        [B_POSITION_PLAYER_LEFT]    = { 0,   54  },
        [B_POSITION_OPPONENT_LEFT]  = { 144, 4   },
        [B_POSITION_PLAYER_RIGHT]   = { 0,   80  },
        [B_POSITION_OPPONENT_RIGHT] = { 144, 28  },
    }
};

// positioned to left-most possible coord (lvl 100)
static const s8 sBWBattleUI_GimmickIndicatorCoords[MAX_BATTLERS_COUNT][2] =
{
    [B_POSITION_PLAYER_LEFT]    = { 47, -11 },
    [B_POSITION_OPPONENT_LEFT]  = { 33, -11 },
    [B_POSITION_PLAYER_RIGHT]   = { 47, -11 },
    [B_POSITION_OPPONENT_RIGHT] = { 33, -11 },
};

// BATTLE! / BAG / POKEMON / RUN
static const struct Subsprite sBWBattleUI_ActionCursorSubsprite[] =
{
    {
        .x = 0,
        .y = 0,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
    },
    {
        .x = BUI_ACTION_CURSOR_MAX_X,
        .y = 0,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 4,
    },
    {
        .x = 0,
        .y = BUI_ACTION_CURSOR_MAX_Y,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 8,
    },
    {
        .x = BUI_ACTION_CURSOR_MAX_X,
        .y = BUI_ACTION_CURSOR_MAX_Y,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 12,
    },
};

static const struct Subsprite sBWBattleUI_MoveCursorSubsprite[] =
{
    {
        .x = 0,
        .y = 0,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 0
    },
    {
        .x = BUI_MOVE_CURSOR_MAX_X,
        .y = 0,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 4,
        .priority = 0
    },
    {
        .x = 0,
        .y = BUI_MOVE_CURSOR_MAX_Y,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 8,
        .priority = 0
    },
    {
        .x = BUI_MOVE_CURSOR_MAX_X,
        .y = BUI_MOVE_CURSOR_MAX_Y,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 12,
        .priority = 0
    },
};

static const struct Subsprite sBWBattleUI_ZMoveCursorSubsprite[] =
{
    {
        .x = 0,
        .y = 0,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 0
    },
    {
        .x = BUI_Z_MOVE_CURSOR_MAX_X,
        .y = 0,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 4,
        .priority = 0
    },
    {
        .x = 0,
        .y = BUI_Z_MOVE_CURSOR_MAX_Y,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 8,
        .priority = 0
    },
    {
        .x = BUI_Z_MOVE_CURSOR_MAX_X,
        .y = BUI_Z_MOVE_CURSOR_MAX_Y,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 12,
        .priority = 0
    },
};

static const struct SubspriteTable sBWBattleUI_CursorSubspritesTable[] =
{
    { ARRAY_COUNT(sBWBattleUI_ActionCursorSubsprite), sBWBattleUI_ActionCursorSubsprite },
    { ARRAY_COUNT(sBWBattleUI_MoveCursorSubsprite),   sBWBattleUI_MoveCursorSubsprite },
    { ARRAY_COUNT(sBWBattleUI_ZMoveCursorSubsprite),  sBWBattleUI_ZMoveCursorSubsprite },
    { }
};

static const struct SpriteTemplate sBWBattleUI_CursorTemplate =
{
    .tileTag = TAG_CURSOR,
    .paletteTag = TAG_CURSOR,
    .oam = &(struct OamData){
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
    },
    .anims = (const union AnimCmd *const[]){
        [0] = (const union AnimCmd[]){
            ANIMCMD_FRAME( 0, 16),
            ANIMCMD_FRAME(16, 16),
            ANIMCMD_FRAME(32, 16),
            ANIMCMD_JUMP(0),
        },
    },
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_BattleUICursor,
};

static const struct SpriteTemplate sBWBattleUI_AbilityPopUpTemplate =
{
    .tileTag = TAG_NONE, // automatically assigned when spawned
    .paletteTag = TAG_ABILITY_POP_UP,
    .oam = &(const struct OamData){
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
    },
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sBWBattleUI_GimmickTriggerTemplate =
{
    .tileTag = TAG_GIMMICK_TRIGGER_TILE,
    .paletteTag = TAG_GIMMICK_TRIGGER_PAL,
    .oam = &(const struct OamData){
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .priority = 1,
    },
    .anims = (const union AnimCmd *const[]){
        [0] = (const union AnimCmd[]){
            ANIMCMD_FRAME( 0, 8),
            ANIMCMD_END,
        },
        [1] = (const union AnimCmd[]){
            ANIMCMD_FRAME(16, 8),
            ANIMCMD_END,
        },
    },
    .callback = SpriteCB_GimmickTrigger,
};

static const struct SpriteTemplate sBWBattleUI_MoveInfoTriggerTemplate =
{
    .tileTag = MOVE_INFO_WINDOW_TAG,
    .paletteTag = TAG_ABILITY_POP_UP,
    .oam = &(const struct OamData){
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .priority = 1,
    },
    .callback = SpriteCB_MoveInfoTrigger,
};

static const struct SpriteTemplate sBWBattleUI_LastBallTriggerTemplate =
{
    .tileTag = TAG_LAST_BALL_WINDOW,
    .paletteTag = TAG_ABILITY_POP_UP,
    .oam = &(const struct OamData){
        .shape = SPRITE_SHAPE(32x64),
        .size = SPRITE_SIZE(32x64),
        .priority = 1,
    },
    .anims = (const union AnimCmd *const[]){
        [0] = (const union AnimCmd[]){
            ANIMCMD_FRAME( 0, 8),
            ANIMCMD_END,
        },
        [1] = (const union AnimCmd[]){
            ANIMCMD_FRAME(32, 8),
            ANIMCMD_END,
        },
    },
    .callback = SpriteCB_LastBallTrigger,
};

static const union TextColor sBWBattleUI_TextColors[NUM_BUI_TXTCLRS] =
{
    [BUI_TXTCLR_MOVE_BOX] =
    {
        .foreground = 13,
        .shadow = 15,
    },
    [BUI_TXTCLR_HEALTHBOX] =
    {
        .foreground = 1,
        .shadow = 3,
    },
    [BUI_TXTCLR_HBOX_NAME] =
    {
        .foreground = 1,
        .shadow = 2,
    },
    [BUI_TXTCLR_HBOX_STATUS] =
    {
        // foreground defined on the fly
        .shadow = 2,
        .accent = 1,
        .background = 3,
    },
    [BUI_TXTCLR_ABOX_1] =
    {
        .foreground = 4,
        .accent = 2,
        .shadow = 9,
    },
    [BUI_TXTCLR_ABOX_2] =
    {
        .foreground = 14,
        .accent = 5,
        .shadow = 9,
    },
    [BUI_TXTCLR_ABOX_3] =
    {
        .foreground = 11,
        .accent = 10,
        .shadow = 9,
    },
    [BUI_TXTCLR_ABOX_4] =
    {
        .foreground = 12,
        .accent = 8,
        .shadow = 9,
    },
};
