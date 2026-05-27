FallarborTown_MoveRelearnersHouse_MapScripts::
	.byte 0


FallarborTown_MoveRelearnersHouse_EvoStoneMan::
# 5 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	lock
# 6 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	faceplayer
# 7 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	goto_if_unset FLAG_EVO_STONE_MAN_FIRST_ENCOUNTER, FallarborTown_MoveRelearnersHouse_EvoStoneMan_2
# 22 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	msgbox FallarborTown_MoveRelearnersHouse_EvoStoneMan_Text_1
# 27 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	waitmessage
# 28 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	goto_if_set FLAG_BADGE05_GET, FallarborTown_MoveRelearnersHouse_EvoStoneMan_5
# 32 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	pokemart EvoStone_Man
FallarborTown_MoveRelearnersHouse_EvoStoneMan_4:
# 34 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	msgbox FallarborTown_MoveRelearnersHouse_EvoStoneMan_Text_0
# 35 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	waitmessage
# 36 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	release
	end

FallarborTown_MoveRelearnersHouse_EvoStoneMan_2:
# 8 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	setflag FLAG_EVO_STONE_MAN_FIRST_ENCOUNTER
# 9 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	msgbox FallarborTown_EvoStoneMan_Text_FirstEncounter
# 10 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	waitmessage
# 11 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	goto_if_set FLAG_BADGE05_GET, FallarborTown_MoveRelearnersHouse_EvoStoneMan_9
# 15 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	pokemart EvoStone_Man
FallarborTown_MoveRelearnersHouse_EvoStoneMan_8:
# 17 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	msgbox FallarborTown_MoveRelearnersHouse_EvoStoneMan_Text_0
# 18 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	waitmessage
# 19 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	release
	end

FallarborTown_MoveRelearnersHouse_EvoStoneMan_5:
# 29 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	pokemart EvoStone_Man_Expanded
	goto FallarborTown_MoveRelearnersHouse_EvoStoneMan_4

FallarborTown_MoveRelearnersHouse_EvoStoneMan_9:
# 12 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	pokemart EvoStone_Man_Expanded
	goto FallarborTown_MoveRelearnersHouse_EvoStoneMan_8


FallarborTown_MoveRelearnersHouse_EvoItemLady::
# 42 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	lock
# 43 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	faceplayer
# 44 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	goto_if_unset FLAG_EVO_ITEM_LADY_FIRST_ENCOUNTER, FallarborTown_MoveRelearnersHouse_EvoItemLady_2
# 48 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	msgbox FallarborTown_MoveRelearnersHouse_EvoItemLady_Text_0
FallarborTown_MoveRelearnersHouse_EvoItemLady_1:
# 53 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	goto_if_unset FLAG_BADGE04_GET, FallarborTown_MoveRelearnersHouse_EvoItemLady_6
# 58 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	goto_if_set FLAG_BADGE05_GET, FallarborTown_MoveRelearnersHouse_EvoItemLady_9
# 61 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	pokemart EvoItem_Lady
FallarborTown_MoveRelearnersHouse_EvoItemLady_8:
# 63 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	msgbox FallarborTown_MoveRelearnersHouse_EvoStoneMan_Text_0
# 66 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	release
	end

FallarborTown_MoveRelearnersHouse_EvoItemLady_2:
# 45 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	setflag FLAG_EVO_ITEM_LADY_FIRST_ENCOUNTER
# 46 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	msgbox FallarborTown_MoveRelearnersHouse_Text_EvoItemLadyFirstEncounter
	goto FallarborTown_MoveRelearnersHouse_EvoItemLady_1

FallarborTown_MoveRelearnersHouse_EvoItemLady_6:
# 54 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	msgbox EvoItem_Lady_Text_ImSorryNoStock
# 55 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	release
	end

FallarborTown_MoveRelearnersHouse_EvoItemLady_9:
# 59 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	pokemart EvoItem_Lady_Expanded
	goto FallarborTown_MoveRelearnersHouse_EvoItemLady_8


	.align 2
# 70 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
EvoStone_Man:
# 71 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_FIRE_STONE
# 72 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_WATER_STONE
# 73 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_LEAF_STONE
# 74 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_THUNDER_STONE
# 75 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_MOON_STONE
# 76 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_SUN_STONE
	.2byte ITEM_NONE

	.align 2
# 79 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
EvoStone_Man_Expanded:
# 80 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_FIRE_STONE
# 81 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_WATER_STONE
# 82 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_LEAF_STONE
# 83 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_THUNDER_STONE
# 84 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_MOON_STONE
# 85 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_SUN_STONE
# 86 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_SHINY_STONE
# 87 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_DUSK_STONE
# 88 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_DAWN_STONE
# 89 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_ICE_STONE
	.2byte ITEM_NONE

	.align 2
