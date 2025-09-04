# 1 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_MapScripts::
# 2 "data/maps/LittlerootTown/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_OnTransition
# 3 "data/maps/LittlerootTown/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_OnFrame
# 4 "data/maps/LittlerootTown/scripts.pory"
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_OnWarp
# 5 "data/maps/LittlerootTown/scripts.pory"
	.byte 0
# 6 "data/maps/LittlerootTown/scripts.pory"

# 7 "data/maps/LittlerootTown/scripts.pory"
	@ State descriptions for VAR_LITTLEROOT_TOWN_STATE
# 8 "data/maps/LittlerootTown/scripts.pory"
	@ 1: Met Rival
# 9 "data/maps/LittlerootTown/scripts.pory"
	@ 2: Saving Birch
# 10 "data/maps/LittlerootTown/scripts.pory"
	@ 3: Received Pokedex
# 11 "data/maps/LittlerootTown/scripts.pory"
	@ 4: Received Running Shoes
# 12 "data/maps/LittlerootTown/scripts.pory"

# 13 "data/maps/LittlerootTown/scripts.pory"
	@ State descriptions for VAR_LITTLEROOT_INTRO_STATE
# 14 "data/maps/LittlerootTown/scripts.pory"
	@ 1: In truck male
# 15 "data/maps/LittlerootTown/scripts.pory"
	@ 2: In truck female
# 16 "data/maps/LittlerootTown/scripts.pory"
	@ 3: Entered house
# 17 "data/maps/LittlerootTown/scripts.pory"
	@ 4: Told to go set clock
# 18 "data/maps/LittlerootTown/scripts.pory"
	@ 5: Entered 2F to set clock
# 19 "data/maps/LittlerootTown/scripts.pory"
	@ 6: Set clock
# 20 "data/maps/LittlerootTown/scripts.pory"
	@ 7: Told to go meet rival
# 21 "data/maps/LittlerootTown/scripts.pory"

# 22 "data/maps/LittlerootTown/scripts.pory"
	@ State descriptions for VAR_LITTLEROOT_HOUSES_STATE_MAY
# 23 "data/maps/LittlerootTown/scripts.pory"
	@                    and VAR_LITTLEROOT_HOUSES_STATE_BRENDAN
# 24 "data/maps/LittlerootTown/scripts.pory"
	@ 1: On Truck (and is corresponding gender)
# 25 "data/maps/LittlerootTown/scripts.pory"
	@ 2: Met Rival's Mom (and is corresponding gender)
# 26 "data/maps/LittlerootTown/scripts.pory"
	@ 3: Entered Hall of Fame
# 27 "data/maps/LittlerootTown/scripts.pory"
	@ 4: Completed Lati TV / SS Ticket event
# 28 "data/maps/LittlerootTown/scripts.pory"
	@ 5: Exited house after above event
# 29 "data/maps/LittlerootTown/scripts.pory"

# 30 "data/maps/LittlerootTown/scripts.pory"
	@ State descriptions for VAR_LITTLEROOT_RIVAL_STATE
# 31 "data/maps/LittlerootTown/scripts.pory"
	@ 1: Never occurs
# 32 "data/maps/LittlerootTown/scripts.pory"
	@ 2: Entered Rival's bedroom
# 33 "data/maps/LittlerootTown/scripts.pory"
	@ 3: Met Rival
# 34 "data/maps/LittlerootTown/scripts.pory"
	@ 4: Received Pokedex
# 35 "data/maps/LittlerootTown/scripts.pory"

# 36 "data/maps/LittlerootTown/scripts.pory"

# 37 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_OnTransition:
# 38 "data/maps/LittlerootTown/scripts.pory"
	setflag FLAG_VISITED_LITTLEROOT_TOWN
# 39 "data/maps/LittlerootTown/scripts.pory"
	call Common_EventScript_SetupRivalGfxId
# 40 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_MoveMomToMaysDoor
# 41 "data/maps/LittlerootTown/scripts.pory"
	call_if_unset FLAG_RESCUED_BIRCH, LittlerootTown_EventScript_SetTwinPos
# 42 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_LITTLEROOT_TOWN_STATE, 3, LittlerootTown_EventScript_SetMomStandingInFrontOfDoorPos
# 43 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_LITTLEROOT_HOUSES_STATE_MAY, 4, LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
# 44 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 4, LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
# 45 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_OLDALE_RIVAL_STATE, 1, LittlerootTown_EventScript_MoveRivalFromOldale
# 46 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_LITTLEROOT_RIVAL_STATE, 3, LittlerootTown_EventScript_SetRivalLeftForRoute103
# 47 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_HideMapNamePopup
# 48 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_EventScript_LeftLabAfterDexUpgrade
# 49 "data/maps/LittlerootTown/scripts.pory"
	end
# 50 "data/maps/LittlerootTown/scripts.pory"

# 51 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_LeftLabAfterDexUpgrade::
# 52 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3
# 53 "data/maps/LittlerootTown/scripts.pory"
	return
# 54 "data/maps/LittlerootTown/scripts.pory"

# 55 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_HideMapNamePopup::
# 56 "data/maps/LittlerootTown/scripts.pory"
	setflag FLAG_HIDE_MAP_NAME_POPUP
# 57 "data/maps/LittlerootTown/scripts.pory"
	return
# 58 "data/maps/LittlerootTown/scripts.pory"

# 59 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetRivalLeftForRoute103::
# 60 "data/maps/LittlerootTown/scripts.pory"
	setflag FLAG_RIVAL_LEFT_FOR_ROUTE103
# 61 "data/maps/LittlerootTown/scripts.pory"
	return
# 62 "data/maps/LittlerootTown/scripts.pory"

# 63 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MoveRivalFromOldale::
# 64 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_OLDALE_RIVAL_STATE, 2
# 65 "data/maps/LittlerootTown/scripts.pory"
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
# 66 "data/maps/LittlerootTown/scripts.pory"
	return
# 67 "data/maps/LittlerootTown/scripts.pory"

# 68 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent::
# 69 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 5
# 70 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 5
# 71 "data/maps/LittlerootTown/scripts.pory"
	return
# 72 "data/maps/LittlerootTown/scripts.pory"

# 73 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MoveMomToMaysDoor::
# 74 "data/maps/LittlerootTown/scripts.pory"
	setobjectxyperm LOCALID_LITTLEROOT_MOM, 14, 8
# 75 "data/maps/LittlerootTown/scripts.pory"
	return
# 76 "data/maps/LittlerootTown/scripts.pory"

# 77 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetTwinPos::
# 78 "data/maps/LittlerootTown/scripts.pory"
	goto_if_eq VAR_LITTLEROOT_TOWN_STATE, 0, LittlerootTown_EventScript_SetTwinGuardingRoutePos
# 79 "data/maps/LittlerootTown/scripts.pory"
	setobjectxyperm LOCALID_LITTLEROOT_TWIN, 10, 1
# 80 "data/maps/LittlerootTown/scripts.pory"
	setobjectmovementtype LOCALID_LITTLEROOT_TWIN, MOVEMENT_TYPE_FACE_UP
# 81 "data/maps/LittlerootTown/scripts.pory"
	return
# 82 "data/maps/LittlerootTown/scripts.pory"

# 83 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetTwinGuardingRoutePos::
# 84 "data/maps/LittlerootTown/scripts.pory"
	setobjectxyperm LOCALID_LITTLEROOT_TWIN, 7, 2
# 85 "data/maps/LittlerootTown/scripts.pory"
	setobjectmovementtype LOCALID_LITTLEROOT_TWIN, MOVEMENT_TYPE_FACE_DOWN
