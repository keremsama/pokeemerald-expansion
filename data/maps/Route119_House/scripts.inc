# 1 "data/maps/Route119_House/scripts.pory"

# 2 "data/maps/Route119_House/scripts.pory"
Route119_House_MapScripts::
# 3 "data/maps/Route119_House/scripts.pory"
	.byte 0
# 4 "data/maps/Route119_House/scripts.pory"

# 5 "data/maps/Route119_House/scripts.pory"
Route119_House_EventScript_Woman::
# 6 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_Text_RumorAboutCaveOfOrigin, MSGBOX_NPC
# 7 "data/maps/Route119_House/scripts.pory"
	end
# 8 "data/maps/Route119_House/scripts.pory"

# 9 "data/maps/Route119_House/scripts.pory"
Route119_House_EventScript_Wingull::
# 10 "data/maps/Route119_House/scripts.pory"
	lock
# 11 "data/maps/Route119_House/scripts.pory"
	faceplayer
# 12 "data/maps/Route119_House/scripts.pory"
	waitse
# 13 "data/maps/Route119_House/scripts.pory"
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
# 14 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_Text_Wingull, MSGBOX_DEFAULT
# 15 "data/maps/Route119_House/scripts.pory"
	waitmoncry
# 16 "data/maps/Route119_House/scripts.pory"
	release
# 17 "data/maps/Route119_House/scripts.pory"
	end
# 18 "data/maps/Route119_House/scripts.pory"

# 19 "data/maps/Route119_House/scripts.pory"
Route119_House_Text_RumorAboutCaveOfOrigin:
# 20 "data/maps/Route119_House/scripts.pory"
	.string "I heard about a cave called the CAVE\n"
# 21 "data/maps/Route119_House/scripts.pory"
	.string "OF ORIGIN.\p"
# 22 "data/maps/Route119_House/scripts.pory"
	.string "People rumor that the spirits of\n"
# 23 "data/maps/Route119_House/scripts.pory"
	.string "POKéMON are revived there. Could\l"
# 24 "data/maps/Route119_House/scripts.pory"
	.string "something like that really happen?$"
# 25 "data/maps/Route119_House/scripts.pory"

# 26 "data/maps/Route119_House/scripts.pory"
Route119_House_Text_Wingull:
# 27 "data/maps/Route119_House/scripts.pory"
	.string "WINGULL: Pihyoh!$"

Route119_House_EventScript_CapMan::
# 34 "data/maps/Route119_House/scripts.pory"
	lock
# 35 "data/maps/Route119_House/scripts.pory"
	faceplayer
# 37 "data/maps/Route119_House/scripts.pory"
	setvar VAR_0x8009, FALSE
# 39 "data/maps/Route119_House/scripts.pory"
	goto_if_unset FLAG_MET_CAP_MAN, Route119_House_EventScript_CapMan_2
# 52 "data/maps/Route119_House/scripts.pory"
	setvar VAR_0x8009, TRUE
Route119_House_EventScript_CapMan_1:
# 55 "data/maps/Route119_House/scripts.pory"
	specialvar VAR_RESULT, CapMan_GetBottleCapAvailability
# 56 "data/maps/Route119_House/scripts.pory"
	copyvar VAR_0x8008, VAR_RESULT
# 58 "data/maps/Route119_House/scripts.pory"
	compare VAR_0x8009, TRUE
	goto_if_eq Route119_House_EventScript_CapMan_6
Route119_House_EventScript_CapMan_5:
# 62 "data/maps/Route119_House/scripts.pory"
	compare VAR_0x8008, 0
	goto_if_eq Route119_House_EventScript_CapMan_9
# 70 "data/maps/Route119_House/scripts.pory"
	compare VAR_0x8009, TRUE
	goto_if_eq Route119_House_EventScript_CapMan_12
Route119_House_EventScript_CapMan_11:
# 79 "data/maps/Route119_House/scripts.pory"
	switch VAR_0x8008
# 80 "data/maps/Route119_House/scripts.pory"
	case 1, Route119_House_EventScript_CapMan_16
# 82 "data/maps/Route119_House/scripts.pory"
	case 2, Route119_House_EventScript_CapMan_17
# 84 "data/maps/Route119_House/scripts.pory"
	case 3, Route119_House_EventScript_CapMan_18
Route119_House_EventScript_CapMan_14:
Route119_House_EventScript_CapMan_20:
# 89 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_6
# 90 "data/maps/Route119_House/scripts.pory"
	multichoice 22, 6, MULTI_YESNOINFO, FALSE
