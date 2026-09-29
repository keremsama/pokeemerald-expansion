BattleFrontier_Lounge7_MapScripts::
	.byte 0

BattleFrontier_Lounge7_EventScript_LeftMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_1
	goto_if_set FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor
	msgbox BattleFrontier_Lounge7_Text_LeftTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor::
	msgbox BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide
	case 7, BattleFrontier_Lounge7_EventScript_Counter
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide
	case 7, BattleFrontier_Lounge7_EventScript_Counter
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_Softboiled::
	setvar VAR_0x8008, 11
	setvar VAR_0x8005, MOVE_SOFT_BOILED
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SeismicToss::
	setvar VAR_0x8008, 16
	setvar VAR_0x8005, MOVE_SEISMIC_TOSS
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_DreamEater::
	setvar VAR_0x8008, 16
	setvar VAR_0x8005, MOVE_DREAM_EATER
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MegaPunch::
	setvar VAR_0x8008, 16
	setvar VAR_0x8005, MOVE_MEGA_PUNCH
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MegaKick::
	setvar VAR_0x8008, 32
	setvar VAR_0x8005, MOVE_MEGA_KICK
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_BodySlam::
	setvar VAR_0x8008, 32
	setvar VAR_0x8005, MOVE_BODY_SLAM
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_RockSlide::
	setvar VAR_0x8008, 32
	setvar VAR_0x8005, MOVE_ROCK_SLIDE
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Counter::
	setvar VAR_0x8008, 32
	setvar VAR_0x8005, MOVE_COUNTER
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ThunderWave::
	setvar VAR_0x8008, 40
	setvar VAR_0x8005, MOVE_THUNDER_WAVE
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SwordsDance::
	setvar VAR_0x8008, 40
	setvar VAR_0x8005, MOVE_SWORDS_DANCE
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_RightMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_2
	goto_if_set FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor
	msgbox BattleFrontier_Lounge7_Text_RightTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor::
	msgbox BattleFrontier_Lounge7_Text_RightTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind
	case 5, BattleFrontier_Lounge7_EventScript_Endure
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind
	case 5, BattleFrontier_Lounge7_EventScript_Endure
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_DefenseCurl::
	setvar VAR_0x8008, 11
	setvar VAR_0x8005, MOVE_DEFENSE_CURL
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Snore::
	setvar VAR_0x8008, 11
	setvar VAR_0x8005, MOVE_SNORE
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MudSlap::
	setvar VAR_0x8008, 11
	setvar VAR_0x8005, MOVE_MUD_SLAP
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Swift::
	setvar VAR_0x8008, 11
	setvar VAR_0x8005, MOVE_SWIFT
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_IcyWind::
	setvar VAR_0x8008, 16
	setvar VAR_0x8005, MOVE_ICY_WIND
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Endure::
	setvar VAR_0x8008, 32
	setvar VAR_0x8005, MOVE_ENDURE
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_PsychUp::
	setvar VAR_0x8008, 32
	setvar VAR_0x8005, MOVE_PSYCH_UP
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_IcePunch::
	setvar VAR_0x8008, 32
	setvar VAR_0x8005, MOVE_ICE_PUNCH
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ThunderPunch::
	setvar VAR_0x8008, 32
	setvar VAR_0x8005, MOVE_THUNDER_PUNCH
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_FirePunch::
	setvar VAR_0x8008, 32
	setvar VAR_0x8005, MOVE_FIRE_PUNCH
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_OldManMoveTutor::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge7_Text_OldManTutorIntro, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseOldManTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseOldManTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	goto BattleFrontier_Lounge7_EventScript_ChooseNewOldManTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseNewOldManTutorMove::
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 2
	dynmultipush BattleFrontier_Lounge7_Text_PrizeRapidSpin, MOVE_RAPID_SPIN
	dynmultipush BattleFrontier_Lounge7_Text_PrizeFakeOut, MOVE_FAKE_OUT
	dynmultipush BattleFrontier_Lounge7_Text_PrizeEncore, MOVE_ENCORE
	dynmultipush BattleFrontier_Lounge7_Text_PrizeFlipTurn, MOVE_FLIP_TURN
	dynmultipush BattleFrontier_Lounge7_Text_PrizeVoltSwitch, MOVE_VOLT_SWITCH
	dynmultipush BattleFrontier_Lounge7_Text_PrizeTrick, MOVE_TRICK
	dynmultipush BattleFrontier_Lounge7_Text_PrizeTailwind, MOVE_TAILWIND
	dynmultipush BattleFrontier_Lounge7_Text_PrizeSpikes, MOVE_SPIKES
	dynmultipush BattleFrontier_Lounge7_Text_PrizeLiquidation, MOVE_LIQUIDATION
	dynmultipush BattleFrontier_Lounge7_Text_PrizeIronHead, MOVE_IRON_HEAD
	dynmultipush BattleFrontier_Lounge7_Text_PrizePsyshock, MOVE_PSYSHOCK
	dynmultipush BattleFrontier_Lounge7_Text_PrizeKnockOff, MOVE_KNOCK_OFF
	dynmultipush BattleFrontier_Lounge7_Text_PrizeStickyWeb, MOVE_STICKY_WEB
	dynmultipush BattleFrontier_Lounge7_Text_PrizeBodyPress, MOVE_BODY_PRESS
	dynmultipush BattleFrontier_Lounge7_Text_PrizeHeatWave, MOVE_HEAT_WAVE
	dynmultipush BattleFrontier_Lounge7_Text_PrizeScaleShot, MOVE_SCALE_SHOT
	dynmultipush BattleFrontier_Lounge7_Text_PrizeGunkShot, MOVE_GUNK_SHOT
	dynmultipush BattleFrontier_Lounge7_Text_PrizeHighHorsepower, MOVE_HIGH_HORSEPOWER
	dynmultipush BattleFrontier_Lounge7_Text_PrizePoltergeist, MOVE_POLTERGEIST
	dynmultipush BattleFrontier_Lounge7_Text_PrizeDracoMeteor, MOVE_DRACO_METEOR
	dynmultipush BattleFrontier_Lounge7_Text_PrizeExit, MOVE_NONE
	dynmultistack 14, 0, FALSE, 6, FALSE, MOVE_RAPID_SPIN, DYN_MULTICHOICE_CB_SHOW_MOVE_DESC_LEFT
	switch VAR_RESULT
	case MOVE_NONE, BattleFrontier_Lounge7_EventScript_ExitDynamicTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitDynamicTutorMoveSelect
	copyvar VAR_0x8005, VAR_RESULT
	call BattleFrontier_Lounge7_EventScript_SetDynamicTutorMovePrice
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_YoungsterMoveTutor::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge7_Text_YoungsterTutorIntro, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseYoungsterTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseYoungsterTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	goto BattleFrontier_Lounge7_EventScript_ChooseNewYoungsterTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseNewYoungsterTutorMove::
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 3
	dynmultipush BattleFrontier_Lounge7_Text_PrizeAquaJet, MOVE_AQUA_JET
	dynmultipush BattleFrontier_Lounge7_Text_PrizeShadowSneak, MOVE_SHADOW_SNEAK
	dynmultipush BattleFrontier_Lounge7_Text_PrizeIceShard, MOVE_ICE_SHARD
	dynmultipush BattleFrontier_Lounge7_Text_PrizeNuzzle, MOVE_NUZZLE
	dynmultipush BattleFrontier_Lounge7_Text_PrizeSuckerPunch, MOVE_SUCKER_PUNCH
	dynmultipush BattleFrontier_Lounge7_Text_PrizeLeechSeed, MOVE_LEECH_SEED
	dynmultipush BattleFrontier_Lounge7_Text_PrizeSynthesis, MOVE_SYNTHESIS
	dynmultipush BattleFrontier_Lounge7_Text_PrizeToxicSpikes, MOVE_TOXIC_SPIKES
	dynmultipush BattleFrontier_Lounge7_Text_PrizeFutureSight, MOVE_FUTURE_SIGHT
	dynmultipush BattleFrontier_Lounge7_Text_PrizeDrainingKiss, MOVE_DRAINING_KISS
	dynmultipush BattleFrontier_Lounge7_Text_PrizeBulletPunch, MOVE_BULLET_PUNCH
	dynmultipush BattleFrontier_Lounge7_Text_PrizePartingShot, MOVE_PARTING_SHOT
	dynmultipush BattleFrontier_Lounge7_Text_PrizeWideGuard, MOVE_WIDE_GUARD
	dynmultipush BattleFrontier_Lounge7_Text_PrizeFirstImpression, MOVE_FIRST_IMPRESSION
	dynmultipush BattleFrontier_Lounge7_Text_PrizeFreezeDry, MOVE_FREEZE_DRY
	dynmultipush BattleFrontier_Lounge7_Text_PrizeMysticalFire, MOVE_MYSTICAL_FIRE
	dynmultipush BattleFrontier_Lounge7_Text_PrizeFlareBlitz, MOVE_FLARE_BLITZ
	dynmultipush BattleFrontier_Lounge7_Text_PrizeBraveBird, MOVE_BRAVE_BIRD
	dynmultipush BattleFrontier_Lounge7_Text_PrizeHeavySlam, MOVE_HEAVY_SLAM
	dynmultipush BattleFrontier_Lounge7_Text_PrizeRockBlast, MOVE_ROCK_BLAST
	dynmultipush BattleFrontier_Lounge7_Text_PrizeDragonTail, MOVE_DRAGON_TAIL
	dynmultipush BattleFrontier_Lounge7_Text_PrizeSludgeWave, MOVE_SLUDGE_WAVE
	dynmultipush BattleFrontier_Lounge7_Text_PrizePowerGem, MOVE_POWER_GEM
	dynmultipush BattleFrontier_Lounge7_Text_PrizeAuraSphere, MOVE_AURA_SPHERE
	dynmultipush BattleFrontier_Lounge7_Text_PrizeMoonblast, MOVE_MOONBLAST
	dynmultipush BattleFrontier_Lounge7_Text_PrizeExit, MOVE_NONE
	dynmultistack 14, 0, FALSE, 6, FALSE, MOVE_AQUA_JET, DYN_MULTICHOICE_CB_SHOW_MOVE_DESC_LEFT
	switch VAR_RESULT
	case MOVE_NONE, BattleFrontier_Lounge7_EventScript_ExitDynamicTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitDynamicTutorMoveSelect
	copyvar VAR_0x8005, VAR_RESULT
	call BattleFrontier_Lounge7_EventScript_SetDynamicTutorMovePrice
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SetDynamicTutorMovePrice::
	switch VAR_0x8005
	case MOVE_RAPID_SPIN, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice32
	case MOVE_FAKE_OUT, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice32
	case MOVE_AQUA_JET, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice32
	case MOVE_SHADOW_SNEAK, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice32
	case MOVE_ICE_SHARD, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice32
	case MOVE_NUZZLE, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice32
	case MOVE_KNOCK_OFF, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_STICKY_WEB, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_BODY_PRESS, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_HEAT_WAVE, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_SCALE_SHOT, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_GUNK_SHOT, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_HIGH_HORSEPOWER, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_BULLET_PUNCH, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_PARTING_SHOT, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_WIDE_GUARD, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_FIRST_IMPRESSION, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_FREEZE_DRY, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_FLARE_BLITZ, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_BRAVE_BIRD, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_HEAVY_SLAM, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_ROCK_BLAST, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_DRAGON_TAIL, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_SLUDGE_WAVE, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_POWER_GEM, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_AURA_SPHERE, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_MYSTICAL_FIRE, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48
	case MOVE_POLTERGEIST, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice64
	case MOVE_DRACO_METEOR, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice64
	case MOVE_MOONBLAST, BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice64
	setvar VAR_0x8008, 40
	return

BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice32::
	setvar VAR_0x8008, 32
	return

BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice48::
	setvar VAR_0x8008, 48
	return

BattleFrontier_Lounge7_EventScript_SetDynamicTutorPrice64::
	setvar VAR_0x8008, 64
	return

BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect::
	special CloseBattleFrontierTutorWindow
	special CloseBattlePointsWindow
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge7_EventScript_ExitDynamicTutorMoveSelect::
	special CloseBattlePointsWindow
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge7_EventScript_CancelChooseMon::
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

@ VAR_0x8008 is the price
@ VAR_TEMP_C is the scroll multichoice ID
@ VAR_TEMP_FRONTIER_TUTOR_SELECTION is the move selection
@ VAR_TEMP_FRONTIER_TUTOR_ID is which move tutor was spoken to
BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection::
	special BufferBattleFrontierTutorMoveName
	buffernumberstring STR_VAR_2, VAR_0x8008
	msgbox BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge7_EventScript_ChooseNewMove
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge7_EventScript_TeachTutorMove
	msgbox BattleFrontier_Lounge7_Text_HaventGotEnoughPoints, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseNewMove
	end

BattleFrontier_Lounge7_EventScript_TeachTutorMove::
	msgbox BattleFrontier_Lounge7_Text_TeachMoveToWhichMon, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special CloseBattlePointsWindow
	goto_if_ge VAR_TEMP_FRONTIER_TUTOR_ID, 2, BattleFrontier_Lounge7_EventScript_TeachDynamicTutorMove
	special CloseBattleFrontierTutorWindow
	special ChooseMonForMoveTutor
	waitstate
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_Lounge7_EventScript_CancelChooseMon
	msgbox BattleFrontier_Lounge7_Text_IllTakeBattlePoints, MSGBOX_DEFAULT
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	release
	end