# 86 "data/maps/LittlerootTown/scripts.pory"
	return
# 87 "data/maps/LittlerootTown/scripts.pory"

# 88 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetMomStandingInFrontOfDoorPos::
# 89 "data/maps/LittlerootTown/scripts.pory"
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
# 90 "data/maps/LittlerootTown/scripts.pory"
	setobjectmovementtype LOCALID_LITTLEROOT_MOM, MOVEMENT_TYPE_FACE_DOWN
# 91 "data/maps/LittlerootTown/scripts.pory"
	checkplayergender
# 92 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetMomInFrontOfDoorMale
# 93 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetMomInFrontOfDoorFemale
# 94 "data/maps/LittlerootTown/scripts.pory"
	return
# 95 "data/maps/LittlerootTown/scripts.pory"

# 96 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetMomInFrontOfDoorMale::
# 97 "data/maps/LittlerootTown/scripts.pory"
	setobjectxyperm LOCALID_LITTLEROOT_MOM, 5, 9
# 98 "data/maps/LittlerootTown/scripts.pory"
	return
# 99 "data/maps/LittlerootTown/scripts.pory"

# 100 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetMomInFrontOfDoorFemale::
# 101 "data/maps/LittlerootTown/scripts.pory"
	setobjectxyperm LOCALID_LITTLEROOT_MOM, 14, 9
# 102 "data/maps/LittlerootTown/scripts.pory"
	return
# 103 "data/maps/LittlerootTown/scripts.pory"

# 104 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_OnFrame:
# 105 "data/maps/LittlerootTown/scripts.pory"
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 1, LittlerootTown_EventScript_StepOffTruckMale
# 106 "data/maps/LittlerootTown/scripts.pory"
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_StepOffTruckFemale
# 107 "data/maps/LittlerootTown/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_BeginDexUpgradeScene
# 108 "data/maps/LittlerootTown/scripts.pory"
	.2byte 0
# 109 "data/maps/LittlerootTown/scripts.pory"

# 110 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_StepOffTruckMale::
# 111 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 112 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x8004, 5
# 113 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x8005, 8
# 114 "data/maps/LittlerootTown/scripts.pory"
	call LittlerootTown_EventScript_GoInsideWithMom
# 115 "data/maps/LittlerootTown/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
# 116 "data/maps/LittlerootTown/scripts.pory"
	warpsilent MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F, 8, 8
# 117 "data/maps/LittlerootTown/scripts.pory"
	waitstate
# 118 "data/maps/LittlerootTown/scripts.pory"
	releaseall
# 119 "data/maps/LittlerootTown/scripts.pory"
	end
# 120 "data/maps/LittlerootTown/scripts.pory"

# 121 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_StepOffTruckFemale::
# 122 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 123 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x8004, 14
# 124 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x8005, 8
# 125 "data/maps/LittlerootTown/scripts.pory"
	call LittlerootTown_EventScript_GoInsideWithMom
# 126 "data/maps/LittlerootTown/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
# 127 "data/maps/LittlerootTown/scripts.pory"
	warpsilent MAP_LITTLEROOT_TOWN_MAYS_HOUSE_1F, 2, 8
# 128 "data/maps/LittlerootTown/scripts.pory"
	waitstate
# 129 "data/maps/LittlerootTown/scripts.pory"
	releaseall
# 130 "data/maps/LittlerootTown/scripts.pory"
	end
# 131 "data/maps/LittlerootTown/scripts.pory"

# 132 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_GoInsideWithMom::
# 133 "data/maps/LittlerootTown/scripts.pory"
	delay 15
# 134 "data/maps/LittlerootTown/scripts.pory"
	playse SE_LEDGE
# 135 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerStepOffTruck
# 136 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 137 "data/maps/LittlerootTown/scripts.pory"
	opendoor VAR_0x8004, VAR_0x8005
# 138 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 139 "data/maps/LittlerootTown/scripts.pory"
	addobject LOCALID_LITTLEROOT_MOM
# 140 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitHouse
# 141 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 142 "data/maps/LittlerootTown/scripts.pory"
	closedoor VAR_0x8004, VAR_0x8005
# 143 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 144 "data/maps/LittlerootTown/scripts.pory"
	delay 10
# 145 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerAtTruck
# 146 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 147 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_OurNewHomeLetsGoInside, MSGBOX_DEFAULT
# 148 "data/maps/LittlerootTown/scripts.pory"
	closemessage
# 149 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachDoor
# 150 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerApproachDoor
# 151 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 152 "data/maps/LittlerootTown/scripts.pory"
	opendoor VAR_0x8004, VAR_0x8005
# 153 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 154 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomEnterHouse
# 155 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PlayerEnterHouse
# 156 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 157 "data/maps/LittlerootTown/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
# 158 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_LITTLEROOT_INTRO_STATE, 3
# 159 "data/maps/LittlerootTown/scripts.pory"
	hideobjectat LOCALID_PLAYER, 0
# 160 "data/maps/LittlerootTown/scripts.pory"
	closedoor VAR_0x8004, VAR_0x8005
# 161 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 162 "data/maps/LittlerootTown/scripts.pory"
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
# 163 "data/maps/LittlerootTown/scripts.pory"
	clearflag FLAG_HIDE_MAP_NAME_POPUP
# 164 "data/maps/LittlerootTown/scripts.pory"
	return
# 165 "data/maps/LittlerootTown/scripts.pory"

# 166 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomExitHouse:
# 167 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 168 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 169 "data/maps/LittlerootTown/scripts.pory"

# 170 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomApproachPlayerAtTruck:
# 171 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 172 "data/maps/LittlerootTown/scripts.pory"
	walk_in_place_faster_left
# 173 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 174 "data/maps/LittlerootTown/scripts.pory"

# 175 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomApproachDoor:
# 176 "data/maps/LittlerootTown/scripts.pory"
	delay_16
# 177 "data/maps/LittlerootTown/scripts.pory"
	delay_8
# 178 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 179 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 180 "data/maps/LittlerootTown/scripts.pory"

# 181 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomEnterHouse:
# 182 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 183 "data/maps/LittlerootTown/scripts.pory"
	set_invisible
# 184 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 185 "data/maps/LittlerootTown/scripts.pory"

# 186 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_PlayerApproachDoor:
# 187 "data/maps/LittlerootTown/scripts.pory"
	delay_16
# 188 "data/maps/LittlerootTown/scripts.pory"
	delay_8
# 189 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 190 "data/maps/LittlerootTown/scripts.pory"
	walk_in_place_faster_up
# 191 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 192 "data/maps/LittlerootTown/scripts.pory"

# 193 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_PlayerEnterHouse:
# 194 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 195 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 196 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 197 "data/maps/LittlerootTown/scripts.pory"

# 198 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_PlayerStepOffTruck:
# 199 "data/maps/LittlerootTown/scripts.pory"
	jump_right
# 200 "data/maps/LittlerootTown/scripts.pory"
	delay_16
# 201 "data/maps/LittlerootTown/scripts.pory"
	delay_16
# 202 "data/maps/LittlerootTown/scripts.pory"
	delay_16
# 203 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 204 "data/maps/LittlerootTown/scripts.pory"

# 205 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_BeginDexUpgradeScene::
# 206 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 207 "data/maps/LittlerootTown/scripts.pory"
	playse SE_PIN
# 208 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_BIRCH, Common_Movement_ExclamationMark
# 209 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 210 "data/maps/LittlerootTown/scripts.pory"
	delay 80
# 211 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_BirchSomethingToShowYouAtLab, MSGBOX_DEFAULT
# 212 "data/maps/LittlerootTown/scripts.pory"
	closemessage
