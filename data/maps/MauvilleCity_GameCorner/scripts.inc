.set LOCALID_BOUNCER, 24

MauvilleCity_GameCorner_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerId_Onframe
	.byte 0

    @ Game Corner prices
	.set TM_DOUBLE_TEAM_COINS, 1500
	.set TM_PSYCHIC_COINS, 3500
	.set TM_FIREPUNCH_COINS, 3000
	.set TM_THUNDERPUNCH_COINS, 3000
	.set TM_ICEPUNCH_COINS, 3000
	.set TM_FLASH_CANNON_COINS, 3700
	.set TM_DAZZLING_GLEAM_COINS, 3700
	.set TM_WILL_O_WISP_COINS, 3800
	.set TM_THUNDER_WAVE_COINS, 3800
	.set TM_FLAMETHROWER_COINS, 4000
	.set TM_THUNDERBOLT_COINS, 4000
	.set TM_ICE_BEAM_COINS, 4000
	.set TM_EARTH_POWER_COINS, 4000
	.set DOLL_COINS, 1000
	.set SOOTHEBELL_COINS, 1200
	.set EXPERTBELT_COINS, 1600
	.set PUNCHINGGLOVE_COINS, 1700
	.set WIDELENS_COINS, 1700
	.set THICKCLUB_COINS, 1800
	.set MUSCLEBAND_COINS, 1800
	.set WISEGLASSES_COINS, 1800
	.set FOCUSSASH_COINS, 2400
	.set ASSAULTVEST_COINS, 2800
	.set LIFEORB_COINS, 3800
	.set ROCKYHELMET_COINS, 3000
	.set LOADEDDICE_COINS, 3600
	.set FIRESTONE_COINS, 1400
	.set THUNDERSTONE_COINS, 1400
	.set WATERSTONE_COINS, 1400
	.set LEAFSTONE_COINS, 1400
	.set ICESTONE_COINS, 1400
	.set SUNSTONE_COINS, 1400
	.set MOONSTONE_COINS, 1400
	.set SHINYSTONE_COINS, 1400
	.set DUSKSTONE_COINS, 1400
	.set DAWNSTONE_COINS, 1400
	.set LINKINGCORD_COINS, 1500
	.set EVIOLITE_COINS, 2700
	.set LEFTOVERS_COINS, 3500
	.set BOTTLECAP_COINS, 2300
	.set GOLDBOTTLECAP_COINS, 7000

	.set ABRA_COINS, 1500
	.set CUBONE_COINS, 1800
	.set RALTS_COINS, 3200
	.set DRATINI_COINS, 5500
	.set BAGON_COINS, 5500
	.set LARVESTA_COINS, 5200
	.set LARVITAR_COINS, 5000
	.set DREEPY_COINS, 6000
	.set SCYTHER_COINS, 4800
	.set FRIGIBAX_COINS, 6300
	.set BELDUM_COINS, 8000
	.set PORYGON_COINS, 9999

	.set COINS_PRICE_50,  1000
	.set COINS_PRICE_500, 10000

TrainerId_Onframe:
.if GAME_CORNER_VAR_ID_CHECK != 0
	map_script_2 GAME_CORNER_VAR_ID_CHECK, 0, BouncerCheck
.endif
	.2byte 0
	
BouncerCheck::
	lockall
	applymovement LOCALID_BOUNCER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_BOUNCER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_BOUNCER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_BOUNCER, Movement_Bouncer_Approach
	waitmovement 0
	msgbox MauvilleCity_GameCorner_Text_Bouncer1, MSGBOX_DEFAULT
	closemessage
	setvar GAME_CORNER_VAR_ID_CHECK, 1
	applymovement LOCALID_BOUNCER, Movement_Bouncer_Leave
	waitmovement 0
	releaseall
	end	
	
Movement_Bouncer_Approach:
	walk_left
	walk_left
	step_end	
	
Movement_Bouncer_Leave:
	walk_right
	walk_right
	walk_in_place_faster_left
	step_end		

MauvilleCity_GameCorner_EventScript_Blackjack::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	msgbox MauvilleCity_GameCorner_Text_BlackJack, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelBJ
	nop // playbgm MUS_GAME_CORNER, FALSE
	special StartBlackJack
	waitstate
	savebgm MUS_DUMMY
	nop //fadedefaultbgm
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_Derby::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	msgbox MauvilleCity_GameCorner_Text_Derby, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelBJ
	playbgm MUS_RG_PEWTER, FALSE
	special StartDerby
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto_if_eq GAME_CORNER_VAR_WINNINGS, 0, MauvilleCity_GameCorner_NoWin
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS
	msgbox PB_YOU_WON_TEXT, MSGBOX_DEFAULT
	waitmessage
	addcoins GAME_CORNER_VAR_WINNINGS
	setvar GAME_CORNER_VAR_WINNINGS, 0
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	closemessage
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_Snake::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 25, Onix_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Snake, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
	removecoins 25
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_NONE, FALSE
	special StartSnake
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto_if_eq GAME_CORNER_VAR_WINNINGS, 0, MauvilleCity_GameCorner_NoWin
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS
	msgbox PB_YOU_WON_TEXT, MSGBOX_DEFAULT
	waitmessage
	addcoins GAME_CORNER_VAR_WINNINGS
	setvar GAME_CORNER_VAR_WINNINGS, 0
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	closemessage
	releaseall
	end	
	
MauvilleCity_GameCorner_EventScript_FlappyBird::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 25, Butterfree_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Bird, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
	removecoins 25
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_NONE, FALSE
	special StartFlappyBird
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto_if_eq GAME_CORNER_VAR_WINNINGS, 0, MauvilleCity_GameCorner_NoWin
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS
	msgbox PB_YOU_WON_TEXT, MSGBOX_DEFAULT
	waitmessage
	addcoins GAME_CORNER_VAR_WINNINGS
	setvar GAME_CORNER_VAR_WINNINGS, 0
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	closemessage
	releaseall
	end		
	
MauvilleCity_GameCorner_EventScript_BlockStacker::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 25, BlockStacker_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_BS, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF	
	removecoins 25
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_CASINO_PLUS_1, FALSE
	special StartBlockStacker
    waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto_if_eq GAME_CORNER_VAR_WINNINGS, 0, MauvilleCity_GameCorner_NoWin
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS
	msgbox PB_YOU_WON_TEXT, MSGBOX_DEFAULT
	waitmessage
	addcoins GAME_CORNER_VAR_WINNINGS
	setvar GAME_CORNER_VAR_WINNINGS, 0
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	closemessage
	releaseall
	end

BlockStacker_Not_Enough::
	msgbox BS_Not_Enough, MSGBOX_DEFAULT
	releaseall
	end	
	
Pinball_Not_Enough::
	msgbox PB_Not_Enough, MSGBOX_DEFAULT
	releaseall
	end	
	
Onix_Not_Enough::
	msgbox Snake_Not_Enough, MSGBOX_DEFAULT
	releaseall
	end		
	
Juice_Not_Enough::
	msgbox Bjuice_Not_Enough, MSGBOX_DEFAULT
	releaseall
	end			
	
Butterfree_Not_Enough::
	msgbox Bird_Not_Enough, MSGBOX_DEFAULT
	releaseall
	end			
	
VF_Not_Enough::
	msgbox Flip_Not_Enough, MSGBOX_DEFAULT
	releaseall
	end		
	
MauvilleCity_GameCorner_EventScript_Pachinko::	
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	msgbox MauvilleCity_GameCorner_Text_Pachinko, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF	
	playbgm MUS_RG_ROUTE1, FALSE
	callnative PlayPachinko
    waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_PinballMeowth::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 25, Pinball_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Pinball_Meowth, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF	
	removecoins 25
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_RG_POKE_CENTER, FALSE
	callnative PlayMeowthPinballGame
    waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto_if_eq GAME_CORNER_VAR_WINNINGS, 0, MauvilleCity_GameCorner_NoWin
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS
	msgbox PB_YOU_WON_TEXT, MSGBOX_DEFAULT
	waitmessage
	addcoins GAME_CORNER_VAR_WINNINGS
	setvar GAME_CORNER_VAR_WINNINGS, 0
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	closemessage
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_PinballDiglett::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 50, Pinball_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Pinball_Diglett, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF	
	removecoins 50
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_RG_POKE_JUMP, FALSE
	callnative PlayDiglettPinballGame
    waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto_if_eq GAME_CORNER_VAR_WINNINGS, 0, MauvilleCity_GameCorner_NoWin
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS
	msgbox PB_YOU_WON_TEXT, MSGBOX_DEFAULT
	waitmessage
	addcoins GAME_CORNER_VAR_WINNINGS
	setvar GAME_CORNER_VAR_WINNINGS, 0
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	closemessage
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_PinballSeel::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 25, Pinball_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Pinball_Seel, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF	
	removecoins 25
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_RG_SS_ANNE, FALSE
	callnative PlaySeelPinballGame
    waitstate 
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto_if_eq GAME_CORNER_VAR_WINNINGS, 0, MauvilleCity_GameCorner_NoWin
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS
	msgbox PB_YOU_WON_TEXT, MSGBOX_DEFAULT
	waitmessage
	addcoins GAME_CORNER_VAR_WINNINGS
	setvar GAME_CORNER_VAR_WINNINGS, 0
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	closemessage
	releaseall
	end	
	
MauvilleCity_GameCorner_EventScript_PinballGengar::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 100, Pinball_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Pinball_Gengar, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF	
	removecoins 100
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_RG_POKE_TOWER, FALSE
	callnative PlayGengarPinballGame
    waitstate
	savebgm MUS_DUMMY
	goto_if_eq GAME_CORNER_VAR_WINNINGS, 0, MauvilleCity_GameCorner_NoWin
	fadedefaultbgm
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS
	msgbox PB_YOU_WON_TEXT, MSGBOX_DEFAULT
	waitmessage
	addcoins GAME_CORNER_VAR_WINNINGS
	setvar GAME_CORNER_VAR_WINNINGS, 0
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	closemessage
	releaseall
	end	
	
MauvilleCity_GameCorner_EventScript_VoltorbFlip::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 50, VF_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_VF, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
	removecoins 50
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_RG_OAK, FALSE
	setvar GAME_CORNER_VAR_WINNINGS, 0
	special Special_ViewVoltorbFlip
	waitstate
	goto_if_eq VAR_RESULT, 0, VF_Come_Again
	goto_if_eq VAR_RESULT, 1, VF_Go_On
	releaseall
	end
	
VF_Come_Again::
	savebgm MUS_DUMMY
	fadedefaultbgm
	msgbox VF_Come_Again_Text, MSGBOX_DEFAULT
	setvar GAME_CORNER_VAR_WINNINGS, 0
	releaseall
	end
	
VF_Go_On::
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS	
	msgbox MauvilleCity_GameCorner_Text_VF_Keep_Going, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, VF_Cash_Out
	goto VF_Loop
	
VF_Loop::
	hidecoinsbox 0, 5
	special Special_ViewVoltorbFlip
	waitstate
	goto_if_eq VAR_RESULT, 0, VF_Come_Again
	goto_if_eq VAR_RESULT, 1, VF_Go_On
	releaseall
	end
	
VF_Cash_Out::	
	addcoins GAME_CORNER_VAR_WINNINGS
	setvar GAME_CORNER_VAR_WINNINGS, 0
.if FLIP_VAR_LEVEL != 0
	setvar FLIP_VAR_LEVEL, 0
.endif
	updatecoinsbox 1, 1
	playse SE_SHOP
	savebgm MUS_DUMMY
	fadedefaultbgm
	delay 40
	hidecoinsbox 0, 5
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_Gacha_Basic::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	playbgm MUS_RG_CINNABAR, FALSE
	special StartGacha
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end
	
	
MauvilleCity_GameCorner_EventScript_Gacha_Great::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 2
	playbgm MUS_RG_CINNABAR, FALSE
	special StartGacha
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_Gacha_Ultra::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 3
	playbgm MUS_RG_CINNABAR, FALSE
	special StartGacha
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_Gacha_Master::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 4
	playbgm MUS_RG_CINNABAR, FALSE
	special StartGacha
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

MauvilleCity_GameCorner_CancelBJ::
	closemessage
	releaseall
	end
	
MauvilleCity_GameCorner_NoWin::
	releaseall
	end	
	
