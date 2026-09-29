#include "global.h"
#include "day_night.h"
#include "decompress.h"
#include "event_data.h"
#include "field_tasks.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "malloc.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "rtc.h"
#include "constants/day_night.h"
#include "constants/rgb.h"

#define TINT_MORNING Q_8_8(0.7), Q_8_8(0.7), Q_8_8(0.9)
#define TINT_DAY     Q_8_8(1.0), Q_8_8(1.0), Q_8_8(1.0)
#define TINT_NIGHT   Q_8_8(0.6), Q_8_8(0.6), Q_8_8(0.92)

// Untinted copy of every palette that was loaded with day/night tinting.
// Entries of palettes loaded without tinting are kept at 0 (RGB_BLACK), which the retint skips.
EWRAM_DATA static u16 sPlttBufferPreDN[PLTT_BUFFER_SIZE] = {0};
EWRAM_DATA const struct PaletteOverride *gPaletteOverrides[4] = {NULL};

static EWRAM_DATA struct {
    bool8 initialized:1;
    bool8 retintPhase:1;
    u8 timeOfDay;
    u32 prevTintPeriod;
    u32 currTintPeriod;
    u16 currRGBTint[3];
} sDNSystemControl = {0};

static const u16 sTimeOfDayTints[][3] =
{
    [0] =  {TINT_NIGHT},
    [1] =  {TINT_NIGHT},
    [2] =  {TINT_NIGHT},
    [3] =  {TINT_NIGHT},
    [4] =  {Q_8_8(0.6), Q_8_8(0.65), Q_8_8(1.0)},
    [5] =  {TINT_MORNING},
    [6] =  {TINT_MORNING},
    [7] =  {TINT_MORNING},
    [8] =  {Q_8_8(0.9), Q_8_8(0.85), Q_8_8(1.0)},
    [9] =  {Q_8_8(1.0), Q_8_8(0.9), Q_8_8(1.0)},
    [10] = {TINT_DAY},
    [11] = {TINT_DAY},
    [12] = {TINT_DAY},
    [13] = {TINT_DAY},
    [14] = {TINT_DAY},
    [15] = {TINT_DAY},
    [16] = {TINT_DAY},
    [17] = {Q_8_8(1.0), Q_8_8(0.98), Q_8_8(0.9)},
    [18] = {Q_8_8(0.9), Q_8_8(0.7), Q_8_8(0.67)},
    [19] = {Q_8_8(0.75), Q_8_8(0.66), Q_8_8(0.77)},
    [20] = {Q_8_8(0.7), Q_8_8(0.63), Q_8_8(0.82)},
    [21] = {TINT_NIGHT},
    [22] = {TINT_NIGHT},
    [23] = {TINT_NIGHT},
};

u8 GetCurrentTimeOfDay(void)
{
    if (IsBetweenHours(gLocalTime.hours, MORNING_HOUR_BEGIN, MORNING_HOUR_END))
        return TIME_MORNING;
    else if (IsBetweenHours(gLocalTime.hours, EVENING_HOUR_BEGIN, EVENING_HOUR_END))
        return TIME_EVENING;
    else if (IsBetweenHours(gLocalTime.hours, NIGHT_HOUR_BEGIN, NIGHT_HOUR_END))
        return TIME_NIGHT;

    return TIME_DAY;
}

static bool32 IsOverrideActive(const struct PaletteOverride *override, s8 hour)
{
    return (override->startHour < override->endHour && hour >= override->startHour && hour < override->endHour)
        || (override->startHour > override->endHour && (hour >= override->startHour || hour < override->endHour));
}

