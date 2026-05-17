#ifndef GUARD_HEAT_START_MENU_H
#define GUARD_HEAT_START_MENU_H

#include "global.h"

void HeatStartMenu_Init(void);
void GoToHandleInput(void);
const u16 *GetStartMenuPalette(u8 id);

#define MENU_PAL_COUNT 4
#define DEFAULT_START_MENU_PALETTE 0

#endif // GUARD_HEAT_START_MENU_H