BattleFrontier_Lounge7_EventScript_TeachDynamicTutorMove::
	special ChooseMonForMoveTutor
	waitstate
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_Lounge7_EventScript_CancelChooseMon
	msgbox BattleFrontier_Lounge7_Text_IllTakeBattlePoints, MSGBOX_DEFAULT
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	release
	end

BattleFrontier_Lounge7_EventScript_ChooseNewMove::
	goto_if_eq VAR_TEMP_FRONTIER_TUTOR_ID, 0, BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove
	goto_if_eq VAR_TEMP_FRONTIER_TUTOR_ID, 1, BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove
	goto_if_eq VAR_TEMP_FRONTIER_TUTOR_ID, 2, BattleFrontier_Lounge7_EventScript_ChooseNewOldManTutorMove
	goto BattleFrontier_Lounge7_EventScript_ChooseNewYoungsterTutorMove
	end

BattleFrontier_Lounge7_EventScript_Sailor::
	msgbox BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong, MSGBOX_NPC
	end

BattleFrontier_Lounge7_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful, MSGBOX_NPC
	end

BattleFrontier_Lounge7_Text_LeftTutorIntro:
	.string "Buhahaha!\p"
	.string "You couldn't tell it from looking now,\n"
	.string "but I used to be one tough TRAINER.\p"
	.string "I had a reputation as the toughest\n"
	.string "BEAUTY around, I tell you!\p"
	.string "… … … … … …\p"
	.string "What is it now?\n"
	.string "You don't believe me.\p"
	.string "I'm not like that blowhard woman over\n"
	.string "there. I'm actually talented!\p"
	.string "Let me prove it to you.\n"
	.string "I can teach your POKéMON special and\l"
	.string "yet cute moves.\p"
	.string "But my lessons don't come free.\n"
	.string "How about paying for the moves I teach\l"
	.string "with a wee bit of Battle Points?$"

BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack:
	.string "Buhahaha!\p"
	.string "Are you back to learn special and\n"
	.string "yet cute POKéMON moves?$"

BattleFrontier_Lounge7_Text_TeachWhichMove:
	.string "Fine, fine, look here!\n"
	.string "Which move should I teach?$"

BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints:
	.string "The move {STR_VAR_1}, is it?\n"
	.string "That will be {STR_VAR_2} Battle Points, okay?$"

BattleFrontier_Lounge7_Text_TeachMoveToWhichMon:
	.string "Fine, fine, now pick the POKéMON\n"
	.string "I should teach the move to.$"

BattleFrontier_Lounge7_Text_HaventGotEnoughPoints:
	.string "What the…\n"
	.string "You haven't got enough Battle Points!$"

BattleFrontier_Lounge7_Text_IllTakeBattlePoints:
	.string "Do you see how skilled I am now?\n"
	.string "I'll take your Battle Points, thanks!$"

BattleFrontier_Lounge7_Text_YouDontWantTo:
	.string "What's that?\n"
	.string "You don't want to…\p"
	.string "If you want to see how skilled I am,\n"
	.string "you come see me anytime!$"

BattleFrontier_Lounge7_Text_RightTutorIntro:
	.string "Ihihihi!\p"
	.string "I know it's hard to see now, but I used\n"
	.string "to be one fantastic TRAINER.\p"
	.string "I had a reputation as the most\n"
	.string "invincible SWIMMER around, I tell you!\p"
	.string "… … … … … …\p"
	.string "What's wrong?\n"
	.string "You don't believe me.\p"
	.string "I'm not like that buffoonish woman over\n"
	.string "there. I'm actually experienced!\p"
	.string "I can prove it to you.\n"
	.string "I can teach your POKéMON hard and\l"
	.string "yet pretty moves.\p"
	.string "But my lessons don't come free.\n"
	.string "How about paying for the moves I teach\l"
	.string "with a wee bit of Battle Points?$"

