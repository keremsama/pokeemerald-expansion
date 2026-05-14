#include "global.h"
#include "event_data.h"
#include "item.h"
#include "overworld.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "tx_randomizer_and_challenges.h"
#include "constants/items.h"
#include "constants/party_menu.h"
#include "constants/pokedex.h"
#include "constants/pokemon.h"
#include "constants/region_map_sections.h"

EWRAM_DATA u8 NuzlockeIsCaptureBlocked = FALSE;
EWRAM_DATA u8 NuzlockeIsSpeciesClauseActive = FALSE;
EWRAM_DATA u8 NuzlockeShouldSkipEncounterFlag = FALSE;

static bool8 TryGetNuzlockeEncounterId(u16 mapsec, u16 *id);
static u16 GetNuzlockeEncounterId(u16 mapsec);
static bool8 TryGetNuzlockeEncounterFlagIndex(u16 mapsec, u16 *id);
static bool8 IsSpeciesCaughtForNuzlocke(u16 species);
static u16 GetSpeciesFamilyBase(u16 species);
static bool8 IsEvolutionLineCaughtForNuzlocke(u16 species, u8 depth);
static void ClearNuzlockeChecks(void);

bool8 IsNuzlockeActive(void)
{
    if (!FlagGet(FLAG_SYS_POKEMON_GET))
        return FALSE;
    if (!FlagGet(FLAG_ADVENTURE_STARTED))
        return FALSE;
    if (FlagGet(FLAG_IS_CHAMPION))
        return FALSE;

    return gSaveBlock1Ptr->tx_Challenges_Nuzlocke;
}

bool8 IsNuzlockeDeathRulesActive(void)
{
    return IsNuzlockeActive();
}

bool8 IsNuzlockeNicknamingActive(void)
{
    if (!gSaveBlock1Ptr->tx_Challenges_Nuzlocke)
        return FALSE;
    if (FlagGet(FLAG_IS_CHAMPION))
        return FALSE;

    return gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming;
}

u8 NuzlockeGetCurrentRegionMapSectionId(void)
{
    return GetCurrentRegionMapSectionId();
}