MauvilleCity_GameCorner_CancelVF::
	hidecoinsbox 0, 5
	closemessage
	releaseall
	end

MauvilleCity_GameCorner_EventScript_CoinsClerk::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ThisIsMauvilleGameCorner, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NeedCoinCase
	message MauvilleCity_GameCorner_Text_WereYouLookingForCoins
	waitmessage
	showmoneybox 0, 0
	showcoinsbox 1, 6
	goto MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault50

MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault50::
	multichoicedefault 15, 0, MULTI_GAME_CORNER_COINS, 0, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_Buy50Coins
	case 1, MauvilleCity_GameCorner_EventScript_Buy500Coins
	goto MauvilleCity_GameCorner_EventScript_CancelBuyCoins
	end

@ Unused
MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault500::
	multichoicedefault 15, 0, MULTI_GAME_CORNER_COINS, 1, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_Buy50Coins
	case 1, MauvilleCity_GameCorner_EventScript_Buy500Coins
	goto MauvilleCity_GameCorner_EventScript_CancelBuyCoins
	end

MauvilleCity_GameCorner_EventScript_Buy50Coins::
	checkcoins VAR_TEMP_1
	goto_if_ge VAR_TEMP_1, (MAX_COINS + 1 - 50), MauvilleCity_GameCorner_EventScript_NoRoomForCoins
	checkmoney COINS_PRICE_50
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NotEnoughMoney
	addcoins 50
	removemoney COINS_PRICE_50
	updatemoneybox
	updatecoinsbox 1, 6
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox 0, 5
	release
	end

MauvilleCity_GameCorner_EventScript_Buy500Coins::
	checkcoins VAR_TEMP_1
	goto_if_ge VAR_TEMP_1, (MAX_COINS + 1 - 500), MauvilleCity_GameCorner_EventScript_NoRoomForCoins
	checkmoney COINS_PRICE_500
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NotEnoughMoney
	addcoins 500
	removemoney COINS_PRICE_500
	updatemoneybox
	updatecoinsbox 1, 6
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox 0, 5
	release
	end

MauvilleCity_GameCorner_EventScript_NeedCoinCase::
	msgbox MauvilleCity_GameCorner_Text_NeedCoinCaseForCoins, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_NotEnoughMoney::
	msgbox MauvilleCity_GameCorner_Text_DontHaveEnoughMoney, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox 0, 5
	release
	end

MauvilleCity_GameCorner_EventScript_CancelBuyCoins::
	msgbox MauvilleCity_GameCorner_Text_DontNeedCoinsThen, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox 0, 5
	release
	end

MauvilleCity_GameCorner_EventScript_NoRoomForCoins::
	msgbox MauvilleCity_GameCorner_Text_CoinCaseIsFull, MSGBOX_DEFAULT
	hidemoneybox
	hidecoinsbox 0, 5
	release
	end

MauvilleCity_GameCorner_EventScript_PrizeCornerDolls::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseDollPrizeMessage
	release
	end

MauvilleCity_GameCorner_EventScript_ChooseDollPrizeMessage::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 1, 1
	goto MauvilleCity_GameCorner_EventScript_ChooseDollPrize

MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChooseDollPrize

MauvilleCity_GameCorner_EventScript_ChooseDollPrize::
	multichoice 12, 0, MULTI_GAME_CORNER_DOLLS, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_TreeckoDoll
	case 1, MauvilleCity_GameCorner_EventScript_TorchicDoll
	case 2, MauvilleCity_GameCorner_EventScript_MudkipDoll
	case 3, MauvilleCity_GameCorner_EventScript_CancelDollSelect
	goto MauvilleCity_GameCorner_EventScript_CancelDollSelect
	end

MauvilleCity_GameCorner_EventScript_TreeckoDoll::
	setvar VAR_TEMP_1, 1
	bufferdecorationname STR_VAR_1, DECOR_TREECKO_DOLL
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize

MauvilleCity_GameCorner_EventScript_TorchicDoll::
	setvar VAR_TEMP_1, 2
	bufferdecorationname STR_VAR_1, DECOR_TORCHIC_DOLL
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize

MauvilleCity_GameCorner_EventScript_MudkipDoll::
	setvar VAR_TEMP_1, 3
	bufferdecorationname STR_VAR_1, DECOR_MUDKIP_DOLL
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize

MauvilleCity_GameCorner_EventScript_ConfirmDollPrize::
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelDollSelect
	switch VAR_TEMP_1
	case 1, MauvilleCity_GameCorner_EventScript_BuyTreeckoDoll
	case 2, MauvilleCity_GameCorner_EventScript_BuyTorchicDoll
	case 3, MauvilleCity_GameCorner_EventScript_BuyMudkipDoll
	end

MauvilleCity_GameCorner_EventScript_BuyTreeckoDoll::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, DOLL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
	bufferdecorationname STR_VAR_2, DECOR_TREECKO_DOLL
	checkdecorspace DECOR_TREECKO_DOLL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDoll
	removecoins DOLL_COINS
	adddecoration DECOR_TREECKO_DOLL
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTorchicDoll::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, DOLL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
	bufferdecorationname STR_VAR_2, DECOR_TORCHIC_DOLL
	checkdecorspace DECOR_TORCHIC_DOLL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDoll
	removecoins DOLL_COINS
	adddecoration DECOR_TORCHIC_DOLL
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_BuyMudkipDoll::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, DOLL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
	bufferdecorationname STR_VAR_2, DECOR_MUDKIP_DOLL
	checkdecorspace DECOR_MUDKIP_DOLL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDoll
	removecoins DOLL_COINS
	adddecoration DECOR_MUDKIP_DOLL
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll::
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_NoRoomForDoll::
	call Common_EventScript_NoRoomForDecor
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
	end

MauvilleCity_GameCorner_EventScript_CancelDollSelect::
	msgbox MauvilleCity_GameCorner_Text_OhIsThatSo, MSGBOX_DEFAULT
	hidecoinsbox 0, 0
	release
	end

MauvilleCity_GameCorner_EventScript_PrizeCornerTMs::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseTMPrizeMessage
	release
	end
	
MauvilleCity_GameCorner_EventScript_PrizeCornerNew::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseNewPrizeMessage
	release
	end

MauvilleCity_GameCorner_EventScript_PrizeCornerPokemon::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChoosePokemonPrizeMessage
	release
	end	
	
MauvilleCity_GameCorner_EventScript_PrizeCornerEvoItems::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseEvoItems
	release
	end		

MauvilleCity_GameCorner_EventScript_ChooseTMPrizeMessage::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 1, 1
	goto MauvilleCity_GameCorner_EventScript_ChooseTMPrize
	
MauvilleCity_GameCorner_EventScript_ChooseNewPrizeMessage::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 1, 1
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize

MauvilleCity_GameCorner_EventScript_ChoosePokemonPrizeMessage::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 1, 1
	goto MauvilleCity_GameCorner_EventScript_ChoosePokemonPrize
	
MauvilleCity_GameCorner_EventScript_ChooseEvoItems::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 1, 1
	goto MauvilleCity_GameCorner_EventScript_ChooseEvoItem		

MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChooseTMPrize
	
MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize	

MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChoosePokemonPrize
	
MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChooseEvoItem	

MauvilleCity_GameCorner_EventScript_ChooseTMPrize::
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMDoubleTeam, ITEM_TM_DOUBLE_TEAM
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMFirePunch, ITEM_TM_FIRE_PUNCH
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMThunderPunch, ITEM_TM_THUNDER_PUNCH
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMIcePunch, ITEM_TM_ICE_PUNCH
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMPsychic, ITEM_TM_PSYCHIC
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMFlashCannon, ITEM_TM_FLASH_CANNON
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMDazzlingGleam, ITEM_TM_DAZZLING_GLEAM
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMWilloWisp, ITEM_TM_WILL_O_WISP
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMThunderWave, ITEM_TM_THUNDER_WAVE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMFlamethrower, ITEM_TM_FLAMETHROWER
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMThunderbolt, ITEM_TM_THUNDERBOLT
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMIceBeam, ITEM_TM_ICE_BEAM
	dynmultipush MauvilleCity_GameCorner_Text_PrizeTMEarthPower, ITEM_TM_EARTH_POWER
	dynmultipush MauvilleCity_GameCorner_Text_PrizeExit, ITEM_NONE
	dynmultistack 12, 0, FALSE, 6, FALSE, ITEM_TM_DOUBLE_TEAM, DYN_MULTICHOICE_CB_SHOW_ITEM_LEFT
	switch VAR_RESULT
	case ITEM_TM_DOUBLE_TEAM, MauvilleCity_GameCorner_EventScript_TMDoubleTeam
	case ITEM_TM_FIRE_PUNCH, MauvilleCity_GameCorner_EventScript_TMFirePunch
	case ITEM_TM_THUNDER_PUNCH, MauvilleCity_GameCorner_EventScript_TMThunderPunch
	case ITEM_TM_ICE_PUNCH, MauvilleCity_GameCorner_EventScript_TMIcePunch
	case ITEM_TM_PSYCHIC, MauvilleCity_GameCorner_EventScript_TMPsychic
	case ITEM_TM_FLASH_CANNON, MauvilleCity_GameCorner_EventScript_TMFlashCannon
	case ITEM_TM_DAZZLING_GLEAM, MauvilleCity_GameCorner_EventScript_TMDazzlingGleam
	case ITEM_TM_WILL_O_WISP, MauvilleCity_GameCorner_EventScript_TMWilloWisp
	case ITEM_TM_THUNDER_WAVE, MauvilleCity_GameCorner_EventScript_TMThunderWave
	case ITEM_TM_FLAMETHROWER, MauvilleCity_GameCorner_EventScript_TMFlamethrower
	case ITEM_TM_THUNDERBOLT, MauvilleCity_GameCorner_EventScript_TMThunderbolt
	case ITEM_TM_ICE_BEAM, MauvilleCity_GameCorner_EventScript_TMIceBeam
	case ITEM_TM_EARTH_POWER, MauvilleCity_GameCorner_EventScript_TMEarthPower
	case ITEM_NONE, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
	end
	
MauvilleCity_GameCorner_EventScript_ChooseNewPrize::
	dynmultipush MauvilleCity_GameCorner_Text_PrizeSootheBell, ITEM_SOOTHE_BELL
	dynmultipush MauvilleCity_GameCorner_Text_PrizeExpertBelt, ITEM_EXPERT_BELT
	dynmultipush MauvilleCity_GameCorner_Text_PrizePunchingGlove, ITEM_PUNCHING_GLOVE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeWideLens, ITEM_WIDE_LENS
	dynmultipush MauvilleCity_GameCorner_Text_PrizeThickClub, ITEM_THICK_CLUB
	dynmultipush MauvilleCity_GameCorner_Text_PrizeMuscleBand, ITEM_MUSCLE_BAND
	dynmultipush MauvilleCity_GameCorner_Text_PrizeWiseGlasses, ITEM_WISE_GLASSES
	dynmultipush MauvilleCity_GameCorner_Text_PrizeFocusSash, ITEM_FOCUS_SASH
	dynmultipush MauvilleCity_GameCorner_Text_PrizeEviolite, ITEM_EVIOLITE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeAssaultVest, ITEM_ASSAULT_VEST
	dynmultipush MauvilleCity_GameCorner_Text_PrizeRockyHelmet, ITEM_ROCKY_HELMET
	dynmultipush MauvilleCity_GameCorner_Text_PrizeLeftovers, ITEM_LEFTOVERS
	dynmultipush MauvilleCity_GameCorner_Text_PrizeLoadedDice, ITEM_LOADED_DICE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeLifeOrb, ITEM_LIFE_ORB
	dynmultipush MauvilleCity_GameCorner_Text_PrizeExit, ITEM_NONE
	dynmultistack 12, 0, FALSE, 6, FALSE, ITEM_SOOTHE_BELL, DYN_MULTICHOICE_CB_SHOW_ITEM_LEFT
	switch VAR_RESULT
	case ITEM_SOOTHE_BELL, MauvilleCity_GameCorner_EventScript_SootheBell
	case ITEM_EXPERT_BELT, MauvilleCity_GameCorner_EventScript_ExpertBelt
	case ITEM_PUNCHING_GLOVE, MauvilleCity_GameCorner_EventScript_PunchingGlove
	case ITEM_WIDE_LENS, MauvilleCity_GameCorner_EventScript_WideLens
	case ITEM_THICK_CLUB, MauvilleCity_GameCorner_EventScript_ThickClub
	case ITEM_MUSCLE_BAND, MauvilleCity_GameCorner_EventScript_MuscleBand
	case ITEM_WISE_GLASSES, MauvilleCity_GameCorner_EventScript_WiseGlasses
	case ITEM_FOCUS_SASH, MauvilleCity_GameCorner_EventScript_FocusSash
	case ITEM_EVIOLITE, MauvilleCity_GameCorner_EventScript_Eviolite
	case ITEM_ASSAULT_VEST, MauvilleCity_GameCorner_EventScript_AssaultVest
	case ITEM_ROCKY_HELMET, MauvilleCity_GameCorner_EventScript_RockyHelmet
	case ITEM_LEFTOVERS, MauvilleCity_GameCorner_EventScript_Leftovers
	case ITEM_LOADED_DICE, MauvilleCity_GameCorner_EventScript_LoadedDice
	case ITEM_LIFE_ORB, MauvilleCity_GameCorner_EventScript_LifeOrb
	case ITEM_NONE, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
	end