BattleFrontier_Lounge7_Text_RightTutorWelcomeBack:
	.string "Ihihihi!\p"
	.string "Have you come to learn hard and\n"
	.string "yet pretty POKéMON moves?$"

BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong:
	.string "Those ladies, the way they bad-mouth\n"
	.string "each other, you probably think that\l"
	.string "they don't get along.\p"
	.string "But if that were true, they wouldn't\n"
	.string "stay out here together, would they?$"

BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful:
	.string "When I was just a wee YOUNGSTER,\n"
	.string "those ladies were strong and beautiful.\p"
	.string "They were idols among us TRAINERS.\p"
	.string "Even now, age hasn't dulled their\n"
	.string "abilities.\p"
	.string "In fact, their POKéMON moves have\n"
	.string "grown even more polished.\p"
	.string "But… For some reason, I can't help\n"
	.string "but feel this…\p"
	.string "Time is so cruel…$"

BattleFrontier_Lounge7_Text_OldManTutorIntro:
	.string "Hmph. My wife still teaches like\n"
	.string "every battle is a footrace.\p"
	.string "Rush here, rush there...\n"
	.string "No patience for proper technique.\p"
	.string "I teach moves with purpose:\n"
	.string "tempo, pressure, coverage.\p"
	.string "If you have the BP, I have the lesson.$"

BattleFrontier_Lounge7_Text_YoungsterTutorIntro:
	.string "I'm keeping an eye on my grandma.\p"
	.string "She gets so excited about teaching\n"
	.string "moves that she forgets to rest.\p"
	.string "So I made my own list of modern\n"
	.string "battle tricks.\p"
	.string "They're sharp, but don't rush her,\n"
	.string "okay?$"

BattleFrontier_Lounge7_Text_PrizeKnockOff:
	.string "Knock Off{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeEncore:
	.string "Encore{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeRapidSpin:
	.string "Rapid Spin{CLEAR_TO 0x4E}32BP$"

BattleFrontier_Lounge7_Text_PrizeFakeOut:
	.string "Fake Out{CLEAR_TO 0x4E}32BP$"

BattleFrontier_Lounge7_Text_PrizeFlipTurn:
	.string "Flip Turn{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeVoltSwitch:
	.string "Volt Switch{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeTrick:
	.string "Trick{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeTailwind:
	.string "Tailwind{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeSpikes:
	.string "Spikes{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeStickyWeb:
	.string "Sticky Web{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeBodyPress:
	.string "Body Press{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeHeatWave:
	.string "Heat Wave{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizePoltergeist:
	.string "Poltergeist{CLEAR_TO 0x4E}64BP$"

BattleFrontier_Lounge7_Text_PrizeDracoMeteor:
	.string "Draco Meteor{CLEAR_TO 0x4E}64BP$"

BattleFrontier_Lounge7_Text_PrizeScaleShot:
	.string "Scale Shot{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeGunkShot:
	.string "Gunk Shot{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeLiquidation:
	.string "Liquidation{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeIronHead:
	.string "Iron Head{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeHighHorsepower:
	.string "High H.Power{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizePsyshock:
	.string "Psyshock{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeSuckerPunch:
	.string "Sucker Punch{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeAquaJet:
	.string "Aqua Jet{CLEAR_TO 0x4E}32BP$"

BattleFrontier_Lounge7_Text_PrizeShadowSneak:
	.string "ShadowSneak{CLEAR_TO 0x4E}32BP$"

