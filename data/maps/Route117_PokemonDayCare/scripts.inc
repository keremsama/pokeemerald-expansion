# 1 "data/maps/Route117_PokemonDayCare/scripts.pory"

# 2 "data/maps/Route117_PokemonDayCare/scripts.pory"
Route117_PokemonDayCare_MapScripts::
# 3 "data/maps/Route117_PokemonDayCare/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route117_PokemonDayCare_OnTransition
# 4 "data/maps/Route117_PokemonDayCare/scripts.pory"
	.byte 0
# 5 "data/maps/Route117_PokemonDayCare/scripts.pory"

# 6 "data/maps/Route117_PokemonDayCare/scripts.pory"
Route117_PokemonDayCare_OnTransition:
# 7 "data/maps/Route117_PokemonDayCare/scripts.pory"
	setflag FLAG_LANDMARK_POKEMON_DAYCARE
# 8 "data/maps/Route117_PokemonDayCare/scripts.pory"
	end

Route117_PokemonDayCare_Trader::
# 14 "data/maps/Route117_PokemonDayCare/scripts.pory"
	lock
# 15 "data/maps/Route117_PokemonDayCare/scripts.pory"
	faceplayer
# 16 "data/maps/Route117_PokemonDayCare/scripts.pory"
	goto_if_set FLAG_ROUTE117_NPC_TRADE_COMPLETED, Route117_PokemonDayCare_Trader_2
Route117_PokemonDayCare_Trader_1:
# 19 "data/maps/Route117_PokemonDayCare/scripts.pory"
	setvar VAR_0x8008, INGAME_TRADE_HORSEA
# 20 "data/maps/Route117_PokemonDayCare/scripts.pory"
	copyvar VAR_0x8004, VAR_0x8008
# 21 "data/maps/Route117_PokemonDayCare/scripts.pory"
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
# 22 "data/maps/Route117_PokemonDayCare/scripts.pory"
	copyvar VAR_0x8009, VAR_RESULT
# 23 "data/maps/Route117_PokemonDayCare/scripts.pory"
	msgbox Route117_Trader_WillingToTrade, MSGBOX_YESNO
# 24 "data/maps/Route117_PokemonDayCare/scripts.pory"
	compare VAR_RESULT, NO
	goto_if_eq Route117_PokemonDayCare_Trader_5
Route117_PokemonDayCare_Trader_4:
# 27 "data/maps/Route117_PokemonDayCare/scripts.pory"
	special ChoosePartyMon
# 28 "data/maps/Route117_PokemonDayCare/scripts.pory"
	waitstate
# 29 "data/maps/Route117_PokemonDayCare/scripts.pory"
	copyvar VAR_0x800A, VAR_0x8004
# 30 "data/maps/Route117_PokemonDayCare/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_0x8009
# 31 "data/maps/Route117_PokemonDayCare/scripts.pory"
	bufferspeciesname STR_VAR_2, VAR_0x8008
# 32 "data/maps/Route117_PokemonDayCare/scripts.pory"
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_eq Route117_PokemonDayCare_Trader_8
Route117_PokemonDayCare_Trader_7:
# 35 "data/maps/Route117_PokemonDayCare/scripts.pory"
	copyvar VAR_0x8005, VAR_0x800A
# 36 "data/maps/Route117_PokemonDayCare/scripts.pory"
	specialvar VAR_RESULT, GetTradeSpecies
# 37 "data/maps/Route117_PokemonDayCare/scripts.pory"
	copyvar VAR_0x800B, VAR_RESULT
# 38 "data/maps/Route117_PokemonDayCare/scripts.pory"
	compare VAR_RESULT, VAR_0x8009
	goto_if_ne Route117_PokemonDayCare_Trader_11
Route117_PokemonDayCare_Trader_10:
# 41 "data/maps/Route117_PokemonDayCare/scripts.pory"
	copyvar VAR_0x8004, VAR_0x8008
# 42 "data/maps/Route117_PokemonDayCare/scripts.pory"
	copyvar VAR_0x8005, VAR_0x800A
# 43 "data/maps/Route117_PokemonDayCare/scripts.pory"
	special CreateInGameTradePokemon
# 44 "data/maps/Route117_PokemonDayCare/scripts.pory"
	special DoInGameTradeScene
# 45 "data/maps/Route117_PokemonDayCare/scripts.pory"
	waitstate
# 46 "data/maps/Route117_PokemonDayCare/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_0x8009
# 47 "data/maps/Route117_PokemonDayCare/scripts.pory"
	msgbox Route117_Trader_ThankYouForTrade