# 213 "data/maps/LittlerootTown/scripts.pory"
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
# 214 "data/maps/LittlerootTown/scripts.pory"
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
# 215 "data/maps/LittlerootTown/scripts.pory"
	delay 20
# 216 "data/maps/LittlerootTown/scripts.pory"
	clearflag FLAG_HIDE_MAP_NAME_POPUP
# 217 "data/maps/LittlerootTown/scripts.pory"
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 6, 5
# 218 "data/maps/LittlerootTown/scripts.pory"
	waitstate
# 219 "data/maps/LittlerootTown/scripts.pory"
	releaseall
# 220 "data/maps/LittlerootTown/scripts.pory"
	end
# 221 "data/maps/LittlerootTown/scripts.pory"

# 222 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_OnWarp:
# 223 "data/maps/LittlerootTown/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_SetRivalBirchPosForDexUpgrade
# 224 "data/maps/LittlerootTown/scripts.pory"
	.2byte 0
# 225 "data/maps/LittlerootTown/scripts.pory"

# 226 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetRivalBirchPosForDexUpgrade::
# 227 "data/maps/LittlerootTown/scripts.pory"
	addobject LOCALID_LITTLEROOT_BIRCH
# 228 "data/maps/LittlerootTown/scripts.pory"
	addobject LOCALID_LITTLEROOT_RIVAL
# 229 "data/maps/LittlerootTown/scripts.pory"
	checkplayergender
# 230 "data/maps/LittlerootTown/scripts.pory"
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeMale
# 231 "data/maps/LittlerootTown/scripts.pory"
	goto LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeFemale
# 232 "data/maps/LittlerootTown/scripts.pory"
	end
# 233 "data/maps/LittlerootTown/scripts.pory"

# 234 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeMale::
# 235 "data/maps/LittlerootTown/scripts.pory"
	setobjectxy LOCALID_LITTLEROOT_RIVAL, 6, 10
# 236 "data/maps/LittlerootTown/scripts.pory"
	setobjectxy LOCALID_LITTLEROOT_BIRCH, 5, 10
# 237 "data/maps/LittlerootTown/scripts.pory"
	end
# 238 "data/maps/LittlerootTown/scripts.pory"

# 239 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeFemale::
# 240 "data/maps/LittlerootTown/scripts.pory"
	setobjectxy LOCALID_LITTLEROOT_RIVAL, 13, 10
# 241 "data/maps/LittlerootTown/scripts.pory"
	setobjectxy LOCALID_LITTLEROOT_BIRCH, 14, 10
# 242 "data/maps/LittlerootTown/scripts.pory"
	end
# 243 "data/maps/LittlerootTown/scripts.pory"

# 244 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_FatMan::
# 245 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_CanUsePCToStoreItems, MSGBOX_NPC
# 246 "data/maps/LittlerootTown/scripts.pory"
	end
# 247 "data/maps/LittlerootTown/scripts.pory"

# 248 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_Boy::
# 249 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_BirchSpendsDaysInLab, MSGBOX_NPC
# 250 "data/maps/LittlerootTown/scripts.pory"
	end
# 251 "data/maps/LittlerootTown/scripts.pory"

# 252 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_Twin::
# 253 "data/maps/LittlerootTown/scripts.pory"
	lock
# 254 "data/maps/LittlerootTown/scripts.pory"
	faceplayer
# 255 "data/maps/LittlerootTown/scripts.pory"
	goto_if_set FLAG_ADVENTURE_STARTED, LittlerootTown_EventScript_GoodLuck
# 256 "data/maps/LittlerootTown/scripts.pory"
	goto_if_set FLAG_RESCUED_BIRCH, LittlerootTown_EventScript_YouSavedBirch
# 257 "data/maps/LittlerootTown/scripts.pory"
	goto_if_ne VAR_LITTLEROOT_TOWN_STATE, 0, LittlerootTown_EventScript_GoSaveBirch
# 258 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
# 259 "data/maps/LittlerootTown/scripts.pory"
	release
# 260 "data/maps/LittlerootTown/scripts.pory"
	end
# 261 "data/maps/LittlerootTown/scripts.pory"

# 262 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_GoSaveBirch::
# 263 "data/maps/LittlerootTown/scripts.pory"
	special GetPlayerBigGuyGirlString
# 264 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
# 265 "data/maps/LittlerootTown/scripts.pory"
	closemessage
# 266 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_TWIN, Common_Movement_FaceOriginalDirection
# 267 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 268 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
# 269 "data/maps/LittlerootTown/scripts.pory"
	release
# 270 "data/maps/LittlerootTown/scripts.pory"
	end
# 271 "data/maps/LittlerootTown/scripts.pory"

# 272 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_YouSavedBirch::
# 273 "data/maps/LittlerootTown/scripts.pory"
	special GetPlayerBigGuyGirlString
# 274 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_YouSavedBirch, MSGBOX_DEFAULT
# 275 "data/maps/LittlerootTown/scripts.pory"
	release
# 276 "data/maps/LittlerootTown/scripts.pory"
	end
# 277 "data/maps/LittlerootTown/scripts.pory"

# 278 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_GoodLuck::
# 279 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_GoodLuckCatchingPokemon, MSGBOX_DEFAULT
# 280 "data/maps/LittlerootTown/scripts.pory"
	release
# 281 "data/maps/LittlerootTown/scripts.pory"
	end
# 282 "data/maps/LittlerootTown/scripts.pory"

# 283 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_NeedPokemonTriggerLeft::
# 284 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 285 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinApproachPlayerLeft
# 286 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 287 "data/maps/LittlerootTown/scripts.pory"
	call LittlerootTown_EventScript_DangerousWithoutPokemon
# 288 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinReturnLeft
# 289 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 290 "data/maps/LittlerootTown/scripts.pory"
	releaseall
# 291 "data/maps/LittlerootTown/scripts.pory"
	end
# 292 "data/maps/LittlerootTown/scripts.pory"

# 293 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_DangerousWithoutPokemon::
# 294 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
# 295 "data/maps/LittlerootTown/scripts.pory"
	closemessage
# 296 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinPushPlayerFromRoute
# 297 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, LittlerootTown_Movement_PushPlayerBackFromRoute
# 298 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 299 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_DangerousIfYouDontHavePokemon, MSGBOX_DEFAULT
# 300 "data/maps/LittlerootTown/scripts.pory"
	closemessage
# 301 "data/maps/LittlerootTown/scripts.pory"
	return
# 302 "data/maps/LittlerootTown/scripts.pory"

# 303 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_TwinApproachPlayerLeft:
# 304 "data/maps/LittlerootTown/scripts.pory"
	face_right
# 305 "data/maps/LittlerootTown/scripts.pory"
	delay_8
# 306 "data/maps/LittlerootTown/scripts.pory"
	disable_jump_landing_ground_effect
# 307 "data/maps/LittlerootTown/scripts.pory"
	jump_in_place_right
# 308 "data/maps/LittlerootTown/scripts.pory"
	delay_8
# 309 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_right
# 310 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_right
# 311 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_right
# 312 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_right
# 313 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_up
# 314 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_up
# 315 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_left
# 316 "data/maps/LittlerootTown/scripts.pory"
	face_down
# 317 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 318 "data/maps/LittlerootTown/scripts.pory"

# 319 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_TwinPushPlayerFromRoute:
# 320 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 321 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 322 "data/maps/LittlerootTown/scripts.pory"

# 323 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_TwinReturnLeft:
# 324 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 325 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 326 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 327 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 328 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 329 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 330 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 331 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 332 "data/maps/LittlerootTown/scripts.pory"
	walk_in_place_faster_down