static bool8 TryGetNuzlockeEncounterId(u16 mapsec, u16 *id)
{
    switch (mapsec)
    {
    case MAPSEC_ROUTE_101: *id = 0x00; return TRUE;
    case MAPSEC_ROUTE_102: *id = 0x01; return TRUE;
    case MAPSEC_ROUTE_103: *id = 0x02; return TRUE;
    case MAPSEC_ROUTE_104: *id = 0x03; return TRUE;
    case MAPSEC_ROUTE_105: *id = 0x04; return TRUE;
    case MAPSEC_ROUTE_106: *id = 0x05; return TRUE;
    case MAPSEC_ROUTE_107: *id = 0x06; return TRUE;
    case MAPSEC_ROUTE_108: *id = 0x07; return TRUE;
    case MAPSEC_ROUTE_109: *id = 0x08; return TRUE;
    case MAPSEC_ROUTE_110: *id = 0x09; return TRUE;
    case MAPSEC_ROUTE_111: *id = 0x0A; return TRUE;
    case MAPSEC_ROUTE_112: *id = 0x0B; return TRUE;
    case MAPSEC_ROUTE_113: *id = 0x0C; return TRUE;
    case MAPSEC_ROUTE_114: *id = 0x0D; return TRUE;
    case MAPSEC_ROUTE_115: *id = 0x0E; return TRUE;
    case MAPSEC_ROUTE_116: *id = 0x0F; return TRUE;
    case MAPSEC_ROUTE_117: *id = 0x10; return TRUE;
    case MAPSEC_ROUTE_118: *id = 0x11; return TRUE;
    case MAPSEC_ROUTE_119: *id = 0x12; return TRUE;
    case MAPSEC_ROUTE_120: *id = 0x13; return TRUE;
    case MAPSEC_ROUTE_121: *id = 0x14; return TRUE;
    case MAPSEC_ROUTE_122: *id = 0x15; return TRUE;
    case MAPSEC_ROUTE_123: *id = 0x16; return TRUE;
    case MAPSEC_ROUTE_124: *id = 0x17; return TRUE;
    case MAPSEC_ROUTE_125: *id = 0x18; return TRUE;
    case MAPSEC_ROUTE_126: *id = 0x19; return TRUE;
    case MAPSEC_ROUTE_127: *id = 0x1A; return TRUE;
    case MAPSEC_ROUTE_128: *id = 0x1B; return TRUE;
    case MAPSEC_ROUTE_129: *id = 0x1C; return TRUE;
    case MAPSEC_ROUTE_130: *id = 0x1D; return TRUE;
    case MAPSEC_ROUTE_131: *id = 0x1E; return TRUE;
    case MAPSEC_ROUTE_132: *id = 0x1F; return TRUE;
    case MAPSEC_ROUTE_133: *id = 0x20; return TRUE;
    case MAPSEC_ROUTE_134: *id = 0x21; return TRUE;
    case MAPSEC_PETALBURG_CITY: *id = 0x22; return TRUE;
    case MAPSEC_DEWFORD_TOWN: *id = 0x23; return TRUE;
    case MAPSEC_SLATEPORT_CITY: *id = 0x24; return TRUE;
    case MAPSEC_LILYCOVE_CITY: *id = 0x25; return TRUE;
    case MAPSEC_MOSSDEEP_CITY: *id = 0x26; return TRUE;
    case MAPSEC_PACIFIDLOG_TOWN: *id = 0x27; return TRUE;
    case MAPSEC_SOOTOPOLIS_CITY: *id = 0x28; return TRUE;
    case MAPSEC_EVER_GRANDE_CITY: *id = 0x29; return TRUE;
    case MAPSEC_PETALBURG_WOODS: *id = 0x2A; return TRUE;
    case MAPSEC_RUSTURF_TUNNEL: *id = 0x2B; return TRUE;
    case MAPSEC_GRANITE_CAVE: *id = 0x2C; return TRUE;
    case MAPSEC_FIERY_PATH:
    case MAPSEC_FIERY_PATH2: *id = 0x2D; return TRUE;
    case MAPSEC_METEOR_FALLS:
    case MAPSEC_METEOR_FALLS2: *id = 0x2E; return TRUE;
    case MAPSEC_JAGGED_PASS:
    case MAPSEC_JAGGED_PASS2: *id = 0x2F; return TRUE;
    case MAPSEC_MIRAGE_TOWER: *id = 0x30; return TRUE;
    case MAPSEC_ABANDONED_SHIP: *id = 0x31; return TRUE;
    case MAPSEC_NEW_MAUVILLE: *id = 0x32; return TRUE;
    case MAPSEC_SAFARI_ZONE: *id = 0x33; return TRUE;
    case MAPSEC_MT_PYRE: *id = 0x37; return TRUE;
    case MAPSEC_SHOAL_CAVE: *id = 0x38; return TRUE;
    case MAPSEC_AQUA_HIDEOUT:
    case MAPSEC_AQUA_HIDEOUT_OLD: *id = 0x39; return TRUE;
    case MAPSEC_MAGMA_HIDEOUT: *id = 0x3A; return TRUE;
    case MAPSEC_SEAFLOOR_CAVERN: *id = 0x3B; return TRUE;
    case MAPSEC_CAVE_OF_ORIGIN: *id = 0x3C; return TRUE;
    case MAPSEC_SKY_PILLAR: *id = 0x3D; return TRUE;
    case MAPSEC_VICTORY_ROAD: *id = 0x3E; return TRUE;
    case MAPSEC_UNDERWATER_124:
    case MAPSEC_UNDERWATER_126:
    case MAPSEC_UNDERWATER_127:
    case MAPSEC_UNDERWATER_128: *id = 0x3F; return TRUE;
    case MAPSEC_ARTISAN_CAVE: *id = 0x40; return TRUE;
    case MAPSEC_DESERT_UNDERPASS: *id = 0x41; return TRUE;
    case MAPSEC_ALTERING_CAVE:
    case MAPSEC_ALTERING_CAVE_FRLG: *id = 0x42; return TRUE;
    case MAPSEC_MARINE_CAVE: *id = 0x43; return TRUE;
    case MAPSEC_UNDERWATER_MARINE_CAVE: *id = 0x44; return TRUE;
    case MAPSEC_TERRA_CAVE: *id = 0x45; return TRUE;
    case MAPSEC_UNDERWATER_105: *id = 0x46; return TRUE;
    case MAPSEC_UNDERWATER_125: *id = 0x47; return TRUE;
    case MAPSEC_UNDERWATER_129: *id = 0x48; return TRUE;
    case MAPSEC_NAVEL_ROCK: *id = 0x49; return TRUE;
    case MAPSEC_BIRTH_ISLAND: *id = 0x4A; return TRUE;
    case MAPSEC_FARAWAY_ISLAND: *id = 0x4B; return TRUE;
    case MAPSEC_MOJAVE_CAVE: *id = 0x4C; return TRUE;
    case MAPSEC_SCORCHED_SLAB: *id = 0x4D; return TRUE;
    default:
        return FALSE;
    }
}

