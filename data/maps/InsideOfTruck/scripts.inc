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
	msgbox InsideOfTruck_Text_SkipIntro, MSGBOX_YESNO
# 20 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_eq VAR_RESULT, YES, InsideOfTruck_EventScript_IntroSkipStart
# 21 "data/maps/InsideOfTruck/scripts.pory"
	checkplayergender
# 22 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_eq VAR_RESULT, MALE, InsideOfTruck_EventScript_SetIntroFlagsMale
# 23 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_eq VAR_RESULT, FEMALE, InsideOfTruck_EventScript_SetIntroFlagsFemale
# 24 "data/maps/InsideOfTruck/scripts.pory"
	end
# 25 "data/maps/InsideOfTruck/scripts.pory"

# 26 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_SetIntroFlagsMale::
# 27 "data/maps/InsideOfTruck/scripts.pory"
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
# 28 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_INTRO_STATE, 1
# 29 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MOM
# 30 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
# 31 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_MOM
# 32 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_SIBLING
# 33 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
# 34 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 1
# 35 "data/maps/InsideOfTruck/scripts.pory"
	setdynamicwarp MAP_LITTLEROOT_TOWN, 3, 10
# 36 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
# 37 "data/maps/InsideOfTruck/scripts.pory"
	end
# 38 "data/maps/InsideOfTruck/scripts.pory"

# 39 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_SetIntroFlagsFemale::
# 40 "data/maps/InsideOfTruck/scripts.pory"
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F
# 41 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_INTRO_STATE, 2
# 42 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_MOM
# 43 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
# 44 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_MOM
# 45 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_SIBLING
# 46 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
# 47 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 1
# 48 "data/maps/InsideOfTruck/scripts.pory"
	setdynamicwarp MAP_LITTLEROOT_TOWN, 12, 10
# 49 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
# 50 "data/maps/InsideOfTruck/scripts.pory"
	end
# 51 "data/maps/InsideOfTruck/scripts.pory"

# 52 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_IntroSkipStart::
# 53 "data/maps/InsideOfTruck/scripts.pory"
	checkplayergender
# 54 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_eq VAR_RESULT, MALE, InsideOfTruck_EventScript_IntroSkipMale
# 55 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_eq VAR_RESULT, FEMALE, InsideOfTruck_EventScript_IntroSkipFemale
# 56 "data/maps/InsideOfTruck/scripts.pory"
	end
# 57 "data/maps/InsideOfTruck/scripts.pory"

# 58 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_IntroSkipMale::
# 59 "data/maps/InsideOfTruck/scripts.pory"
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
# 60 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MOM
# 61 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
# 62 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_MOM
# 63 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_SIBLING
# 64 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
# 65 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
# 66 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
# 67 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
# 68 "data/maps/InsideOfTruck/scripts.pory"
	goto InsideOfTruck_EventScript_IntroSkipCommon
# 69 "data/maps/InsideOfTruck/scripts.pory"

# 70 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_IntroSkipFemale::
# 71 "data/maps/InsideOfTruck/scripts.pory"
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F
# 72 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_MOM
# 73 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
# 74 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_MOM
# 75 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_SIBLING
# 76 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
# 77 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
# 78 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
# 79 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
# 80 "data/maps/InsideOfTruck/scripts.pory"
	goto InsideOfTruck_EventScript_IntroSkipCommon
# 81 "data/maps/InsideOfTruck/scripts.pory"

# 82 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_IntroSkipCommon::
# 83 "data/maps/InsideOfTruck/scripts.pory"
	call New_Birch_Bag_NoBattle
# 84 "data/maps/InsideOfTruck/scripts.pory"
	bufferleadmonspeciesname STR_VAR_1
# 85 "data/maps/InsideOfTruck/scripts.pory"
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
# 86 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, InsideOfTruck_EventScript_IntroSkipNicknameStarter
# 87 "data/maps/InsideOfTruck/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 88 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_eq VAR_RESULT, YES, InsideOfTruck_EventScript_IntroSkipNicknameStarter
# 89 "data/maps/InsideOfTruck/scripts.pory"
	goto InsideOfTruck_EventScript_IntroSkipFinalize
# 90 "data/maps/InsideOfTruck/scripts.pory"

