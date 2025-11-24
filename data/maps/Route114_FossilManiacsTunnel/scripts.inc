# 1 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_MapScripts::
# 2 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsTunnel_OnTransition
# 3 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, Route114_FossilManiacsTunnel_OnLoad
# 4 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.byte 0
# 5 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"

# 6 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_OnTransition:
# 7 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	call_if_set FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac
# 8 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	end
# 9 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"

# 10 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac::
# 11 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	setobjectxyperm LOCALID_FOSSIL_MANIAC, 6, 5
# 12 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	setobjectmovementtype LOCALID_FOSSIL_MANIAC, MOVEMENT_TYPE_FACE_DOWN
# 13 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	return
# 14 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"

# 15 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_OnLoad:
# 16 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	call_if_unset FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass
# 17 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	end
# 18 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"

# 19 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass::
# 20 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	setmetatile 6, 1, METATILE_Fallarbor_RedRockWall, TRUE
# 21 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	setmetatile 6, 2, METATILE_Fallarbor_RedRockWall, TRUE
# 22 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	return
# 23 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"

# 24 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_EventScript_ManiacMentionCaveIn::
# 25 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	lockall
# 26 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	applymovement LOCALID_FOSSIL_MANIAC, Common_Movement_WalkInPlaceFasterUp
# 27 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
# 28 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	waitmovement 0
# 29 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_Text_NotSafeThatWay, MSGBOX_DEFAULT
# 30 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	setvar VAR_FOSSIL_MANIAC_STATE, 2
# 31 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	releaseall
# 32 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	end
# 33 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"

# 34 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_EventScript_FossilManiac::
# 35 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	lock
# 36 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	faceplayer
# 37 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	goto_if_set FLAG_RECEIVED_REVIVED_FOSSIL_MON, Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil
# 38 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	checkitem ITEM_ROOT_FOSSIL
# 39 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
# 40 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	checkitem ITEM_CLAW_FOSSIL
# 41 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
# 42 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_Text_LookInDesertForFossils, MSGBOX_DEFAULT
# 43 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	release
# 44 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	end
# 45 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"

# 46 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil::
# 47 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils, MSGBOX_DEFAULT
# 48 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	release
# 49 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	end
# 50 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"

# 51 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil::
# 52 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_Text_FossilsAreWonderful, MSGBOX_DEFAULT
# 53 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	release
# 54 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	end
# 55 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"

# 56 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_Text_LookInDesertForFossils:
# 57 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "I'm the FOSSIL MANIAC…\n"
# 58 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "I'm a nice guy who loves FOSSILS…\p"
# 59 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "Do you want a FOSSIL?\p"
# 60 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "But the FOSSILS around these parts all\n"
# 61 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "belong to me… None for you…\p"
# 62 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "If you can't bear to go without\n"
# 63 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "a FOSSIL, look in a desert where there\l"
# 64 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "are boulders and sand that may hide\l"
# 65 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "FOSSILS…$"
# 66 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"

# 67 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils:
# 68 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "You found a FOSSIL, didn't you?\n"
# 69 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "That's so nice… It's so dreamy…\p"
# 70 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "What are you going to do with that\n"
# 71 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "FOSSIL?\p"
# 72 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "From what I've heard, DEVON is doing\n"
# 73 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "research on reviving POKéMON from\l"
# 74 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "FOSSILS…\p"
# 75 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "I love my FOSSILS, so I would never\n"
# 76 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "do anything like that…$"
# 77 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"

# 78 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_Text_FossilsAreWonderful:
# 79 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "FOSSILS are so… Wonderful…\n"
# 80 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "It's so dreamy…$"
# 81 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"

# 82 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
Route114_FossilManiacsTunnel_Text_NotSafeThatWay:
# 83 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "Oh…\n"
# 84 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "It's not safe that way…\p"
# 85 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "I was digging away, you see…\n"
# 86 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "When the whole wall collapsed…\p"
# 87 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "I think there's a giant cavern\n"
# 88 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "underneath now…\p"
# 89 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "But I've left it alone because I don't\n"
# 90 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "think there are any FOSSILS there…$"