static void LoadPaletteOverrides(void)
{
    u32 i, j;
    u32 blockedSlots = 0;
    s8 hour = gLocalTime.hours;

    // An entry without palette blocks every override of that slot, e.g. so a secondary tileset
    // can keep a primary tileset palette from being overridden when it uses those colors differently
    for (i = 0; i < ARRAY_COUNT(gPaletteOverrides); i++)
    {
        const struct PaletteOverride *curr = gPaletteOverrides[i];
        for (; curr != NULL && curr->slot != PALOVER_LIST_TERM; curr++)
        {
            if (curr->palette == NULL && IsOverrideActive(curr, hour))
                blockedSlots |= 1 << curr->slot;
        }
    }

    for (i = 0; i < ARRAY_COUNT(gPaletteOverrides); i++)
    {
        const struct PaletteOverride *curr = gPaletteOverrides[i];
        for (; curr != NULL && curr->slot != PALOVER_LIST_TERM; curr++)
        {
            if (curr->palette != NULL && !(blockedSlots & (1 << curr->slot)) && IsOverrideActive(curr, hour))
            {
                const u16 *src = curr->palette;
                u16 *dest = &gPlttBufferUnfaded[curr->slot * 16];

                for (j = 0; j < 16; j++, src++, dest++)
                {
                    if (*src != RGB_BLACK)
                        *dest = *src;
                }
            }
        }
    }
}

static void LerpColors(u16 *rgbDest, s32 hour, s32 nextHour, u8 coeff)
{
    const u16 *rgb1 = sTimeOfDayTints[hour];
    const u16 *rgb2 = sTimeOfDayTints[nextHour];
    u16 rgbTemp[3];

    memcpy(rgbTemp, rgb1, sizeof(rgbTemp));

    if (rgb1[0] != rgb2[0] || rgb1[1] != rgb2[1] || rgb1[2] != rgb2[2])
    {
        rgbTemp[0] = (((rgb2[0] - rgb1[0]) * coeff) / TINT_PERIODS_PER_HOUR) + rgb1[0];
        rgbTemp[1] = (((rgb2[1] - rgb1[1]) * coeff) / TINT_PERIODS_PER_HOUR) + rgb1[1];
        rgbTemp[2] = (((rgb2[2] - rgb1[2]) * coeff) / TINT_PERIODS_PER_HOUR) + rgb1[2];
    }

    if (rgbTemp[0] != rgbDest[0] || rgbTemp[1] != rgbDest[1] || rgbTemp[2] != rgbDest[2])
        memcpy(rgbDest, rgbTemp, sizeof(rgbTemp));
}

static void TintPalette_CustomToneWithCopy(const u16 *src, u16 *dest, u32 count, u16 rTone, u16 gTone, u16 bTone, bool32 excludeZeroes)
{
    u32 i;

    for (i = 0; i < count; i++, src++, dest++)
    {
        s32 r, g, b;

        if (excludeZeroes && *src == RGB_BLACK)
            continue;

        r = GET_R(*src);
        g = GET_G(*src);
        b = GET_B(*src);

        r = (u16)(rTone * r) >> 8;
        g = (u16)(gTone * g) >> 8;
        b = (u16)(bTone * b) >> 8;

        if (r > 31)
            r = 31;
        if (g > 31)
            g = 31;
        if (b > 31)
            b = 31;

        *dest = RGB2(r, g, b);
    }
}

// Reads the RTC and updates currRGBTint if the tint period changed
static void UpdateCurrentTint(void)
{
    s8 hour, nextHour;
    u8 hourPhase;
    u32 period;

    RtcCalcLocalTimeFast();

    hour = gLocalTime.hours;
    hourPhase = gLocalTime.minutes / MINUTES_PER_TINT_PERIOD;
    period = (hour * TINT_PERIODS_PER_HOUR) + hourPhase;

    if (!sDNSystemControl.initialized || sDNSystemControl.currTintPeriod != period)
    {
        sDNSystemControl.initialized = TRUE;
        sDNSystemControl.currTintPeriod = period;
        nextHour = (hour + 1) % 24;
        LerpColors(sDNSystemControl.currRGBTint, hour, nextHour, hourPhase);
    }
}

static void TintPaletteForDayNight(u32 offset, u32 size)
{
    if (IsMapTypeOutdoors(gMapHeader.mapType))
    {
        UpdateCurrentTint();
        TintPalette_CustomToneWithCopy(&sPlttBufferPreDN[offset], &gPlttBufferUnfaded[offset], size / 2, sDNSystemControl.currRGBTint[0], sDNSystemControl.currRGBTint[1], sDNSystemControl.currRGBTint[2], FALSE);
        LoadPaletteOverrides();
    }
    else
    {
        CpuCopy16(&sPlttBufferPreDN[offset], &gPlttBufferUnfaded[offset], size);
    }
}