# 91 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_IntroSkipNicknameStarter::
# 92 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_0x8004, 0
# 93 "data/maps/InsideOfTruck/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 94 "data/maps/InsideOfTruck/scripts.pory"
	goto InsideOfTruck_EventScript_IntroSkipFinalize
# 95 "data/maps/InsideOfTruck/scripts.pory"

# 96 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_IntroSkipFinalize::
# 97 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_VISITED_LITTLEROOT_TOWN
# 98 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_MET_RIVAL_MOM
# 99 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 100 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RESCUED_BIRCH
# 101 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE
# 102 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_ROUTE_101_ZIGZAGOON
# 103 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
# 104 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_ROUTE_101_BIRCH
# 105 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_ROUTE_103_BIRCH
# 106 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_ROUTE_103_RIVAL
# 107 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_ROUTE103
# 108 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RIVAL_LEFT_FOR_ROUTE103
# 109 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
# 110 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
# 111 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
# 112 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_BRENDAN
# 113 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MAY
# 114 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_POKEBALL_CYNDAQUIL
# 115 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_POKEBALL_TOTODILE
# 116 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_POKEBALL_CHIKORITA
# 117 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
# 118 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_PLAYERS_BEDROOM_MOM
# 119 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_PLAYERS_HOUSE_VIGOROTH_1
# 120 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_PLAYERS_HOUSE_VIGOROTH_2
# 121 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_SET_WALL_CLOCK
# 122 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RECEIVED_RUNNING_SHOES
# 123 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_SYS_B_DASH
# 124 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_HIDE_ROUTE_101_BOY
# 125 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
# 126 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
# 127 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_HIDE_MAP_NAME_POPUP
# 128 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_SYS_POKEDEX_GET
# 129 "data/maps/InsideOfTruck/scripts.pory"
	special SetUnlockedPokedexFlags
# 130 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
# 131 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_unset FLAG_RANDOM_WILD_MON, InsideOfTruck_EventScript_IntroSkipNoNationalDex
# 132 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_SYS_NATIONAL_DEX
# 133 "data/maps/InsideOfTruck/scripts.pory"
	special EnableNationalPokedex
# 134 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_IntroSkipNoNationalDex::
# 135 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 1
# 136 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 137 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_BIRCH_LAB_STATE, 5
# 138 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_ROUTE101_STATE, 3
# 139 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_OLDALE_TOWN_STATE, 1
# 140 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_OLDALE_RIVAL_STATE, 2
# 141 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 4
# 142 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_INTRO_STATE, 7
# 143 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 2
# 144 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2
# 145 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_RIVAL_STATE, 4
# 146 "data/maps/InsideOfTruck/scripts.pory"
	additem ITEM_POKE_BALL, 10
# 147 "data/maps/InsideOfTruck/scripts.pory"
	special HealPlayerParty
# 148 "data/maps/InsideOfTruck/scripts.pory"
	checkplayergender
# 149 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_eq VAR_RESULT, MALE, InsideOfTruck_EventScript_IntroSkipWarpBrendansHouse
# 150 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_eq VAR_RESULT, FEMALE, InsideOfTruck_EventScript_IntroSkipWarpMaysHouse
# 151 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
# 152 "data/maps/InsideOfTruck/scripts.pory"
	end
# 153 "data/maps/InsideOfTruck/scripts.pory"

# 154 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_IntroSkipWarpBrendansHouse::
# 155 "data/maps/InsideOfTruck/scripts.pory"
	warpsilent MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, 1, 4
# 156 "data/maps/InsideOfTruck/scripts.pory"
	waitstate
# 157 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
# 158 "data/maps/InsideOfTruck/scripts.pory"
	end
# 159 "data/maps/InsideOfTruck/scripts.pory"

# 160 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_IntroSkipWarpMaysHouse::
# 161 "data/maps/InsideOfTruck/scripts.pory"
	warpsilent MAP_LITTLEROOT_TOWN_MAYS_HOUSE_2F, 7, 4
# 162 "data/maps/InsideOfTruck/scripts.pory"
	waitstate
# 163 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
# 164 "data/maps/InsideOfTruck/scripts.pory"
	end
# 165 "data/maps/InsideOfTruck/scripts.pory"

# 166 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_MovingBox::
# 167 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_Text_BoxPrintedWithMonLogo, MSGBOX_SIGN
# 168 "data/maps/InsideOfTruck/scripts.pory"
	end