# 333 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 334 "data/maps/LittlerootTown/scripts.pory"

# 335 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_PushPlayerBackFromRoute:
# 336 "data/maps/LittlerootTown/scripts.pory"
	lock_facing_direction
# 337 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 338 "data/maps/LittlerootTown/scripts.pory"
	unlock_facing_direction
# 339 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 340 "data/maps/LittlerootTown/scripts.pory"

# 341 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_NeedPokemonTriggerRight::
# 342 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 343 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinApproachPlayerRight
# 344 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 345 "data/maps/LittlerootTown/scripts.pory"
	call LittlerootTown_EventScript_DangerousWithoutPokemon
# 346 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_TWIN, LittlerootTown_Movement_TwinReturnRight
# 347 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 348 "data/maps/LittlerootTown/scripts.pory"
	releaseall
# 349 "data/maps/LittlerootTown/scripts.pory"
	end
# 350 "data/maps/LittlerootTown/scripts.pory"

# 351 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_TwinApproachPlayerRight:
# 352 "data/maps/LittlerootTown/scripts.pory"
	face_right
# 353 "data/maps/LittlerootTown/scripts.pory"
	delay_8
# 354 "data/maps/LittlerootTown/scripts.pory"
	disable_jump_landing_ground_effect
# 355 "data/maps/LittlerootTown/scripts.pory"
	jump_in_place_right
# 356 "data/maps/LittlerootTown/scripts.pory"
	delay_8
# 357 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_right
# 358 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_right
# 359 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_right
# 360 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_up
# 361 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_up
# 362 "data/maps/LittlerootTown/scripts.pory"
	walk_fast_right
# 363 "data/maps/LittlerootTown/scripts.pory"
	face_down
# 364 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 365 "data/maps/LittlerootTown/scripts.pory"

# 366 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_TwinReturnRight:
# 367 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 368 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 369 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 370 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 371 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 372 "data/maps/LittlerootTown/scripts.pory"
	walk_in_place_faster_down
# 373 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 374 "data/maps/LittlerootTown/scripts.pory"

# 375 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_GoSaveBirchTrigger::
# 376 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 377 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_TWIN, Common_Movement_WalkInPlaceFasterRight
# 378 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 379 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
# 380 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 381 "data/maps/LittlerootTown/scripts.pory"
	special GetPlayerBigGuyGirlString
# 382 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
# 383 "data/maps/LittlerootTown/scripts.pory"
	closemessage
# 384 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_TWIN, Common_Movement_FaceOriginalDirection
# 385 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 386 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
# 387 "data/maps/LittlerootTown/scripts.pory"
	releaseall
# 388 "data/maps/LittlerootTown/scripts.pory"
	end
# 389 "data/maps/LittlerootTown/scripts.pory"

# 390 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_TownSign::
# 391 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_TownSign, MSGBOX_SIGN
# 392 "data/maps/LittlerootTown/scripts.pory"
	end
# 393 "data/maps/LittlerootTown/scripts.pory"

# 394 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_BirchsLabSign::
# 395 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_ProfBirchsLab, MSGBOX_SIGN
# 396 "data/maps/LittlerootTown/scripts.pory"
	end
# 397 "data/maps/LittlerootTown/scripts.pory"

# 398 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_BrendansHouseSign::
# 399 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 400 "data/maps/LittlerootTown/scripts.pory"
	checkplayergender
# 401 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_PlayersHouseSignMale
# 402 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_BirchsHouseSignFemale
# 403 "data/maps/LittlerootTown/scripts.pory"
	releaseall
# 404 "data/maps/LittlerootTown/scripts.pory"
	end
# 405 "data/maps/LittlerootTown/scripts.pory"

# 406 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_PlayersHouseSignMale::
# 407 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
# 408 "data/maps/LittlerootTown/scripts.pory"
	return
# 409 "data/maps/LittlerootTown/scripts.pory"

# 410 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_BirchsHouseSignFemale::
# 411 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_DEFAULT
# 412 "data/maps/LittlerootTown/scripts.pory"
	return
# 413 "data/maps/LittlerootTown/scripts.pory"

# 414 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MaysHouseSign::
# 415 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 416 "data/maps/LittlerootTown/scripts.pory"
	checkplayergender
# 417 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_BirchsHouseSignMale
# 418 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_PlayersHouseSignFemale
# 419 "data/maps/LittlerootTown/scripts.pory"
	releaseall
# 420 "data/maps/LittlerootTown/scripts.pory"
	end
# 421 "data/maps/LittlerootTown/scripts.pory"

# 422 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_BirchsHouseSignMale::
# 423 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_DEFAULT
# 424 "data/maps/LittlerootTown/scripts.pory"
	return
# 425 "data/maps/LittlerootTown/scripts.pory"

# 426 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_PlayersHouseSignFemale::
# 427 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
# 428 "data/maps/LittlerootTown/scripts.pory"
	return
# 429 "data/maps/LittlerootTown/scripts.pory"

# 430 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_GiveRunningShoesTrigger0::
# 431 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 432 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x8008, 0
# 433 "data/maps/LittlerootTown/scripts.pory"
	setobjectxy LOCALID_LITTLEROOT_MOM, 10, 9
# 434 "data/maps/LittlerootTown/scripts.pory"
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
# 435 "data/maps/LittlerootTown/scripts.pory"
	end
# 436 "data/maps/LittlerootTown/scripts.pory"

# 437 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_GiveRunningShoesTrigger1::
# 438 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 439 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x8008, 1
# 440 "data/maps/LittlerootTown/scripts.pory"
	setobjectxy LOCALID_LITTLEROOT_MOM, 11, 9
# 441 "data/maps/LittlerootTown/scripts.pory"
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
# 442 "data/maps/LittlerootTown/scripts.pory"
	end
# 443 "data/maps/LittlerootTown/scripts.pory"

# 444 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_GiveRunningShoesTrigger2::
# 445 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 446 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x8008, 2
# 447 "data/maps/LittlerootTown/scripts.pory"
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
# 448 "data/maps/LittlerootTown/scripts.pory"
	end
# 449 "data/maps/LittlerootTown/scripts.pory"

# 450 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_GiveRunningShoesTrigger3::
# 451 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 452 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x8008, 3
# 453 "data/maps/LittlerootTown/scripts.pory"
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
# 454 "data/maps/LittlerootTown/scripts.pory"
	end
# 455 "data/maps/LittlerootTown/scripts.pory"

# 456 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_GiveRunningShoesTrigger4::
# 457 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 458 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x8008, 4
# 459 "data/maps/LittlerootTown/scripts.pory"
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
# 460 "data/maps/LittlerootTown/scripts.pory"
	end
# 461 "data/maps/LittlerootTown/scripts.pory"

# 462 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_GiveRunningShoesTrigger5::
# 463 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 464 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x8008, 5
# 465 "data/maps/LittlerootTown/scripts.pory"
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
# 466 "data/maps/LittlerootTown/scripts.pory"
	end
# 467 "data/maps/LittlerootTown/scripts.pory"

# 468 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_GiveRunningShoesTrigger::
# 469 "data/maps/LittlerootTown/scripts.pory"
	checkplayergender
# 470 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_MomNoticePlayerMale
# 471 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_MomNoticePlayerFemale
# 472 "data/maps/LittlerootTown/scripts.pory"
	checkplayergender
# 473 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetHomeDoorCoordsMale
# 474 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetHomeDoorCoordsFemale
# 475 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_WaitPlayer, MSGBOX_DEFAULT
# 476 "data/maps/LittlerootTown/scripts.pory"
	closemessage
# 477 "data/maps/LittlerootTown/scripts.pory"
	checkplayergender