BattleFrontier_Lounge7_Text_PrizeIceShard:
	.string "Ice Shard{CLEAR_TO 0x4E}32BP$"

BattleFrontier_Lounge7_Text_PrizeBulletPunch:
	.string "BulletPnch{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeNuzzle:
	.string "Nuzzle{CLEAR_TO 0x4E}32BP$"

BattleFrontier_Lounge7_Text_PrizeLeechSeed:
	.string "Leech Seed{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeSynthesis:
	.string "Synthesis{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeToxicSpikes:
	.string "ToxicSpikes{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizePartingShot:
	.string "PartingShot{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeWideGuard:
	.string "Wide Guard{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeFirstImpression:
	.string "First Impr.{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeFreezeDry:
	.string "Freeze-Dry{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeMysticalFire:
	.string "Mystic Fire{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeFlareBlitz:
	.string "FlareBlitz{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeBraveBird:
	.string "Brave Bird{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeHeavySlam:
	.string "Heavy Slam{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeRockBlast:
	.string "Rock Blast{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeDragonTail:
	.string "DragonTail{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeFutureSight:
	.string "FutureSght{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeSludgeWave:
	.string "SludgeWave{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizePowerGem:
	.string "Power Gem{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeAuraSphere:
	.string "AuraSphere{CLEAR_TO 0x4E}48BP$"

BattleFrontier_Lounge7_Text_PrizeDrainingKiss:
	.string "Drain Kiss{CLEAR_TO 0x4E}40BP$"

BattleFrontier_Lounge7_Text_PrizeMoonblast:
	.string "Moonblast{CLEAR_TO 0x4E}64BP$"

BattleFrontier_Lounge7_Text_PrizeExit:
	.string "Exit$"

BattleFrontier_Lounge7_Text_KnockOffDesc::
	.string "Knocks off the\n"
	.string "foe's held item\n"
	.string "while attacking.$"

BattleFrontier_Lounge7_Text_EncoreDesc::
	.string "Forces the foe\n"
	.string "to repeat its\n"
	.string "last move.$"

BattleFrontier_Lounge7_Text_RapidSpinDesc::
	.string "Hits, then clears\n"
	.string "binds, seeds and\n"
	.string "hazards.$"

BattleFrontier_Lounge7_Text_FakeOutDesc::
	.string "Strikes first and\n"
	.string "flinches on the\n"
	.string "first turn.$"

BattleFrontier_Lounge7_Text_FlipTurnDesc::
	.string "Attacks, then\n"
	.string "switches the user\n"
	.string "out of battle.$"

BattleFrontier_Lounge7_Text_VoltSwitchDesc::
	.string "An electric hit\n"
	.string "that switches the\n"
	.string "user out.$"

BattleFrontier_Lounge7_Text_TrickDesc::
	.string "Swaps held items\n"
	.string "with the target\n"
	.string "if possible.$"

BattleFrontier_Lounge7_Text_TailwindDesc::
	.string "Stirs up a wind\n"
	.string "that boosts the\n"
	.string "team's SPEED.$"

BattleFrontier_Lounge7_Text_SpikesDesc::
	.string "Sets spikes that\n"
	.string "hurt foes on\n"
	.string "switch-in.$"

BattleFrontier_Lounge7_Text_StickyWebDesc::
	.string "Sets a web that\n"
	.string "slows switch-in\n"
	.string "foes.$"

BattleFrontier_Lounge7_Text_BodyPressDesc::
	.string "Attacks using\n"
	.string "the user's DEF\n"
	.string "stat.$"

BattleFrontier_Lounge7_Text_HeatWaveDesc::
	.string "Scorches foes\n"
	.string "with hot breath.\n"
	.string "May burn.$"

BattleFrontier_Lounge7_Text_PoltergeistDesc::
	.string "Uses the foe's\n"
	.string "item to attack.\n"
	.string "May fail.$"

BattleFrontier_Lounge7_Text_DracoMeteorDesc::
	.string "Drops meteors.\n"
	.string "Sharply lowers\n"
	.string "Sp. ATK.$"

BattleFrontier_Lounge7_Text_ScaleShotDesc::
	.string "Hits 2-5 times.\n"
	.string "Raises SPEED,\n"
	.string "lowers DEFENSE.$"