static u16 GetNuzlockeEncounterId(u16 mapsec)
{
    u16 id;

    if (TryGetNuzlockeEncounterId(mapsec, &id))
        return id;
    if (mapsec < ARRAY_COUNT(gSaveBlock1Ptr->NuzlockeEncounterFlags) * 8)
        return mapsec;
    return MAPSEC_DYNAMIC;
}

static bool8 TryGetNuzlockeEncounterFlagIndex(u16 mapsec, u16 *id)
{
    *id = GetNuzlockeEncounterId(mapsec);
    return *id < ARRAY_COUNT(gSaveBlock1Ptr->NuzlockeEncounterFlags) * 8;
}

u8 NuzlockeFlagSet(u16 mapsec)
{
    u16 id;

    if (!TryGetNuzlockeEncounterFlagIndex(mapsec, &id))
        return 0;

    gSaveBlock1Ptr->NuzlockeEncounterFlags[id / 8] |= 1 << (id & 7);
    return 0;
}

u8 NuzlockeFlagClear(u16 mapsec)
{
    u16 id;

    if (!TryGetNuzlockeEncounterFlagIndex(mapsec, &id))
        return 0;

    gSaveBlock1Ptr->NuzlockeEncounterFlags[id / 8] &= ~(1 << (id & 7));
    return 0;
}

u8 NuzlockeFlagGet(u16 mapsec)
{
    u16 id;

    if (!TryGetNuzlockeEncounterFlagIndex(mapsec, &id))
        return 0;

    return (gSaveBlock1Ptr->NuzlockeEncounterFlags[id / 8] >> (id & 7)) & 1;
}

static u16 GetSpeciesFamilyBase(u16 species)
{
    u8 depth = 0;
    u16 preEvolution;

    if (species == SPECIES_NONE || species >= NUM_SPECIES)
        return SPECIES_NONE;

    species = GET_BASE_SPECIES_ID(species);
    while ((preEvolution = GetSpeciesPreEvolution(species)) != SPECIES_NONE && depth++ < 12)
        species = GET_BASE_SPECIES_ID(preEvolution);

    return species;
}

static bool8 IsSpeciesCaughtForNuzlocke(u16 species)
{
    u16 dexNum;

    if (species == SPECIES_NONE || species >= NUM_SPECIES)
        return FALSE;

    dexNum = SpeciesToNationalPokedexNum(species);
    if (dexNum == NATIONAL_DEX_NONE || dexNum > NATIONAL_DEX_COUNT)
        return FALSE;

    return GetSetPokedexFlag(dexNum, FLAG_GET_CAUGHT);
}

static bool8 IsEvolutionLineCaughtForNuzlocke(u16 species, u8 depth)
{
    int i;
    const struct Evolution *evolutions;

    if (depth > 12)
        return FALSE;

    species = SanitizeSpeciesId(species);
    if (species == SPECIES_NONE)
        return FALSE;

    if (IsSpeciesCaughtForNuzlocke(species))
        return TRUE;

    evolutions = GetSpeciesEvolutions(species);
    if (evolutions == NULL)
        return FALSE;

    for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
    {
        u16 targetSpecies = SanitizeSpeciesId(evolutions[i].targetSpecies);

        if (targetSpecies == SPECIES_NONE || targetSpecies == species)
            continue;

        targetSpecies = GET_BASE_SPECIES_ID(targetSpecies);
        if (targetSpecies != species && IsEvolutionLineCaughtForNuzlocke(targetSpecies, depth + 1))
            return TRUE;
    }

    return FALSE;
}