# 478 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_MomApproachPlayerMale
# 479 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_MomApproachPlayerFemale
# 480 "data/maps/LittlerootTown/scripts.pory"
	call LittlerootTown_EventScript_GiveRunningShoes
# 481 "data/maps/LittlerootTown/scripts.pory"
	checkplayergender
# 482 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_MomReturnHomeMale
# 483 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_MomReturnHomeFemale
# 484 "data/maps/LittlerootTown/scripts.pory"
	goto LittlerootTown_EventScript_SetReceivedRunningShoes
# 485 "data/maps/LittlerootTown/scripts.pory"
	end
# 486 "data/maps/LittlerootTown/scripts.pory"

# 487 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetHomeDoorCoordsMale::
# 488 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x8009, 5
# 489 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x800A, 8
# 490 "data/maps/LittlerootTown/scripts.pory"
	return
# 491 "data/maps/LittlerootTown/scripts.pory"

# 492 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetHomeDoorCoordsFemale::
# 493 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x8009, 14
# 494 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_0x800A, 8
# 495 "data/maps/LittlerootTown/scripts.pory"
	return
# 496 "data/maps/LittlerootTown/scripts.pory"

# 497 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomNoticePlayerMale::
# 498 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, Common_Movement_WalkInPlaceFasterRight
# 499 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 500 "data/maps/LittlerootTown/scripts.pory"
	return
# 501 "data/maps/LittlerootTown/scripts.pory"

# 502 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomNoticePlayerFemale::
# 503 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, Common_Movement_WalkInPlaceFasterLeft
# 504 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 505 "data/maps/LittlerootTown/scripts.pory"
	return
# 506 "data/maps/LittlerootTown/scripts.pory"

# 507 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomApproachPlayerMale::
# 508 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomApproachPlayer0
# 509 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomApproachPlayer1
# 510 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomApproachPlayerMale2
# 511 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomApproachPlayerMale3
# 512 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomApproachPlayerMale4
# 513 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomApproachPlayerMale5
# 514 "data/maps/LittlerootTown/scripts.pory"
	return
# 515 "data/maps/LittlerootTown/scripts.pory"

# 516 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomApproachPlayerFemale::
# 517 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomApproachPlayer0
# 518 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomApproachPlayer1
# 519 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomApproachPlayerFemale2
# 520 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomApproachPlayerFemale3
# 521 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomApproachPlayerFemale4
# 522 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomApproachPlayerFemale5
# 523 "data/maps/LittlerootTown/scripts.pory"
	return
# 524 "data/maps/LittlerootTown/scripts.pory"

# 525 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomApproachPlayer0::
# 526 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
# 527 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 528 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayer0
# 529 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 530 "data/maps/LittlerootTown/scripts.pory"
	return
# 531 "data/maps/LittlerootTown/scripts.pory"

# 532 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomApproachPlayer1::
# 533 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
# 534 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 535 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayer1
# 536 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 537 "data/maps/LittlerootTown/scripts.pory"
	return
# 538 "data/maps/LittlerootTown/scripts.pory"

# 539 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomApproachPlayerMale2::
# 540 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
# 541 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 542 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerMale2
# 543 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 544 "data/maps/LittlerootTown/scripts.pory"
	return
# 545 "data/maps/LittlerootTown/scripts.pory"

# 546 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomApproachPlayerMale3::
# 547 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
# 548 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 549 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerMale3
# 550 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 551 "data/maps/LittlerootTown/scripts.pory"
	return
# 552 "data/maps/LittlerootTown/scripts.pory"

# 553 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomApproachPlayerMale4::
# 554 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
# 555 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 556 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerMale4
# 557 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 558 "data/maps/LittlerootTown/scripts.pory"
	return
# 559 "data/maps/LittlerootTown/scripts.pory"

# 560 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomApproachPlayerMale5::
# 561 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
# 562 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 563 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerMale5
# 564 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 565 "data/maps/LittlerootTown/scripts.pory"
	return
# 566 "data/maps/LittlerootTown/scripts.pory"

# 567 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomApproachPlayerFemale2::
# 568 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 569 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 570 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerFemale2
# 571 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 572 "data/maps/LittlerootTown/scripts.pory"
	return
# 573 "data/maps/LittlerootTown/scripts.pory"

# 574 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomApproachPlayerFemale3::
# 575 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 576 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 577 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerFemale3
# 578 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 579 "data/maps/LittlerootTown/scripts.pory"
	return
# 580 "data/maps/LittlerootTown/scripts.pory"

# 581 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomApproachPlayerFemale4::
# 582 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 583 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 584 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerFemale4
# 585 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 586 "data/maps/LittlerootTown/scripts.pory"
	return
# 587 "data/maps/LittlerootTown/scripts.pory"

# 588 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomApproachPlayerFemale5::
# 589 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 590 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 591 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomApproachPlayerFemale5
# 592 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 593 "data/maps/LittlerootTown/scripts.pory"
	return
# 594 "data/maps/LittlerootTown/scripts.pory"

# 595 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomReturnHomeMale::
# 596 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomReturnHome0
# 597 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomReturnHome1
# 598 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomReturnHomeMale2
# 599 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomReturnHomeMale3
# 600 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomReturnHomeMale4
# 601 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomReturnHomeMale5
# 602 "data/maps/LittlerootTown/scripts.pory"
	return
# 603 "data/maps/LittlerootTown/scripts.pory"

# 604 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomReturnHomeFemale::
# 605 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomReturnHome0
# 606 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomReturnHome1
# 607 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomReturnHomeFemale2
# 608 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomReturnHomeFemale3
# 609 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomReturnHomeFemale4
# 610 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomReturnHomeFemale5
# 611 "data/maps/LittlerootTown/scripts.pory"
	return
# 612 "data/maps/LittlerootTown/scripts.pory"

# 613 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomReturnHome0::
# 614 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHome0
# 615 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 616 "data/maps/LittlerootTown/scripts.pory"
	return
# 617 "data/maps/LittlerootTown/scripts.pory"

# 618 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomReturnHome1::
# 619 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHome1
# 620 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 621 "data/maps/LittlerootTown/scripts.pory"
	return
# 622 "data/maps/LittlerootTown/scripts.pory"

# 623 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomReturnHomeMale2::
# 624 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeMale2
# 625 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 626 "data/maps/LittlerootTown/scripts.pory"
	opendoor VAR_0x8009, VAR_0x800A
# 627 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 628 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
# 629 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 630 "data/maps/LittlerootTown/scripts.pory"
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
# 631 "data/maps/LittlerootTown/scripts.pory"
	closedoor VAR_0x8009, VAR_0x800A
# 632 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 633 "data/maps/LittlerootTown/scripts.pory"
	return
# 634 "data/maps/LittlerootTown/scripts.pory"

# 635 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomReturnHomeMale3::
# 636 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeMale3
# 637 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 638 "data/maps/LittlerootTown/scripts.pory"
	opendoor VAR_0x8009, VAR_0x800A
# 639 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 640 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
# 641 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 642 "data/maps/LittlerootTown/scripts.pory"
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
# 643 "data/maps/LittlerootTown/scripts.pory"
	closedoor VAR_0x8009, VAR_0x800A
# 644 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 645 "data/maps/LittlerootTown/scripts.pory"
	return
# 646 "data/maps/LittlerootTown/scripts.pory"

# 647 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomReturnHomeMale4::
# 648 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeMale4
# 649 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 650 "data/maps/LittlerootTown/scripts.pory"
	opendoor VAR_0x8009, VAR_0x800A
