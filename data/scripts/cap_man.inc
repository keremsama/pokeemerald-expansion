CapMan_EventScript_HyperTrain::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, CapMan_EventScript_NoPokemon
	specialvar VAR_RESULT, CapMan_GetBottleCapAvailability
	goto_if_eq VAR_RESULT, 0, CapMan_EventScript_NoBottleCap
	goto_if_eq VAR_RESULT, 1, CapMan_EventScript_UseBottleCap
	goto_if_eq VAR_RESULT, 2, CapMan_EventScript_UseGoldBottleCap
	msgbox CapMan_Text_ChooseCap, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_CAPMAN_CAP, FALSE
	switch VAR_RESULT
	case 0, CapMan_EventScript_UseBottleCap
	case 1, CapMan_EventScript_UseGoldBottleCap
	goto CapMan_EventScript_Cancel
	end

CapMan_EventScript_UseBottleCap::
	setvar VAR_0x8005, ITEM_BOTTLE_CAP
	goto CapMan_EventScript_ChoosePokemon
	end

CapMan_EventScript_UseGoldBottleCap::
	setvar VAR_0x8005, ITEM_GOLD_BOTTLE_CAP
	goto CapMan_EventScript_ChoosePokemon
	end

CapMan_EventScript_ChoosePokemon::
	msgbox CapMan_Text_ChoosePokemon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, CapMan_EventScript_Cancel
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, CapMan_EventScript_Egg
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	goto_if_eq VAR_0x8005, ITEM_GOLD_BOTTLE_CAP, CapMan_EventScript_ApplyTraining
	msgbox CapMan_Text_ChooseStat, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_CAPMAN_STAT, FALSE
	goto_if_ge VAR_RESULT, 6, CapMan_EventScript_Cancel
	copyvar VAR_0x8006, VAR_RESULT
	goto CapMan_EventScript_ApplyTraining
	end

CapMan_EventScript_ApplyTraining::
	special CapMan_HyperTrainSelectedMon
	removeitem VAR_0x8005, 1
	playfanfare MUS_LEVEL_UP
	msgbox CapMan_Text_TrainingComplete, MSGBOX_DEFAULT
	waitfanfare
	releaseall
	end

CapMan_EventScript_Egg::
	msgbox CapMan_Text_Egg, MSGBOX_DEFAULT
	goto CapMan_EventScript_ChoosePokemon
	end

CapMan_EventScript_NoPokemon::
	msgbox CapMan_Text_NoPokemon, MSGBOX_DEFAULT
	releaseall
	end

CapMan_EventScript_NoBottleCap::
	msgbox CapMan_Text_NoBottleCap, MSGBOX_DEFAULT
	releaseall
	end

CapMan_EventScript_Cancel::
	msgbox CapMan_Text_Cancel, MSGBOX_DEFAULT
	releaseall
	end

CapMan_Text_ChooseCap:
	.string "You have both kinds of BOTTLE CAP.\p"
	.string "Which one should I use?$"

CapMan_Text_ChoosePokemon:
	.string "Which POKéMON do you want\n"
	.string "to HYPER TRAIN?$"

CapMan_Text_ChooseStat:
	.string "Which stat should I train?$"

CapMan_Text_TrainingComplete:
	.string "{STR_VAR_1}'s potential has been\n"
	.string "raised to the max!$"

CapMan_Text_Egg:
	.string "Even I can't HYPER TRAIN an EGG.\p"
	.string "Choose another POKéMON.$"

CapMan_Text_NoPokemon:
	.string "You don't have any POKéMON with you.$"

CapMan_Text_NoBottleCap:
	.string "Bring me a BOTTLE CAP or\n"
	.string "a GOLD BOTTLE CAP.$"

CapMan_Text_Cancel:
	.string "Come back if you want to\n"
	.string "HYPER TRAIN a POKéMON.$"
