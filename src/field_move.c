#include "global.h"
#include "event_data.h"
#include "field_move.h"
#include "fldeff.h"
#include "fldeff_misc.h"
#include "party_menu.h"
#include "constants/field_move.h"
#include "constants/moves.h"
#include "constants/party_menu.h"

#ifndef IS_FRLG
#define IS_FRLG FALSE
#endif

bool32 SetUpFieldMove_Surf(void);
bool32 SetUpFieldMove_Fly(void);
bool32 SetUpFieldMove_Dive(void);
bool32 SetUpFieldMove_Waterfall(void);
#if OW_ROCK_CLIMB_FIELD_MOVE == TRUE
bool32 SetUpFieldMove_RockClimb(void);
#endif

static bool32 FieldMove_SetUpCut(void)
{
    return SetUpFieldMove_Cut();
}

static bool32 FieldMove_SetUpFlash(void)
{
    return SetUpFieldMove_Flash();
}

static bool32 FieldMove_SetUpRockSmash(void)
{
    return SetUpFieldMove_RockSmash();
}

static bool32 FieldMove_SetUpStrength(void)
{
    return SetUpFieldMove_Strength();
}

static bool32 FieldMove_SetUpTeleport(void)
{
    return SetUpFieldMove_Teleport();
}

static bool32 FieldMove_SetUpDig(void)
{
    return SetUpFieldMove_Dig();
}

static bool32 FieldMove_SetUpSecretPower(void)
{
    return SetUpFieldMove_SecretPower();
}

static bool32 FieldMove_SetUpSoftBoiled(void)
{
    return SetUpFieldMove_SoftBoiled();
}

static bool32 FieldMove_SetUpSweetScent(void)
{
    return SetUpFieldMove_SweetScent();
}

static bool32 IsFieldMoveUnlocked_Cut(void)
{
    if (IS_FRLG)
        return FlagGet(FLAG_BADGE02_GET);

    return FlagGet(FLAG_BADGE01_GET);
}

static bool32 IsFieldMoveUnlocked_Flash(void)
{
    if (IS_FRLG)
        return FlagGet(FLAG_BADGE01_GET);

    return FlagGet(FLAG_BADGE02_GET);
}

static bool32 IsFieldMoveUnlocked_RockSmash(void)
{
    if (IS_FRLG)
        return FlagGet(FLAG_BADGE06_GET);

    return FlagGet(FLAG_BADGE03_GET);
}

static bool32 IsFieldMoveUnlocked_Strength(void)
{
    return FlagGet(FLAG_BADGE04_GET);
}

static bool32 IsFieldMoveUnlocked_Surf(void)
{
    return FlagGet(FLAG_BADGE05_GET);
}

static bool32 IsFieldMoveUnlocked_Fly(void)
{
    if (IS_FRLG)
        return FlagGet(FLAG_BADGE03_GET);

    return FlagGet(FLAG_BADGE06_GET);
}

static bool32 IsFieldMoveUnlocked_Dive(void)
{
    return FlagGet(FLAG_BADGE07_GET);
}

static bool32 IsFieldMoveUnlocked_Waterfall(void)
{
    if (IS_FRLG)
        return FlagGet(FLAG_BADGE07_GET);

    return FlagGet(FLAG_BADGE08_GET);
}

#if OW_ROCK_CLIMB_FIELD_MOVE == TRUE
static bool32 IsFieldMoveUnlocked_RockClimb(void)
{
    return TRUE;
}
#endif

static bool32 IsFieldMoveUnlocked_Teleport(void)
{
    return TRUE;
}

static bool32 IsFieldMoveUnlocked_Dig(void)
{
    return TRUE;
}

static bool32 IsFieldMoveUnlocked_SecretPower(void)
{
    return TRUE;
}

static bool32 IsFieldMoveUnlocked_MilkDrink(void)
{
    return TRUE;
}

static bool32 IsFieldMoveUnlocked_SoftBoiled(void)
{
    return TRUE;
}

static bool32 IsFieldMoveUnlocked_SweetScent(void)
{
    return TRUE;
}

#if OW_DEFOG_FIELD_MOVE == TRUE
static bool32 IsFieldMoveUnlocked_Defog(void)
{
    return TRUE;
}
#endif