MauvilleCity_GameCorner_EventScript_ChoosePokemonPrize::
	dynmultipush MauvilleCity_GameCorner_Text_PrizeAbra, SPECIES_ABRA
	dynmultipush MauvilleCity_GameCorner_Text_PrizeCubone, SPECIES_CUBONE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeRalts, SPECIES_RALTS
	dynmultipush MauvilleCity_GameCorner_Text_PrizeScyther, SPECIES_SCYTHER
	dynmultipush MauvilleCity_GameCorner_Text_PrizeLarvitar, SPECIES_LARVITAR
	dynmultipush MauvilleCity_GameCorner_Text_PrizeLarvesta, SPECIES_LARVESTA
	dynmultipush MauvilleCity_GameCorner_Text_PrizeDratini, SPECIES_DRATINI
	dynmultipush MauvilleCity_GameCorner_Text_PrizeBagon, SPECIES_BAGON
	dynmultipush MauvilleCity_GameCorner_Text_PrizeDreepy, SPECIES_DREEPY
	dynmultipush MauvilleCity_GameCorner_Text_PrizeFrigibax, SPECIES_FRIGIBAX
	dynmultipush MauvilleCity_GameCorner_Text_PrizeBeldum, SPECIES_BELDUM
	dynmultipush MauvilleCity_GameCorner_Text_PrizePorygon, SPECIES_PORYGON
	dynmultipush MauvilleCity_GameCorner_Text_PrizeExit, SPECIES_NONE
	dynmultistack 13, 0, FALSE, 6, FALSE, SPECIES_ABRA, DYN_MULTICHOICE_CB_SHOW_MON_LEFT
	switch VAR_RESULT
	case SPECIES_ABRA, MauvilleCity_GameCorner_EventScript_Abra
	case SPECIES_CUBONE, MauvilleCity_GameCorner_EventScript_Cubone
	case SPECIES_RALTS, MauvilleCity_GameCorner_EventScript_Ralts
	case SPECIES_SCYTHER, MauvilleCity_GameCorner_EventScript_Scyther
	case SPECIES_LARVITAR, MauvilleCity_GameCorner_EventScript_Larvitar
	case SPECIES_LARVESTA, MauvilleCity_GameCorner_EventScript_Larvesta
	case SPECIES_DRATINI, MauvilleCity_GameCorner_EventScript_Dratini
	case SPECIES_BAGON, MauvilleCity_GameCorner_EventScript_Bagon
	case SPECIES_DREEPY, MauvilleCity_GameCorner_EventScript_Dreepy
	case SPECIES_FRIGIBAX, MauvilleCity_GameCorner_EventScript_Frigibax
	case SPECIES_BELDUM, MauvilleCity_GameCorner_EventScript_Beldum
	case SPECIES_PORYGON, MauvilleCity_GameCorner_EventScript_Porygon
	case SPECIES_NONE, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
	end

MauvilleCity_GameCorner_EventScript_ChooseEvoItem::
	dynmultipush MauvilleCity_GameCorner_Text_PrizeFireStone, ITEM_FIRE_STONE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeThunderStone, ITEM_THUNDER_STONE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeWaterStone, ITEM_WATER_STONE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeLeafStone, ITEM_LEAF_STONE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeIceStone, ITEM_ICE_STONE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeSunStone, ITEM_SUN_STONE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeMoonStone, ITEM_MOON_STONE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeShinyStone, ITEM_SHINY_STONE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeDuskStone, ITEM_DUSK_STONE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeDawnStone, ITEM_DAWN_STONE
	dynmultipush MauvilleCity_GameCorner_Text_PrizeLinkingCord, ITEM_LINKING_CORD
	dynmultipush MauvilleCity_GameCorner_Text_PrizeExit, ITEM_NONE
	dynmultistack 12, 0, FALSE, 6, FALSE, ITEM_FIRE_STONE, DYN_MULTICHOICE_CB_SHOW_ITEM_LEFT
	switch VAR_RESULT
	case ITEM_FIRE_STONE, MauvilleCity_GameCorner_EventScript_FireStone
	case ITEM_THUNDER_STONE, MauvilleCity_GameCorner_EventScript_ThunderStone
	case ITEM_WATER_STONE, MauvilleCity_GameCorner_EventScript_WaterStone
	case ITEM_LEAF_STONE, MauvilleCity_GameCorner_EventScript_LeafStone
	case ITEM_ICE_STONE, MauvilleCity_GameCorner_EventScript_IceStone
	case ITEM_SUN_STONE, MauvilleCity_GameCorner_EventScript_SunStone
	case ITEM_MOON_STONE, MauvilleCity_GameCorner_EventScript_MoonStone
	case ITEM_SHINY_STONE, MauvilleCity_GameCorner_EventScript_ShinyStone
	case ITEM_DUSK_STONE, MauvilleCity_GameCorner_EventScript_DuskStone
	case ITEM_DAWN_STONE, MauvilleCity_GameCorner_EventScript_DawnStone
	case ITEM_LINKING_CORD, MauvilleCity_GameCorner_EventScript_LinkingCord
	case ITEM_NONE, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
	end		

MauvilleCity_GameCorner_EventScript_Eviolite::
	setvar VAR_TEMP_1, ITEM_EVIOLITE
	bufferitemname STR_VAR_1, ITEM_EVIOLITE
	setvar VAR_0x8004, ITEM_EVIOLITE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
	
MauvilleCity_GameCorner_EventScript_Leftovers::
	setvar VAR_TEMP_1, ITEM_LEFTOVERS
	bufferitemname STR_VAR_1, ITEM_LEFTOVERS
	setvar VAR_0x8004, ITEM_LEFTOVERS
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize	
	
MauvilleCity_GameCorner_EventScript_SootheBell::
	setvar VAR_TEMP_1, ITEM_SOOTHE_BELL
	bufferitemname STR_VAR_1, ITEM_SOOTHE_BELL
	setvar VAR_0x8004, ITEM_SOOTHE_BELL
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
	
MauvilleCity_GameCorner_EventScript_ThickClub::
	setvar VAR_TEMP_1, ITEM_THICK_CLUB
	bufferitemname STR_VAR_1, ITEM_THICK_CLUB
	setvar VAR_0x8004, ITEM_THICK_CLUB
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_LifeOrb::
	setvar VAR_TEMP_1, ITEM_LIFE_ORB
	bufferitemname STR_VAR_1, ITEM_LIFE_ORB
	setvar VAR_0x8004, ITEM_LIFE_ORB
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_ExpertBelt::
	setvar VAR_TEMP_1, ITEM_EXPERT_BELT
	bufferitemname STR_VAR_1, ITEM_EXPERT_BELT
	setvar VAR_0x8004, ITEM_EXPERT_BELT
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_PunchingGlove::
	setvar VAR_TEMP_1, ITEM_PUNCHING_GLOVE
	bufferitemname STR_VAR_1, ITEM_PUNCHING_GLOVE
	setvar VAR_0x8004, ITEM_PUNCHING_GLOVE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_WideLens::
	setvar VAR_TEMP_1, ITEM_WIDE_LENS
	bufferitemname STR_VAR_1, ITEM_WIDE_LENS
	setvar VAR_0x8004, ITEM_WIDE_LENS
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_MuscleBand::
	setvar VAR_TEMP_1, ITEM_MUSCLE_BAND
	bufferitemname STR_VAR_1, ITEM_MUSCLE_BAND
	setvar VAR_0x8004, ITEM_MUSCLE_BAND
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_WiseGlasses::
	setvar VAR_TEMP_1, ITEM_WISE_GLASSES
	bufferitemname STR_VAR_1, ITEM_WISE_GLASSES
	setvar VAR_0x8004, ITEM_WISE_GLASSES
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_FocusSash::
	setvar VAR_TEMP_1, ITEM_FOCUS_SASH
	bufferitemname STR_VAR_1, ITEM_FOCUS_SASH
	setvar VAR_0x8004, ITEM_FOCUS_SASH
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_AssaultVest::
	setvar VAR_TEMP_1, ITEM_ASSAULT_VEST
	bufferitemname STR_VAR_1, ITEM_ASSAULT_VEST
	setvar VAR_0x8004, ITEM_ASSAULT_VEST
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_RockyHelmet::
	setvar VAR_TEMP_1, ITEM_ROCKY_HELMET
	bufferitemname STR_VAR_1, ITEM_ROCKY_HELMET
	setvar VAR_0x8004, ITEM_ROCKY_HELMET
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_LoadedDice::
	setvar VAR_TEMP_1, ITEM_LOADED_DICE
	bufferitemname STR_VAR_1, ITEM_LOADED_DICE
	setvar VAR_0x8004, ITEM_LOADED_DICE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_ThunderStone::
	setvar VAR_TEMP_1, ITEM_THUNDER_STONE
	bufferitemname STR_VAR_1, ITEM_THUNDER_STONE
	setvar VAR_0x8004, ITEM_THUNDER_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_WaterStone::
	setvar VAR_TEMP_1, ITEM_WATER_STONE
	bufferitemname STR_VAR_1, ITEM_WATER_STONE
	setvar VAR_0x8004, ITEM_WATER_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_LeafStone::
	setvar VAR_TEMP_1, ITEM_LEAF_STONE
	bufferitemname STR_VAR_1, ITEM_LEAF_STONE
	setvar VAR_0x8004, ITEM_LEAF_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_FireStone::
	setvar VAR_TEMP_1, ITEM_FIRE_STONE
	bufferitemname STR_VAR_1, ITEM_FIRE_STONE
	setvar VAR_0x8004, ITEM_FIRE_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_IceStone::
	setvar VAR_TEMP_1, ITEM_ICE_STONE
	bufferitemname STR_VAR_1, ITEM_ICE_STONE
	setvar VAR_0x8004, ITEM_ICE_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_SunStone::
	setvar VAR_TEMP_1, ITEM_SUN_STONE
	bufferitemname STR_VAR_1, ITEM_SUN_STONE
	setvar VAR_0x8004, ITEM_SUN_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_MoonStone::
	setvar VAR_TEMP_1, ITEM_MOON_STONE
	bufferitemname STR_VAR_1, ITEM_MOON_STONE
	setvar VAR_0x8004, ITEM_MOON_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_ShinyStone::
	setvar VAR_TEMP_1, ITEM_SHINY_STONE
	bufferitemname STR_VAR_1, ITEM_SHINY_STONE
	setvar VAR_0x8004, ITEM_SHINY_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_DuskStone::
	setvar VAR_TEMP_1, ITEM_DUSK_STONE
	bufferitemname STR_VAR_1, ITEM_DUSK_STONE
	setvar VAR_0x8004, ITEM_DUSK_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_DawnStone::
	setvar VAR_TEMP_1, ITEM_DAWN_STONE
	bufferitemname STR_VAR_1, ITEM_DAWN_STONE
	setvar VAR_0x8004, ITEM_DAWN_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_LinkingCord::
	setvar VAR_TEMP_1, ITEM_LINKING_CORD
	bufferitemname STR_VAR_1, ITEM_LINKING_CORD
	setvar VAR_0x8004, ITEM_LINKING_CORD
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_Abra::
	setvar VAR_TEMP_1, 1
	bufferspeciesname STR_VAR_1, SPECIES_ABRA
	setvar VAR_0x8004, SPECIES_ABRA
	goto MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize

