# 1 "data/maps/MtPyre_6F/scripts.pory"

# 2 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_MapScripts::
# 3 "data/maps/MtPyre_6F/scripts.pory"
	.byte 0
# 4 "data/maps/MtPyre_6F/scripts.pory"

# 5 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_EventScript_Valerie::
# 6 "data/maps/MtPyre_6F/scripts.pory"
	trainerbattle_single TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieIntro, MtPyre_6F_Text_ValerieDefeat, MtPyre_6F_EventScript_RegisterValerie
# 7 "data/maps/MtPyre_6F/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 8 "data/maps/MtPyre_6F/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MtPyre_6F_EventScript_RematchValerie
# 9 "data/maps/MtPyre_6F/scripts.pory"
	msgbox MtPyre_6F_Text_ValeriePostBattle, MSGBOX_DEFAULT
# 10 "data/maps/MtPyre_6F/scripts.pory"
	release
# 11 "data/maps/MtPyre_6F/scripts.pory"
	end
# 12 "data/maps/MtPyre_6F/scripts.pory"

# 13 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_EventScript_RegisterValerie::
# 14 "data/maps/MtPyre_6F/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 15 "data/maps/MtPyre_6F/scripts.pory"
	waitmovement 0
# 16 "data/maps/MtPyre_6F/scripts.pory"
	msgbox MtPyre_6F_Text_ValerieRegister, MSGBOX_DEFAULT
# 17 "data/maps/MtPyre_6F/scripts.pory"
	register_matchcall TRAINER_VALERIE_1
# 18 "data/maps/MtPyre_6F/scripts.pory"
	release
# 19 "data/maps/MtPyre_6F/scripts.pory"
	end
# 20 "data/maps/MtPyre_6F/scripts.pory"

# 21 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_EventScript_RematchValerie::
# 22 "data/maps/MtPyre_6F/scripts.pory"
	trainerbattle_rematch TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieRematchIntro, MtPyre_6F_Text_ValerieRematchDefeat
# 23 "data/maps/MtPyre_6F/scripts.pory"
	msgbox MtPyre_6F_Text_ValeriePostRematch, MSGBOX_AUTOCLOSE
# 24 "data/maps/MtPyre_6F/scripts.pory"
	end
# 25 "data/maps/MtPyre_6F/scripts.pory"

# 26 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_EventScript_Cedric::
# 27 "data/maps/MtPyre_6F/scripts.pory"
	trainerbattle_single TRAINER_CEDRIC, MtPyre_6F_Text_CedricIntro, MtPyre_6F_Text_CedricDefeat
# 28 "data/maps/MtPyre_6F/scripts.pory"
	msgbox MtPyre_6F_Text_CedricPostBattle, MSGBOX_AUTOCLOSE
# 29 "data/maps/MtPyre_6F/scripts.pory"
	end
# 30 "data/maps/MtPyre_6F/scripts.pory"

# 31 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_Text_ValerieIntro:
# 32 "data/maps/MtPyre_6F/scripts.pory"
	.string "When I'm here…\n"
# 33 "data/maps/MtPyre_6F/scripts.pory"
	.string "A curious power flows into me…$"
# 34 "data/maps/MtPyre_6F/scripts.pory"

# 35 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_Text_ValerieDefeat:
# 36 "data/maps/MtPyre_6F/scripts.pory"
	.string "The power is ebbing away…$"
# 37 "data/maps/MtPyre_6F/scripts.pory"

# 38 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_Text_ValeriePostBattle:
# 39 "data/maps/MtPyre_6F/scripts.pory"
	.string "Perhaps the power is from the spirits\n"
# 40 "data/maps/MtPyre_6F/scripts.pory"
	.string "of POKéMON in fitful sleep here…$"
# 41 "data/maps/MtPyre_6F/scripts.pory"

# 42 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_Text_ValerieRegister:
# 43 "data/maps/MtPyre_6F/scripts.pory"
	.string "Fufufu… I lost the match, but…\n"
# 44 "data/maps/MtPyre_6F/scripts.pory"
	.string "I have this little ability…\p"
# 45 "data/maps/MtPyre_6F/scripts.pory"
	.string "Without ever laying my hands on\n"
# 46 "data/maps/MtPyre_6F/scripts.pory"
	.string "your POKéNAV… Hiyah!$"
# 47 "data/maps/MtPyre_6F/scripts.pory"

# 48 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_Text_ValerieRematchIntro:
# 49 "data/maps/MtPyre_6F/scripts.pory"
	.string "Behind you…\n"
# 50 "data/maps/MtPyre_6F/scripts.pory"
	.string "What is it…$"
# 51 "data/maps/MtPyre_6F/scripts.pory"

# 52 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_Text_ValerieRematchDefeat:
# 53 "data/maps/MtPyre_6F/scripts.pory"
	.string "Something faded away…$"
# 54 "data/maps/MtPyre_6F/scripts.pory"

# 55 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_Text_ValeriePostRematch:
# 56 "data/maps/MtPyre_6F/scripts.pory"
	.string "The POKéMON at rest here…\n"
# 57 "data/maps/MtPyre_6F/scripts.pory"
	.string "Sometimes, they play…$"
# 58 "data/maps/MtPyre_6F/scripts.pory"

# 59 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_Text_CedricIntro:
# 60 "data/maps/MtPyre_6F/scripts.pory"
	.string "Have you lost your bearings?\n"
# 61 "data/maps/MtPyre_6F/scripts.pory"
	.string "Have no fear for I am here!$"