# 651 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 652 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
# 653 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 654 "data/maps/LittlerootTown/scripts.pory"
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
# 655 "data/maps/LittlerootTown/scripts.pory"
	closedoor VAR_0x8009, VAR_0x800A
# 656 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 657 "data/maps/LittlerootTown/scripts.pory"
	return
# 658 "data/maps/LittlerootTown/scripts.pory"

# 659 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomReturnHomeMale5::
# 660 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeMale5
# 661 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 662 "data/maps/LittlerootTown/scripts.pory"
	opendoor VAR_0x8009, VAR_0x800A
# 663 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 664 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
# 665 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 666 "data/maps/LittlerootTown/scripts.pory"
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
# 667 "data/maps/LittlerootTown/scripts.pory"
	closedoor VAR_0x8009, VAR_0x800A
# 668 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 669 "data/maps/LittlerootTown/scripts.pory"
	return
# 670 "data/maps/LittlerootTown/scripts.pory"

# 671 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomReturnHomeFemale2::
# 672 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeFemale2
# 673 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 674 "data/maps/LittlerootTown/scripts.pory"
	opendoor VAR_0x8009, VAR_0x800A
# 675 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 676 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
# 677 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 678 "data/maps/LittlerootTown/scripts.pory"
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
# 679 "data/maps/LittlerootTown/scripts.pory"
	closedoor VAR_0x8009, VAR_0x800A
# 680 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 681 "data/maps/LittlerootTown/scripts.pory"
	return
# 682 "data/maps/LittlerootTown/scripts.pory"

# 683 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomReturnHomeFemale3::
# 684 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeFemale3
# 685 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 686 "data/maps/LittlerootTown/scripts.pory"
	opendoor VAR_0x8009, VAR_0x800A
# 687 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 688 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
# 689 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 690 "data/maps/LittlerootTown/scripts.pory"
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
# 691 "data/maps/LittlerootTown/scripts.pory"
	closedoor VAR_0x8009, VAR_0x800A
# 692 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 693 "data/maps/LittlerootTown/scripts.pory"
	return
# 694 "data/maps/LittlerootTown/scripts.pory"

# 695 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomReturnHomeFemale4::
# 696 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeFemale4
# 697 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 698 "data/maps/LittlerootTown/scripts.pory"
	opendoor VAR_0x8009, VAR_0x800A
# 699 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 700 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
# 701 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 702 "data/maps/LittlerootTown/scripts.pory"
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
# 703 "data/maps/LittlerootTown/scripts.pory"
	closedoor VAR_0x8009, VAR_0x800A
# 704 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 705 "data/maps/LittlerootTown/scripts.pory"
	return
# 706 "data/maps/LittlerootTown/scripts.pory"

# 707 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_MomReturnHomeFemale5::
# 708 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomReturnHomeFemale5
# 709 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 710 "data/maps/LittlerootTown/scripts.pory"
	opendoor VAR_0x8009, VAR_0x800A
# 711 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 712 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
# 713 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 714 "data/maps/LittlerootTown/scripts.pory"
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
# 715 "data/maps/LittlerootTown/scripts.pory"
	closedoor VAR_0x8009, VAR_0x800A
# 716 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 717 "data/maps/LittlerootTown/scripts.pory"
	return
# 718 "data/maps/LittlerootTown/scripts.pory"

# 719 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomApproachPlayer0:
# 720 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 721 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 722 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 723 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 724 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 725 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 726 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 727 "data/maps/LittlerootTown/scripts.pory"

# 728 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomApproachPlayer1:
# 729 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 730 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 731 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 732 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 733 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 734 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 735 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 736 "data/maps/LittlerootTown/scripts.pory"

# 737 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomApproachPlayerMale2:
# 738 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 739 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 740 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 741 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 742 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 743 "data/maps/LittlerootTown/scripts.pory"

# 744 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomApproachPlayerMale3:
# 745 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 746 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 747 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 748 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 749 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 750 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 751 "data/maps/LittlerootTown/scripts.pory"

# 752 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomApproachPlayerMale4:
# 753 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 754 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 755 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 756 "data/maps/LittlerootTown/scripts.pory"

# 757 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomApproachPlayerMale5:
# 758 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 759 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 760 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 761 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 762 "data/maps/LittlerootTown/scripts.pory"

# 763 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomApproachPlayerFemale2:
# 764 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 765 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 766 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 767 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 768 "data/maps/LittlerootTown/scripts.pory"

# 769 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomApproachPlayerFemale3:
# 770 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 771 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 772 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 773 "data/maps/LittlerootTown/scripts.pory"

# 774 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomApproachPlayerFemale4:
# 775 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 776 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 777 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 778 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 779 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 780 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 781 "data/maps/LittlerootTown/scripts.pory"

# 782 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomApproachPlayerFemale5:
# 783 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 784 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 785 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 786 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 787 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 788 "data/maps/LittlerootTown/scripts.pory"

# 789 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomReturnHome0:
# 790 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 791 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 792 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 793 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 794 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 795 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 796 "data/maps/LittlerootTown/scripts.pory"

# 797 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomReturnHome1:
# 798 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 799 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 800 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 801 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 802 "data/maps/LittlerootTown/scripts.pory"
	walk_down
# 803 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 804 "data/maps/LittlerootTown/scripts.pory"

# 805 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomReturnHomeMale2:
# 806 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 807 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 808 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 809 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 810 "data/maps/LittlerootTown/scripts.pory"
	walk_in_place_faster_up
# 811 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 812 "data/maps/LittlerootTown/scripts.pory"

# 813 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomReturnHomeMale3:
# 814 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 815 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 816 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 817 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 818 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 819 "data/maps/LittlerootTown/scripts.pory"
	walk_in_place_faster_up
# 820 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 821 "data/maps/LittlerootTown/scripts.pory"

# 822 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomReturnHomeMale4:
# 823 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 824 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 825 "data/maps/LittlerootTown/scripts.pory"
	walk_in_place_faster_up
# 826 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 827 "data/maps/LittlerootTown/scripts.pory"

# 828 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomReturnHomeMale5:
# 829 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 830 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 831 "data/maps/LittlerootTown/scripts.pory"
	walk_left
# 832 "data/maps/LittlerootTown/scripts.pory"
	walk_in_place_faster_up
# 833 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 834 "data/maps/LittlerootTown/scripts.pory"

# 835 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomReturnHomeFemale2:
# 836 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 837 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 838 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 839 "data/maps/LittlerootTown/scripts.pory"
	walk_in_place_faster_up
# 840 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 841 "data/maps/LittlerootTown/scripts.pory"

# 842 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomReturnHomeFemale3:
# 843 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 844 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 845 "data/maps/LittlerootTown/scripts.pory"
	walk_in_place_faster_up
# 846 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 847 "data/maps/LittlerootTown/scripts.pory"

# 848 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomReturnHomeFemale4:
# 849 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 850 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 851 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 852 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 853 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 854 "data/maps/LittlerootTown/scripts.pory"
	walk_in_place_faster_up
# 855 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 856 "data/maps/LittlerootTown/scripts.pory"

# 857 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomReturnHomeFemale5:
# 858 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 859 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 860 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 861 "data/maps/LittlerootTown/scripts.pory"
	walk_right
# 862 "data/maps/LittlerootTown/scripts.pory"
	walk_in_place_faster_up
# 863 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 864 "data/maps/LittlerootTown/scripts.pory"

# 865 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Movement_MomExitThroughDoor:
# 866 "data/maps/LittlerootTown/scripts.pory"
	walk_up
# 867 "data/maps/LittlerootTown/scripts.pory"
	step_end
# 868 "data/maps/LittlerootTown/scripts.pory"

# 869 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_Mom::
# 870 "data/maps/LittlerootTown/scripts.pory"
	lock