MauvilleCity_GameCorner_EventScript_Cubone::
	setvar VAR_TEMP_1, 2
	bufferspeciesname STR_VAR_1, SPECIES_CUBONE
	setvar VAR_0x8004, SPECIES_CUBONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize

MauvilleCity_GameCorner_EventScript_Ralts::
	setvar VAR_TEMP_1, 3
	bufferspeciesname STR_VAR_1, SPECIES_RALTS
	setvar VAR_0x8004, SPECIES_RALTS
	goto MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize

MauvilleCity_GameCorner_EventScript_Dratini::
	setvar VAR_TEMP_1, 4
	bufferspeciesname STR_VAR_1, SPECIES_DRATINI
	setvar VAR_0x8004, SPECIES_DRATINI
	goto MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize

MauvilleCity_GameCorner_EventScript_Bagon::
	setvar VAR_TEMP_1, 5
	bufferspeciesname STR_VAR_1, SPECIES_BAGON
	setvar VAR_0x8004, SPECIES_BAGON
	goto MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize

MauvilleCity_GameCorner_EventScript_Frigibax::
	setvar VAR_TEMP_1, 9
	bufferspeciesname STR_VAR_1, SPECIES_FRIGIBAX
	setvar VAR_0x8004, SPECIES_FRIGIBAX
	goto MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize

MauvilleCity_GameCorner_EventScript_Beldum::
	setvar VAR_TEMP_1, 10
	bufferspeciesname STR_VAR_1, SPECIES_BELDUM
	setvar VAR_0x8004, SPECIES_BELDUM
	goto MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize

MauvilleCity_GameCorner_EventScript_Porygon::
	setvar VAR_TEMP_1, 11
	bufferspeciesname STR_VAR_1, SPECIES_PORYGON
	setvar VAR_0x8004, SPECIES_PORYGON
	goto MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize

MauvilleCity_GameCorner_EventScript_Larvitar::
	setvar VAR_TEMP_1, 6
	bufferspeciesname STR_VAR_1, SPECIES_LARVITAR
	setvar VAR_0x8004, SPECIES_LARVITAR
	goto MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize

MauvilleCity_GameCorner_EventScript_Larvesta::
	setvar VAR_TEMP_1, 12
	bufferspeciesname STR_VAR_1, SPECIES_LARVESTA
	setvar VAR_0x8004, SPECIES_LARVESTA
	goto MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize

MauvilleCity_GameCorner_EventScript_Dreepy::
	setvar VAR_TEMP_1, 7
	bufferspeciesname STR_VAR_1, SPECIES_DREEPY
	setvar VAR_0x8004, SPECIES_DREEPY
	goto MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize

MauvilleCity_GameCorner_EventScript_Scyther::
	setvar VAR_TEMP_1, 8
	bufferspeciesname STR_VAR_1, SPECIES_SCYTHER
	setvar VAR_0x8004, SPECIES_SCYTHER
	goto MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize


MauvilleCity_GameCorner_EventScript_ConfirmNewPrize::
	//special BufferItemName
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsTheNewX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	switch VAR_TEMP_1
	case ITEM_FIRE_STONE, MauvilleCity_GameCorner_EventScript_BuyFireStone
	case ITEM_THUNDER_STONE, MauvilleCity_GameCorner_EventScript_BuyThunderStone
	case ITEM_WATER_STONE, MauvilleCity_GameCorner_EventScript_BuyWaterStone
	case ITEM_LEAF_STONE, MauvilleCity_GameCorner_EventScript_BuyLeafStone
	case ITEM_ICE_STONE, MauvilleCity_GameCorner_EventScript_BuyIceStone
	case ITEM_SUN_STONE, MauvilleCity_GameCorner_EventScript_BuySunStone
	case ITEM_MOON_STONE, MauvilleCity_GameCorner_EventScript_BuyMoonStone
	case ITEM_SHINY_STONE, MauvilleCity_GameCorner_EventScript_BuyShinyStone
	case ITEM_DUSK_STONE, MauvilleCity_GameCorner_EventScript_BuyDuskStone
	case ITEM_DAWN_STONE, MauvilleCity_GameCorner_EventScript_BuyDawnStone
	case ITEM_LINKING_CORD, MauvilleCity_GameCorner_EventScript_BuyLinkingCord
	case ITEM_SOOTHE_BELL, MauvilleCity_GameCorner_EventScript_BuySootheBell
	case ITEM_EXPERT_BELT, MauvilleCity_GameCorner_EventScript_BuyExpertBelt
	case ITEM_PUNCHING_GLOVE, MauvilleCity_GameCorner_EventScript_BuyPunchingGlove
	case ITEM_WIDE_LENS, MauvilleCity_GameCorner_EventScript_BuyWideLens
	case ITEM_THICK_CLUB, MauvilleCity_GameCorner_EventScript_BuyThickClub
	case ITEM_MUSCLE_BAND, MauvilleCity_GameCorner_EventScript_BuyMuscleBand
	case ITEM_WISE_GLASSES, MauvilleCity_GameCorner_EventScript_BuyWiseGlasses
	case ITEM_FOCUS_SASH, MauvilleCity_GameCorner_EventScript_BuyFocusSash
	case ITEM_EVIOLITE, MauvilleCity_GameCorner_EventScript_BuyEviolite
	case ITEM_ASSAULT_VEST, MauvilleCity_GameCorner_EventScript_BuyAssaultVest
	case ITEM_ROCKY_HELMET, MauvilleCity_GameCorner_EventScript_BuyRockyHelmet
	case ITEM_LEFTOVERS, MauvilleCity_GameCorner_EventScript_BuyLeftovers
	case ITEM_LOADED_DICE, MauvilleCity_GameCorner_EventScript_BuyLoadedDice
	case ITEM_LIFE_ORB, MauvilleCity_GameCorner_EventScript_BuyLifeOrb
	end

MauvilleCity_GameCorner_EventScript_ConfirmPokemonPrize::
	//special BufferItemName
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	switch VAR_TEMP_1
	case 1, MauvilleCity_GameCorner_EventScript_BuyAbra
	case 2, MauvilleCity_GameCorner_EventScript_BuyCubone
	case 3, MauvilleCity_GameCorner_EventScript_BuyRalts
	case 4, MauvilleCity_GameCorner_EventScript_BuyDratini
	case 5, MauvilleCity_GameCorner_EventScript_BuyBagon
	case 6, MauvilleCity_GameCorner_EventScript_BuyLarvitar
	case 7, MauvilleCity_GameCorner_EventScript_BuyDreepy
	case 8, MauvilleCity_GameCorner_EventScript_BuyScyther
	case 9, MauvilleCity_GameCorner_EventScript_BuyFrigibax
	case 10, MauvilleCity_GameCorner_EventScript_BuyBeldum
	case 11, MauvilleCity_GameCorner_EventScript_BuyPorygon
	case 12, MauvilleCity_GameCorner_EventScript_BuyLarvesta
	end

MauvilleCity_GameCorner_EventScript_BuyAbra::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, ABRA_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon
	removecoins ABRA_COINS
	setvar VAR_0x8004, SPECIES_ABRA
	special GiveGameCornerPrizeMonWithRandomIVs
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_BuyCubone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, CUBONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon
	removecoins CUBONE_COINS
	setvar VAR_0x8004, SPECIES_CUBONE
	special GiveGameCornerPrizeMonWithRandomIVs
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_BuyRalts::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, RALTS_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon
	removecoins RALTS_COINS
	setvar VAR_0x8004, SPECIES_RALTS
	special GiveGameCornerPrizeMonWithRandomIVs
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_BuyDratini::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, DRATINI_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon
	removecoins DRATINI_COINS
	setvar VAR_0x8004, SPECIES_DRATINI
	special GiveGameCornerPrizeMonWithRandomIVs
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_BuyBagon::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, BAGON_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon
	removecoins BAGON_COINS
	setvar VAR_0x8004, SPECIES_BAGON
	special GiveGameCornerPrizeMonWithRandomIVs
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_BuyLarvitar::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, LARVITAR_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon
	removecoins LARVITAR_COINS
	setvar VAR_0x8004, SPECIES_LARVITAR
	special GiveGameCornerPrizeMonWithRandomIVs
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_BuyLarvesta::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, LARVESTA_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon
	removecoins LARVESTA_COINS
	setvar VAR_0x8004, SPECIES_LARVESTA
	special GiveGameCornerPrizeMonWithRandomIVs
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_BuyDreepy::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, DREEPY_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon
	removecoins DREEPY_COINS
	setvar VAR_0x8004, SPECIES_DREEPY
	special GiveGameCornerPrizeMonWithRandomIVs
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_BuyScyther::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, SCYTHER_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon
	removecoins SCYTHER_COINS
	setvar VAR_0x8004, SPECIES_SCYTHER
	special GiveGameCornerPrizeMonWithRandomIVs
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_BuyFrigibax::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, FRIGIBAX_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon
	removecoins FRIGIBAX_COINS
	setvar VAR_0x8004, SPECIES_FRIGIBAX
	special GiveGameCornerPrizeMonWithRandomIVs
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_BuyBeldum::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, BELDUM_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon
	removecoins BELDUM_COINS
	setvar VAR_0x8004, SPECIES_BELDUM
	special GiveGameCornerPrizeMonWithRandomIVs
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_BuyPorygon::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, PORYGON_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon
	removecoins PORYGON_COINS
	setvar VAR_0x8004, SPECIES_PORYGON
	special GiveGameCornerPrizeMonWithRandomIVs
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_BuyLeftovers::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, LEFTOVERS_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_LEFTOVERS
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins LEFTOVERS_COINS
	additem ITEM_LEFTOVERS
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyEviolite::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, EVIOLITE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_EVIOLITE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins EVIOLITE_COINS
	additem ITEM_EVIOLITE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuySootheBell::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, SOOTHEBELL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_SOOTHE_BELL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins SOOTHEBELL_COINS
	additem ITEM_SOOTHE_BELL
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyExpertBelt::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, EXPERTBELT_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_EXPERT_BELT
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins EXPERTBELT_COINS
	additem ITEM_EXPERT_BELT
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyPunchingGlove::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, PUNCHINGGLOVE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_PUNCHING_GLOVE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins PUNCHINGGLOVE_COINS
	additem ITEM_PUNCHING_GLOVE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyWideLens::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, WIDELENS_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_WIDE_LENS
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins WIDELENS_COINS
	additem ITEM_WIDE_LENS
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end
	
MauvilleCity_GameCorner_EventScript_BuyThickClub::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, THICKCLUB_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_THICK_CLUB
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins THICKCLUB_COINS
	additem ITEM_THICK_CLUB
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyMuscleBand::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, MUSCLEBAND_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_MUSCLE_BAND
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins MUSCLEBAND_COINS
	additem ITEM_MUSCLE_BAND
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyWiseGlasses::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, WISEGLASSES_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_WISE_GLASSES
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins WISEGLASSES_COINS
	additem ITEM_WISE_GLASSES
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyFocusSash::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, FOCUSSASH_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_FOCUS_SASH
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins FOCUSSASH_COINS
	additem ITEM_FOCUS_SASH
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyAssaultVest::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, ASSAULTVEST_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_ASSAULT_VEST
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins ASSAULTVEST_COINS
	additem ITEM_ASSAULT_VEST
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyRockyHelmet::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, ROCKYHELMET_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_ROCKY_HELMET
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins ROCKYHELMET_COINS
	additem ITEM_ROCKY_HELMET
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyLoadedDice::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, LOADEDDICE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_LOADED_DICE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins LOADEDDICE_COINS
	additem ITEM_LOADED_DICE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyLifeOrb::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, LIFEORB_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_LIFE_ORB
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins LIFEORB_COINS
	additem ITEM_LIFE_ORB
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyFireStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, FIRESTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_FIRE_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins FIRESTONE_COINS
	additem ITEM_FIRE_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end

MauvilleCity_GameCorner_EventScript_BuyThunderStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, THUNDERSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_THUNDER_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins THUNDERSTONE_COINS
	additem ITEM_THUNDER_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end