# 48 "data/maps/Route117_PokemonDayCare/scripts.pory"
	setflag FLAG_ROUTE117_NPC_TRADE_COMPLETED
# 49 "data/maps/Route117_PokemonDayCare/scripts.pory"
	release
	end

Route117_PokemonDayCare_Trader_2:
# 17 "data/maps/Route117_PokemonDayCare/scripts.pory"
	call Route117_PokemonDayCare_TadeCompleted
	goto Route117_PokemonDayCare_Trader_1

Route117_PokemonDayCare_Trader_5:
# 25 "data/maps/Route117_PokemonDayCare/scripts.pory"
	call Route117_PokemonDayCare_ComeBackIfYouWant
	goto Route117_PokemonDayCare_Trader_4

Route117_PokemonDayCare_Trader_8:
# 33 "data/maps/Route117_PokemonDayCare/scripts.pory"
	call Route117_PokemonDayCare_ComeBackIfYouWant
	goto Route117_PokemonDayCare_Trader_7

Route117_PokemonDayCare_Trader_11:
# 39 "data/maps/Route117_PokemonDayCare/scripts.pory"
	call Route117_PokemonDayCare_ThatsNotTheMonIWant
	goto Route117_PokemonDayCare_Trader_10


Route117_PokemonDayCare_TadeCompleted::
# 55 "data/maps/Route117_PokemonDayCare/scripts.pory"
	msgbox Route117_PokemonDayCare_TadeCompleted_Text_0
# 61 "data/maps/Route117_PokemonDayCare/scripts.pory"
	release
	end


Route117_PokemonDayCare_ComeBackIfYouWant::
# 66 "data/maps/Route117_PokemonDayCare/scripts.pory"
	msgbox Route117_PokemonDayCare_ComeBackIfYouWant_Text_0
# 71 "data/maps/Route117_PokemonDayCare/scripts.pory"
	release
	end


Route117_PokemonDayCare_ThatsNotTheMonIWant::
# 76 "data/maps/Route117_PokemonDayCare/scripts.pory"
	msgbox Route117_PokemonDayCare_ThatsNotTheMonIWant_Text_0
# 81 "data/maps/Route117_PokemonDayCare/scripts.pory"
	release
	end


Route117_PokemonDayCare_TadeCompleted_Text_0:
# 56 "data/maps/Route117_PokemonDayCare/scripts.pory"
	.string "Thanks again for the Munchlax!\p"
	.string "It's been great at keeping my snack\n"
	.string "habit in check.\p"
	.string "Whenever I try grabbing a snack, it\n"
	.string "snatches it right out of my hands!\p"
	.string "Hope you and my Horsea are getting\n"
	.string "along well!$"

Route117_PokemonDayCare_ComeBackIfYouWant_Text_0:
# 67 "data/maps/Route117_PokemonDayCare/scripts.pory"
	.string "No worries, no worries!\p"
	.string "I'll be right here… snacking…\p"
	.string "and hoping someone brings me a\n"
	.string "{STR_VAR_1} someday.$"

Route117_PokemonDayCare_ThatsNotTheMonIWant_Text_0:
# 77 "data/maps/Route117_PokemonDayCare/scripts.pory"
	.string "Hmm… That's a fine Pokémon you've got\n"
	.string "there, but it's not a {STR_VAR_1}.\p"
	.string "I really need a {STR_VAR_1} to help\n"
	.string "me keep my snack habit under control!\p"
	.string "Come back if you find one, alright?$"

Route117_Trader_WillingToTrade::
# 85 "data/maps/Route117_PokemonDayCare/scripts.pory"
	.string "I've been fishing for years, y'know…\p"
	.string "But lately I've had a little problem.\p"
	.string "You see, I snack way too much while\n"
	.string "waiting for a bite…\p"
	.string "My buddies keep teasing me about it!\p"
	.string "So I thought - maybe if I had a\n"
	.string "{STR_VAR_1} with me, it would eat all\l"
	.string "the snacks before I do!\p"
	.string "If you've got a {STR_VAR_1} to\n"
	.string "spare, would you trade it for\l"
	.string "my loyal {STR_VAR_2}?$"

Route117_Trader_ThankYouForTrade::
# 97 "data/maps/Route117_PokemonDayCare/scripts.pory"
	.string "Look at that little guy! Perfect!\p"
	.string "No more snack piles while waiting for a\n"
	.string "bite!\p"
	.string "Take good care of {STR_VAR_2},\n"
	.string "okay?$"