# 169 "data/maps/InsideOfTruck/scripts.pory"

# 170 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_Text_SkipIntro:
# 171 "data/maps/InsideOfTruck/scripts.pory"
	.string "Skip the intro?$"
# 172 "data/maps/InsideOfTruck/scripts.pory"

# 173 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_Text_BoxPrintedWithMonLogo:
# 174 "data/maps/InsideOfTruck/scripts.pory"
	.string "The box is printed with a POKéMON logo.\p"
# 175 "data/maps/InsideOfTruck/scripts.pory"
	.string "It's a POKéMON brand moving and\n"
# 176 "data/maps/InsideOfTruck/scripts.pory"
	.string "delivery service.$"

FadeScreenBlack::
# 182 "data/maps/InsideOfTruck/scripts.pory"
	lock
# 183 "data/maps/InsideOfTruck/scripts.pory"
	fadescreen FADE_TO_BLACK
# 184 "data/maps/InsideOfTruck/scripts.pory"
	playbgm MUS_HG_NEW_GAME, TRUE
# 185 "data/maps/InsideOfTruck/scripts.pory"
	call Randomizer_Option_Setup
	return


Randomizer_Option_Setup::
# 190 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Option_Setup_Text_0, MSGBOX_YESNO
# 191 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Option_Setup_1
# 198 "data/maps/InsideOfTruck/scripts.pory"
	playse SE_PC_OFF
# 199 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Option_Setup_Text_2
# 200 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_WILD_MON
# 201 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_FIELD_ITEMS
# 202 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_TRAINER_MON
# 203 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_FIXED_MON
# 204 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_STARTERS
# 205 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_EGG_MON
# 206 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_ABILITIES
# 207 "data/maps/InsideOfTruck/scripts.pory"
	waitmessage
# 208 "data/maps/InsideOfTruck/scripts.pory"
	closemessage
# 209 "data/maps/InsideOfTruck/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 210 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
	end

Randomizer_Option_Setup_1:
# 192 "data/maps/InsideOfTruck/scripts.pory"
	playse SE_PC_ON
# 193 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Option_Setup_Text_1
# 194 "data/maps/InsideOfTruck/scripts.pory"
	waitmessage
# 195 "data/maps/InsideOfTruck/scripts.pory"
	call Randomizer_Settings
	return


Randomizer_Settings::
# 218 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_0, MSGBOX_YESNO
# 219 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_2
# 223 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_WILD_MON
Randomizer_Settings_1:
# 225 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_1, MSGBOX_YESNO
# 226 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_6
# 230 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_STARTERS
Randomizer_Settings_5:
# 232 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_2, MSGBOX_YESNO
# 233 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_10
# 237 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_TRAINER_MON
Randomizer_Settings_9:
# 239 "data/maps/InsideOfTruck/scripts.pory"
	goto_if_set FLAG_RANDOM_TRAINER_MON, Randomizer_Settings_14
Randomizer_Settings_13:
# 248 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_4, MSGBOX_YESNO
# 249 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_17
# 253 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_FIXED_MON
Randomizer_Settings_16:
# 255 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_5, MSGBOX_YESNO
# 256 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_24
# 260 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_EGG_MON
Randomizer_Settings_23:
# 262 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_6, MSGBOX_YESNO
# 263 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_28
# 267 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_ABILITIES
Randomizer_Settings_27:
# 269 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_7, MSGBOX_YESNO
# 270 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_32
# 274 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_FIELD_ITEMS
Randomizer_Settings_31:
# 276 "data/maps/InsideOfTruck/scripts.pory"
	waitmessage
# 277 "data/maps/InsideOfTruck/scripts.pory"
	call Randomizer_Species_Mode
	return

Randomizer_Settings_2:
# 220 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_WILD_MON
	goto Randomizer_Settings_1

Randomizer_Settings_6:
# 227 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_STARTERS
	goto Randomizer_Settings_5

Randomizer_Settings_10:
# 234 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_TRAINER_MON
	goto Randomizer_Settings_9

Randomizer_Settings_14:
# 240 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Settings_Text_3, MSGBOX_YESNO
# 241 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Randomizer_Settings_20
# 245 "data/maps/InsideOfTruck/scripts.pory"
	clearflag FLAG_RANDOM_TYPE_THEMED_ARENAS
	goto Randomizer_Settings_13

