SlateportCity_House_GenderChange_MapScripts::
	.byte 0

	.set GENDER_CHANGE_RESULT_SUCCESS, 0
	.set GENDER_CHANGE_RESULT_EGG, 1
	.set GENDER_CHANGE_RESULT_GENDERLESS, 2
	.set GENDER_CHANGE_RESULT_FIXED_GENDER, 3

SlateportCity_House_GenderChange_EventScript_Researcher::
	lock
	faceplayer
	goto_if_set FLAG_MET_GENDER_RESEARCHER, SlateportCity_House_GenderChange_EventScript_RepeatGreeting
	msgbox SlateportCity_House_GenderChange_Text_ResearcherIntro, MSGBOX_YESNO
	setflag FLAG_MET_GENDER_RESEARCHER
	goto_if_eq VAR_RESULT, YES, SlateportCity_House_GenderChange_EventScript_ChooseMon
	goto SlateportCity_House_GenderChange_EventScript_Decline
	end

SlateportCity_House_GenderChange_EventScript_RepeatGreeting::
	msgbox SlateportCity_House_GenderChange_Text_RepeatGreeting, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_House_GenderChange_EventScript_ChooseMon
	goto SlateportCity_House_GenderChange_EventScript_Decline
	end

SlateportCity_House_GenderChange_EventScript_ChooseMon::
	msgbox SlateportCity_House_GenderChange_Text_ChooseMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_House_GenderChange_EventScript_Decline
	specialvar VAR_RESULT, Script_ToggleSelectedMonGender
	goto_if_eq VAR_RESULT, GENDER_CHANGE_RESULT_SUCCESS, SlateportCity_House_GenderChange_EventScript_Success
	goto_if_eq VAR_RESULT, GENDER_CHANGE_RESULT_EGG, SlateportCity_House_GenderChange_EventScript_Egg
	goto_if_eq VAR_RESULT, GENDER_CHANGE_RESULT_GENDERLESS, SlateportCity_House_GenderChange_EventScript_Genderless
	goto SlateportCity_House_GenderChange_EventScript_FixedGender
	end

SlateportCity_House_GenderChange_EventScript_Success::
	special BufferMonNickname
	playse MUS_LEVEL_UP
	waitse
	msgbox SlateportCity_House_GenderChange_Text_Success, MSGBOX_DEFAULT
	release
	end

SlateportCity_House_GenderChange_EventScript_Egg::
	msgbox SlateportCity_House_GenderChange_Text_Egg, MSGBOX_DEFAULT
	release
	end

SlateportCity_House_GenderChange_EventScript_Genderless::
	msgbox SlateportCity_House_GenderChange_Text_Genderless, MSGBOX_DEFAULT
	release
	end

SlateportCity_House_GenderChange_EventScript_FixedGender::
	msgbox SlateportCity_House_GenderChange_Text_FixedGender, MSGBOX_DEFAULT
	release
	end

SlateportCity_House_GenderChange_EventScript_Decline::
	msgbox SlateportCity_House_GenderChange_Text_Decline, MSGBOX_DEFAULT
	release
	end

SlateportCity_House_GenderChange_EventScript_Gallade::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_House_GenderChange_EventScript_Kirlia::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KIRLIA, CRY_MODE_NORMAL
	msgbox SlateportCity_House_GenderChange_Text_Kirlia, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_House_GenderChange_EventScript_Snorunt::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SNORUNT, CRY_MODE_NORMAL
	msgbox SlateportCity_House_GenderChange_Text_Snorunt, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_House_GenderChange_Text_Kirlia:
	.string "KIRLIA: Kyaaa ..?$"

SlateportCity_House_GenderChange_Text_Snorunt:
	.string "SNORUNT: Snooo!$"


SlateportCity_House_GenderChange_Text_ResearcherIntro:
	.string "Ah, a young TRAINER! Perfect timing.\p"
	.string "I was just reviewing my research notes.\p"
	.string "My field of study is POKéMON gender.\p"
	.string "It may seem like a small detail,\n"
	.string "but it can shape evolution,\l"
	.string "appearance, and even behavior.\p"
	.string "A male KIRLIA may become GALLADE,\n"
	.string "while only a female SALANDIT may\l"
	.string "evolve into SALAZZLE.\p"
	.string "Some species even show different\n"
	.string "forms depending on gender.\p"
	.string "Quietly fascinating, isn't it?\p"
	.string "Now then... Shall I change the gender\n"
	.string "of one of your POKéMON?$"

SlateportCity_House_GenderChange_Text_ChooseMon:
	.string "Which POKéMON would you like\n"
	.string "me to examine?\p"
	.string "Do not worry. I will be careful.$"

SlateportCity_House_GenderChange_Text_RepeatGreeting:
	.string "Ah, welcome back.\p"
	.string "Shall I change the gender\n"
	.string "of one of your POKéMON?$"

SlateportCity_House_GenderChange_Text_Success:
	.string "Excellent. {STR_VAR_1}'s data\n"
	.string "responded as expected.\p"
	.string "Its gender has been changed\n"
	.string "successfully.\p"
	.string "A small adjustment,\n"
	.string "but a fascinating one.$"

SlateportCity_House_GenderChange_Text_Egg:
	.string "An EGG? No, that would be far\n"
	.string "too early.\p"
	.string "There is not enough developed data\n"
	.string "for my instruments to work with.$"

SlateportCity_House_GenderChange_Text_Genderless:
	.string "Hm... Interesting.\p"
	.string "This POKéMON has no changeable gender.\p"
	.string "There is simply nothing\n"
	.string "for my research to adjust.$"

SlateportCity_House_GenderChange_Text_FixedGender:
	.string "Ah, I see. This species has\n"
	.string "only one possible gender\l"
	.string "listed in my research tables.\p"
	.string "Some things remain beyond\n"
	.string "even careful science.$"

SlateportCity_House_GenderChange_Text_Decline:
	.string "I understand. Research should never\n"
	.string "be rushed.\p"
	.string "Come back when your team is ready\n"
	.string "for a small study.$"
