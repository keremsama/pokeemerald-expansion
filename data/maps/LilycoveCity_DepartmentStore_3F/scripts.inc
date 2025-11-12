LilycoveCity_DepartmentStore_3F_MapScripts::
	.byte 0

LilycoveCity_DepartmentStore_3F_EventScript_ClerkLeft::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_3F_Pokemart_Balls
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
@LilycoveCity_DepartmentStore_3F_Pokemart_Vitamins:
@	.2byte ITEM_PROTEIN
@	.2byte ITEM_CALCIUM
@	.2byte ITEM_IRON
@	.2byte ITEM_ZINC
@	.2byte ITEM_CARBOS
@	.2byte ITEM_HP_UP
@	pokemartlistend

LilycoveCity_DepartmentStore_3F_Pokemart_Balls:
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAVY_BALL
	.2byte ITEM_HEAL_BALL
	pokemartlistend

LilycoveCity_DepartmentStore_3F_EventScript_ClerkRight::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_3F_Pokemart_StatBoosters
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_3F_Pokemart_StatBoosters:
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	pokemartlistend

LilycoveCity_DepartmentStore_3F_EventScript_ClerkDownRight::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_3F_Pokemart_TypeBoosting_HeldItems
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_3F_Pokemart_TypeBoosting_HeldItems:
	.2byte ITEM_SILK_SCARF
	.2byte ITEM_CHARCOAL
	.2byte ITEM_MYSTIC_WATER
	.2byte ITEM_MAGNET
	.2byte ITEM_MIRACLE_SEED
	.2byte ITEM_NEVER_MELT_ICE
	.2byte ITEM_BLACK_BELT
	.2byte ITEM_POISON_BARB
	.2byte ITEM_SOFT_SAND
	.2byte ITEM_SHARP_BEAK
	.2byte ITEM_TWISTED_SPOON
	.2byte ITEM_SILVER_POWDER
	.2byte ITEM_HARD_STONE
	.2byte ITEM_SPELL_TAG
	.2byte ITEM_DRAGON_FANG
	.2byte ITEM_BLACK_GLASSES
	.2byte ITEM_METAL_COAT
	pokemartlistend

LilycoveCity_DepartmentStore_3F_EventScript_ClerkDownLeft::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_3F_Pokemart_HoldItems
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_3F_Pokemart_HoldItems:
    .2byte ITEM_BRIGHT_POWDER
    .2byte ITEM_WHITE_HERB
    .2byte ITEM_QUICK_CLAW
    .2byte ITEM_SOOTHE_BELL
    .2byte ITEM_MENTAL_HERB
    .2byte ITEM_KINGS_ROCK
    .2byte ITEM_CLEANSE_TAG
    .2byte ITEM_SMOKE_BALL
    .2byte ITEM_FOCUS_BAND
    .2byte ITEM_SCOPE_LENS
    .2byte ITEM_LEFTOVERS
    .2byte ITEM_SHELL_BELL
    .2byte ITEM_WIDE_LENS
    .2byte ITEM_MUSCLE_BAND
    .2byte ITEM_WISE_GLASSES
    .2byte ITEM_EXPERT_BELT
    .2byte ITEM_LIGHT_CLAY
    .2byte ITEM_LIFE_ORB
    .2byte ITEM_POWER_HERB
    .2byte ITEM_FOCUS_SASH
    .2byte ITEM_ZOOM_LENS
    .2byte ITEM_METRONOME
    .2byte ITEM_IRON_BALL
    .2byte ITEM_LAGGING_TAIL
    .2byte ITEM_DESTINY_KNOT
    .2byte ITEM_BLACK_SLUDGE
    .2byte ITEM_GRIP_CLAW
    .2byte ITEM_STICKY_BARB
    .2byte ITEM_SHED_SHELL
    .2byte ITEM_BIG_ROOT
    .2byte ITEM_RAZOR_CLAW
    .2byte ITEM_RAZOR_FANG
    .2byte ITEM_EVIOLITE
    .2byte ITEM_FLOAT_STONE
    .2byte ITEM_ROCKY_HELMET
    .2byte ITEM_AIR_BALLOON
    .2byte ITEM_RED_CARD
    .2byte ITEM_RING_TARGET
    .2byte ITEM_BINDING_BAND
    .2byte ITEM_EJECT_BUTTON
    .2byte ITEM_WEAKNESS_POLICY
    .2byte ITEM_ASSAULT_VEST
    .2byte ITEM_SAFETY_GOGGLES
    .2byte ITEM_ADRENALINE_ORB
    .2byte ITEM_TERRAIN_EXTENDER
    .2byte ITEM_PROTECTIVE_PADS
    .2byte ITEM_THROAT_SPRAY
    .2byte ITEM_EJECT_PACK
    .2byte ITEM_HEAVY_DUTY_BOOTS
    .2byte ITEM_BLUNDER_POLICY
    .2byte ITEM_ROOM_SERVICE
    .2byte ITEM_UTILITY_UMBRELLA
    pokemartlistend

LilycoveCity_DepartmentStore_3F_EventScript_TriathleteM::
	msgbox LilycoveCity_DepartmentStore_3F_Text_ItemsBestForTougheningPokemon, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_3F_EventScript_PokefanM::
	msgbox LilycoveCity_DepartmentStore_3F_Text_WantMoreEndurance, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_3F_EventScript_Woman::
	msgbox LilycoveCity_DepartmentStore_3F_Text_GaveCarbosToSpeedUpMon, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_3F_Text_ItemsBestForTougheningPokemon:
	.string "For quickly toughening up POKéMON,\n"
	.string "items are the best.\p"
	.string "PROTEIN boosts ATTACK,\n"
	.string "and CALCIUM raises SP. ATK.$"

LilycoveCity_DepartmentStore_3F_Text_WantMoreEndurance:
	.string "I want my POKéMON to have more\n"
	.string "endurance.\p"
	.string "I'm trying to decide whether to raise\n"
	.string "DEFENSE with IRON, or SP. DEF with ZINC.$"

LilycoveCity_DepartmentStore_3F_Text_GaveCarbosToSpeedUpMon:
	.string "I gave a CARBOS to my POKéMON,\n"
	.string "and its SPEED went up.$"