const struct FieldMoveInfo gFieldMoveInfo[FIELD_MOVES_COUNT] =
{
    [FIELD_MOVE_CUT] =
    {
        .fieldMoveFunc = FieldMove_SetUpCut,
        .isUnlockedFunc = IsFieldMoveUnlocked_Cut,
        .moveID = MOVE_CUT,
        .partyMsgID = PARTY_MSG_NOTHING_TO_CUT,
    },

    [FIELD_MOVE_FLASH] =
    {
        .fieldMoveFunc = FieldMove_SetUpFlash,
        .isUnlockedFunc = IsFieldMoveUnlocked_Flash,
        .moveID = MOVE_FLASH,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_ROCK_SMASH] =
    {
        .fieldMoveFunc = FieldMove_SetUpRockSmash,
        .isUnlockedFunc = IsFieldMoveUnlocked_RockSmash,
        .moveID = MOVE_ROCK_SMASH,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_STRENGTH] =
    {
        .fieldMoveFunc = FieldMove_SetUpStrength,
        .isUnlockedFunc = IsFieldMoveUnlocked_Strength,
        .moveID = MOVE_STRENGTH,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_SURF] =
    {
        .fieldMoveFunc = SetUpFieldMove_Surf,
        .isUnlockedFunc = IsFieldMoveUnlocked_Surf,
        .moveID = MOVE_SURF,
        .partyMsgID = PARTY_MSG_CANT_SURF_HERE,
    },

    [FIELD_MOVE_FLY] =
    {
        .fieldMoveFunc = SetUpFieldMove_Fly,
        .isUnlockedFunc = IsFieldMoveUnlocked_Fly,
        .moveID = MOVE_FLY,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_DIVE] =
    {
        .fieldMoveFunc = SetUpFieldMove_Dive,
        .isUnlockedFunc = IsFieldMoveUnlocked_Dive,
        .moveID = MOVE_DIVE,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_WATERFALL] =
    {
        .fieldMoveFunc = SetUpFieldMove_Waterfall,
        .isUnlockedFunc = IsFieldMoveUnlocked_Waterfall,
        .moveID = MOVE_WATERFALL,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_TELEPORT] =
    {
        .fieldMoveFunc = FieldMove_SetUpTeleport,
        .isUnlockedFunc = IsFieldMoveUnlocked_Teleport,
        .moveID = MOVE_TELEPORT,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_DIG] =
    {
        .fieldMoveFunc = FieldMove_SetUpDig,
        .isUnlockedFunc = IsFieldMoveUnlocked_Dig,
        .moveID = MOVE_DIG,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_SECRET_POWER] =
    {
        .fieldMoveFunc = FieldMove_SetUpSecretPower,
        .isUnlockedFunc = IsFieldMoveUnlocked_SecretPower,
        .moveID = MOVE_SECRET_POWER,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_MILK_DRINK] =
    {
        .fieldMoveFunc = FieldMove_SetUpSoftBoiled,
        .isUnlockedFunc = IsFieldMoveUnlocked_MilkDrink,
        .moveID = MOVE_MILK_DRINK,
        .partyMsgID = PARTY_MSG_NOT_ENOUGH_HP,
    },

    [FIELD_MOVE_SOFT_BOILED] =
    {
        .fieldMoveFunc = FieldMove_SetUpSoftBoiled,
        .isUnlockedFunc = IsFieldMoveUnlocked_SoftBoiled,
        .moveID = MOVE_SOFT_BOILED,
        .partyMsgID = PARTY_MSG_NOT_ENOUGH_HP,
    },

    [FIELD_MOVE_SWEET_SCENT] =
    {
        .fieldMoveFunc = FieldMove_SetUpSweetScent,
        .isUnlockedFunc = IsFieldMoveUnlocked_SweetScent,
        .moveID = MOVE_SWEET_SCENT,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },
#if OW_ROCK_CLIMB_FIELD_MOVE == TRUE
    [FIELD_MOVE_ROCK_CLIMB] =
    {
        .fieldMoveFunc = SetUpFieldMove_RockClimb,
        .isUnlockedFunc = IsFieldMoveUnlocked_RockClimb,
        .moveID = MOVE_ROCK_CLIMB,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },
#endif
#if OW_DEFOG_FIELD_MOVE == TRUE
    [FIELD_MOVE_DEFOG] =
    {
        .fieldMoveFunc = SetUpFieldMove_Defog,
        .isUnlockedFunc = IsFieldMoveUnlocked_Defog,
        .moveID = MOVE_DEFOG,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },
#endif
};