void LoadCompressedPaletteDayNight(const u32 *src, u32 offset, u32 size)
{
    LoadCompressedPalette_HandleDayNight(src, offset, size, TRUE);
}

void LoadPaletteDayNight(const void *src, u32 offset, u32 size)
{
    LoadPalette_HandleDayNight(src, offset, size, TRUE);
}

// Forget the untinted copy of a palette range, so the periodic retint leaves it alone.
// Needed whenever a slot is reused for something that isn't day/night tinted.
void ClearDayNightPalette(u32 offset, u32 size)
{
    CpuFill16(RGB_BLACK, &sPlttBufferPreDN[offset], size);
}

// Returns the untinted colors of a palette that was loaded with day/night tinting, or NULL
const u16 *GetDayNightSourcePalette(u32 offset)
{
    u32 i;

    for (i = 0; i < 16; i++)
    {
        if (sPlttBufferPreDN[offset + i] != RGB_BLACK)
            return &sPlttBufferPreDN[offset];
    }
    return NULL;
}

void CheckClockForImmediateTimeEvents(void)
{
    if (!sDNSystemControl.retintPhase && IsMapTypeOutdoors(gMapHeader.mapType))
        RtcCalcLocalTimeFast();
}

void ProcessImmediateTimeEvents(void)
{
    u32 period;

    if (IsMapTypeOutdoors(gMapHeader.mapType))
    {
        if (sDNSystemControl.retintPhase)
        {
            u32 paletteIndex;

            sDNSystemControl.retintPhase = FALSE;
            TintPalette_CustomToneWithCopy(&sPlttBufferPreDN[OBJ_PLTT_OFFSET], &gPlttBufferUnfaded[OBJ_PLTT_OFFSET], OBJ_PLTT_SIZE / 2, sDNSystemControl.currRGBTint[0], sDNSystemControl.currRGBTint[1], sDNSystemControl.currRGBTint[2], TRUE);
            LoadPaletteOverrides();

            // Don't touch the faded buffer while the screen is (being) faded, the fade reads from the unfaded buffer anyway
            if (gWeatherPtr->palProcessingState != WEATHER_PAL_STATE_SCREEN_FADING_IN
             && gWeatherPtr->palProcessingState != WEATHER_PAL_STATE_SCREEN_FADING_OUT
             && !gPaletteFade.active)
            {
                CpuCopy16(gPlttBufferUnfaded, gPlttBufferFaded, PLTT_SIZE);

                for (paletteIndex = 0; paletteIndex < NUM_PALS_TOTAL; paletteIndex++)
                    ApplyWeatherColorMapToPal(paletteIndex);
                for (paletteIndex = 0; paletteIndex < 16; paletteIndex++)
                    UpdateSpritePaletteWithWeather(paletteIndex);
            }
        }
        else
        {
            s8 hour, nextHour;
            u8 hourPhase;

            hour = gLocalTime.hours;
            hourPhase = gLocalTime.minutes / MINUTES_PER_TINT_PERIOD;
            period = (hour * TINT_PERIODS_PER_HOUR) + hourPhase;

            if (!sDNSystemControl.initialized || sDNSystemControl.prevTintPeriod != period)
            {
                sDNSystemControl.initialized = TRUE;
                sDNSystemControl.prevTintPeriod = sDNSystemControl.currTintPeriod = period;
                nextHour = (hour + 1) % 24;
                LerpColors(sDNSystemControl.currRGBTint, hour, nextHour, hourPhase);
                TintPalette_CustomToneWithCopy(sPlttBufferPreDN, gPlttBufferUnfaded, BG_PLTT_SIZE / 2, sDNSystemControl.currRGBTint[0], sDNSystemControl.currRGBTint[1], sDNSystemControl.currRGBTint[2], TRUE);
                sDNSystemControl.retintPhase = TRUE;
            }
        }
    }

    period = GetCurrentTimeOfDay();
    if (sDNSystemControl.timeOfDay != period)
    {
        sDNSystemControl.timeOfDay = period;
        ForceTimeBasedEvents();
    }
}