Route114_FossilManiacsTunnel_UncleDigger::
# 97 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	lock
# 98 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	faceplayer
# 100 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	goto_if_unset FLAG_ROUTE114_UNCLE_DIGGER_FIRST_ENCOUNTER, Route114_FossilManiacsTunnel_UncleDigger_2
Route114_FossilManiacsTunnel_UncleDigger_1:
# 108 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	goto_if_set FLAG_ROUTE114_UNCLE_DIGGER_BAGISFULL, Route114_FossilManiacsTunnel_UncleDigger_5
# 129 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	showmoneybox 0, 0
# 130 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	compare VAR_TEMP_0, 0
	goto_if_eq Route114_FossilManiacsTunnel_UncleDigger_8
# 133 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	compare VAR_TEMP_0, 1
	goto_if_eq Route114_FossilManiacsTunnel_UncleDigger_9
Route114_FossilManiacsTunnel_UncleDigger_7:
# 136 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	call Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo
	return

Route114_FossilManiacsTunnel_UncleDigger_2:
# 101 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	setflag FLAG_ROUTE114_UNCLE_DIGGER_FIRST_ENCOUNTER
# 102 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_Text_FirstEncounter
# 103 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	showmoneybox 0, 0
# 104 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_Text_0, MSGBOX_YESNO
# 105 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	call Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo
	goto Route114_FossilManiacsTunnel_UncleDigger_1

Route114_FossilManiacsTunnel_UncleDigger_5:
# 109 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	bufferitemname STR_VAR_1, VAR_UNCLE_DIG_ITEM
# 110 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	checkitemspace VAR_UNCLE_DIG_ITEM, 1
# 111 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route114_FossilManiacsTunnel_UncleDigger_13
# 116 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_Text_2
# 121 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	giveitem VAR_UNCLE_DIG_ITEM
# 122 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	closemessage
# 123 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	setvar VAR_TEMP_0, 1
# 124 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	clearflag FLAG_ROUTE114_UNCLE_DIGGER_BAGISFULL
# 125 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	release
	end

Route114_FossilManiacsTunnel_UncleDigger_8:
# 131 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_Text_3, MSGBOX_YESNO
	goto Route114_FossilManiacsTunnel_UncleDigger_7

Route114_FossilManiacsTunnel_UncleDigger_9:
# 134 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_Text_4, MSGBOX_YESNO
	goto Route114_FossilManiacsTunnel_UncleDigger_7

Route114_FossilManiacsTunnel_UncleDigger_13:
# 112 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_Text_1
# 113 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	release
	end


Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo::
# 141 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	compare VAR_RESULT, NO
	goto_if_eq Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo_2
Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo_1:
# 144 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	checkmoney 300
# 145 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo_5
Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo_4:
# 148 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	setvar VAR_TEMP_0, 1
# 149 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	removemoney 300
# 150 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	updatemoneybox
# 151 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	playse SE_SHOP
# 152 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	delay 60
# 153 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo_Text_0
# 154 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	hidemoneybox
# 155 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	closemessage
# 156 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	call Route114_FossilManiacsTunnel_UncleDigger_RNG
	return

Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo_2:
# 142 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	call Route114_FossilManiacsTunnel_UncleDigger_ComeBackAgain
	goto Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo_1

Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo_5:
# 146 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	call Route114_FossilManiacsTunnel_UncleDigger_NotEnoughMoney
	goto Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo_4


