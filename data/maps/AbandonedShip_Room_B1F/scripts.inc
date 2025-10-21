# 1 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
AbandonedShip_Room_B1F_MapScripts::
# 2 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	.byte 0

AbandonedShip_Room_B1F_Rotom_Encounter::
# 8 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	lock
# 9 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	goto_if_unset FLAG_ROTOM_ENCOUNTER, AbandonedShip_Room_B1F_Rotom_Encounter_1
# 13 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	msgbox AbandonedShip_Room_B1F_Rotom_Encounter_Text_0
# 14 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	waitmessage
# 15 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	releaseall
	end

AbandonedShip_Room_B1F_Rotom_Encounter_1:
# 10 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	call Battle_Rotom_Encounter
	return


Battle_Rotom_Encounter::
# 21 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	setflag FLAG_ROTOM_ENCOUNTER
# 22 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	msgbox Battle_Rotom_Encounter_Text_0, MSGBOX_AUTOCLOSE
# 23 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	waitmessage
# 24 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_ENCOUNTER
# 25 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	waitmoncry
# 26 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	msgbox Battle_Rotom_Encounter_Text_1
# 27 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	setflag FLAG_SET_BGM
# 28 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	setvar VAR_TEMP_F, MUS_DP_VS_WILD
# 29 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	setwildbattle SPECIES_ROTOM, 40, ITEM_NONE
# 30 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	dowildbattle
# 31 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 32 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Battle_Rotom_Encounter_2
# 35 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Battle_Rotom_Encounter_3
# 38 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq Battle_Rotom_Encounter_4
# 41 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq Battle_Rotom_Encounter_5
Battle_Rotom_Encounter_1:
# 44 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	waitmessage
# 45 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	releaseall
	return

Battle_Rotom_Encounter_2:
# 33 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	call Won_or_Caught
	goto Battle_Rotom_Encounter_1

Battle_Rotom_Encounter_3:
# 36 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	call Won_or_Caught
	goto Battle_Rotom_Encounter_1

Battle_Rotom_Encounter_4:
# 39 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	call RanAway
	goto Battle_Rotom_Encounter_1

Battle_Rotom_Encounter_5:
# 42 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	call RanAway
	goto Battle_Rotom_Encounter_1


Won_or_Caught::
# 49 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	msgbox Won_or_Caught_Text_0
	return


RanAway::
# 54 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_ENCOUNTER
# 55 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	waitmoncry
# 56 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	msgbox RanAway_Text_0, MSGBOX_AUTOCLOSE
# 57 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	delay 20
# 58 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	clearflag FLAG_ROTOM_ENCOUNTER
	return


AbandonedShip_Room_B1F_Rotom_Encounter_Text_0:
# 13 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	.string "There is nothing in the\nbin now.$"

Battle_Rotom_Encounter_Text_0:
# 22 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	.string "....\p....\p.. ...?\pThere is a strange noise coming from\ninside the bin...\pIt sounds like a POKéMON is hiding\ninside...$"

Battle_Rotom_Encounter_Text_1:
# 26 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	.string "It jumped out!$"

Won_or_Caught_Text_0:
# 49 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	.string "Phew! That was a close one..$"

RanAway_Text_0:
# 56 "data/maps/AbandonedShip_Room_B1F/scripts.pory"
	.string "Bzzzzt!....$"