# 871 "data/maps/LittlerootTown/scripts.pory"
	faceplayer
# 872 "data/maps/LittlerootTown/scripts.pory"
	checkplayergender
# 873 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetHomeDoorCoordsMale
# 874 "data/maps/LittlerootTown/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetHomeDoorCoordsFemale
# 875 "data/maps/LittlerootTown/scripts.pory"
	call LittlerootTown_EventScript_GiveRunningShoes
# 876 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, Common_Movement_WalkInPlaceFasterUp
# 877 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 878 "data/maps/LittlerootTown/scripts.pory"
	opendoor VAR_0x8009, VAR_0x800A
# 879 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 880 "data/maps/LittlerootTown/scripts.pory"
	applymovement LOCALID_LITTLEROOT_MOM, LittlerootTown_Movement_MomExitThroughDoor
# 881 "data/maps/LittlerootTown/scripts.pory"
	waitmovement 0
# 882 "data/maps/LittlerootTown/scripts.pory"
	hideobjectat LOCALID_LITTLEROOT_MOM, MAP_LITTLEROOT_TOWN
# 883 "data/maps/LittlerootTown/scripts.pory"
	closedoor VAR_0x8009, VAR_0x800A
# 884 "data/maps/LittlerootTown/scripts.pory"
	waitdooranim
# 885 "data/maps/LittlerootTown/scripts.pory"
	goto LittlerootTown_EventScript_SetReceivedRunningShoes
# 886 "data/maps/LittlerootTown/scripts.pory"
	end
# 887 "data/maps/LittlerootTown/scripts.pory"

# 888 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_SetReceivedRunningShoes::
# 889 "data/maps/LittlerootTown/scripts.pory"
	removeobject LOCALID_LITTLEROOT_MOM
# 890 "data/maps/LittlerootTown/scripts.pory"
	setflag FLAG_SYS_B_DASH
# 891 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 4
# 892 "data/maps/LittlerootTown/scripts.pory"
	release
# 893 "data/maps/LittlerootTown/scripts.pory"
	end
# 894 "data/maps/LittlerootTown/scripts.pory"

# 895 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_EventScript_GiveRunningShoes::
# 896 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_WearTheseRunningShoes, MSGBOX_DEFAULT
# 897 "data/maps/LittlerootTown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 898 "data/maps/LittlerootTown/scripts.pory"
	message LittlerootTown_Text_SwitchShoesWithRunningShoes
# 899 "data/maps/LittlerootTown/scripts.pory"
	waitfanfare
# 900 "data/maps/LittlerootTown/scripts.pory"
	setflag FLAG_RECEIVED_RUNNING_SHOES
# 901 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_ExplainRunningShoes, MSGBOX_DEFAULT
# 902 "data/maps/LittlerootTown/scripts.pory"
	msgbox LittlerootTown_Text_ComeHomeIfAnythingHappens, MSGBOX_DEFAULT
# 903 "data/maps/LittlerootTown/scripts.pory"
	closemessage
# 904 "data/maps/LittlerootTown/scripts.pory"
	delay 30
# 905 "data/maps/LittlerootTown/scripts.pory"
	return
# 906 "data/maps/LittlerootTown/scripts.pory"

# 907 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_OurNewHomeLetsGoInside:
# 908 "data/maps/LittlerootTown/scripts.pory"
	.string "MOM: {PLAYER}, we're here, honey!\p"
# 909 "data/maps/LittlerootTown/scripts.pory"
	.string "It must be tiring riding with our things\n"
# 910 "data/maps/LittlerootTown/scripts.pory"
	.string "in the moving truck.\p"
# 911 "data/maps/LittlerootTown/scripts.pory"
	.string "Well, this is LITTLEROOT TOWN.\p"
# 912 "data/maps/LittlerootTown/scripts.pory"
	.string "How do you like it?\n"
# 913 "data/maps/LittlerootTown/scripts.pory"
	.string "This is our new home!\p"
# 914 "data/maps/LittlerootTown/scripts.pory"
	.string "It has a quaint feel, but it seems to be\n"
# 915 "data/maps/LittlerootTown/scripts.pory"
	.string "an easy place to live, don't you think?\p"
# 916 "data/maps/LittlerootTown/scripts.pory"
	.string "And, you get your own room, {PLAYER}!\n"
# 917 "data/maps/LittlerootTown/scripts.pory"
	.string "Let's go inside.$"
# 918 "data/maps/LittlerootTown/scripts.pory"

# 919 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_WaitPlayer:
# 920 "data/maps/LittlerootTown/scripts.pory"
	.string "MOM: Wait, {PLAYER}!$"
# 921 "data/maps/LittlerootTown/scripts.pory"

# 922 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_WearTheseRunningShoes:
# 923 "data/maps/LittlerootTown/scripts.pory"
	.string "MOM: {PLAYER}! {PLAYER}! Did you\n"
# 924 "data/maps/LittlerootTown/scripts.pory"
	.string "introduce yourself to PROF. BIRCH?\p"
# 925 "data/maps/LittlerootTown/scripts.pory"
	.string "Oh! What an adorable POKéMON!\n"
# 926 "data/maps/LittlerootTown/scripts.pory"
	.string "You got it from PROF. BIRCH. How nice!\p"
# 927 "data/maps/LittlerootTown/scripts.pory"
	.string "You're your father's child, all right.\n"
# 928 "data/maps/LittlerootTown/scripts.pory"
	.string "You look good together with POKéMON!\p"
# 929 "data/maps/LittlerootTown/scripts.pory"
	.string "Here, honey! If you're going out on an\n"
# 930 "data/maps/LittlerootTown/scripts.pory"
	.string "adventure, wear these RUNNING SHOES.\p"
# 931 "data/maps/LittlerootTown/scripts.pory"
	.string "They'll put a zip in your step!$"
# 932 "data/maps/LittlerootTown/scripts.pory"

# 933 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_SwitchShoesWithRunningShoes:
# 934 "data/maps/LittlerootTown/scripts.pory"
	.string "{PLAYER} switched shoes with the\n"
# 935 "data/maps/LittlerootTown/scripts.pory"
	.string "RUNNING SHOES.$"
# 936 "data/maps/LittlerootTown/scripts.pory"

# 937 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_ExplainRunningShoes:
# 938 "data/maps/LittlerootTown/scripts.pory"
	.string "MOM: {PLAYER}, those shoes came with\n"
# 939 "data/maps/LittlerootTown/scripts.pory"
	.string "instructions.\p"
# 940 "data/maps/LittlerootTown/scripts.pory"
	.string "“Press the B Button while wearing these\n"
# 941 "data/maps/LittlerootTown/scripts.pory"
	.string "RUNNING SHOES to run extra-fast!\p"
# 942 "data/maps/LittlerootTown/scripts.pory"
	.string "“Slip on these RUNNING SHOES and race\n"
# 943 "data/maps/LittlerootTown/scripts.pory"
	.string "in the great outdoors!”$"
# 944 "data/maps/LittlerootTown/scripts.pory"

# 945 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_ComeHomeIfAnythingHappens:
# 946 "data/maps/LittlerootTown/scripts.pory"
	.string "… … … … … … … …\n"
# 947 "data/maps/LittlerootTown/scripts.pory"
	.string "… … … … … … … …\p"
# 948 "data/maps/LittlerootTown/scripts.pory"
	.string "To think that you have your very own\n"
# 949 "data/maps/LittlerootTown/scripts.pory"
	.string "POKéMON now…\l"
# 950 "data/maps/LittlerootTown/scripts.pory"
	.string "Your father will be overjoyed.\p"
