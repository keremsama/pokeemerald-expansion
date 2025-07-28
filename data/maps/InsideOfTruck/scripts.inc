# 1 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_MapScripts::
# 2 "data/maps/InsideOfTruck/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, InsideOfTruck_OnLoad
# 3 "data/maps/InsideOfTruck/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, InsideOfTruck_OnResume
# 4 "data/maps/InsideOfTruck/scripts.pory"
	.byte 0
# 5 "data/maps/InsideOfTruck/scripts.pory"

# 6 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_OnLoad:
# 7 "data/maps/InsideOfTruck/scripts.pory"
	setmetatile 4, 1, METATILE_InsideOfTruck_ExitLight_Top, FALSE
# 8 "data/maps/InsideOfTruck/scripts.pory"
	setmetatile 4, 2, METATILE_InsideOfTruck_ExitLight_Mid, FALSE
# 9 "data/maps/InsideOfTruck/scripts.pory"
	setmetatile 4, 3, METATILE_InsideOfTruck_ExitLight_Bottom, FALSE
# 10 "data/maps/InsideOfTruck/scripts.pory"
	end
# 11 "data/maps/InsideOfTruck/scripts.pory"

# 12 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_OnResume:
# 13 "data/maps/InsideOfTruck/scripts.pory"
	setstepcallback STEP_CB_TRUCK
# 14 "data/maps/InsideOfTruck/scripts.pory"
	end
# 15 "data/maps/InsideOfTruck/scripts.pory"

# 16 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_SetIntroFlags::
# 17 "data/maps/InsideOfTruck/scripts.pory"
	lockall
# 18 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_MAP_NAME_POPUP
# 19 "data/maps/InsideOfTruck/scripts.pory"
	checkplayergender
# 20 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_eq VAR_RESULT, MALE, InsideOfTruck_EventScript_SetIntroFlagsMale
# 21 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_eq VAR_RESULT, FEMALE, InsideOfTruck_EventScript_SetIntroFlagsFemale
# 22 "data/maps/InsideOfTruck/scripts.pory"
	end
# 23 "data/maps/InsideOfTruck/scripts.pory"

# 24 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_SetIntroFlagsMale::
# 25 "data/maps/InsideOfTruck/scripts.pory"
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
# 26 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_INTRO_STATE, 1
# 27 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MOM
# 28 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
# 29 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_MOM
# 30 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_SIBLING
# 31 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
# 32 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 1
# 33 "data/maps/InsideOfTruck/scripts.pory"
	setdynamicwarp MAP_LITTLEROOT_TOWN, 3, 10
# 34 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
# 35 "data/maps/InsideOfTruck/scripts.pory"
    call FadeScreenBlack
# 36 "data/maps/InsideOfTruck/scripts.pory"
	end
# 37 "data/maps/InsideOfTruck/scripts.pory"

# 38 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_SetIntroFlagsFemale::
# 39 "data/maps/InsideOfTruck/scripts.pory"
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F
# 40 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_INTRO_STATE, 2
# 41 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_MOM
# 42 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
# 43 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_MOM
# 44 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_SIBLING
# 45 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
# 46 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 1
# 47 "data/maps/InsideOfTruck/scripts.pory"
	setdynamicwarp MAP_LITTLEROOT_TOWN, 12, 10
# 48 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
# 49 "data/maps/InsideOfTruck/scripts.pory"
    call FadeScreenBlack
# 50 "data/maps/InsideOfTruck/scripts.pory"
	end
# 51 "data/maps/InsideOfTruck/scripts.pory"

# 52 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_MovingBox::
# 53 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_Text_BoxPrintedWithMonLogo, MSGBOX_SIGN
# 54 "data/maps/InsideOfTruck/scripts.pory"
	end
# 55 "data/maps/InsideOfTruck/scripts.pory"

# 56 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_Text_BoxPrintedWithMonLogo:
# 57 "data/maps/InsideOfTruck/scripts.pory"
	.string "The box is printed with a POKéMON logo.\p"
# 58 "data/maps/InsideOfTruck/scripts.pory"
	.string "It's a POKéMON brand moving and\n"
# 59 "data/maps/InsideOfTruck/scripts.pory"
	.string "delivery service.$"

FadeScreenBlack::
# 65 "data/maps/InsideOfTruck/scripts.pory"
	lock
# 66 "data/maps/InsideOfTruck/scripts.pory"
	fadescreen FADE_TO_BLACK
# 67 "data/maps/InsideOfTruck/scripts.pory"
	call Randomizer_Option_Setup
	end


Randomizer_Option_Setup::
# 73 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Option_Setup_Text_0, MSGBOX_YESNO
# 74 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Option_Setup_1
# 81 "data/maps/InsideOfTruck/scripts.pory"
	playse SE_PC_OFF
# 82 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Option_Setup_Text_2
# 83 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_WILD_MON
# 84 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_FIELD_ITEMS
# 85 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_TRAINER_MON
# 86 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_FIXED_MON
# 87 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_STARTERS
# 88 "data/maps/InsideOfTruck/scripts.pory"
	waitmessage
# 89 "data/maps/InsideOfTruck/scripts.pory"
	closemessage
# 90 "data/maps/InsideOfTruck/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 91 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
	end

Randomizer_Option_Setup_1:
# 75 "data/maps/InsideOfTruck/scripts.pory"
	playse SE_PC_ON
