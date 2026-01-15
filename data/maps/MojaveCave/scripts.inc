MojaveCave_MapScripts::
	.byte 0


MojaveCave_Spiritomb::
	checkitem ITEM_ODD_KEYSTONE
# 0 "data/maps/MojaveCave/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq MojaveCave_Spiritomb_2
# 7 "data/maps/MojaveCave/scripts.pory"
	compare VAR_TEMP_0, 1
	goto_if_eq MojaveCave_Spiritomb_5
# 10 "data/maps/MojaveCave/scripts.pory"
	lock
# 11 "data/maps/MojaveCave/scripts.pory"
	faceplayer
# 12 "data/maps/MojaveCave/scripts.pory"
	msgbox MojaveCave_Text_Spiritomb_LayDownOddKeystone, MSGBOX_YESNO
# 13 "data/maps/MojaveCave/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq MojaveCave_Spiritomb_8
# 17 "data/maps/MojaveCave/scripts.pory"
	msgbox MojaveCave_Spiritomb_Text_0
# 18 "data/maps/MojaveCave/scripts.pory"
	closemessage
# 19 "data/maps/MojaveCave/scripts.pory"
	removeitem ITEM_ODD_KEYSTONE, 1
# 20 "data/maps/MojaveCave/scripts.pory"
	fadescreen FADE_TO_BLACK
# 21 "data/maps/MojaveCave/scripts.pory"
	delay 90
# 22 "data/maps/MojaveCave/scripts.pory"
	addobject OBJ_EVENT_GFX_MOJAVE_CAVE_SPIRITOMB
# 23 "data/maps/MojaveCave/scripts.pory"
	playmoncry SPECIES_SPIRITOMB, CRY_MODE_ENCOUNTER
# 24 "data/maps/MojaveCave/scripts.pory"
	waitmoncry
# 25 "data/maps/MojaveCave/scripts.pory"
	delay 90
# 26 "data/maps/MojaveCave/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 27 "data/maps/MojaveCave/scripts.pory"
	delay 30
# 28 "data/maps/MojaveCave/scripts.pory"
	playmoncry SPECIES_SPIRITOMB, CRY_MODE_ENCOUNTER
# 29 "data/maps/MojaveCave/scripts.pory"
	msgbox MojaveCave_Spiritomb_Text_1
# 30 "data/maps/MojaveCave/scripts.pory"
	closemessage
# 31 "data/maps/MojaveCave/scripts.pory"
	setwildbattle SPECIES_SPIRITOMB, 50, ITEM_NONE
# 32 "data/maps/MojaveCave/scripts.pory"
	dowildbattle
# 33 "data/maps/MojaveCave/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 34 "data/maps/MojaveCave/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq MojaveCave_Spiritomb_11
# 37 "data/maps/MojaveCave/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq MojaveCave_Spiritomb_12
# 40 "data/maps/MojaveCave/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq MojaveCave_Spiritomb_13
# 43 "data/maps/MojaveCave/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq MojaveCave_Spiritomb_14
MojaveCave_Spiritomb_10:
# 46 "data/maps/MojaveCave/scripts.pory"
	releaseall
	end

MojaveCave_Spiritomb_2:
	end

MojaveCave_Spiritomb_5:
	end

MojaveCave_Spiritomb_8:
# 14 "data/maps/MojaveCave/scripts.pory"
	release
	end

MojaveCave_Spiritomb_11:
# 35 "data/maps/MojaveCave/scripts.pory"
	call MojaveCave_Spiritomb_Caught
	goto MojaveCave_Spiritomb_10

MojaveCave_Spiritomb_12:
# 38 "data/maps/MojaveCave/scripts.pory"
	call MojaveCave_Spiritomb_Won
	goto MojaveCave_Spiritomb_10

MojaveCave_Spiritomb_13:
# 41 "data/maps/MojaveCave/scripts.pory"
	call MojaveCave_Spiritomb_RanAway
	goto MojaveCave_Spiritomb_10

MojaveCave_Spiritomb_14:
# 44 "data/maps/MojaveCave/scripts.pory"
	call MojaveCave_Spiritomb_RanAway
	goto MojaveCave_Spiritomb_10


MojaveCave_Spiritomb_Caught::
# 51 "data/maps/MojaveCave/scripts.pory"
	setflag FLAG_MOJAVECAVE_CATCH_SPIRITOMB
# 52 "data/maps/MojaveCave/scripts.pory"
	fadescreen FADE_TO_BLACK
# 53 "data/maps/MojaveCave/scripts.pory"
	removeobject OBJ_EVENT_GFX_MOJAVE_CAVE_SPIRITOMB
# 54 "data/maps/MojaveCave/scripts.pory"
	delay 30
# 55 "data/maps/MojaveCave/scripts.pory"
	fadescreen FADE_FROM_BLACK
	return


MojaveCave_Spiritomb_Won::
# 60 "data/maps/MojaveCave/scripts.pory"
	playmoncry SPECIES_SPIRITOMB, CRY_MODE_ENCOUNTER
# 61 "data/maps/MojaveCave/scripts.pory"
	waitmoncry
# 62 "data/maps/MojaveCave/scripts.pory"
	fadescreen FADE_TO_BLACK