# 92 "data/maps/Route119_House/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Route119_House_EventScript_CapMan_26
# 96 "data/maps/Route119_House/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq Route119_House_EventScript_CapMan_35
# 105 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_8
# 106 "data/maps/Route119_House/scripts.pory"
	release
	end

Route119_House_EventScript_CapMan_2:
# 40 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_0
# 50 "data/maps/Route119_House/scripts.pory"
	setflag FLAG_MET_CAP_MAN
	goto Route119_House_EventScript_CapMan_1

Route119_House_EventScript_CapMan_6:
# 59 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_1
	goto Route119_House_EventScript_CapMan_5

Route119_House_EventScript_CapMan_9:
# 63 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_2
# 66 "data/maps/Route119_House/scripts.pory"
	release
	end

Route119_House_EventScript_CapMan_12:
# 71 "data/maps/Route119_House/scripts.pory"
	playse SE_PIN
# 72 "data/maps/Route119_House/scripts.pory"
	applymovement CAP_MAN, Route119_House_EventScript_CapMan_Movement_0
# 76 "data/maps/Route119_House/scripts.pory"
	waitmovement CAP_MAN
	goto Route119_House_EventScript_CapMan_11

Route119_House_EventScript_CapMan_16:
# 81 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_3
	goto Route119_House_EventScript_CapMan_14

Route119_House_EventScript_CapMan_17:
# 83 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_4
	goto Route119_House_EventScript_CapMan_14

Route119_House_EventScript_CapMan_18:
# 85 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_5
	goto Route119_House_EventScript_CapMan_14

Route119_House_EventScript_CapMan_19:
Route119_House_EventScript_CapMan_23:
# 111 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_9
# 112 "data/maps/Route119_House/scripts.pory"
	special ChoosePartyMon
# 113 "data/maps/Route119_House/scripts.pory"
	waitstate
# 115 "data/maps/Route119_House/scripts.pory"
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_eq Route119_House_EventScript_CapMan_32
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
# 0 "data/maps/Route119_House/scripts.pory"
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq Route119_House_EventScript_CapMan_41
# 129 "data/maps/Route119_House/scripts.pory"
	bufferpartymonnick STR_VAR_1, VAR_0x8004
# 131 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_11
	checkitem ITEM_BOTTLE_CAP
# 0 "data/maps/Route119_House/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq Route119_House_EventScript_CapMan_29
Route119_House_EventScript_CapMan_28:
	checkitem ITEM_GOLD_BOTTLE_CAP
# 0 "data/maps/Route119_House/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq Route119_House_EventScript_CapMan_38
Route119_House_EventScript_CapMan_37:
# 138 "data/maps/Route119_House/scripts.pory"
	dynmultistack 22, 8, FALSE, 2, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 140 "data/maps/Route119_House/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq Route119_House_EventScript_CapMan_44
# 146 "data/maps/Route119_House/scripts.pory"
	copyvar VAR_0x8005, VAR_RESULT
# 148 "data/maps/Route119_House/scripts.pory"
	compare VAR_0x8005, ITEM_BOTTLE_CAP
	goto_if_eq Route119_House_EventScript_CapMan_47
Route119_House_EventScript_CapMan_46:
# 161 "data/maps/Route119_House/scripts.pory"
	special CapMan_HyperTrainSelectedMon
# 162 "data/maps/Route119_House/scripts.pory"
	removeitem VAR_0x8005, 1
# 164 "data/maps/Route119_House/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 165 "data/maps/Route119_House/scripts.pory"
	compare VAR_0x8005, ITEM_GOLD_BOTTLE_CAP
	goto_if_eq Route119_House_EventScript_CapMan_50
# 168 "data/maps/Route119_House/scripts.pory"
	switch VAR_0x8006
# 169 "data/maps/Route119_House/scripts.pory"
	case 0, Route119_House_EventScript_CapMan_57
# 171 "data/maps/Route119_House/scripts.pory"
	case 1, Route119_House_EventScript_CapMan_58
# 173 "data/maps/Route119_House/scripts.pory"
	case 2, Route119_House_EventScript_CapMan_59
# 175 "data/maps/Route119_House/scripts.pory"
	case 3, Route119_House_EventScript_CapMan_60
# 177 "data/maps/Route119_House/scripts.pory"
	case 4, Route119_House_EventScript_CapMan_61
# 179 "data/maps/Route119_House/scripts.pory"
	case 5, Route119_House_EventScript_CapMan_62
