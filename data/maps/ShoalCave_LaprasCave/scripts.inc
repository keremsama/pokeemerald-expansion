ShoalCave_LaprasCave_MapScripts::
	.byte 0


ShoalCave_Inside_Lapras_Encounter::
# 6 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	lockall
# 7 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	delay 30
# 8 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	faceplayer
# 9 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	playse SE_PIN
# 10 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Lapras_Sees_You
# 11 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 12 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	playmoncry SPECIES_LAPRAS, CRY_MODE_ENCOUNTER
# 13 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	waitmoncry
# 14 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	msgbox ShoalCave_Inside_Lapras_Encounter_Text_0
# 15 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	setwildbattle SPECIES_LAPRAS, 55, ITEM_NONE
# 16 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	dowildbattle
# 17 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 18 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq ShoalCave_Inside_Lapras_Encounter_2
# 21 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq ShoalCave_Inside_Lapras_Encounter_3
# 24 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq ShoalCave_Inside_Lapras_Encounter_4
# 27 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq ShoalCave_Inside_Lapras_Encounter_5
ShoalCave_Inside_Lapras_Encounter_1:
# 30 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	releaseall
	end

ShoalCave_Inside_Lapras_Encounter_2:
# 19 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	call ShoalCave_Lapras_Caught
	goto ShoalCave_Inside_Lapras_Encounter_1

ShoalCave_Inside_Lapras_Encounter_3:
# 22 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	call ShoalCave_Lapras_Won
	goto ShoalCave_Inside_Lapras_Encounter_1

ShoalCave_Inside_Lapras_Encounter_4:
# 25 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	call ShoalCave_Lapras_RanAway
	goto ShoalCave_Inside_Lapras_Encounter_1

ShoalCave_Inside_Lapras_Encounter_5:
# 28 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	call ShoalCave_Lapras_RanAway
	goto ShoalCave_Inside_Lapras_Encounter_1


ShoalCave_Lapras_Caught::
# 35 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	fadescreen FADE_TO_BLACK
# 36 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	setflag FLAG_HIDE_SHOALCAVE_LAPRAS
# 37 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	removeobject 1
# 38 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	delay 40
# 39 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	fadescreen FADE_FROM_BLACK
	return


ShoalCave_Lapras_Won::
# 44 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	playmoncry SPECIES_LAPRAS, CRY_MODE_ENCOUNTER
# 45 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	waitmoncry
# 46 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	msgbox ShoalCave_Lapras_Won_Text_0, MSGBOX_AUTOCLOSE
# 47 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	fadescreen FADE_TO_BLACK
# 48 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	setflag FLAG_HIDE_SHOALCAVE_LAPRAS
# 49 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	removeobject 1
# 50 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	delay 40
# 51 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	fadescreen FADE_FROM_BLACK
	return


ShoalCave_Lapras_RanAway::
# 56 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	playmoncry SPECIES_LAPRAS, CRY_MODE_ENCOUNTER
# 57 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	waitmoncry
# 58 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	msgbox ShoalCave_Lapras_RanAway_Text_0, MSGBOX_AUTOCLOSE
# 59 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	fadescreen FADE_TO_BLACK
# 60 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	setflag FLAG_HIDE_SHOALCAVE_LAPRAS
# 61 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	removeobject 1
# 62 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	delay 40
# 63 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	fadescreen FADE_FROM_BLACK
	return


# 67 "data/maps/ShoalCave_LaprasCave/scripts.pory"
Lapras_Sees_You:
# 68 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	emote_exclamation_mark
# 69 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	delay_16
# 69 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	delay_16
# 69 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	delay_16
# 69 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	delay_16
	step_end

ShoalCave_Inside_Lapras_Encounter_Text_0:
# 14 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	.string "Lapras lets out a resonant cry!$"

ShoalCave_Lapras_Won_Text_0:
# 46 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	.string "Lapras's cry fades into the air...$"

ShoalCave_Lapras_RanAway_Text_0:
# 58 "data/maps/ShoalCave_LaprasCave/scripts.pory"
	.string "Lapras slipped away into the darkness...$"