# 63 "data/maps/MojaveCave/scripts.pory"
	removeobject OBJ_EVENT_GFX_MOJAVE_CAVE_SPIRITOMB
# 64 "data/maps/MojaveCave/scripts.pory"
	delay 30
# 65 "data/maps/MojaveCave/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 66 "data/maps/MojaveCave/scripts.pory"
	msgbox MojaveCave_Spiritomb_Won_Text_0
# 67 "data/maps/MojaveCave/scripts.pory"
	additem ITEM_ODD_KEYSTONE, 1
# 68 "data/maps/MojaveCave/scripts.pory"
	setvar VAR_TEMP_0, 1
	return


MojaveCave_Spiritomb_RanAway::
# 73 "data/maps/MojaveCave/scripts.pory"
	playmoncry SPECIES_SPIRITOMB, CRY_MODE_ENCOUNTER
# 74 "data/maps/MojaveCave/scripts.pory"
	waitmoncry
# 75 "data/maps/MojaveCave/scripts.pory"
	fadescreen FADE_TO_BLACK
# 76 "data/maps/MojaveCave/scripts.pory"
	removeobject OBJ_EVENT_GFX_MOJAVE_CAVE_SPIRITOMB
# 77 "data/maps/MojaveCave/scripts.pory"
	delay 30
# 78 "data/maps/MojaveCave/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 79 "data/maps/MojaveCave/scripts.pory"
	msgbox MojaveCave_Spiritomb_Won_Text_0
# 80 "data/maps/MojaveCave/scripts.pory"
	additem ITEM_ODD_KEYSTONE, 1
# 81 "data/maps/MojaveCave/scripts.pory"
	setvar VAR_TEMP_0, 1
	return


MojaveCave_NPC_Hiker::
# 93 "data/maps/MojaveCave/scripts.pory"
	lock
# 94 "data/maps/MojaveCave/scripts.pory"
	faceplayer
# 95 "data/maps/MojaveCave/scripts.pory"
	msgbox MojaveCave_NPC_Hiker_Text_0
# 98 "data/maps/MojaveCave/scripts.pory"
	waitmessage
# 99 "data/maps/MojaveCave/scripts.pory"
	release
	end


MojaveCave_NPC_Scientist::
# 104 "data/maps/MojaveCave/scripts.pory"
	lock
# 105 "data/maps/MojaveCave/scripts.pory"
	faceplayer
# 106 "data/maps/MojaveCave/scripts.pory"
	msgbox MojaveCave_NPC_Scientist_Text_0
# 110 "data/maps/MojaveCave/scripts.pory"
	waitmessage
# 111 "data/maps/MojaveCave/scripts.pory"
	applymovement 6, MojaveCave_NPC_Scientist_Movement_0
# 114 "data/maps/MojaveCave/scripts.pory"
	waitmovement 6
# 115 "data/maps/MojaveCave/scripts.pory"
	release
	end


MojaveCave_NPC_OldMan::
# 120 "data/maps/MojaveCave/scripts.pory"
	lock
# 121 "data/maps/MojaveCave/scripts.pory"
	faceplayer
# 122 "data/maps/MojaveCave/scripts.pory"
	msgbox MojaveCave_NPC_OldMan_Text_0
# 127 "data/maps/MojaveCave/scripts.pory"
	waitmessage
# 128 "data/maps/MojaveCave/scripts.pory"
	release
	end


# 111 "data/maps/MojaveCave/scripts.pory"
MojaveCave_NPC_Scientist_Movement_0:
# 112 "data/maps/MojaveCave/scripts.pory"
	face_left
	step_end

MojaveCave_Spiritomb_Text_0:
# 17 "data/maps/MojaveCave/scripts.pory"
	.string "You placed the Odd Keystone on the\n"
	.string "ground.$"

MojaveCave_Spiritomb_Text_1:
# 29 "data/maps/MojaveCave/scripts.pory"
	.string "....tooooomb !$"

MojaveCave_Spiritomb_Won_Text_0:
# 66 "data/maps/MojaveCave/scripts.pory"
	.string "It disappered to the core.\p"
	.string "You put the Keystone back in your bag.$"

MojaveCave_NPC_Hiker_Text_0:
# 96 "data/maps/MojaveCave/scripts.pory"
	.string "Hot, dusty, cramped… just the way a real\n"
	.string "cave adventure should be!$"

MojaveCave_NPC_Scientist_Text_0:
# 107 "data/maps/MojaveCave/scripts.pory"
	.string "Shh… I'm examining this rock.\p"
	.string "One wrong vibration and the readings\n"
	.string "get messed up!$"

MojaveCave_NPC_OldMan_Text_0:
# 123 "data/maps/MojaveCave/scripts.pory"
	.string "I'm visiting this cave for many years\n"
	.string "now.\p"
	.string "If you listen closely, you can hear the\n"
	.string "desert whisper through the stones.\p"
	.string "And you know what? I like it!$"

MojaveCave_Text_Spiritomb_LayDownOddKeystone::
# 85 "data/maps/MojaveCave/scripts.pory"
	.string "Look's like you can place the Odd\n"
	.string "Keystone here.\p"
	.string "Do you want to place it down?$"
