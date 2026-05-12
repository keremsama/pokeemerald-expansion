#ifndef GUARD_RANDOMIZER_NUZLOCKE_MENU_H
#define GUARD_RANDOMIZER_NUZLOCKE_MENU_H

void CB2_InitRandomizerNuzlockeMenu(void);
void ApplyNewGameRandomizerNuzlockeSettings(void);

bool8 IsNuzlockeActive(void);
bool8 IsNuzlockeDeathRulesActive(void);
bool8 IsNuzlockeNicknamingActive(void);
bool8 IsNuzlockeCaptureBlocked(u16 species);
u8 NuzlockeFlagGet(u16 mapsec);
u8 NuzlockeFlagSet(u16 mapsec);
u8 NuzlockeFlagClear(u16 mapsec);
void NuzlockeDeleteFaintedPartyPokemon(void);

#endif // GUARD_RANDOMIZER_NUZLOCKE_MENU_H