BattleFrontier_Lounge7_Text_GunkShotDesc::
	.string "Fires dirty gunk.\n"
	.string "May poison the\n"
	.string "target.$"

BattleFrontier_Lounge7_Text_LiquidationDesc::
	.string "Crashes water\n"
	.string "into the target.\n"
	.string "May lower DEF.$"

BattleFrontier_Lounge7_Text_IronHeadDesc::
	.string "Slams with a\n"
	.string "steel-hard head.\n"
	.string "May flinch.$"

BattleFrontier_Lounge7_Text_HighHorsepowerDesc::
	.string "A full-force\n"
	.string "GROUND attack\n"
	.string "with high power.$"

BattleFrontier_Lounge7_Text_PsyshockDesc::
	.string "Psychic waves\n"
	.string "strike the foe's\n"
	.string "DEFENSE.$"

BattleFrontier_Lounge7_Text_SuckerPunchDesc::
	.string "Strikes first if\n"
	.string "the foe chose an\n"
	.string "attack.$"

BattleFrontier_Lounge7_Text_AquaJetDesc::
	.string "Strikes first\n"
	.string "with a burst of\n"
	.string "water.$"

BattleFrontier_Lounge7_Text_ShadowSneakDesc::
	.string "Strikes first\n"
	.string "from the foe's\n"
	.string "shadow.$"

BattleFrontier_Lounge7_Text_IceShardDesc::
	.string "Strikes first\n"
	.string "with ice shards\n"
	.string "at the foe.$"

BattleFrontier_Lounge7_Text_BulletPunchDesc::
	.string "Strikes first\n"
	.string "with bullet-fast\n"
	.string "punches.$"

BattleFrontier_Lounge7_Text_NuzzleDesc::
	.string "Nuzzles to deal\n"
	.string "damage and cause\n"
	.string "paralysis.$"

BattleFrontier_Lounge7_Text_LeechSeedDesc::
	.string "Seeds the foe and\n"
	.string "steals HP every\n"
	.string "turn.$"

BattleFrontier_Lounge7_Text_SynthesisDesc::
	.string "Restores HP. The\n"
	.string "amount changes\n"
	.string "with weather.$"

BattleFrontier_Lounge7_Text_ToxicSpikesDesc::
	.string "Poisons foes that\n"
	.string "switch into\n"
	.string "battle.$"

BattleFrontier_Lounge7_Text_PartingShotDesc::
	.string "Lowers offenses,\n"
	.string "then switches the\n"
	.string "user out.$"

BattleFrontier_Lounge7_Text_WideGuardDesc::
	.string "Protects allies\n"
	.string "from wide-ranging\n"
	.string "attacks.$"

BattleFrontier_Lounge7_Text_FirstImpressionDesc::
	.string "Hits first, but\n"
	.string "only on the first\n"
	.string "turn out.$"

BattleFrontier_Lounge7_Text_FreezeDryDesc::
	.string "May freeze. Hits\n"
	.string "WATER foes super\n"
	.string "effectively.$"

BattleFrontier_Lounge7_Text_MysticalFireDesc::
	.string "Attacks with fire\n"
	.string "and lowers the\n"
	.string "foe's Sp. ATK.$"

BattleFrontier_Lounge7_Text_FlareBlitzDesc::
	.string "A fierce charge.\n"
	.string "May burn, but has\n"
	.string "recoil.$"

BattleFrontier_Lounge7_Text_BraveBirdDesc::
	.string "A reckless flying\n"
	.string "charge that hurts\n"
	.string "the user too.$"

BattleFrontier_Lounge7_Text_HeavySlamDesc::
	.string "Heavier users hit\n"
	.string "with more power\n"
	.string "than targets.$"

BattleFrontier_Lounge7_Text_RockBlastDesc::
	.string "Throws rocks to\n"
	.string "strike the foe\n"
	.string "2-5 times.$"

BattleFrontier_Lounge7_Text_DragonTailDesc::
	.string "Knocks the foe\n"
	.string "away and drags\n"
	.string "another in.$"

BattleFrontier_Lounge7_Text_FutureSightDesc::
	.string "Stores psychic\n"
	.string "power to hit two\n"
	.string "turns later.$"