MauvilleCity_GameCorner_EventScript_BuyWaterStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, WATERSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_WATER_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins WATERSTONE_COINS
	additem ITEM_WATER_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end

MauvilleCity_GameCorner_EventScript_BuyLeafStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, LEAFSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_LEAF_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins LEAFSTONE_COINS
	additem ITEM_LEAF_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end	

MauvilleCity_GameCorner_EventScript_BuyIceStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, ICESTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_ICE_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins ICESTONE_COINS
	additem ITEM_ICE_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end

MauvilleCity_GameCorner_EventScript_BuySunStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, SUNSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_SUN_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins SUNSTONE_COINS
	additem ITEM_SUN_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end

MauvilleCity_GameCorner_EventScript_BuyMoonStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, MOONSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_MOON_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins MOONSTONE_COINS
	additem ITEM_MOON_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end

MauvilleCity_GameCorner_EventScript_BuyShinyStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, SHINYSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_SHINY_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins SHINYSTONE_COINS
	additem ITEM_SHINY_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end

MauvilleCity_GameCorner_EventScript_BuyDuskStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, DUSKSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_DUSK_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins DUSKSTONE_COINS
	additem ITEM_DUSK_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end

MauvilleCity_GameCorner_EventScript_BuyDawnStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, DAWNSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_DAWN_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins DAWNSTONE_COINS
	additem ITEM_DAWN_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end

MauvilleCity_GameCorner_EventScript_BuyLinkingCord::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, LINKINGCORD_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_LINKING_CORD
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins LINKINGCORD_COINS
	additem ITEM_LINKING_CORD
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end	

MauvilleCity_GameCorner_EventScript_TMDoubleTeam::
	setvar VAR_TEMP_1, ITEM_TM_DOUBLE_TEAM
	bufferitemname STR_VAR_1, ITEM_TM_DOUBLE_TEAM
	setvar VAR_0x8004, ITEM_TM_DOUBLE_TEAM
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMPsychic::
	setvar VAR_TEMP_1, ITEM_TM_PSYCHIC
	bufferitemname STR_VAR_1, ITEM_TM_PSYCHIC
	setvar VAR_0x8004, ITEM_TM_PSYCHIC
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMFirePunch::
	setvar VAR_TEMP_1, ITEM_TM_FIRE_PUNCH
	bufferitemname STR_VAR_1, ITEM_TM_FIRE_PUNCH
	setvar VAR_0x8004, ITEM_TM_FIRE_PUNCH
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMThunderPunch::
	setvar VAR_TEMP_1, ITEM_TM_THUNDER_PUNCH
	bufferitemname STR_VAR_1, ITEM_TM_THUNDER_PUNCH
	setvar VAR_0x8004, ITEM_TM_THUNDER_PUNCH
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMIcePunch::
	setvar VAR_TEMP_1, ITEM_TM_ICE_PUNCH
	bufferitemname STR_VAR_1, ITEM_TM_ICE_PUNCH
	setvar VAR_0x8004, ITEM_TM_ICE_PUNCH
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMFlamethrower::
	setvar VAR_TEMP_1, ITEM_TM_FLAMETHROWER
	bufferitemname STR_VAR_1, ITEM_TM_FLAMETHROWER
	setvar VAR_0x8004, ITEM_TM_FLAMETHROWER
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMThunderbolt::
	setvar VAR_TEMP_1, ITEM_TM_THUNDERBOLT
	bufferitemname STR_VAR_1, ITEM_TM_THUNDERBOLT
	setvar VAR_0x8004, ITEM_TM_THUNDERBOLT
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMIceBeam::
	setvar VAR_TEMP_1, ITEM_TM_ICE_BEAM
	bufferitemname STR_VAR_1, ITEM_TM_ICE_BEAM
	setvar VAR_0x8004, ITEM_TM_ICE_BEAM
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMFlashCannon::
	setvar VAR_TEMP_1, ITEM_TM_FLASH_CANNON
	bufferitemname STR_VAR_1, ITEM_TM_FLASH_CANNON
	setvar VAR_0x8004, ITEM_TM_FLASH_CANNON
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMDazzlingGleam::
	setvar VAR_TEMP_1, ITEM_TM_DAZZLING_GLEAM
	bufferitemname STR_VAR_1, ITEM_TM_DAZZLING_GLEAM
	setvar VAR_0x8004, ITEM_TM_DAZZLING_GLEAM
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMEarthPower::
	setvar VAR_TEMP_1, ITEM_TM_EARTH_POWER
	bufferitemname STR_VAR_1, ITEM_TM_EARTH_POWER
	setvar VAR_0x8004, ITEM_TM_EARTH_POWER
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMWilloWisp::
	setvar VAR_TEMP_1, ITEM_TM_WILL_O_WISP
	bufferitemname STR_VAR_1, ITEM_TM_WILL_O_WISP
	setvar VAR_0x8004, ITEM_TM_WILL_O_WISP
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_TMThunderWave::
	setvar VAR_TEMP_1, ITEM_TM_THUNDER_WAVE
	bufferitemname STR_VAR_1, ITEM_TM_THUNDER_WAVE
	setvar VAR_0x8004, ITEM_TM_THUNDER_WAVE
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize

MauvilleCity_GameCorner_EventScript_ConfirmTMPrize::
	special BufferTMHMMoveName
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsTheTMX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	switch VAR_TEMP_1
	case ITEM_TM_DOUBLE_TEAM, MauvilleCity_GameCorner_EventScript_BuyTMDoubleTeam
	case ITEM_TM_PSYCHIC, MauvilleCity_GameCorner_EventScript_BuyTMPsychic
	case ITEM_TM_FIRE_PUNCH, MauvilleCity_GameCorner_EventScript_BuyTMFirePunch
	case ITEM_TM_THUNDER_PUNCH, MauvilleCity_GameCorner_EventScript_BuyTMThunderPunch
	case ITEM_TM_ICE_PUNCH, MauvilleCity_GameCorner_EventScript_BuyTMIcePunch
	case ITEM_TM_FLAMETHROWER, MauvilleCity_GameCorner_EventScript_BuyTMFlamethrower
	case ITEM_TM_THUNDERBOLT, MauvilleCity_GameCorner_EventScript_BuyTMThunderbolt
	case ITEM_TM_ICE_BEAM, MauvilleCity_GameCorner_EventScript_BuyTMIceBeam
	case ITEM_TM_FLASH_CANNON, MauvilleCity_GameCorner_EventScript_BuyTMFlashCannon
	case ITEM_TM_DAZZLING_GLEAM, MauvilleCity_GameCorner_EventScript_BuyTMDazzlingGleam
	case ITEM_TM_EARTH_POWER, MauvilleCity_GameCorner_EventScript_BuyTMEarthPower
	case ITEM_TM_WILL_O_WISP, MauvilleCity_GameCorner_EventScript_BuyTMWilloWisp
	case ITEM_TM_THUNDER_WAVE, MauvilleCity_GameCorner_EventScript_BuyTMThunderWave
	end

MauvilleCity_GameCorner_EventScript_BuyTMDoubleTeam::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_DOUBLE_TEAM_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_DOUBLE_TEAM
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_DOUBLE_TEAM_COINS
	additem ITEM_TM_DOUBLE_TEAM
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMPsychic::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_PSYCHIC_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_PSYCHIC
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_PSYCHIC_COINS
	additem ITEM_TM_PSYCHIC
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMFirePunch::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_FIREPUNCH_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_FIRE_PUNCH
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_FIREPUNCH_COINS
	additem ITEM_TM_FIRE_PUNCH
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMThunderPunch::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_THUNDERPUNCH_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_THUNDER_PUNCH
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_THUNDERPUNCH_COINS
	additem ITEM_TM_THUNDER_PUNCH
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMIcePunch::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_ICEPUNCH_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_ICE_PUNCH
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_ICEPUNCH_COINS
	additem ITEM_TM_ICE_PUNCH
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMFlamethrower::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_FLAMETHROWER_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_FLAMETHROWER
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_FLAMETHROWER_COINS
	additem ITEM_TM_FLAMETHROWER
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMThunderbolt::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_THUNDERBOLT_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_THUNDERBOLT_COINS
	additem ITEM_TM_THUNDERBOLT
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMIceBeam::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_ICE_BEAM_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_ICE_BEAM
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_ICE_BEAM_COINS
	additem ITEM_TM_ICE_BEAM
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMFlashCannon::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_FLASH_CANNON_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_FLASH_CANNON
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_FLASH_CANNON_COINS
	additem ITEM_TM_FLASH_CANNON
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMDazzlingGleam::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_DAZZLING_GLEAM_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_DAZZLING_GLEAM
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_DAZZLING_GLEAM_COINS
	additem ITEM_TM_DAZZLING_GLEAM
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMEarthPower::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_EARTH_POWER_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_EARTH_POWER
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_EARTH_POWER_COINS
	additem ITEM_TM_EARTH_POWER
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMWilloWisp::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_WILL_O_WISP_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_WILL_O_WISP
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_WILL_O_WISP_COINS
	additem ITEM_TM_WILL_O_WISP
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_BuyTMThunderWave::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_THUNDER_WAVE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_THUNDER_WAVE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
	removecoins TM_THUNDER_WAVE_COINS
	additem ITEM_TM_THUNDER_WAVE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end

MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM::
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end
	
MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew::
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end	

MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForPokemon::
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChoosePokemonPrize
	end

MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2::
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end		

MauvilleCity_GameCorner_EventScript_NoRoomForTM::
	call Common_EventScript_BagIsFull
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
	end
	
MauvilleCity_GameCorner_EventScript_NoRoomForNew::
	call Common_EventScript_BagIsFull
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end	
	
MauvilleCity_GameCorner_EventScript_NoRoomForNew2::
	call Common_EventScript_BagIsFull
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end		

MauvilleCity_GameCorner_EventScript_Bottle_Cap_Clerk::
	lock
	goto_if_set FLAG_MET_BOTTLE_CAP_CLERK, MauvilleCity_GameCorner_EventScript_BottleCapClerkStandard
	msgbox MauvilleCity_GameCorner_Text_BottleCapClerkFirst, MSGBOX_DEFAULT
	applymovement 9, MauvilleCity_GameCorner_Movement_BottleCapClerkExclamation
	playse SE_PIN
	waitmovement 0
	faceplayer
	setflag FLAG_MET_BOTTLE_CAP_CLERK
	msgbox MauvilleCity_GameCorner_Text_BottleCapClerkOffer, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_BottleCapClerkOpenShop

MauvilleCity_GameCorner_EventScript_BottleCapClerkStandard::
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_BottleCapClerkStandard, MSGBOX_DEFAULT

MauvilleCity_GameCorner_EventScript_BottleCapClerkOpenShop::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_BottleCapClerkNeedCoinCase
	message MauvilleCity_GameCorner_Text_BottleCapClerkWhichCap
	waitmessage
	showcoinsbox 1, 1
	goto MauvilleCity_GameCorner_EventScript_ChooseBottleCapPrize

MauvilleCity_GameCorner_EventScript_ReturnToChooseBottleCapPrize::
	message MauvilleCity_GameCorner_Text_BottleCapClerkWhichCap
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChooseBottleCapPrize

MauvilleCity_GameCorner_EventScript_ChooseBottleCapPrize::
	dynmultipush MauvilleCity_GameCorner_Text_PrizeBottleCap, ITEM_BOTTLE_CAP
	dynmultipush MauvilleCity_GameCorner_Text_PrizeGoldBottleCap, ITEM_GOLD_BOTTLE_CAP
	dynmultipush MauvilleCity_GameCorner_Text_PrizeExit, ITEM_NONE
	dynmultistack 12, 0, FALSE, 3, FALSE, ITEM_BOTTLE_CAP, DYN_MULTICHOICE_CB_SHOW_ITEM_LEFT
	switch VAR_RESULT
	case ITEM_BOTTLE_CAP, MauvilleCity_GameCorner_EventScript_BottleCap
	case ITEM_GOLD_BOTTLE_CAP, MauvilleCity_GameCorner_EventScript_GoldBottleCap
	case ITEM_NONE, MauvilleCity_GameCorner_EventScript_CancelBottleCapSelect
	goto MauvilleCity_GameCorner_EventScript_CancelBottleCapSelect
	end