Randomizer_Settings_17:
# 250 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_FIXED_MON
	goto Randomizer_Settings_16

Randomizer_Settings_20:
# 242 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_TYPE_THEMED_ARENAS
	goto Randomizer_Settings_13

Randomizer_Settings_24:
# 257 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_EGG_MON
	goto Randomizer_Settings_23

Randomizer_Settings_28:
# 264 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_ABILITIES
	goto Randomizer_Settings_27

Randomizer_Settings_32:
# 271 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RANDOM_FIELD_ITEMS
	goto Randomizer_Settings_31


Randomizer_Species_Mode::
# 281 "data/maps/InsideOfTruck/scripts.pory"
	message Randomizer_Species_Mode_Text_0
# 282 "data/maps/InsideOfTruck/scripts.pory"
	waitmessage
# 283 "data/maps/InsideOfTruck/scripts.pory"
	multichoice 25, 3, MULTI_RANDOMIZER_SPECIES_CHOICE, 1
# 284 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Randomizer_Species_Mode_2
# 287 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Randomizer_Species_Mode_3
# 290 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq Randomizer_Species_Mode_4
# 293 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq Randomizer_Species_Mode_5
Randomizer_Species_Mode_1:
# 296 "data/maps/InsideOfTruck/scripts.pory"
	closemessage
# 297 "data/maps/InsideOfTruck/scripts.pory"
	msgbox Randomizer_Species_Mode_Text_1
# 298 "data/maps/InsideOfTruck/scripts.pory"
	playse SE_SAVE
# 299 "data/maps/InsideOfTruck/scripts.pory"
	waitse
# 300 "data/maps/InsideOfTruck/scripts.pory"
	waitmessage
# 301 "data/maps/InsideOfTruck/scripts.pory"
	closemessage
# 302 "data/maps/InsideOfTruck/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 303 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
	end

Randomizer_Species_Mode_2:
# 285 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_RANDOM_SPECIES_MODE, 0
	goto Randomizer_Species_Mode_1

Randomizer_Species_Mode_3:
# 288 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_RANDOM_SPECIES_MODE, 1
	goto Randomizer_Species_Mode_1

Randomizer_Species_Mode_4:
# 291 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_RANDOM_SPECIES_MODE, 2
	goto Randomizer_Species_Mode_1

Randomizer_Species_Mode_5:
# 294 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_RANDOM_SPECIES_MODE, 3
	goto Randomizer_Species_Mode_1


Randomizer_Option_Setup_Text_0:
# 190 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE the game?$"

Randomizer_Option_Setup_Text_1:
# 193 "data/maps/InsideOfTruck/scripts.pory"
	.string "RANDOMIZER is ON!$"

Randomizer_Option_Setup_Text_2:
# 199 "data/maps/InsideOfTruck/scripts.pory"
	.string "Randomizer is OFF!$"

Randomizer_Settings_Text_0:
# 218 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE WILD\nPokémon?$"

Randomizer_Settings_Text_1:
# 225 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE STARTER\nPokémon?$"

Randomizer_Settings_Text_2:
# 232 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE TRAINER\nPokémon?$"

Randomizer_Settings_Text_3:
# 240 "data/maps/InsideOfTruck/scripts.pory"
	.string "Should the Gym's, Elite Four, and the\nChampion keep their POKéMON TYPE'S?$"

Randomizer_Settings_Text_4:
# 248 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE STATIC\nPokémon?$"

Randomizer_Settings_Text_5:
# 255 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE EGG\nPokémon?$"

Randomizer_Settings_Text_6:
# 262 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE Pokémon\nABILITIES?$"

Randomizer_Settings_Text_7:
# 269 "data/maps/InsideOfTruck/scripts.pory"
	.string "Would you like to RANDOMIZE\nFIELD ITEMS?$"

Randomizer_Species_Mode_Text_0:
# 281 "data/maps/InsideOfTruck/scripts.pory"
	.string "Which mode would you like to use?$"

Randomizer_Species_Mode_Text_1:
# 297 "data/maps/InsideOfTruck/scripts.pory"
	.string "RANDOMIZER settings have been saved!$"