void LoadCompressedPalette_HandleDayNight(const u32 *src, u32 offset, u32 size, bool32 isDayNight)
{
    void *buffer = malloc_and_decompress(src, NULL);
    LoadPalette_HandleDayNight(buffer, offset, size, isDayNight);
    Free(buffer);
}

void LoadPalette_HandleDayNight(const void *src, u32 offset, u32 size, bool32 isDayNight)
{
    if (isDayNight)
    {
        CpuCopy16(src, &sPlttBufferPreDN[offset], size);
        TintPaletteForDayNight(offset, size);
        CpuCopy16(&gPlttBufferUnfaded[offset], &gPlttBufferFaded[offset], size);
    }
    else
    {
        ClearDayNightPalette(offset, size);
        CpuCopy16(src, &gPlttBufferUnfaded[offset], size);
        CpuCopy16(src, &gPlttBufferFaded[offset], size);
    }
}

// Battle day/night tinting (based on Kasen's battle-dns branch)
// Battles don't retint over time, so the palettes are tinted once when they are loaded.
// The tint always starts from the given untinted source, so loading the same palette twice can't tint it twice.

static bool32 GetBattleTint(u16 *rgbTint, u32 blendLevel)
{
    u32 i;

    if (!IsMapTypeOutdoors(gMapHeader.mapType) || blendLevel == 0)
        return FALSE;

    UpdateCurrentTint();
    for (i = 0; i < 3; i++)
    {
        s32 tone = sDNSystemControl.currRGBTint[i];
        rgbTint[i] = Q_8_8(1.0) + (((tone - Q_8_8(1.0)) * (s32)blendLevel) / 100);
    }
    return TRUE;
}

static void TintBattlePalette(const u16 *src, u32 offset, u32 size, u32 blendLevel)
{
    u16 rgbTint[3];

    if (GetBattleTint(rgbTint, blendLevel))
    {
        TintPalette_CustomToneWithCopy(src, &gPlttBufferUnfaded[offset], size / 2, rgbTint[0], rgbTint[1], rgbTint[2], FALSE);
        CpuCopy16(&gPlttBufferUnfaded[offset], &gPlttBufferFaded[offset], size);
    }
}

void LoadBattleBgPaletteDayNight(const void *src, u32 offset, u32 size)
{
    LoadPalette(src, offset, size);
    if (B_APPLY_DNS_TO_BACKGROUND)
        TintBattlePalette(src, offset, size, 100);
}

void LoadCompressedBattleBgPaletteDayNight(const u32 *src, u32 offset, u32 size)
{
    void *buffer = malloc_and_decompress(src, NULL);
    LoadBattleBgPaletteDayNight(buffer, offset, size);
    Free(buffer);
}

// Tints a sprite palette that was already loaded to 'offset' from the untinted colors in 'src'
void TintBattleSpritePaletteDayNight(const u16 *src, u32 offset)
{
    if (B_APPLY_DNS_TO_SPRITES)
        TintBattlePalette(src, offset, PLTT_SIZE_4BPP, B_SPRITE_BLEND_LEVEL);
}

void TintCompressedBattleSpritePaletteDayNight(const u32 *src, u32 offset)
{
    void *buffer;

    if (!B_APPLY_DNS_TO_SPRITES)
        return;

    buffer = malloc_and_decompress(src, NULL);
    TintBattleSpritePaletteDayNight(buffer, offset);
    Free(buffer);
}

// Darkens single colors of a sprite palette, e.g. the shadow under the opponent's Pokémon
void TintBattleSpritePaletteColorDayNight(u32 offset, u16 color)
{
    u16 rgbTint[3];

    if (B_APPLY_DNS_TO_BACKGROUND && GetBattleTint(rgbTint, 100))
    {
        TintPalette_CustomToneWithCopy(&color, &gPlttBufferUnfaded[offset], 1, rgbTint[0], rgbTint[1], rgbTint[2], FALSE);
        gPlttBufferFaded[offset] = gPlttBufferUnfaded[offset];
    }
}