MauvilleCity_GameCorner_EventScript_BottleCap::
	setvar VAR_TEMP_1, ITEM_BOTTLE_CAP
	bufferitemname STR_VAR_1, ITEM_BOTTLE_CAP
	goto MauvilleCity_GameCorner_EventScript_ConfirmBottleCapPrize

MauvilleCity_GameCorner_EventScript_GoldBottleCap::
	setvar VAR_TEMP_1, ITEM_GOLD_BOTTLE_CAP
	bufferitemname STR_VAR_1, ITEM_GOLD_BOTTLE_CAP
	goto MauvilleCity_GameCorner_EventScript_ConfirmBottleCapPrize

MauvilleCity_GameCorner_EventScript_ConfirmBottleCapPrize::
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsTheNewX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelBottleCapSelect
	switch VAR_TEMP_1
	case ITEM_BOTTLE_CAP, MauvilleCity_GameCorner_EventScript_BuyBottleCap
	case ITEM_GOLD_BOTTLE_CAP, MauvilleCity_GameCorner_EventScript_BuyGoldBottleCap
	end

MauvilleCity_GameCorner_EventScript_BuyBottleCap::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, BOTTLECAP_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForBottleCap
	checkitemspace ITEM_BOTTLE_CAP
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForBottleCap
	removecoins BOTTLECAP_COINS
	additem ITEM_BOTTLE_CAP
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseBottleCapPrize
	end

MauvilleCity_GameCorner_EventScript_BuyGoldBottleCap::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, GOLDBOTTLECAP_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForBottleCap
	checkitemspace ITEM_GOLD_BOTTLE_CAP
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForBottleCap
	removecoins GOLDBOTTLECAP_COINS
	additem ITEM_GOLD_BOTTLE_CAP
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseBottleCapPrize
	end

MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForBottleCap::
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseBottleCapPrize
	end

MauvilleCity_GameCorner_EventScript_NoRoomForBottleCap::
	call Common_EventScript_BagIsFull
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseBottleCapPrize
	end

MauvilleCity_GameCorner_EventScript_CancelBottleCapSelect::
	msgbox MauvilleCity_GameCorner_Text_BottleCapClerkComeBack, MSGBOX_DEFAULT
	hidecoinsbox 0, 0
	applymovement 9, MauvilleCity_GameCorner_Movement_BottleCapClerkFaceRight
	waitmovement 0
	release
	end

MauvilleCity_GameCorner_EventScript_BottleCapClerkNeedCoinCase::
	msgbox MauvilleCity_GameCorner_Text_NeedCoinCaseForCoins, MSGBOX_DEFAULT
	applymovement 9, MauvilleCity_GameCorner_Movement_BottleCapClerkFaceRight
	waitmovement 0
	release
	end

MauvilleCity_GameCorner_Movement_BottleCapClerkExclamation:
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

MauvilleCity_GameCorner_Movement_BottleCapClerkFaceRight:
	face_right
	step_end

MauvilleCity_GameCorner_EventScript_VendingMachine::
	lockall
	message MauvilleCity_GameCorner_Text_WhichDrinkWouldYouLike
	waitmessage
	showmoneybox 0, 0
	goto MauvilleCity_GameCorner_EventScript_ChooseDrink
	end

MauvilleCity_GameCorner_EventScript_ChooseDrink::
	multichoice 16, 0, MULTI_VENDING_MACHINE, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, MauvilleCity_GameCorner_EventScript_FreshWater
	case 1, MauvilleCity_GameCorner_EventScript_SodaPop
	case 2, MauvilleCity_GameCorner_EventScript_Lemonade
	msgbox MauvilleCity_GameCorner_Text_DecidedAgainstBuyingDrink, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ExitVendingMachine
	end

MauvilleCity_GameCorner_EventScript_FreshWater::
	setvar VAR_TEMP_0, ITEM_FRESH_WATER
	goto MauvilleCity_GameCorner_EventScript_TryBuyDrink
	end

MauvilleCity_GameCorner_EventScript_SodaPop::
	setvar VAR_TEMP_0, ITEM_SODA_POP
	goto MauvilleCity_GameCorner_EventScript_TryBuyDrink
	end

MauvilleCity_GameCorner_EventScript_Lemonade::
	setvar VAR_TEMP_0, ITEM_LEMONADE
	goto MauvilleCity_GameCorner_EventScript_TryBuyDrink
	end

MauvilleCity_GameCorner_EventScript_CheckMoneyFreshWater::
	checkmoney 200
	return

MauvilleCity_GameCorner_EventScript_CheckMoneySodaPop::
	checkmoney 300
	return

MauvilleCity_GameCorner_EventScript_CheckMoneyLemonade::
	checkmoney 350
	return

MauvilleCity_GameCorner_EventScript_RemoveMoneyFreshWater::
	removemoney 200
	return

MauvilleCity_GameCorner_EventScript_RemoveMoneySodaPop::
	removemoney 300
	return

MauvilleCity_GameCorner_EventScript_RemoveMoneyLemonade::
	removemoney 350
	return

MauvilleCity_GameCorner_EventScript_TryBuyDrink::
	call_if_eq VAR_TEMP_1, 0, MauvilleCity_GameCorner_EventScript_CheckMoneyFreshWater
	call_if_eq VAR_TEMP_1, 1, MauvilleCity_GameCorner_EventScript_CheckMoneySodaPop
	call_if_eq VAR_TEMP_1, 2, MauvilleCity_GameCorner_EventScript_CheckMoneyLemonade
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NotEnoughMoneyForDrink
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDrink
	call_if_eq VAR_TEMP_1, 0, MauvilleCity_GameCorner_EventScript_RemoveMoneyFreshWater
	call_if_eq VAR_TEMP_1, 1, MauvilleCity_GameCorner_EventScript_RemoveMoneySodaPop
	call_if_eq VAR_TEMP_1, 2, MauvilleCity_GameCorner_EventScript_RemoveMoneyLemonade
	updatemoneybox
	bufferitemname STR_VAR_1, VAR_TEMP_0
	playse SE_VEND
	msgbox MauvilleCity_GameCorner_Text_CanOfDrinkDroppedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname STR_VAR_2, VAR_TEMP_0
	bufferstdstring STR_VAR_3, STDSTRING_ITEMS
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	random 64
	goto_if_ne VAR_RESULT, 0, MauvilleCity_GameCorner_EventScript_ChooseNewDrink
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDrink
	playse SE_VEND
	msgbox MauvilleCity_GameCorner_Text_ExtraCanOfDrinkDroppedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname STR_VAR_2, VAR_TEMP_0
	bufferstdstring STR_VAR_3, STDSTRING_ITEMS
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	random 64
	goto_if_ne VAR_RESULT, 0, MauvilleCity_GameCorner_EventScript_ChooseNewDrink
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, 0, MauvilleCity_GameCorner_EventScript_NoRoomForDrink
	playse SE_VEND
	msgbox MauvilleCity_GameCorner_Text_ExtraCanOfDrinkDroppedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname STR_VAR_2, VAR_TEMP_0
	bufferstdstring STR_VAR_3, STDSTRING_ITEMS
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ChooseNewDrink
	end

MauvilleCity_GameCorner_EventScript_ChooseNewDrink::
	message MauvilleCity_GameCorner_Text_WhichDrinkWouldYouLike
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChooseDrink
	end

MauvilleCity_GameCorner_EventScript_NotEnoughMoneyForDrink::
	msgbox MauvilleCity_GameCorner_Text_NotEnoughMoney, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ExitVendingMachine
	end

MauvilleCity_GameCorner_EventScript_NoRoomForDrink::
	msgbox gText_TheBagIsFull, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ExitVendingMachine
	end

MauvilleCity_GameCorner_EventScript_ExitVendingMachine::
	hidemoneybox
	releaseall
	end

MauvilleCity_GameCorner_EventScript_CancelTMSelect::
	msgbox MauvilleCity_GameCorner_Text_OhIsThatSo, MSGBOX_DEFAULT
	hidecoinsbox 0, 0
	release
	end

MauvilleCity_GameCorner_EventScript_Woman2::
	msgbox MauvilleCity_GameCorner_Text_CoinsAreNeededToPlay, MSGBOX_NPC
	end
	
MauvilleCity_GameCorner_EventScript_Dealer::
	msgbox MauvilleCity_GameCorner_Text_Dealer, MSGBOX_NPC
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end
	
MauvilleCity_GameCorner_EventScript_Dealer2::
	msgbox MauvilleCity_GameCorner_Text_Dealer2, MSGBOX_NPC
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end	
	
MauvilleCity_GameCorner_EventScript_VFGuy1::
	msgbox MauvilleCity_GameCorner_Text_VFGuy1, MSGBOX_NPC
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end		
	
MauvilleCity_GameCorner_EventScript_VFGuy2::
	msgbox MauvilleCity_GameCorner_Text_VFGuy2, MSGBOX_NPC
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end			

MauvilleCity_GameCorner_EventScript_Gentleman::
	msgbox MauvilleCity_GameCorner_Text_RouletteOnlyLuck, MSGBOX_NPC
	end

MauvilleCity_GameCorner_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_STARTER_DOLL, MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
	msgbox MauvilleCity_GameCorner_Text_GotTwoOfSameDollWantOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_DeclineStarterDoll
	switch VAR_STARTER_MON
	case 0, MauvilleCity_GameCorner_EventScript_GiveTreeckoDoll
	case 1, MauvilleCity_GameCorner_EventScript_GiveTorchicDoll
	case 2, MauvilleCity_GameCorner_EventScript_GiveMudkipDoll
	end

MauvilleCity_GameCorner_EventScript_GiveTreeckoDoll::
	bufferdecorationname STR_VAR_2, DECOR_TREECKO_DOLL
	checkdecorspace DECOR_TREECKO_DOLL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
	givedecoration DECOR_TREECKO_DOLL
	setflag FLAG_RECEIVED_STARTER_DOLL
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
	end

MauvilleCity_GameCorner_EventScript_GiveTorchicDoll::
	bufferdecorationname STR_VAR_2, DECOR_TORCHIC_DOLL
	checkdecorspace DECOR_TORCHIC_DOLL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
	givedecoration DECOR_TORCHIC_DOLL
	setflag FLAG_RECEIVED_STARTER_DOLL
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
	end

MauvilleCity_GameCorner_EventScript_GiveMudkipDoll::
	bufferdecorationname STR_VAR_2, DECOR_MUDKIP_DOLL
	checkdecorspace DECOR_MUDKIP_DOLL
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
	givedecoration DECOR_MUDKIP_DOLL
	setflag FLAG_RECEIVED_STARTER_DOLL
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
	end

MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll::
	call Common_EventScript_NoRoomForDecor
	msgbox MauvilleCity_GameCorner_Text_YouWantItButNotNow, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_DeclineStarterDoll::
	msgbox MauvilleCity_GameCorner_Text_DontBeNegative, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll::
	msgbox MauvilleCity_GameCorner_Text_CantWinJackpot, MSGBOX_DEFAULT
	release
	end

MauvilleCity_GameCorner_EventScript_PokefanM::
	lock
	faceplayer
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_TryGive20Coins
	msgbox MauvilleCity_GameCorner_Text_NeedCoinCaseGoNextDoor, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_TryGive20Coins::
	goto_if_set FLAG_RECEIVED_20_COINS, MauvilleCity_GameCorner_EventScript_PokefanMNormal
	checkcoins VAR_TEMP_1
	goto_if_ge VAR_TEMP_1, 1, MauvilleCity_GameCorner_EventScript_PokefanMNormal @ Only give 20 coins if player has no coins
	setflag FLAG_RECEIVED_20_COINS
	addcoins 20
	msgbox MauvilleCity_GameCorner_Text_LuckOnlyLastSoLongTakeCoins, MSGBOX_DEFAULT
	playse SE_SHOP
	goto MauvilleCity_GameCorner_EventScript_PokefanMNormal
	end

MauvilleCity_GameCorner_EventScript_PokefanMNormal::
	msgbox MauvilleCity_GameCorner_Text_MauvilleSomethingForEveryone, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_OldMan::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_RouletteTablesDifferentRates, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end
	
MauvilleCity_GameCorner_EventScript_PachinkoGuy::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_PachinkoGuy, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end	
	
MauvilleCity_GameCorner_EventScript_Hiker::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Hiker, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end		

