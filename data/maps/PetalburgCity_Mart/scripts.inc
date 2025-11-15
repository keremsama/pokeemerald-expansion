# 1 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_MapScripts::
# 2 "data/maps/PetalburgCity_Mart/scripts.pory"
	.byte 0
# 3 "data/maps/PetalburgCity_Mart/scripts.pory"

# 4 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_EventScript_Clerk::
# 5 "data/maps/PetalburgCity_Mart/scripts.pory"
	lock
# 6 "data/maps/PetalburgCity_Mart/scripts.pory"
	faceplayer
# 7 "data/maps/PetalburgCity_Mart/scripts.pory"
	message gText_HowMayIServeYou
# 8 "data/maps/PetalburgCity_Mart/scripts.pory"
	waitmessage
# 9 "data/maps/PetalburgCity_Mart/scripts.pory"
	goto_if_set FLAG_PETALBURG_MART_EXPANDED_ITEMS, PetalburgCity_Mart_EventScript_ExpandedItems
# 10 "data/maps/PetalburgCity_Mart/scripts.pory"
	pokemart PetalburgCity_Mart_Pokemart_Basic
# 11 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
# 12 "data/maps/PetalburgCity_Mart/scripts.pory"
	release
# 13 "data/maps/PetalburgCity_Mart/scripts.pory"
	end
# 14 "data/maps/PetalburgCity_Mart/scripts.pory"

# 15 "data/maps/PetalburgCity_Mart/scripts.pory"
	.align 2
# 16 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_Pokemart_Basic:
# 17 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 18 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 19 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 20 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 21 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 22 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 23 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 24 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_SPEED
# 25 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_ATTACK
# 26 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 27 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ORANGE_MAIL
# 28 "data/maps/PetalburgCity_Mart/scripts.pory"
	pokemartlistend
# 29 "data/maps/PetalburgCity_Mart/scripts.pory"

# 30 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_Pokemart_Balls:
# 31 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_NET_BALL
# 32 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_DIVE_BALL
# 33 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_NEST_BALL
# 34 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 35 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_DUSK_BALL
# 36 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_HEAL_BALL
# 37 "data/maps/PetalburgCity_Mart/scripts.pory"
	pokemartlistend
# 38 "data/maps/PetalburgCity_Mart/scripts.pory"

# 39 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_EventScript_ExpandedItems::
# 40 "data/maps/PetalburgCity_Mart/scripts.pory"
	pokemart PetalburgCity_Mart_Pokemart_Expanded
# 41 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
# 42 "data/maps/PetalburgCity_Mart/scripts.pory"
	release
# 43 "data/maps/PetalburgCity_Mart/scripts.pory"
	end
# 44 "data/maps/PetalburgCity_Mart/scripts.pory"

# 45 "data/maps/PetalburgCity_Mart/scripts.pory"
	.align 2
# 46 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_Pokemart_Expanded:
# 47 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 48 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 49 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ULTRA_BALL
# 50 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 51 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 52 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_HYPER_POTION
# 53 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 54 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 55 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 56 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 57 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 58 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_SPEED
# 59 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_ATTACK
# 60 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 61 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ORANGE_MAIL
# 62 "data/maps/PetalburgCity_Mart/scripts.pory"
	pokemartlistend
# 63 "data/maps/PetalburgCity_Mart/scripts.pory"

# 64 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_EventScript_Woman::
# 65 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox PetalburgCity_Mart_Text_WeakWillGrowStronger, MSGBOX_NPC
# 66 "data/maps/PetalburgCity_Mart/scripts.pory"
	end
# 67 "data/maps/PetalburgCity_Mart/scripts.pory"

# 68 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_EventScript_Boy::
# 69 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox PetalburgCity_Mart_Text_RepelIsUseful, MSGBOX_NPC
# 70 "data/maps/PetalburgCity_Mart/scripts.pory"
	end
# 71 "data/maps/PetalburgCity_Mart/scripts.pory"

# 72 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_EventScript_Man::
# 73 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou, MSGBOX_NPC
# 74 "data/maps/PetalburgCity_Mart/scripts.pory"
	end
# 75 "data/maps/PetalburgCity_Mart/scripts.pory"

# 76 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_Text_WeakWillGrowStronger:
# 77 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "Even if a POKéMON is weak now,\n"
# 78 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "it will grow stronger.\p"
# 79 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "The most important thing is love!\n"
# 80 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "Love for your POKéMON!$"
# 81 "data/maps/PetalburgCity_Mart/scripts.pory"

# 82 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_Text_RepelIsUseful:
# 83 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "Do you use REPEL?\n"
# 84 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "It keeps POKéMON away, so it's\l"
# 85 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "useful when you're in a hurry.$"
# 86 "data/maps/PetalburgCity_Mart/scripts.pory"

# 87 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou:
# 88 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "Do you have any ANTIDOTES with\n"
# 89 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "you?\p"
# 90 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "If you walk around with a poisoned\n"
# 91 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "POKéMON, it will lose HP until it faints.\l"
# 92 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "Take some ANTIDOTES with you.$"

LavaridgeTown_Mart_EventScript_Clerk2::
# 99 "data/maps/PetalburgCity_Mart/scripts.pory"
	lock
# 100 "data/maps/PetalburgCity_Mart/scripts.pory"
	faceplayer
# 101 "data/maps/PetalburgCity_Mart/scripts.pory"
	goto_if_unset FLAG_BADGE04_GET, LavaridgeTown_Mart_EventScript_Clerk2_2
# 111 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox gText_HowMayIServeYou
# 112 "data/maps/PetalburgCity_Mart/scripts.pory"
	waitmessage
# 113 "data/maps/PetalburgCity_Mart/scripts.pory"
	pokemart PetalburgCity_Mart_Pokemart_Balls
# 114 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox gText_PleaseComeAgain
# 115 "data/maps/PetalburgCity_Mart/scripts.pory"
	waitmessage
# 116 "data/maps/PetalburgCity_Mart/scripts.pory"
	release
	end

LavaridgeTown_Mart_EventScript_Clerk2_2:
# 102 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox LavaridgeTown_Mart_EventScript_Clerk2_Text_0
# 107 "data/maps/PetalburgCity_Mart/scripts.pory"
	waitmessage
# 108 "data/maps/PetalburgCity_Mart/scripts.pory"
	release
	end


LavaridgeTown_Mart_EventScript_Clerk2_Text_0:
# 103 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "Welcome!\p"
	.string "We'll be selling different kinds of\p"
	.string "Poké Balls in the future.\p"
	.string "Be sure to stop by again soon!$"
