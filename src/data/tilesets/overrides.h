#include "constants/day_night.h"

static const u16 sTilesetPalOverride_General01_05[] = INCBIN_U16("data/tilesets/primary/general/override_palettes/01_05.gbapal");
static const u16 sTilesetPalOverride_Petalburg06_08[] = INCBIN_U16("data/tilesets/secondary/petalburg/override_palettes/06_08.gbapal");

#define OVERRIDES_END { .slot = PALOVER_LIST_TERM }

const struct PaletteOverride gTilesetPalOverrides_General[] =
{
    {
        .slot = 1,
        .startHour = HOUR_NIGHT,
        .endHour = HOUR_MORNING,
        .palette = sTilesetPalOverride_General01_05,
    },
    {
        .slot = 5,
        .startHour = HOUR_NIGHT,
        .endHour = HOUR_MORNING,
        .palette = sTilesetPalOverride_General01_05,
    },
    OVERRIDES_END
};

const struct PaletteOverride gTilesetPalOverrides_Petalburg[] =
{
    {
        .slot = 6,
        .startHour = HOUR_NIGHT,
        .endHour = HOUR_MORNING,
        .palette = sTilesetPalOverride_Petalburg06_08,
    },
    {
        .slot = 8,
        .startHour = HOUR_NIGHT,
        .endHour = HOUR_MORNING,
        .palette = sTilesetPalOverride_Petalburg06_08,
    },
    OVERRIDES_END
};

// Rustboro's fountain uses the window colors of the General tileset's palette 5
const struct PaletteOverride gTilesetPalOverrides_Rustboro[] =
{
    {
        .slot = 5,
        .startHour = HOUR_NIGHT,
        .endHour = HOUR_MORNING,
        .palette = NULL,
    },
    OVERRIDES_END
};