MauvilleCity_GameCorner_EventScript_Bouncer::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Bouncer2, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end		
	
MauvilleCity_GameCorner_EventScript_DerbyLady1::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Derby_1, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end			
	
MauvilleCity_GameCorner_EventScript_DerbyLady2::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Derby_2, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end			

MauvilleCity_GameCorner_EventScript_Fisherman::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Fisherman, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end			
	
MauvilleCity_GameCorner_EventScript_Gachalady::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Gachalady, MSGBOX_DEFAULT
	closemessage
	end			

MauvilleCity_GameCorner_EventScript_Employee::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Employee, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end			

MauvilleCity_GameCorner_EventScript_Cook::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_EasyToLoseTrackOfTime, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_Man::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_UpTo3CoinsCanBeUsed, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_JuiceLady::	
	lock
	faceplayer
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase2
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Juice, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 10, Juice_Not_Enough
	removecoins 10
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	giveitem ITEM_BERRY_JUICE
	release
	end

MauvilleCity_GameCorner_EventScript_NPCReturnToSlots::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_GameCorner_EventScript_Maniac::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_DifficultToStopOn7, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_Woman::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_HeresSomeSlotsInfo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end

MauvilleCity_GameCorner_EventScript_SlotMachine0::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetSlotMachineId
	nop // playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine1::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, GetSlotMachineId
	nop // playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine2::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 2
	specialvar VAR_RESULT, GetSlotMachineId
	nop // playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine3::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 3
	specialvar VAR_RESULT, GetSlotMachineId
	nop // playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine4::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 4
	specialvar VAR_RESULT, GetSlotMachineId
	nop // playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine5::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 5
	specialvar VAR_RESULT, GetSlotMachineId
	nop // playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine6::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 6
	specialvar VAR_RESULT, GetSlotMachineId
	nop // playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine7::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 7
	specialvar VAR_RESULT, GetSlotMachineId
	nop // playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine8::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 8
	specialvar VAR_RESULT, GetSlotMachineId
	nop // playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine9::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 9
	specialvar VAR_RESULT, GetSlotMachineId
	nop // playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine10::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 10
	specialvar VAR_RESULT, GetSlotMachineId
	nop // playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_SlotMachine11::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 11
	specialvar VAR_RESULT, GetSlotMachineId
	nop // playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_NoCoinCase::
	msgbox MauvilleCity_GameCorner_Text_CantPlayWithNoCoinCase, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_GameCorner_EventScript_NoCoinCase2::
	msgbox MauvilleCity_GameCorner_Text_CantBuyWithNoCoinCase, MSGBOX_DEFAULT
	releaseall
	end	

MauvilleCity_GameCorner_Text_ThisIsMauvilleGameCorner:
	.string "This is MAUVILLE GAME CORNER.$"

MauvilleCity_GameCorner_Text_PachinkoGuy:
	.string "I used to own one of these dusty old\n"
	.string "DROPSPIN MACHINES.\p"
	.string "The manual always said 'Use the\n"
	.string "DIRECTIONAL BUTTONS to TILT and\l"
	.string "change the DROP SPEED…'\p"
	.string "I've always wondered what that\n"
	.string "means.$"

MauvilleCity_GameCorner_Text_Hiker:
	.string "Gah!\n"
	.string "I blew it all on that ONIX game.\p"
	.string "You need to be careful…\p"
	.string "You only win 2 COINS for\n"
	.string "every point in these machines.$"
	
MauvilleCity_GameCorner_Text_Derby_1:
	.string "Looking to bet on the DERBY?\n"
	.string "We've gone digital!\p"
	.string "Use one of the tablets\n"
	.string "in front of the counter.$"	
	
MauvilleCity_GameCorner_Text_Derby_2:
	.string "It's not all about CONDITION.\p"
	.string "At the end of the day, it's\n"
	.string "really all luck.\p"
	.string "Sometimes it's best to just\n"
	.string "pick your favorite!$"	
	
MauvilleCity_GameCorner_Text_Fisherman:
	.string "I come here for the food.\p"
	.string "It's no CELADON CAFE…\n"
	.string "But it'll do.$"		
	
MauvilleCity_GameCorner_Text_Gachalady:
	.string "The LOTTERY MACHINES have odds,\n"
	.string "but nothing is guaranteed.\p"
	.string "Some machines are better than\n"
	.string "others, and there are different\l"
	.string "rarities in all of them.\p"
	.string "New POKéMON are also weighted\n"
	.string "By your POKéDEX, so be wary.$"	
	
MauvilleCity_GameCorner_Text_Employee:
	.string "I'm on the lookout for cheaters.\n"
	.string "Nobody likes a cheater!$"
	
MauvilleCity_GameCorner_Text_Bouncer1:
	.string "You need a valid TRAINER ID\n"
	.string "to enter the GAME CORNER.\p"
	.string "Let's see…\p"
	.string "…\p"
	.string "Hmm…\p"
	.string "…\p"
	.string "Everything looks good here.\n"
	.string "Enjoy the GAME CORNER!$"	
	
MauvilleCity_GameCorner_Text_Bouncer2:
	.string "Enjoy the GAME CORNER!$"	
	
MauvilleCity_GameCorner_Text_Pachinko:
	.string "A DROPSPIN MACHINE!\n"
	.string "It's 3 COINS per BALL.$"
	
MauvilleCity_GameCorner_Text_NeedCoinCaseForCoins:
	.string "Okay, you wanted some COINS for\n"
	.string "the games?\p"
	.string "But you don't have a COIN CASE for\n"
	.string "stowing the COINS.$"

MauvilleCity_GameCorner_Text_WereYouLookingForCoins:
	.string "Were you looking for COINS?\p"
	.string "It's ¥1000 for 50 COINS.\n"
	.string "Would you like some?$"

MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins:
	.string "Thank you very much!\n"
	.string "Here are your COINS!$"

MauvilleCity_GameCorner_Text_DontHaveEnoughMoney:
	.string "Um… You don't appear to have\n"
	.string "enough money…$"

MauvilleCity_GameCorner_Text_CoinCaseIsFull:
	.string "Oh?\n"
	.string "Your COIN CASE is full.$"

MauvilleCity_GameCorner_Text_DontNeedCoinsThen:
	.string "Oh… You don't need COINS, then?\n"
	.string "Good luck on your adventure!$"

MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes:
	.string "Welcome.\p"
	.string "You can exchange your COINS for\n"
	.string "prizes here.$"

MauvilleCity_GameCorner_Text_WhichPrize:
	.string "Which prize would you like?$"

MauvilleCity_GameCorner_Text_PrizeTMDoubleTeam:
	.string "Double Team{CLEAR_TO 0x54}1,500 C.$"

MauvilleCity_GameCorner_Text_PrizeTMFirePunch:
	.string "Fire Punch{CLEAR_TO 0x54}3,000 C.$"

MauvilleCity_GameCorner_Text_PrizeTMThunderPunch:
	.string "Thunder Punch{CLEAR_TO 0x54}3,000 C.$"

MauvilleCity_GameCorner_Text_PrizeTMIcePunch:
	.string "Ice Punch{CLEAR_TO 0x54}3,000 C.$"

MauvilleCity_GameCorner_Text_PrizeTMPsychic:
	.string "Psychic{CLEAR_TO 0x54}3,500 C.$"

MauvilleCity_GameCorner_Text_PrizeTMFlashCannon:
	.string "Flash Cannon{CLEAR_TO 0x54}3,700 C.$"

MauvilleCity_GameCorner_Text_PrizeTMDazzlingGleam:
	.string "Dazzling Gleam{CLEAR_TO 0x54}3,700 C.$"

MauvilleCity_GameCorner_Text_PrizeTMWilloWisp:
	.string "Will-O-Wisp{CLEAR_TO 0x54}3,800 C.$"

MauvilleCity_GameCorner_Text_PrizeTMThunderWave:
	.string "Thunder Wave{CLEAR_TO 0x54}3,800 C.$"

MauvilleCity_GameCorner_Text_PrizeTMFlamethrower:
	.string "Flamethrower{CLEAR_TO 0x54}4,000 C.$"

MauvilleCity_GameCorner_Text_PrizeTMThunderbolt:
	.string "Thunderbolt{CLEAR_TO 0x54}4,000 C.$"

MauvilleCity_GameCorner_Text_PrizeTMIceBeam:
	.string "Ice Beam{CLEAR_TO 0x54}4,000 C.$"

MauvilleCity_GameCorner_Text_PrizeTMEarthPower:
	.string "Earth Power{CLEAR_TO 0x54}4,000 C.$"

MauvilleCity_GameCorner_Text_PrizeFireStone:
	.string "Fire Stone{CLEAR_TO 0x54}1,400 C.$"

MauvilleCity_GameCorner_Text_PrizeThunderStone:
	.string "Thunder Stone{CLEAR_TO 0x54}1,400 C.$"

MauvilleCity_GameCorner_Text_PrizeWaterStone:
	.string "Water Stone{CLEAR_TO 0x54}1,400 C.$"

MauvilleCity_GameCorner_Text_PrizeLeafStone:
	.string "Leaf Stone{CLEAR_TO 0x54}1,400 C.$"

MauvilleCity_GameCorner_Text_PrizeIceStone:
	.string "Ice Stone{CLEAR_TO 0x54}1,400 C.$"

MauvilleCity_GameCorner_Text_PrizeSunStone:
	.string "Sun Stone{CLEAR_TO 0x54}1,400 C.$"

MauvilleCity_GameCorner_Text_PrizeMoonStone:
	.string "Moon Stone{CLEAR_TO 0x54}1,400 C.$"

MauvilleCity_GameCorner_Text_PrizeShinyStone:
	.string "Shiny Stone{CLEAR_TO 0x54}1,400 C.$"

MauvilleCity_GameCorner_Text_PrizeDuskStone:
	.string "Dusk Stone{CLEAR_TO 0x54}1,400 C.$"

MauvilleCity_GameCorner_Text_PrizeDawnStone:
	.string "Dawn Stone{CLEAR_TO 0x54}1,400 C.$"

MauvilleCity_GameCorner_Text_PrizeLinkingCord:
	.string "Linking Cord{CLEAR_TO 0x54}1,500 C.$"

MauvilleCity_GameCorner_Text_PrizeSootheBell:
	.string "Soothe Bell{CLEAR_TO 0x54}1,200 C.$"

MauvilleCity_GameCorner_Text_PrizeExpertBelt:
	.string "Expert Belt{CLEAR_TO 0x54}1,600 C.$"

MauvilleCity_GameCorner_Text_PrizePunchingGlove:
	.string "Punching Glove{CLEAR_TO 0x54}1,700 C.$"

MauvilleCity_GameCorner_Text_PrizeWideLens:
	.string "Wide Lens{CLEAR_TO 0x54}1,700 C.$"

MauvilleCity_GameCorner_Text_PrizeThickClub:
	.string "Thick Club{CLEAR_TO 0x54}1,800 C.$"

MauvilleCity_GameCorner_Text_PrizeMuscleBand:
	.string "Muscle Band{CLEAR_TO 0x54}1,800 C.$"

MauvilleCity_GameCorner_Text_PrizeWiseGlasses:
	.string "Wise Glasses{CLEAR_TO 0x54}1,800 C.$"

MauvilleCity_GameCorner_Text_PrizeFocusSash:
	.string "Focus Sash{CLEAR_TO 0x54}2,400 C.$"

MauvilleCity_GameCorner_Text_PrizeEviolite:
	.string "Eviolite{CLEAR_TO 0x54}2,700 C.$"

MauvilleCity_GameCorner_Text_PrizeAssaultVest:
	.string "Assault Vest{CLEAR_TO 0x54}2,800 C.$"

MauvilleCity_GameCorner_Text_PrizeRockyHelmet:
	.string "Rocky Helmet{CLEAR_TO 0x54}3,000 C.$"

MauvilleCity_GameCorner_Text_PrizeLeftovers:
	.string "Leftovers{CLEAR_TO 0x54}3,500 C.$"

MauvilleCity_GameCorner_Text_PrizeLoadedDice:
	.string "Loaded Dice{CLEAR_TO 0x54}3,600 C.$"

MauvilleCity_GameCorner_Text_PrizeLifeOrb:
	.string "Life Orb{CLEAR_TO 0x54}3,800 C.$"