Route114_FossilManiacsTunnel_UncleDigger_RNG::
# 161 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	fadescreen FADE_TO_BLACK
# 162 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	delay 60
# 163 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	playse SE_M_DIG
# 164 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	delay 60
# 165 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	playse SE_M_DIG
# 166 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	delay 60
# 167 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	playse SE_M_DIG
# 168 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_RNG_Text_0
# 169 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	closemessage
# 170 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	delay 30
# 171 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 172 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	randompercentage 20
# 173 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route114_FossilManiacsTunnel_UncleDigger_RNG_2
# 181 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	randompercentage 15
# 182 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route114_FossilManiacsTunnel_UncleDigger_RNG_5
# 200 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	call Route114_FossilManiacsTunnel_UncleDigger_FossilListedScript
# 201 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	copyvar VAR_UNCLE_DIG_ITEM, VAR_RESULT
# 202 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	bufferitemname STR_VAR_1, VAR_UNCLE_DIG_ITEM
# 203 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_YouGotAFossil
# 204 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	giveitem VAR_UNCLE_DIG_ITEM
# 205 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route114_FossilManiacsTunnel_UncleDigger_RNG_8
Route114_FossilManiacsTunnel_UncleDigger_RNG_7:
# 209 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	closemessage
# 210 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	release
	end

Route114_FossilManiacsTunnel_UncleDigger_RNG_2:
# 174 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_RNG_Text_1
# 178 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	release
	end

Route114_FossilManiacsTunnel_UncleDigger_RNG_5:
# 183 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	call Route114_FossilManiacsTunnel_UncleDigger_ItemListedScript
# 184 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	copyvar VAR_UNCLE_DIG_ITEM, VAR_RESULT
# 185 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	bufferitemname STR_VAR_1, VAR_UNCLE_DIG_ITEM
# 186 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_RNG_Text_2
# 191 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	giveitem VAR_UNCLE_DIG_ITEM
# 192 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route114_FossilManiacsTunnel_UncleDigger_RNG_11
Route114_FossilManiacsTunnel_UncleDigger_RNG_10:
# 196 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	closemessage
# 197 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	release
	end

Route114_FossilManiacsTunnel_UncleDigger_RNG_8:
# 206 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_RNG_Text_3
# 207 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	setflag FLAG_ROUTE114_UNCLE_DIGGER_BAGISFULL
	goto Route114_FossilManiacsTunnel_UncleDigger_RNG_7

Route114_FossilManiacsTunnel_UncleDigger_RNG_11:
# 193 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_RNG_Text_3
# 194 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	setflag FLAG_ROUTE114_UNCLE_DIGGER_BAGISFULL
	goto Route114_FossilManiacsTunnel_UncleDigger_RNG_10


Route114_FossilManiacsTunnel_UncleDigger_ItemListedScript::
# 216 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	randomelement ITEM_NUGGET ITEM_BIG_NUGGET ITEM_STARDUST ITEM_STAR_PIECE ITEM_COMET_SHARD ITEM_RARE_BONE ITEM_POKE_BALL ITEM_GREAT_BALL ITEM_ULTRA_BALL ITEM_POTION ITEM_SUPER_POTION ITEM_HYPER_POTION ITEM_MAX_POTION ITEM_FULL_RESTORE ITEM_REVIVE ITEM_MAX_REVIVE ITEM_ENERGY_ROOT ITEM_ANTIDOTE ITEM_PARALYZE_HEAL ITEM_PARALYZE_HEAL ITEM_BURN_HEAL ITEM_ICE_HEAL ITEM_AWAKENING ITEM_FULL_HEAL ITEM_ETHER ITEM_ELIXIR ITEM_FIRE_STONE ITEM_WATER_STONE ITEM_THUNDER_STONE ITEM_LEAF_STONE ITEM_ICE_STONE ITEM_SUN_STONE ITEM_MOON_STONE ITEM_SHINY_STONE ITEM_DUSK_STONE ITEM_DAWN_STONE
	return


Route114_FossilManiacsTunnel_UncleDigger_FossilListedScript::
# 257 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	randomelement ITEM_DOME_FOSSIL ITEM_OLD_AMBER ITEM_HELIX_FOSSIL ITEM_ROOT_FOSSIL ITEM_CLAW_FOSSIL ITEM_ARMOR_FOSSIL ITEM_SKULL_FOSSIL ITEM_COVER_FOSSIL ITEM_PLUME_FOSSIL ITEM_JAW_FOSSIL ITEM_SAIL_FOSSIL ITEM_FOSSILIZED_BIRD ITEM_FOSSILIZED_FISH ITEM_FOSSILIZED_DRAKE ITEM_FOSSILIZED_DINO
	return