# 76 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Option_Setup_Text_1
# 77 "data/maps/InsideOfTruck/scripts.pory"
	waitmessage
# 78 "data/maps/InsideOfTruck/scripts.pory"
	call Randomizer_Settings
	return


Randomizer_Settings::
# 97 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_0, MSGBOX_YESNO
# 98 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_2
# 102 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_WILD_MON
Randomizer_Settings_1:
# 104 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_1, MSGBOX_YESNO
# 105 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_6
# 109 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_STARTERS
Randomizer_Settings_5:
# 111 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_2, MSGBOX_YESNO
# 112 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_10
# 116 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_TRAINER_MON
Randomizer_Settings_9:
# 118 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_3, MSGBOX_YESNO
# 119 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_14
# 123 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_FIXED_MON
Randomizer_Settings_13:
# 125 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_4, MSGBOX_YESNO
# 126 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_18
# 130 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_EGG_MON
Randomizer_Settings_17:
# 132 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_5, MSGBOX_YESNO
# 133 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_22
# 137 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_ABILITIES
Randomizer_Settings_21:
# 139 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_6, MSGBOX_YESNO
# 140 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_26
# 144 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_FIELD_ITEMS
Randomizer_Settings_25:
# 146 "data/maps/InsideOfTruck/scripts.pory"
	waitmessage
# 147 "data/maps/InsideOfTruck/scripts.pory"
	call Randomizer_Species_Mode
	return

Randomizer_Settings_2:
# 99 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_WILD_MON
	goto Randomizer_Settings_1

Randomizer_Settings_6:
# 106 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_STARTERS
	goto Randomizer_Settings_5

Randomizer_Settings_10:
# 113 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_TRAINER_MON
	goto Randomizer_Settings_9

Randomizer_Settings_14:
# 120 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_FIXED_MON
	goto Randomizer_Settings_13

Randomizer_Settings_18:
# 127 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_EGG_MON
	goto Randomizer_Settings_17

Randomizer_Settings_22:
# 134 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_ABILITIES
	goto Randomizer_Settings_21

Randomizer_Settings_26:
# 141 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_FIELD_ITEMS
	goto Randomizer_Settings_25


Randomizer_Species_Mode::
# 151 "data/maps/InsideOfTruck/scripts.pory"
	message Randomizer_Species_Mode_Text_0
# 152 "data/maps/InsideOfTruck/scripts.pory"
	waitmessage
# 153 "data/maps/InsideOfTruck/scripts.pory"
	multichoice 25, 3, MULTI_RANDOMIZER_SPECIES_CHOICE, 1
# 154 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Randomizer_Species_Mode_2
# 157 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Randomizer_Species_Mode_3
# 160 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq Randomizer_Species_Mode_4
# 163 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq Randomizer_Species_Mode_5
Randomizer_Species_Mode_1:
# 166 "data/maps/InsideOfTruck/scripts.pory"
	closemessage
# 167 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Species_Mode_Text_1
# 168 "data/maps/InsideOfTruck/scripts.pory"
	playse SE_SAVE
# 169 "data/maps/InsideOfTruck/scripts.pory"
	waitse
# 170 "data/maps/InsideOfTruck/scripts.pory"
	waitmessage
# 171 "data/maps/InsideOfTruck/scripts.pory"
	closemessage
# 172 "data/maps/InsideOfTruck/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 173 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
	end

Randomizer_Species_Mode_2:
# 155 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_RANDOM_SPECIES_MODE, 0
	goto Randomizer_Species_Mode_1

Randomizer_Species_Mode_3:
# 158 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_RANDOM_SPECIES_MODE, 1
	goto Randomizer_Species_Mode_1

Randomizer_Species_Mode_4:
# 161 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_RANDOM_SPECIES_MODE, 2
	goto Randomizer_Species_Mode_1

Randomizer_Species_Mode_5:
# 164 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_RANDOM_SPECIES_MODE, 3
	goto Randomizer_Species_Mode_1


Randomizer_Option_Setup_Text_0:
# 73 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE the game?$"

Randomizer_Option_Setup_Text_1:
# 76 "data/maps/InsideOfTruck/scripts.pory"
	.string "RANDOMIZER is ON!$"

Randomizer_Option_Setup_Text_2:
# 82 "data/maps/InsideOfTruck/scripts.pory"
	.string "Randomizer is OFF!$"

Randomizer_Settings_Text_0:
# 97 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE WILD\nPokémon?$"

Randomizer_Settings_Text_1:
# 104 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE STARTER\nPokémon?$"

Randomizer_Settings_Text_2:
# 111 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE TRAINER\nPokémon?$"

Randomizer_Settings_Text_3:
# 118 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE STATIC\nPokémon?$"

Randomizer_Settings_Text_4:
# 125 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE EGG\nPokémon?$"

Randomizer_Settings_Text_5:
# 132 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE Pokémon\nABILITIES?$"

Randomizer_Settings_Text_6:
# 139 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE\nFIELD ITEMS?$"

Randomizer_Species_Mode_Text_0:
# 151 "data/maps/InsideOfTruck/scripts.pory"
	.string "Which mode would you like to use?$"

Randomizer_Species_Mode_Text_1:
# 167 "data/maps/InsideOfTruck/scripts.pory"
	.string "RANDOMIZER settings have been saved!$"