u8 NuzlockeIsCaptureBlockedBySpeciesClause(u16 species)
{
    u16 baseSpecies;

    if (!gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause)
        return FALSE;

    if (species == SPECIES_NONE || species >= NUM_SPECIES)
        return FALSE;

    if (IsSpeciesCaughtForNuzlocke(species))
        return 2;

    baseSpecies = GetSpeciesFamilyBase(species);
    if (baseSpecies == SPECIES_NONE)
        return FALSE;

    if (IsEvolutionLineCaughtForNuzlocke(baseSpecies, 0))
        return TRUE;

    return FALSE;
}

u8 IsNuzlockeCaptureBlocked(u16 species)
{
    u8 speciesClause;

    if (!IsNuzlockeActive())
        return FALSE;

    speciesClause = NuzlockeIsCaptureBlockedBySpeciesClause(species);
    if (speciesClause)
        return speciesClause == 2 ? 3 : 2;

    if (NuzlockeFlagGet(NuzlockeGetCurrentRegionMapSectionId()))
        return 1;

    return FALSE;
}

static void ClearNuzlockeChecks(void)
{
    NuzlockeIsCaptureBlocked = FALSE;
    NuzlockeIsSpeciesClauseActive = FALSE;
    NuzlockeShouldSkipEncounterFlag = FALSE;
}

void SetNuzlockeChecks(void)
{
    u16 species = GetMonData(&gEnemyParty[0], MON_DATA_SPECIES);

    if (IsNuzlockeActive())
    {
        if (species == SPECIES_NONE || species >= NUM_SPECIES)
        {
            ClearNuzlockeChecks();
            return;
        }

        NuzlockeIsSpeciesClauseActive = NuzlockeIsCaptureBlockedBySpeciesClause(species);
        NuzlockeIsCaptureBlocked = NuzlockeFlagGet(NuzlockeGetCurrentRegionMapSectionId());

        if (IsMonShiny(&gEnemyParty[0]) && gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause)
        {
            NuzlockeIsCaptureBlocked = FALSE;
            NuzlockeIsSpeciesClauseActive = FALSE;
            NuzlockeShouldSkipEncounterFlag = TRUE;
        }
        else
        {
            NuzlockeShouldSkipEncounterFlag = FALSE;
        }
    }
    else
    {
        ClearNuzlockeChecks();
    }
}

void NuzlockeDeletePartyMon(u8 position)
{
    u8 nuzlockeRibbon = TRUE;
    u16 itemNone = ITEM_NONE;
    struct Pokemon *mon;
    u16 heldItem;

    if (position >= PARTY_SIZE)
        return;
    mon = &gPlayerParty[position];
    if (!GetMonData(mon, MON_DATA_SANITY_HAS_SPECIES, NULL))
        return;

    heldItem = GetMonData(mon, MON_DATA_HELD_ITEM, NULL);
    if (heldItem != ITEM_NONE)
    {
        AddBagItem(heldItem, 1);
        SetMonData(mon, MON_DATA_HELD_ITEM, &itemNone);
    }

    if (!gSaveBlock1Ptr->tx_Nuzlocke_Deletion)
    {
        SetMonData(mon, MON_DATA_NUZLOCKE_RIBBON, &nuzlockeRibbon);
        CopyMonToPC(mon);
    }
    ZeroMonData(mon);
}

void NuzlockeDeleteFaintedPartyPokemon(void)
{
    u8 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];

        if (GetMonData(mon, MON_DATA_SANITY_HAS_SPECIES, NULL)
            && !GetMonData(mon, MON_DATA_IS_EGG, NULL)
            && GetMonAilment(mon) == AILMENT_FNT)
            NuzlockeDeletePartyMon(i);
    }
    CompactPartySlots();
    CalculatePlayerPartyCount();
}