Route114_FossilManiacsTunnel_UncleDigger_NotEnoughMoney::
# 278 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	hidemoneybox
# 279 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_NotEnoughMoney_Text_0
# 280 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	release
	end


Route114_FossilManiacsTunnel_UncleDigger_ComeBackAgain::
# 285 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	hidemoneybox
# 286 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	msgbox Route114_FossilManiacsTunnel_UncleDigger_ComeBackAgain_Text_0
# 287 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	release
	end


Route114_FossilManiacsTunnel_UncleDigger_Text_0:
# 104 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "So, what do you say?\p"
	.string "Ready for some digging?$"

Route114_FossilManiacsTunnel_UncleDigger_Text_1:
# 112 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "You still have a full bag.\p"
	.string "Make some space so I can hand over\n"
	.string "your {STR_VAR_1}.$"

Route114_FossilManiacsTunnel_UncleDigger_Text_2:
# 117 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "Room in your bag now, huh?\p"
	.string "Great! Here's your {STR_VAR_1}.\p"
	.string "Don't lose it - I dug that up with my own\n"
	.string "two hands!$"

Route114_FossilManiacsTunnel_UncleDigger_Text_3:
# 131 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "Back again? Are you ready for some\n"
	.string "digging?\p"
	.string "For ¥300 we can start right now.$"

Route114_FossilManiacsTunnel_UncleDigger_Text_4:
# 134 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "Want me to dig again?\n"
	.string "It'll cost ¥300.$"

Route114_FossilManiacsTunnel_UncleDigger_DigYesOrNo_Text_0:
# 153 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "Alright! Let's get going!$"

Route114_FossilManiacsTunnel_UncleDigger_RNG_Text_0:
# 168 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "... .... ....?$"

Route114_FossilManiacsTunnel_UncleDigger_RNG_Text_1:
# 175 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "Tsk… nothing this time.\p"
	.string "The ground here loves to hide things.$"

Route114_FossilManiacsTunnel_UncleDigger_RNG_Text_2:
# 187 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "Well… no fossil this time, but at least\n"
	.string "something.\p"
	.string "A {STR_VAR_1}! Not what we were\n"
	.string "digging for, but better than empty\l"
	.string "hands, right?$"

Route114_FossilManiacsTunnel_UncleDigger_RNG_Text_3:
# 193 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "Oh, looks like your bag is full. Come\n"
	.string "back after making some space.$"

Route114_FossilManiacsTunnel_UncleDigger_NotEnoughMoney_Text_0:
# 279 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "You need ¥300 for me to dig...$"

Route114_FossilManiacsTunnel_UncleDigger_ComeBackAgain_Text_0:
# 286 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "No digging? No worries, come back\n"
	.string "anytime.$"

Route114_FossilManiacsTunnel_UncleDigger_YouGotAFossil::
# 291 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "Oh ho! Would you look at that!\p"
	.string "A real fossil - a {STR_VAR_1}, and in\n"
	.string "remarkable condition.\p"
	.string "Here, it's yours! Who knows what might\n"
	.string "be revived from it someday!$"

Route114_FossilManiacsTunnel_UncleDigger_Text_FirstEncounter::
# 300 "data/maps/Route114_FossilManiacsTunnel/scripts.pory"
	.string "Hey there, traveler!\p"
	.string "My nephew is absolutely obsessed with\n"
	.string "his fossils, and he claims everything he\l"
	.string "finds here for himself.\p"
	.string "But for ¥300, I can do some digging for\n"
	.string "you.\p"
	.string "Who knows what you might uncover here\n"
	.string "in this tunnel.$"