BattleFrontier_Lounge7_Text_SludgeWaveDesc::
	.string "Swamps the field\n"
	.string "with sludge. May\n"
	.string "poison.$"

BattleFrontier_Lounge7_Text_PowerGemDesc::
	.string "Attacks with rays\n"
	.string "of sparkling\n"
	.string "stone.$"

BattleFrontier_Lounge7_Text_AuraSphereDesc::
	.string "Launches aura\n"
	.string "power that never\n"
	.string "misses.$"

BattleFrontier_Lounge7_Text_DrainingKissDesc::
	.string "Steals HP equal\n"
	.string "to most damage\n"
	.string "it deals.$"

BattleFrontier_Lounge7_Text_MoonblastDesc::
	.string "Calls moonlight\n"
	.string "to attack. May\n"
	.string "lower Sp. ATK.$"

BattleFrontier_Lounge7_Text_SoftboiledDesc::
	.string "Recovers up to\n"
	.string "half the user's\n"
	.string "maximum HP.$"

BattleFrontier_Lounge7_Text_SeismicTossDesc::
	.string "Inflicts damage\n"
	.string "identical to the\n"
	.string "user's level.$"

BattleFrontier_Lounge7_Text_DreamEaterDesc::
	.string "Recovers half the\n"
	.string "damage inflicted\n"
	.string "on a sleeping foe.$"

BattleFrontier_Lounge7_Text_MegaPunchDesc::
	.string "A strong punch\n"
	.string "thrown with\n"
	.string "incredible power.$"

BattleFrontier_Lounge7_Text_MegaKickDesc::
	.string "An extremely\n"
	.string "powerful kick with\n"
	.string "intense force.$"

BattleFrontier_Lounge7_Text_BodySlamDesc::
	.string "A full-body slam\n"
	.string "that may cause\n"
	.string "paralysis.$"

BattleFrontier_Lounge7_Text_RockSlideDesc::
	.string "Large boulders\n"
	.string "are hurled. May\n"
	.string "cause flinching.$"

BattleFrontier_Lounge7_Text_CounterDesc::
	.string "Retaliates any\n"
	.string "physical hit with\n"
	.string "double the power.$"

BattleFrontier_Lounge7_Text_ThunderWaveDesc::
	.string "A weak jolt of\n"
	.string "electricity that\n"
	.string "paralyzes the foe.$"

BattleFrontier_Lounge7_Text_SwordsDanceDesc::
	.string "A fighting dance\n"
	.string "that sharply\n"
	.string "raises ATTACK.$"

BattleFrontier_Lounge7_Text_DefenseCurlDesc::
	.string "Curls up to con-\n"
	.string "ceal weak spots\n"
	.string "and raise DEFENSE.$"

BattleFrontier_Lounge7_Text_SnoreDesc::
	.string "A loud attack\n"
	.string "that can be used\n"
	.string "only while asleep.$"

BattleFrontier_Lounge7_Text_MudSlapDesc::
	.string "Hurls mud in the\n"
	.string "foe's face to re-\n"
	.string "duce its accuracy.$"

BattleFrontier_Lounge7_Text_SwiftDesc::
	.string "Sprays star-\n"
	.string "shaped rays\n"
	.string "that never miss.$"

BattleFrontier_Lounge7_Text_IcyWindDesc::
	.string "A chilling attack\n"
	.string "that lowers the\n"
	.string "foe's SPEED.$"

BattleFrontier_Lounge7_Text_EndureDesc::
	.string "Endures any at-\n"
	.string "tack for 1 turn,\n"
	.string "leaving 1HP.$"

BattleFrontier_Lounge7_Text_PsychUpDesc::
	.string "Copies the foe's\n"
	.string "effect(s) and\n"
	.string "gives to the user.$"

BattleFrontier_Lounge7_Text_IcePunchDesc::
	.string "An icy punch\n"
	.string "that may\n"
	.string "freeze the foe.$"

BattleFrontier_Lounge7_Text_ThunderPunchDesc::
	.string "An electrified\n"
	.string "punch that may\n"
	.string "paralyze the foe.$"

BattleFrontier_Lounge7_Text_FirePunchDesc::
	.string "A fiery punch\n"
	.string "that may burn\n"
	.string "the foe.$"
