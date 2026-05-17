#ifndef GUARD_TX_RANDOMIZER_AND_CHALLENGES_H
#define GUARD_TX_RANDOMIZER_AND_CHALLENGES_H

extern u8 NuzlockeIsCaptureBlocked;
extern u8 NuzlockeIsSpeciesClauseActive;
extern u8 NuzlockeShouldSkipEncounterFlag;

bool8 IsNuzlockeActive(void);
bool8 IsNuzlockeDeathRulesActive(void);
bool8 IsNuzlockeNicknamingActive(void);
u8 IsNuzlockeCaptureBlocked(u16 species);
u8 NuzlockeGetCurrentRegionMapSectionId(void);
u8 NuzlockeFlagGet(u16 mapsec);
u8 NuzlockeFlagSet(u16 mapsec);
u8 NuzlockeFlagClear(u16 mapsec);
u8 NuzlockeIsCaptureBlockedBySpeciesClause(u16 species);
void SetNuzlockeChecks(void);
void NuzlockeDeletePartyMon(u8 position);
void NuzlockeDeleteFaintedPartyPokemon(void);

#endif // GUARD_TX_RANDOMIZER_AND_CHALLENGES_H