# 92 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
EvoItem_Lady:
# 93 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_LINKING_CORD
# 94 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_DEEP_SEA_SCALE
# 95 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_DEEP_SEA_TOOTH
# 96 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_UPGRADE
# 97 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_KINGS_ROCK
# 98 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_OVAL_STONE
# 99 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_SACHET
# 100 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_WHIPPED_DREAM
# 101 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_GALARICA_CUFF
# 102 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_GALARICA_WREATH
	.2byte ITEM_NONE

	.align 2
# 105 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
EvoItem_Lady_Expanded:
# 106 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_LINKING_CORD
# 107 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_DEEP_SEA_SCALE
# 108 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_DEEP_SEA_TOOTH
# 109 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_DRAGON_SCALE
# 110 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_UPGRADE
# 111 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_DUBIOUS_DISC
# 112 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_KINGS_ROCK
# 113 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_ELECTIRIZER
# 114 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_MAGMARIZER
# 115 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_METAL_COAT
# 116 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_OVAL_STONE
# 117 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_PRISM_SCALE
# 118 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_PROTECTOR
# 119 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_RAZOR_CLAW
# 120 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_RAZOR_FANG
# 121 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_REAPER_CLOTH
# 122 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_SACHET
# 123 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_WHIPPED_DREAM
# 124 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_GALARICA_CUFF
# 125 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_GALARICA_WREATH
# 126 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_BLACK_AUGURITE
# 127 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_AUSPICIOUS_ARMOR
# 128 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_MALICIOUS_ARMOR
# 129 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_METAL_ALLOY
# 130 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.2byte ITEM_PEAT_BLOCK
	.2byte ITEM_NONE

FallarborTown_MoveRelearnersHouse_EvoStoneMan_Text_0:
# 17 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.string "Take care out there, Trainer.\p"
	.string "And remember - the right stone can\n"
	.string "bring out a Pokémon's true nature!$"

FallarborTown_MoveRelearnersHouse_EvoStoneMan_Text_1:
# 23 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.string "Ah, back again, are you?\p"
	.string "You've got a good eye for fine stones.\p"
	.string "My stock's a bit different every now\n"
	.string "and then - depends on what I find out\l"
	.string "there in the wild.\p"
	.string "Want to take a look?$"

FallarborTown_MoveRelearnersHouse_EvoItemLady_Text_0:
# 49 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.string "Welcome back!\p"
	.string "Looking for something to help your\n"
	.string "Pokémon reach their next stage?\p"
	.string "Take a look and see what catches your\n"
	.string "eye.$"

FallarborTown_EvoStoneMan_Text_FirstEncounter::
# 133 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.string "Hello there, young traveler!\p"
	.string "They call me the Evo-Stone Man! For\n"
	.string "years, I've studied the mysterious\l"
	.string "power hidden inside these beautiful\l"
	.string "stones.\p"
	.string "Each one holds the key to a Pokémon's\n"
	.string "evolution - nature's own little miracle!\p"
	.string "My collection changes from time to time\n"
	.string "as I find new stones on my journeys\p"
	.string "Care to take a look? You might find just\n"
	.string "the stone your partner's been waiting\l"
	.string "for!$"

FallarborTown_MoveRelearnersHouse_Text_EvoItemLadyFirstEncounter::
# 143 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.string "Hey Trainer!\p"
	.string "You've got the look of a Trainer who\n"
	.string "cares deeply for their Pokémon\p"
	.string "I deal in special Evolution Items - rare\n"
	.string "trinkets and held objects that help\l"
	.string "Pokémon evolve in unique ways\p"
	.string "They're not easy to come by, but I do my\n"
	.string "best to keep my shelves stocked.\p"
	.string "Every now and then, I manage to find\n"
	.string "new ones, so be sure to check back once\l"
	.string "in a while!\p"
	.string "Care to browse my collection?$"

EvoItem_Lady_Text_ImSorryNoStock::
# 154 "data/maps/FallarborTown_MoveRelearnersHouse/scripts.pory"
	.string "Oh, dear… I'm terribly sorry!\p"
	.string "It seems my entire stock has sold out.\p"
	.string "I've placed an order for a fresh batch\n"
	.string "of Evolution Items, but the delivery\l"
	.string "hasn't arrived yet\p"
	.string "The supplier always takes their sweet\n"
	.string "time…\p"
	.string "Do come back a bit later, alright?\p"
	.string "I promise I'll have something special\n"
	.string "waiting for you next time!$"