Route119_House_EventScript_CapMan_49:
# 183 "data/maps/Route119_House/scripts.pory"
	waitfanfare
# 185 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_22
# 187 "data/maps/Route119_House/scripts.pory"
	release
	end

Route119_House_EventScript_CapMan_26:
	goto Route119_House_EventScript_CapMan_19

Route119_House_EventScript_CapMan_29:
# 133 "data/maps/Route119_House/scripts.pory"
	dynmultipush Route119_House_EventScript_CapMan_Text_12, ITEM_BOTTLE_CAP
	goto Route119_House_EventScript_CapMan_28

Route119_House_EventScript_CapMan_32:
# 116 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_8
# 117 "data/maps/Route119_House/scripts.pory"
	release
	end

Route119_House_EventScript_CapMan_35:
# 97 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_7
	goto Route119_House_EventScript_CapMan_20

Route119_House_EventScript_CapMan_38:
# 136 "data/maps/Route119_House/scripts.pory"
	dynmultipush Route119_House_EventScript_CapMan_Text_13, ITEM_GOLD_BOTTLE_CAP
	goto Route119_House_EventScript_CapMan_37

Route119_House_EventScript_CapMan_41:
# 122 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_10
	goto Route119_House_EventScript_CapMan_23

Route119_House_EventScript_CapMan_44:
# 141 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_8
# 142 "data/maps/Route119_House/scripts.pory"
	release
	end

Route119_House_EventScript_CapMan_47:
# 149 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_14
# 150 "data/maps/Route119_House/scripts.pory"
	multichoicegrid 14, 6, MULTI_CAPMAN_STAT, 2, FALSE
# 152 "data/maps/Route119_House/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_ge Route119_House_EventScript_CapMan_54
# 158 "data/maps/Route119_House/scripts.pory"
	copyvar VAR_0x8006, VAR_RESULT
	goto Route119_House_EventScript_CapMan_46

Route119_House_EventScript_CapMan_50:
# 166 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_15
	goto Route119_House_EventScript_CapMan_49

Route119_House_EventScript_CapMan_54:
# 153 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_8
# 154 "data/maps/Route119_House/scripts.pory"
	release
	end

Route119_House_EventScript_CapMan_57:
# 170 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_16
	goto Route119_House_EventScript_CapMan_49

Route119_House_EventScript_CapMan_58:
# 172 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_17
	goto Route119_House_EventScript_CapMan_49

Route119_House_EventScript_CapMan_59:
# 174 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_18
	goto Route119_House_EventScript_CapMan_49

Route119_House_EventScript_CapMan_60:
# 176 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_19
	goto Route119_House_EventScript_CapMan_49

Route119_House_EventScript_CapMan_61:
# 178 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_20
	goto Route119_House_EventScript_CapMan_49

Route119_House_EventScript_CapMan_62:
# 180 "data/maps/Route119_House/scripts.pory"
	msgbox Route119_House_EventScript_CapMan_Text_21
	goto Route119_House_EventScript_CapMan_49


# 72 "data/maps/Route119_House/scripts.pory"
Route119_House_EventScript_CapMan_Movement_0:
# 73 "data/maps/Route119_House/scripts.pory"
	emote_exclamation_mark
# 74 "data/maps/Route119_House/scripts.pory"
	delay_16
# 74 "data/maps/Route119_House/scripts.pory"
	delay_16
# 74 "data/maps/Route119_House/scripts.pory"
	delay_16
# 74 "data/maps/Route119_House/scripts.pory"
	delay_16
	step_end

Route119_House_EventScript_CapMan_Text_0:
# 41 "data/maps/Route119_House/scripts.pory"
	.string "Ah, a Trainer with a sharp eye!\p"
	.string "I'm the CAP MAN.\p"
	.string "I used to scout promising Trainers for\n"
	.string "the ELITE FOUR.\p"
	.string "These days, I would rather awaken the\n"
	.string "hidden potential sleeping inside\l"
	.string "Pokémon.\p"
	.string "With a BOTTLE CAP, I can bring out a\n"
	.string "Pokémon's hidden potential.\p"
	.string "A regular BOTTLE CAP lets me max out\n"
	.string "one IV.\p"
	.string "A GOLD BOTTLE CAP lets me max out every\n"
	.string "IV at once.\p"
	.string "I only ask for caps in return. I collect\n"
	.string "them, you see.$"

Route119_House_EventScript_CapMan_Text_1:
# 59 "data/maps/Route119_House/scripts.pory"
	.string "Hey, it's you again! Looking to Hyper\n"
	.string "Train another Pokémon?$"