# 951 "data/maps/LittlerootTown/scripts.pory"
	.string "…But please be careful.\n"
# 952 "data/maps/LittlerootTown/scripts.pory"
	.string "If anything happens, you can come home.\p"
# 953 "data/maps/LittlerootTown/scripts.pory"
	.string "Go on, go get them, honey!$"
# 954 "data/maps/LittlerootTown/scripts.pory"

# 955 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_CanUsePCToStoreItems:
# 956 "data/maps/LittlerootTown/scripts.pory"
	.string "If you use a PC, you can store items\n"
# 957 "data/maps/LittlerootTown/scripts.pory"
	.string "and POKéMON.\p"
# 958 "data/maps/LittlerootTown/scripts.pory"
	.string "The power of science is staggering!$"
# 959 "data/maps/LittlerootTown/scripts.pory"

# 960 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_BirchSpendsDaysInLab:
# 961 "data/maps/LittlerootTown/scripts.pory"
	.string "PROF. BIRCH spends days in his LAB\n"
# 962 "data/maps/LittlerootTown/scripts.pory"
	.string "studying, then he'll suddenly go out in\l"
# 963 "data/maps/LittlerootTown/scripts.pory"
	.string "the wild to do more research…\p"
# 964 "data/maps/LittlerootTown/scripts.pory"
	.string "When does PROF. BIRCH spend time\n"
# 965 "data/maps/LittlerootTown/scripts.pory"
	.string "at home?$"
# 966 "data/maps/LittlerootTown/scripts.pory"

# 967 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut:
# 968 "data/maps/LittlerootTown/scripts.pory"
	.string "Um, um, um!\p"
# 969 "data/maps/LittlerootTown/scripts.pory"
	.string "If you go outside and go in the grass,\n"
# 970 "data/maps/LittlerootTown/scripts.pory"
	.string "wild POKéMON will jump out!$"
# 971 "data/maps/LittlerootTown/scripts.pory"

# 972 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_DangerousIfYouDontHavePokemon:
# 973 "data/maps/LittlerootTown/scripts.pory"
	.string "It's dangerous if you don't have\n"
# 974 "data/maps/LittlerootTown/scripts.pory"
	.string "your own POKéMON.$"
# 975 "data/maps/LittlerootTown/scripts.pory"

# 976 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_CanYouGoSeeWhatsHappening:
# 977 "data/maps/LittlerootTown/scripts.pory"
	.string "Um, hi!\p"
# 978 "data/maps/LittlerootTown/scripts.pory"
	.string "There are scary POKéMON outside!\n"
# 979 "data/maps/LittlerootTown/scripts.pory"
	.string "I can hear their cries!\p"
# 980 "data/maps/LittlerootTown/scripts.pory"
	.string "I want to go see what's going on,\n"
# 981 "data/maps/LittlerootTown/scripts.pory"
	.string "but I don't have any POKéMON…\p"
# 982 "data/maps/LittlerootTown/scripts.pory"
	.string "Can you go see what's happening\n"
# 983 "data/maps/LittlerootTown/scripts.pory"
	.string "for me?$"
# 984 "data/maps/LittlerootTown/scripts.pory"

# 985 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_YouSavedBirch:
# 986 "data/maps/LittlerootTown/scripts.pory"
	.string "You saved PROF. BIRCH!\n"
# 987 "data/maps/LittlerootTown/scripts.pory"
	.string "I'm so glad!$"
# 988 "data/maps/LittlerootTown/scripts.pory"

# 989 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_GoodLuckCatchingPokemon:
# 990 "data/maps/LittlerootTown/scripts.pory"
	.string "Are you going to catch POKéMON?\n"
# 991 "data/maps/LittlerootTown/scripts.pory"
	.string "Good luck!$"
# 992 "data/maps/LittlerootTown/scripts.pory"

# 993 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_TownSign:
# 994 "data/maps/LittlerootTown/scripts.pory"
	.string "LITTLEROOT TOWN\n"
# 995 "data/maps/LittlerootTown/scripts.pory"
	.string "“A town that can't be shaded any hue.”$"
# 996 "data/maps/LittlerootTown/scripts.pory"

# 997 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_ProfBirchsLab:
# 998 "data/maps/LittlerootTown/scripts.pory"
	.string "PROF. BIRCH'S POKéMON LAB$"
# 999 "data/maps/LittlerootTown/scripts.pory"

# 1000 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_PlayersHouse:
# 1001 "data/maps/LittlerootTown/scripts.pory"
	.string "{PLAYER}'s HOUSE$"
# 1002 "data/maps/LittlerootTown/scripts.pory"

# 1003 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_ProfBirchsHouse:
# 1004 "data/maps/LittlerootTown/scripts.pory"
	.string "PROF. BIRCH'S HOUSE$"
# 1005 "data/maps/LittlerootTown/scripts.pory"

# 1006 "data/maps/LittlerootTown/scripts.pory"
LittlerootTown_Text_BirchSomethingToShowYouAtLab:
# 1007 "data/maps/LittlerootTown/scripts.pory"
	.string "PROF. BIRCH: Well, well, {PLAYER}{KUN}!\n"
# 1008 "data/maps/LittlerootTown/scripts.pory"
	.string "That was good work out there!\p"
# 1009 "data/maps/LittlerootTown/scripts.pory"
	.string "I knew there was something special\n"
# 1010 "data/maps/LittlerootTown/scripts.pory"
	.string "about you when I first saw you,\l"
# 1011 "data/maps/LittlerootTown/scripts.pory"
	.string "but I never expected this.\p"
# 1012 "data/maps/LittlerootTown/scripts.pory"
	.string "Oh, yes. Do you still have the POKéDEX\n"
# 1013 "data/maps/LittlerootTown/scripts.pory"
	.string "I gave you?\p"
# 1014 "data/maps/LittlerootTown/scripts.pory"
	.string "I have something to show you.\n"
# 1015 "data/maps/LittlerootTown/scripts.pory"
	.string "Let's go to my LAB.$"

birch_case::
# 1022 "data/maps/LittlerootTown/scripts.pory"
	lockall
# 1023 "data/maps/LittlerootTown/scripts.pory"
	callnative StartNewPokeballCaseUI
# 1024 "data/maps/LittlerootTown/scripts.pory"
	waitstate
# 1025 "data/maps/LittlerootTown/scripts.pory"
	releaseall
	end


cynthia_fight::
# 1030 "data/maps/LittlerootTown/scripts.pory"
	setflag FLAG_SET_ENCOUNTER_MUSIC
# 1031 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_TEMP_E, MUS_BW_CYNTHIA
# 1032 "data/maps/LittlerootTown/scripts.pory"
	setflag FLAG_SET_BGM
# 1033 "data/maps/LittlerootTown/scripts.pory"
	setvar VAR_TEMP_F, MUS_BW_VS_CYNTHIA
# 1034 "data/maps/LittlerootTown/scripts.pory"
	trainerbattle_single TRAINER_CYNTHIA, Beispiel_Intro, Beispiel_Outro
# 1035 "data/maps/LittlerootTown/scripts.pory"
	msgbox Beispiel_Postbattle, MSGBOX_AUTOCLOSE
# 1036 "data/maps/LittlerootTown/scripts.pory"
	waitmessage
	end


Beispiel_Intro::
# 1042 "data/maps/LittlerootTown/scripts.pory"
	.string "Intro Text!$"

Beispiel_Outro::
# 1046 "data/maps/LittlerootTown/scripts.pory"
	.string "Outro Text.$"

Beispiel_Postbattle::
# 1050 "data/maps/LittlerootTown/scripts.pory"
	.string "Postbattle text.$"