# 62 "data/maps/MtPyre_6F/scripts.pory"

# 63 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_Text_CedricDefeat:
# 64 "data/maps/MtPyre_6F/scripts.pory"
	.string "Weren't you lost?$"
# 65 "data/maps/MtPyre_6F/scripts.pory"

# 66 "data/maps/MtPyre_6F/scripts.pory"
MtPyre_6F_Text_CedricPostBattle:
# 67 "data/maps/MtPyre_6F/scripts.pory"
	.string "I had this feeling that a lost TRAINER\n"
# 68 "data/maps/MtPyre_6F/scripts.pory"
	.string "would be panicked and easy to beat.\p"
# 69 "data/maps/MtPyre_6F/scripts.pory"
	.string "It's dirty and I won't try it again…$"

MtPyre_6F_OldSpiritombLady::
# 76 "data/maps/MtPyre_6F/scripts.pory"
	lock
# 77 "data/maps/MtPyre_6F/scripts.pory"
	faceplayer
# 78 "data/maps/MtPyre_6F/scripts.pory"
	goto_if_set FLAG_GET_ODD_KEY_STONE, MtPyre_6F_OldSpiritombLady_2
MtPyre_6F_OldSpiritombLady_1:
# 81 "data/maps/MtPyre_6F/scripts.pory"
	msgbox MtPyre_6F_OldSpiritombLady_Text_WantSeeBanette, MSGBOX_YESNO
# 82 "data/maps/MtPyre_6F/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq MtPyre_6F_OldSpiritombLady_5
# 87 "data/maps/MtPyre_6F/scripts.pory"
	checkspecies SPECIES_BANETTE, OPEN_PARTY_SCREEN
# 88 "data/maps/MtPyre_6F/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq MtPyre_6F_OldSpiritombLady_8
# 93 "data/maps/MtPyre_6F/scripts.pory"
	msgbox MtPyre_6F_OldSpiritombLady_Text_ThatsIt
# 94 "data/maps/MtPyre_6F/scripts.pory"
	giveitem ITEM_ODD_KEYSTONE, 1
# 95 "data/maps/MtPyre_6F/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq MtPyre_6F_OldSpiritombLady_11
# 100 "data/maps/MtPyre_6F/scripts.pory"
	setflag FLAG_GET_ODD_KEY_STONE
# 101 "data/maps/MtPyre_6F/scripts.pory"
	goto MtPyre_6F_OldSpiritombLady_TheVision
	return

MtPyre_6F_OldSpiritombLady_2:
# 79 "data/maps/MtPyre_6F/scripts.pory"
	goto MtPyre_6F_OldSpiritombLady_TheVision
	goto MtPyre_6F_OldSpiritombLady_1

MtPyre_6F_OldSpiritombLady_5:
# 83 "data/maps/MtPyre_6F/scripts.pory"
	msgbox MtPyre_6F_OldSpiritombLady_Text_PleaseShowMe
# 84 "data/maps/MtPyre_6F/scripts.pory"
	release
	end

MtPyre_6F_OldSpiritombLady_8:
# 89 "data/maps/MtPyre_6F/scripts.pory"
	msgbox MtPyre_6F_OldSpiritombLady_Text_ThatsNotWhatIWantToSee
# 90 "data/maps/MtPyre_6F/scripts.pory"
	release
	end

MtPyre_6F_OldSpiritombLady_11:
# 96 "data/maps/MtPyre_6F/scripts.pory"
	msgbox gText_BagIsFull
# 97 "data/maps/MtPyre_6F/scripts.pory"
	release
	end


MtPyre_6F_OldSpiritombLady_TheVision::
# 105 "data/maps/MtPyre_6F/scripts.pory"
	msgbox MtPyre_6F_OldSpiritombLady_Text_TheVision
# 106 "data/maps/MtPyre_6F/scripts.pory"
	release
	end


MtPyre_6F_OldSpiritombLady_Text_WantSeeBanette::
# 110 "data/maps/MtPyre_6F/scripts.pory"
	.string "…You… You there…\p"
	.string "Your presence… it shivers the air.\p"
	.string "Tell me… do you carry a Banette with\n"
	.string "you?\p"
	.string "Its sorrowful grin… its lingering\n"
	.string "hatred…\p"
	.string "I must see it…\p"
	.string "Show it to me… so I may understand its\n"
	.string "whispers…$"

MtPyre_6F_OldSpiritombLady_Text_PleaseShowMe::
# 121 "data/maps/MtPyre_6F/scripts.pory"
	.string "I must see it…$"

MtPyre_6F_OldSpiritombLady_Text_ThatsIt::
# 127 "data/maps/MtPyre_6F/scripts.pory"
	.string "Ahh… yes…\p"
	.string "Its eyes… still searching.\p"
	.string "Its smile… never healing.\p"
	.string "… Here… take this.$"

MtPyre_6F_OldSpiritombLady_Text_ThatsNotWhatIWantToSee::
# 136 "data/maps/MtPyre_6F/scripts.pory"
	.string "No… no… not that one…\p"
	.string "It is not the lost puppet I seek…$"

MtPyre_6F_OldSpiritombLady_Text_TheVision::
# 143 "data/maps/MtPyre_6F/scripts.pory"
	.string "I saw… a vision… a place buried in\n"
	.string "sun-baked silence…\p"
	.string "A room shaped almost like a circle… sand\n"
	.string "staying in the center…\p"
	.string "Seek the room where the sand does not\n"
	.string "shift…\p"
	.string "And the keystone will answer you…$"
