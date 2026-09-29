#ifndef GUARD_DAY_NIGHT_H
#define GUARD_DAY_NIGHT_H

#define PALOVER_LIST_TERM 0xFF

struct PaletteOverride
{
    u8 slot;
    u8 startHour;
    u8 endHour;
    const u16 *palette;
};

extern EWRAM_DATA const struct PaletteOverride *gPaletteOverrides[];

u8 GetCurrentTimeOfDay(void);
void LoadCompressedPaletteDayNight(const u32 *src, u32 offset, u32 size);
void LoadPaletteDayNight(const void *src, u32 offset, u32 size);
void CheckClockForImmediateTimeEvents(void);
void ProcessImmediateTimeEvents(void);
void LoadCompressedPalette_HandleDayNight(const u32 *src, u32 offset, u32 size, bool32 isDayNight);
void LoadPalette_HandleDayNight(const void *src, u32 offset, u32 size, bool32 isDayNight);
void ClearDayNightPalette(u32 offset, u32 size);
const u16 *GetDayNightSourcePalette(u32 offset);

// Battles
void LoadBattleBgPaletteDayNight(const void *src, u32 offset, u32 size);
void LoadCompressedBattleBgPaletteDayNight(const u32 *src, u32 offset, u32 size);
void TintBattleSpritePaletteDayNight(const u16 *src, u32 offset);
void TintCompressedBattleSpritePaletteDayNight(const u32 *src, u32 offset);
void TintBattleSpritePaletteColorDayNight(u32 offset, u16 color);

#endif // GUARD_DAY_NIGHT_H