MauvilleCity_GameCorner_Text_PrizeBottleCap:
	.string "Bottle Cap{CLEAR_TO 0x54}2,300 C.$"

MauvilleCity_GameCorner_Text_PrizeGoldBottleCap:
	.string "Gold Bottle Cap{CLEAR_TO 0x54}7,000 C.$"

MauvilleCity_GameCorner_Text_PrizeAbra:
	.string "Abra{CLEAR_TO 0x54}1,500 C.$"

MauvilleCity_GameCorner_Text_PrizeCubone:
	.string "Cubone{CLEAR_TO 0x54}1,800 C.$"

MauvilleCity_GameCorner_Text_PrizeRalts:
	.string "Ralts{CLEAR_TO 0x54}3,200 C.$"

MauvilleCity_GameCorner_Text_PrizeDratini:
	.string "Dratini{CLEAR_TO 0x54}5,500 C.$"

MauvilleCity_GameCorner_Text_PrizeBagon:
	.string "Bagon{CLEAR_TO 0x54}5,500 C.$"

MauvilleCity_GameCorner_Text_PrizeLarvitar:
	.string "Larvitar{CLEAR_TO 0x54}5,000 C.$"

MauvilleCity_GameCorner_Text_PrizeLarvesta:
	.string "Larvesta{CLEAR_TO 0x54}5,200 C.$"

MauvilleCity_GameCorner_Text_PrizeDreepy:
	.string "Dreepy{CLEAR_TO 0x54}6,000 C.$"

MauvilleCity_GameCorner_Text_PrizeScyther:
	.string "Scyther{CLEAR_TO 0x54}4,800 C.$"

MauvilleCity_GameCorner_Text_PrizeFrigibax:
	.string "Frigibax{CLEAR_TO 0x54}6,300 C.$"

MauvilleCity_GameCorner_Text_PrizeBeldum:
	.string "Beldum{CLEAR_TO 0x54}8,000 C.$"

MauvilleCity_GameCorner_Text_PrizePorygon:
	.string "Porygon{CLEAR_TO 0x54}9,999 C.$"

MauvilleCity_GameCorner_Text_PrizeExit:
	.string "EXIT$"

MauvilleCity_GameCorner_Text_SoYourChoiceIsTheTMX:
	.string "So your choice is\n"
	.string "the {STR_VAR_1} {STR_VAR_2}?$"
	
MauvilleCity_GameCorner_Text_SoYourChoiceIsTheNewX:
	.string "So your choice is\n"
	.string "the {STR_VAR_1}?$"

MauvilleCity_GameCorner_Text_SoYourChoiceIsThisPokemon:
	.string "So your choice is {STR_VAR_1}?$"

MauvilleCity_GameCorner_Text_BottleCapClerkFirst:
	.string "Gaaahh...!\n"
	.string "I lost almost all my COINS...$"

MauvilleCity_GameCorner_Text_BottleCapClerkOffer:
	.string "Yo! You got COINS?\p"
	.string "I'll trade you these BOTTLE CAPS\n"
	.string "for them!$"

MauvilleCity_GameCorner_Text_BottleCapClerkStandard:
	.string "Yo! You got COINS?\p"
	.string "I'll trade you BOTTLE CAPS\n"
	.string "for them!$"

MauvilleCity_GameCorner_Text_BottleCapClerkWhichCap:
	.string "Which BOTTLE CAP do you want?$"

MauvilleCity_GameCorner_Text_BottleCapClerkComeBack:
	.string "That's it?\n"
	.string "Fine, I'll get some new COINS ...$"

MauvilleCity_GameCorner_Text_WhichDrinkWouldYouLike:
	.string "It's a VENDING MACHINE.\n"
	.string "Which drink would you like?$"

MauvilleCity_GameCorner_Text_CanOfDrinkDroppedDown:
	.string "Clang!\p"
	.string "A can of {STR_VAR_1} dropped down.$"

MauvilleCity_GameCorner_Text_ExtraCanOfDrinkDroppedDown:
	.string "Clang!\p"
	.string "Score! An extra can of {STR_VAR_1}\n"
	.string "dropped down!$"

MauvilleCity_GameCorner_Text_NotEnoughMoney:
	.string "Not enough money...$"

MauvilleCity_GameCorner_Text_DecidedAgainstBuyingDrink:
	.string "Decided against buying a drink.$"

MauvilleCity_GameCorner_Text_BlackJack:
	.string "It's a BLACKJACK TABLE!\n"
	.string "Want to play?$"
	
MauvilleCity_GameCorner_Text_Derby:
	.string "It's the MAUVILLE DERBY!\n"
	.string "Want to place a bet?$"	
	
MauvilleCity_GameCorner_Text_Snake:
	.string "It's ONIX!\n"
	.string "It costs 25 COINS to play.$"		
	
MauvilleCity_GameCorner_Text_Bird:
	.string "It's FLUTTERFREE!\n"
	.string "It costs 25 COINS to play.$"		
	
MauvilleCity_GameCorner_Text_Pinball_Meowth:
	.string "It's a PINBALL MACHINE!\n"
	.string "It costs 25 COINS to play.$"

MauvilleCity_GameCorner_Text_BS:
	.string "It's BLOCK BUILDER!\n"
	.string "It costs 25 COINS to play.$"
	
MauvilleCity_GameCorner_Text_Pinball_Seel:
	.string "It's a PINBALL MACHINE!\n"
	.string "It costs 25 COINS to play.$"
	
MauvilleCity_GameCorner_Text_Pinball_Diglett:
	.string "It's a PINBALL MACHINE!\n"
	.string "It costs 50 COINS to play.$"
	
MauvilleCity_GameCorner_Text_Pinball_Gengar:
	.string "It's a PINBALL MACHINE!\n"
	.string "It costs 100 COINS to play.$"
	
MauvilleCity_GameCorner_Text_VF:
	.string "It's VOLTORB FLIP!\n"
	.string "It costs 50 COINS to play.$"

VF_Come_Again_Text:
	.string "Too bad.\n"
	.string "Try again soon!$"

MauvilleCity_GameCorner_Text_SendToYourHomePC:
	.string "Thank you!\n"
	.string "We'll send it to your PC at home.$"

MauvilleCity_GameCorner_Text_NotEnoughCoins:
	.string "You don't have enough COINS.$"

PB_YOU_WON_TEXT:
	.string "You won\n"
	.string "{STR_VAR_1} COINS!$"

PB_Not_Enough:
	.string "It's a PINBALL MACHINE!\p"
	.string "You don't have enough COINS…$"
	
Snake_Not_Enough:
	.string "It's ONIX!\p"
	.string "You don't have enough COINS…$"	
	
Bjuice_Not_Enough:
	.string "You don't have enough COINS.$"	
	
Bird_Not_Enough:
	.string "It's FLUTTERFREE!\p"
	.string "You don't have enough COINS…$"		
	
BS_Not_Enough:
	.string "It's BLOCK BUILDER!\p"
	.string "You don't have enough COINS…$"	

Flip_Not_Enough:
	.string "It's VOLTORB FLIP!\p"
	.string "You don't have enough COINS…$"

@ Unused
MauvilleCity_GameCorner_Text_NoRoomForPlacingDecor:
	.string "There isn't any room available for\n"
	.string "placing {STR_VAR_1}.$"
	
MauvilleCity_GameCorner_Text_VF_Keep_Going:
	.string "You've made {STR_VAR_1} COINS.\n"
	.string "Keep going?$"

MauvilleCity_GameCorner_Text_OhIsThatSo:
	.string "Oh, is that so? \n"
	.string "You need to save some COINS before\l"
	.string "coming back here.$"

MauvilleCity_GameCorner_Text_SoYourChoiceIsX:
	.string "So your choice is {STR_VAR_1}?$"

MauvilleCity_GameCorner_Text_HereYouGo:
	.string "Here you go!$"

@ Unused
MauvilleCity_GameCorner_Text_CantCarryAnyMore:
	.string "Oh, you can't carry any more than that.$"

MauvilleCity_GameCorner_Text_GotTwoOfSameDollWantOne:
	.string "I made a mistake and got two of\n"
	.string "the same DOLLS.\p"
	.string "Would you like one of them?$"

MauvilleCity_GameCorner_Text_HereYouGo2:
	.string "Here you go!$"

MauvilleCity_GameCorner_Text_YouWantItButNotNow:
	.string "Huh?\n"
	.string "You want it, but not right now?$"

MauvilleCity_GameCorner_Text_DontBeNegative:
	.string "Oh, don't be so negative!\n"
	.string "You can have this!$"

MauvilleCity_GameCorner_Text_CantWinJackpot:
	.string "There's a prize I want, but I can't win\n"
	.string "the jackpot.$"

MauvilleCity_GameCorner_Text_NeedCoinCaseGoNextDoor:
	.string "Hey, kid, if you want to play here,\n"
	.string "you need a COIN CASE.\p"
	.string "I think the young lady next door\n"
	.string "had one. Go see her!$"

MauvilleCity_GameCorner_Text_LuckOnlyLastSoLongTakeCoins:
	.string "My luck can only last so long.\n"
	.string "This is too much for me.\l"
	.string "Here, take some COINS!$"

MauvilleCity_GameCorner_Text_MauvilleSomethingForEveryone:
	.string "MAUVILLE has something for\n"
	.string "everyone.\p"
	.string "For me, it's the GAME CORNER.$"

MauvilleCity_GameCorner_Text_RouletteTablesDifferentRates:
	.string "The ROULETTE tables have different\n"
	.string "rates.\p"
	.string "Check your COINS if you're going to\n"
	.string "pick a table.$"

MauvilleCity_GameCorner_Text_EasyToLoseTrackOfTime:
	.string "It's easy to lose track of time in here. \n"
	.string "I should get back to work.$"

MauvilleCity_GameCorner_Text_CoinsAreNeededToPlay:
	.string "COINS are needed to play here\n"
	.string "in the GAME CORNER.$"
	
	MauvilleCity_GameCorner_Text_Dealer:
	.string "Some say BLACKJACK is about skill.\n"
	.string "Others say it's about luck.\p"
	.string "I say it's about having fun…\n"
	.string "and maybe winning big!$"
	
	MauvilleCity_GameCorner_Text_Dealer2:
	.string "You can bet anything divisible\n"
	.string "by 10 here.\p"
	.string "Maybe you should go all in!$"	

MauvilleCity_GameCorner_Text_VFGuy1:
	.string "You want to play VOLTORB FLIP?\p"
	.string "You need to be on the other\n"
	.string "side of the table.$"
	
MauvilleCity_GameCorner_Text_VFGuy2:
	.string "Try the other side of\n"
	.string "the table, pal.$"	

MauvilleCity_GameCorner_Text_RouletteOnlyLuck:
	.string "This ROULETTE thing…\n"
	.string "It's rather demanding.\p"
	.string "Win or lose, it's only by luck.$"

MauvilleCity_GameCorner_Text_UpTo3CoinsCanBeUsed:
	.string "Up to three COINS can be used to play\n"
	.string "the SLOTS.$"

MauvilleCity_GameCorner_Text_DifficultToStopOn7:
	.string "It's very difficult to make it stop\n"
	.string "right on “7.”\p"
	.string "If it stops on “7” during the REEL TIME\n"
	.string "bonus game, you'll receive extra COINS.$"

MauvilleCity_GameCorner_Text_HeresSomeSlotsInfo:
	.string "Here's some information for you\n"
	.string "about the SLOTS.\p"
	.string "The more lightning bolts you stock,\n"
	.string "the more REEL TIME chances you get.\p"
	.string "In a game with the maximum five\n"
	.string "REEL TIME chances…\p"
	.string "It is possible to receive four regular\n"
	.string "bonuses, then a big bonus.\p"
	.string "That would total 660 COINS, but it's\n"
	.string "very difficult to get.$"

MauvilleCity_GameCorner_Text_CantPlayWithNoCoinCase:
	.string "You can't play if you don't have\n"
	.string "a COIN CASE.$"

MauvilleCity_GameCorner_Text_CantBuyWithNoCoinCase:
	.string "Huh? Looks like you need\n"
	.string "a COIN CASE.$"
	
MauvilleCity_GameCorner_Text_Juice:
	.string "BERRY JUICE!\n"
	.string "Just 10 COINS.$"	