Route119_House_EventScript_CapMan_Text_2:
# 64 "data/maps/Route119_House/scripts.pory"
	.string "No caps right now? Bring me one, and I'll\n"
	.string "Hyper Train one of your Pokémon.$"

Route119_House_EventScript_CapMan_Text_3:
# 81 "data/maps/Route119_House/scripts.pory"
	.string "Ah, I see you have a BOTTLE CAP!$"

Route119_House_EventScript_CapMan_Text_4:
# 83 "data/maps/Route119_House/scripts.pory"
	.string "Ah, I see you have a GOLD BOTTLE CAP!$"

Route119_House_EventScript_CapMan_Text_5:
# 85 "data/maps/Route119_House/scripts.pory"
	.string "Ah, I see you have both a BOTTLE CAP\n"
	.string "and a GOLD BOTTLE CAP!$"

Route119_House_EventScript_CapMan_Text_6:
# 89 "data/maps/Route119_House/scripts.pory"
	.string "Would you like me to Hyper Train one of\n"
	.string "your Pokémon?$"

Route119_House_EventScript_CapMan_Text_7:
# 98 "data/maps/Route119_House/scripts.pory"
	.string "A BOTTLE CAP lets me max out one IV of\n"
	.string "your choice.\p"
	.string "A GOLD BOTTLE CAP maxes out all six IVs\n"
	.string "at once.\p"
	.string "Choose the Pokémon first, then choose\n"
	.string "which cap I should use.$"

Route119_House_EventScript_CapMan_Text_8:
# 105 "data/maps/Route119_House/scripts.pory"
	.string "All right. Come back whenever you're\n"
	.string "ready.$"

Route119_House_EventScript_CapMan_Text_9:
# 111 "data/maps/Route119_House/scripts.pory"
	.string "Which Pokémon would you like me to\n"
	.string "Hyper Train?$"

Route119_House_EventScript_CapMan_Text_10:
# 122 "data/maps/Route119_House/scripts.pory"
	.string "I can't Hyper Train an Egg.\p"
	.string "Please choose another Pokémon.$"

Route119_House_EventScript_CapMan_Text_11:
# 131 "data/maps/Route119_House/scripts.pory"
	.string "Which cap should I use?$"

Route119_House_EventScript_CapMan_Text_12:
# 133 "data/maps/Route119_House/scripts.pory"
	.string "BOTTLE CAP$"

Route119_House_EventScript_CapMan_Text_13:
# 136 "data/maps/Route119_House/scripts.pory"
	.string "GOLD BOTTLE CAP$"

Route119_House_EventScript_CapMan_Text_14:
# 149 "data/maps/Route119_House/scripts.pory"
	.string "Which IV should I max out?$"

Route119_House_EventScript_CapMan_Text_15:
# 166 "data/maps/Route119_House/scripts.pory"
	.string "{STR_VAR_1}'s potential has been\n"
	.string "fully maxed out!$"

Route119_House_EventScript_CapMan_Text_16:
# 170 "data/maps/Route119_House/scripts.pory"
	.string "{STR_VAR_1}'s potential in HP has\n"
	.string "been maxed out!$"

Route119_House_EventScript_CapMan_Text_17:
# 172 "data/maps/Route119_House/scripts.pory"
	.string "{STR_VAR_1}'s potential in ATTACK\n"
	.string "has been maxed out!$"

Route119_House_EventScript_CapMan_Text_18:
# 174 "data/maps/Route119_House/scripts.pory"
	.string "{STR_VAR_1}'s potential in DEFENSE\n"
	.string "has been maxed out!$"

Route119_House_EventScript_CapMan_Text_19:
# 176 "data/maps/Route119_House/scripts.pory"
	.string "{STR_VAR_1}'s potential in SPEED\n"
	.string "has been maxed out!$"

Route119_House_EventScript_CapMan_Text_20:
# 178 "data/maps/Route119_House/scripts.pory"
	.string "{STR_VAR_1}'s potential in SP. ATK\n"
	.string "has been maxed out!$"

Route119_House_EventScript_CapMan_Text_21:
# 180 "data/maps/Route119_House/scripts.pory"
	.string "{STR_VAR_1}'s potential in SP. DEF\n"
	.string "has been maxed out!$"

Route119_House_EventScript_CapMan_Text_22:
# 185 "data/maps/Route119_House/scripts.pory"
	.string "Come back anytime you find another cap.$"
