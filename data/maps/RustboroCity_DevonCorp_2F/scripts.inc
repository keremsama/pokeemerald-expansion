# 1 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 2 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_MapScripts::
# 3 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_2F_OnTransition
# 4 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.byte 0
# 5 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 6 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_OnTransition:
# 7 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
# 8 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	end
# 9 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 10 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_EventScript_SetFossilReady::
# 11 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_FOSSIL_RESURRECTION_STATE, 2
# 12 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	return
# 13 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 14 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_EventScript_TalkToPokemonScientist::
# 15 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	lock
# 16 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	faceplayer
# 17 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
# 18 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon, MSGBOX_DEFAULT
# 19 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
# 20 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	end
# 21 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 22 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_EventScript_BallScientist::
# 23 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	lock
# 24 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	faceplayer
# 25 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
# 26 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls
# 27 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls, MSGBOX_DEFAULT
# 28 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
# 29 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	end
# 30 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 31 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls::
# 32 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls, MSGBOX_DEFAULT
# 33 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
# 34 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	end
# 35 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 36 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_EventScript_PokenavScientist::
# 37 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	lock
# 38 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	faceplayer
# 39 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
# 40 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto_if_set FLAG_RECEIVED_POKENAV, RustboroCity_DevonCorp_2F_EventScript_HasPokenav
# 41 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_IMadePokenav, MSGBOX_DEFAULT
# 42 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
# 43 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	end
# 44 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 45 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_EventScript_HasPokenav::
# 46 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav, MSGBOX_DEFAULT
# 47 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
# 48 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	end
# 49 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 50 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_EventScript_PokemonDreamsScientist::
# 51 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	lock
# 52 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	faceplayer
# 53 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
# 54 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams, MSGBOX_DEFAULT
# 55 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
# 56 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	end
# 57 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 58 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil::
# 59 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_OhIsThatSo, MSGBOX_DEFAULT
# 60 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
# 61 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	end
# 62 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 63 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect::
# 64 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
# 65 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	end
# 66 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 67 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_EventScript_MatchCallScientist::
# 68 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	lock
# 69 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	faceplayer
# 70 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
# 71 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto_if_ge VAR_RUSTBORO_CITY_STATE, 6, RustboroCity_DevonCorp_2F_EventScript_WorkOnNext
# 72 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature, MSGBOX_DEFAULT
# 73 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
# 74 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	end
# 75 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 76 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_EventScript_WorkOnNext::
# 77 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext, MSGBOX_DEFAULT
# 78 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
# 79 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	end
# 80 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 81 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon:
# 82 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "We're developing a device for talking\n"
# 83 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "with POKéMON.\p"
# 84 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "But we haven't had much success…$"
# 85 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 86 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls:
# 87 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "I'm developing new kinds of\n"
# 88 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "POKé BALLS…\p"
# 89 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "But I haven't made much headway…$"
# 90 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 91 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls:
# 92 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "We finally made new kinds of\n"
# 93 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "POKé BALLS!\p"
# 94 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "The REPEAT BALL makes it easier to\n"
# 95 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "catch POKéMON you've caught before.\p"
# 96 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "The TIMER BALL gets better at catching\n"
# 97 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "POKéMON the longer a battle runs.\p"
# 98 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Both are proudly developed by\n"
# 99 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "the DEVON CORPORATION.\p"
# 100 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Please give them a try!$"
# 101 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 102 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_IMadePokenav:
# 103 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "I made the POKéNAV!\p"
# 104 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "As an engineer, I feel blessed to have\n"
# 105 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "made something so great!$"
# 106 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 107 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav:
# 108 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Oh, wow!\n"
# 109 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "That's a POKéNAV!\p"
# 110 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "It came about as a result of our\n"
# 111 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "PRESIDENT's desire to learn about\l"
# 112 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "the feelings of POKéMON.\p"
# 113 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Would you like me to describe its\n"
# 114 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "features in detail?\p"
# 115 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "No, no. I think you'll find out just by\n"
# 116 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "trying the POKéNAV out.$"
# 117 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 118 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams:
# 119 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "I'm trying to develop a device that\n"
# 120 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "visually reproduces the dreams of\l"
# 121 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "POKéMON…\p"
# 122 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "But it's not going well.$"
# 123 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 124 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils:
# 125 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "I've been trying to develop a device\n"
# 126 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "that resurrects POKéMON from fossils…\p"
# 127 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "And, it's working!$"
# 128 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 129 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife:
# 130 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Wait! That thing you have there…\n"
# 131 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Is that a {STR_VAR_1}?\p"
# 132 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Would you like to bring that POKéMON\n"
# 133 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "back to life?\p"
# 134 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "I can with my newly developed\n"
# 135 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "FOSSIL REGENERATOR.$"
# 136 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 137 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_OhIsThatSo:
# 138 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Oh, is that so?\p"
# 139 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "DEVON's technological expertise\n"
# 140 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "is outstanding, I tell you.$"
# 141 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 142 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_TwoFossilsPickOne:
# 143 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Oh, now that's a surprise!\n"
# 144 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "You have not one, but two, fossils?\p"
# 145 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Unfortunately, my machine can only\n"
# 146 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "regenerate one POKéMON at a time.\p"
# 147 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Would you like to pick one of your\n"
# 148 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "fossils for regeneration?$"
# 149 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 150 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher:
# 151 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Excellent!\n"
# 152 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Let's do this right away.\p"
# 153 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "{PLAYER} handed the {STR_VAR_1} to\n"
# 154 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "the DEVON RESEARCHER.$"
# 155 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 156 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime:
# 157 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "The FOSSIL REGENERATOR, which I made,\n"
# 158 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "is incredible.\p"
# 159 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "But it has one drawback--it takes\n"
# 160 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "a long time to work.\p"
# 161 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "So, uh… How about you go for a stroll\n"
# 162 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "and look around for a while?$"
# 163 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 164 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife:
# 165 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Thanks for waiting!\p"
# 166 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Your fossilized POKéMON has been\n"
# 167 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "brought back to life!\p"
# 168 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "The fossil was an ancient POKéMON.\n"
# 169 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "{STR_VAR_2}, it was!$"
# 170 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 171 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher:
# 172 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "{PLAYER} received {STR_VAR_2} from\n"
# 173 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "the DEVON RESEARCHER.$"
# 174 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 175 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
@ Unused
# 176 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_TooManyPokemon:
# 177 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Uh-oh, you've got too many POKéMON.\n"
# 178 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "You have no room for this one.$"
# 179 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 180 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature:
# 181 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "I'm trying to develop a new feature\n"
# 182 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "for the POKéNAV…\p"
# 183 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "But it's not going well.$"
# 184 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"

# 185 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext:
# 186 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Well, now what shall I work on\n"
# 187 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "developing next?\p"
# 188 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Our company allows us to make our\n"
# 189 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "inspirations into reality.\p"
# 190 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "One couldn't ask for a better\n"
# 191 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "environment as an engineer.$"

RustboroCity_DevonCorp_2F_EventScript_FossilScientist::
# 198 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	lock
# 199 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	faceplayer
# 200 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_StillRegenerating
# 201 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 2, RustboroCity_DevonCorp_2F_EventScript_FossilMonReady
# 202 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils
# 203 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call RustboroCity_DevonCorp_2F_EventScript_FossilCounting
# 204 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_TEMP_0, 1
	goto_if_gt RustboroCity_DevonCorp_2F_EventScript_FossilScientist_2
RustboroCity_DevonCorp_2F_EventScript_FossilScientist_1:
# 207 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_TEMP_0, 1
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilScientist_5
RustboroCity_DevonCorp_2F_EventScript_FossilScientist_4:
# 211 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilScientist_2:
# 205 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto RustboroCity_DevonCorp_2F_EventScript_FossilScientist_MultipleFossil
	goto RustboroCity_DevonCorp_2F_EventScript_FossilScientist_1

RustboroCity_DevonCorp_2F_EventScript_FossilScientist_5:
# 208 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call RustboroCity_DevonCorp_2F_EventScript_FossilChecking
# 209 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto RustboroCity_DevonCorp_2F_EventScript_FossilScientist_OnlyOneFossil
	goto RustboroCity_DevonCorp_2F_EventScript_FossilScientist_4


RustboroCity_DevonCorp_2F_EventScript_FossilScientist_MultipleFossil::
# 216 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
# 217 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	playse SE_PIN
# 218 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	waitmovement 0
# 219 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	delay 48
# 220 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife_Multiple, MSGBOX_YESNO
# 221 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilScientist_MultipleFossil_2
# 227 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_EventScript_FossilScientist_MultipleFossil_Text_0
# 228 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList
# 229 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	bufferitemname STR_VAR_1, VAR_TEMP_1
# 230 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher
# 231 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	removeitem VAR_TEMP_1, 1
# 232 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
# 233 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	copyvar VAR_FOSSIL_AT_SCIENTIST, VAR_TEMP_1
# 234 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilScientist_MultipleFossil_2:
# 222 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_0, 0
# 223 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_OhIsThatSo
# 224 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
	end


RustboroCity_DevonCorp_2F_EventScript_FossilScientist_OnlyOneFossil::
# 239 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	bufferitemname STR_VAR_1, VAR_TEMP_1
# 240 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
# 241 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	playse SE_PIN
# 242 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	waitmovement 0
# 243 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	delay 48
# 244 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
# 245 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilScientist_OnlyOneFossil_2
# 251 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher
# 252 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	removeitem VAR_TEMP_1, 1
# 253 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
# 254 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	copyvar VAR_FOSSIL_AT_SCIENTIST, VAR_TEMP_1
# 255 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilScientist_OnlyOneFossil_2:
# 246 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_0, 0
# 247 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_OhIsThatSo
# 248 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
	end


RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList::
	checkitem ITEM_DOME_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_2
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_1:
	checkitem ITEM_OLD_AMBER
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_5
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_4:
	checkitem ITEM_HELIX_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_8
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_7:
	checkitem ITEM_ROOT_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_11
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_10:
	checkitem ITEM_CLAW_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_14
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_13:
	checkitem ITEM_ARMOR_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_17
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_16:
	checkitem ITEM_SKULL_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_20
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_19:
	checkitem ITEM_COVER_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_23
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_22:
	checkitem ITEM_PLUME_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_26
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_25:
	checkitem ITEM_JAW_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_29
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_28:
	checkitem ITEM_SAIL_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_32
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_31:
	checkitem ITEM_FOSSILIZED_BIRD
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_35
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_34:
	checkitem ITEM_FOSSILIZED_FISH
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_38
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_37:
	checkitem ITEM_FOSSILIZED_DRAKE
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_41
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_40:
	checkitem ITEM_FOSSILIZED_DINO
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_44
RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_43:
# 306 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultistack 19, 0, TRUE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 307 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	copyvar VAR_TEMP_1, VAR_RESULT
	return

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_2:
# 262 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_0, ITEM_DOME_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_1

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_5:
# 265 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_1, ITEM_OLD_AMBER
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_4

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_8:
# 268 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_2, ITEM_HELIX_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_7

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_11:
# 271 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_3, ITEM_ROOT_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_10

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_14:
# 274 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_4, ITEM_CLAW_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_13

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_17:
# 277 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_5, ITEM_ARMOR_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_16

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_20:
# 280 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_6, ITEM_SKULL_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_19

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_23:
# 283 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_7, ITEM_COVER_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_22

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_26:
# 286 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_8, ITEM_PLUME_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_25

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_29:
# 289 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_9, ITEM_JAW_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_28

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_32:
# 292 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_10, ITEM_SAIL_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_31

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_35:
# 295 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_11, ITEM_FOSSILIZED_BIRD
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_34

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_38:
# 298 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_12, ITEM_FOSSILIZED_FISH
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_37

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_41:
# 301 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_13, ITEM_FOSSILIZED_DRAKE
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_40

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_44:
# 304 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_14, ITEM_FOSSILIZED_DINO
	goto RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_43


RustboroCity_DevonCorp_2F_EventScript_StillRegenerating::
# 312 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime
# 313 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
	end


RustboroCity_DevonCorp_2F_EventScript_FossilMonReady::
# 318 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing
# 319 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto_if_set FLAG_RANDOM_FIXED_MON, RustboroCity_DevonCorp_2F_EventScript_FossilMonReady_2
RustboroCity_DevonCorp_2F_EventScript_FossilMonReady_1:
# 322 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	bufferspeciesname STR_VAR_2, VAR_TEMP_2
# 323 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife
# 324 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	copyvar VAR_TEMP_TRANSFERRED_SPECIES, VAR_TEMP_2
# 325 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	givemon VAR_TEMP_2, 35
# 326 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveMonParty
# 327 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveMonPC
# 328 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_FossilMonReady_2:
# 320 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	callnative RandomizeSpeciesToVarTemp2
	goto RustboroCity_DevonCorp_2F_EventScript_FossilMonReady_1


RustboroCity_DevonCorp_2F_EventScript_ReceiveMonPC::
# 333 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedMonFanfare
# 334 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox ( gText_NicknameThisPokemon ), MSGBOX_YESNO
# 335 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferMonToPC
# 336 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 337 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto RustboroCity_DevonCorp_2F_EventScript_TransferMonToPC
	end


RustboroCity_DevonCorp_2F_EventScript_TransferMonToPC::
# 342 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call Common_EventScript_TransferredToPC
# 343 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingMon
	end


RustboroCity_DevonCorp_2F_EventScript_ReceiveMonParty::
# 348 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedMonFanfare
# 349 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	msgbox ( gText_NicknameThisPokemon ), MSGBOX_YESNO
# 350 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingMon
# 351 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 352 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 353 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingMon
	end


RustboroCity_DevonCorp_2F_EventScript_ReceivedMonFanfare::
# 358 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	bufferspeciesname STR_VAR_2, VAR_TEMP_2
# 359 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	playfanfare MUS_OBTAIN_TMHM
# 360 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
# 361 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	waitmessage
# 362 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	waitfanfare
# 363 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_2
	return


RustboroCity_DevonCorp_2F_EventScript_FinishReceivingMon::
# 368 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
# 369 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
# 370 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	release
	end


RustboroCity_DevonCorp_2F_EventScript_FossilCounting::
	checkitem ITEM_ROOT_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_2
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_1:
	checkitem ITEM_HELIX_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_5
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_4:
	checkitem ITEM_OLD_AMBER
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_8
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_7:
	checkitem ITEM_DOME_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_11
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_10:
	checkitem ITEM_CLAW_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_14
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_13:
	checkitem ITEM_ARMOR_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_17
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_16:
	checkitem ITEM_SKULL_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_20
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_19:
	checkitem ITEM_COVER_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_23
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_22:
	checkitem ITEM_PLUME_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_26
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_25:
	checkitem ITEM_JAW_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_29
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_28:
	checkitem ITEM_SAIL_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_32
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_31:
	checkitem ITEM_FOSSILIZED_BIRD
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_35
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_34:
	checkitem ITEM_FOSSILIZED_FISH
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_38
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_37:
	checkitem ITEM_FOSSILIZED_DRAKE
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_41
RustboroCity_DevonCorp_2F_EventScript_FossilCounting_40:
	checkitem ITEM_FOSSILIZED_DINO
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilCounting_43
	return

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_2:
# 377 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_1

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_5:
# 380 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_4

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_8:
# 383 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_7

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_11:
# 386 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_10

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_14:
# 389 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_13

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_17:
# 392 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_16

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_20:
# 395 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_19

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_23:
# 398 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_22

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_26:
# 401 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_25

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_29:
# 404 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_28

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_32:
# 407 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_31

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_35:
# 410 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_34

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_38:
# 413 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_37

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_41:
# 416 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	goto RustboroCity_DevonCorp_2F_EventScript_FossilCounting_40

RustboroCity_DevonCorp_2F_EventScript_FossilCounting_43:
# 419 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	addvar VAR_TEMP_0, 1
	return


RustboroCity_DevonCorp_2F_EventScript_FossilChecking::
	checkitem ITEM_ROOT_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_2
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_1:
	checkitem ITEM_HELIX_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_5
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_4:
	checkitem ITEM_OLD_AMBER
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_8
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_7:
	checkitem ITEM_DOME_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_11
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_10:
	checkitem ITEM_CLAW_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_14
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_13:
	checkitem ITEM_ARMOR_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_17
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_16:
	checkitem ITEM_SKULL_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_20
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_19:
	checkitem ITEM_COVER_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_23
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_22:
	checkitem ITEM_PLUME_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_26
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_25:
	checkitem ITEM_JAW_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_29
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_28:
	checkitem ITEM_SAIL_FOSSIL
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_32
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_31:
	checkitem ITEM_FOSSILIZED_BIRD
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_35
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_34:
	checkitem ITEM_FOSSILIZED_FISH
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_38
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_37:
	checkitem ITEM_FOSSILIZED_DRAKE
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_41
RustboroCity_DevonCorp_2F_EventScript_FossilChecking_40:
	checkitem ITEM_FOSSILIZED_DINO
# 0 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilChecking_43
	return

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_2:
# 427 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_ROOT_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_1

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_5:
# 430 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_HELIX_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_4

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_8:
# 433 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_OLD_AMBER
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_7

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_11:
# 436 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_DOME_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_10

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_14:
# 439 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_CLAW_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_13

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_17:
# 442 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_ARMOR_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_16

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_20:
# 445 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_SKULL_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_19

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_23:
# 448 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_COVER_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_22

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_26:
# 451 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_PLUME_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_25

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_29:
# 454 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_JAW_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_28

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_32:
# 457 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_SAIL_FOSSIL
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_31

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_35:
# 460 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_FOSSILIZED_BIRD
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_34

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_38:
# 463 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_FOSSILIZED_FISH
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_37

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_41:
# 466 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_FOSSILIZED_DRAKE
	goto RustboroCity_DevonCorp_2F_EventScript_FossilChecking_40

RustboroCity_DevonCorp_2F_EventScript_FossilChecking_43:
# 469 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_1, ITEM_FOSSILIZED_DINO
	return


RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing::
# 476 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_ROOT_FOSSIL
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_2
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_1:
# 479 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_CLAW_FOSSIL
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_5
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_4:
# 482 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_DOME_FOSSIL
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_8
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_7:
# 485 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_OLD_AMBER
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_11
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_10:
# 488 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_HELIX_FOSSIL
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_14
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_13:
# 491 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_ARMOR_FOSSIL
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_17
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_16:
# 494 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_SKULL_FOSSIL
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_20
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_19:
# 497 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_COVER_FOSSIL
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_23
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_22:
# 500 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_PLUME_FOSSIL
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_26
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_25:
# 503 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_JAW_FOSSIL
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_29
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_28:
# 506 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_SAIL_FOSSIL
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_32
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_31:
# 509 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_FOSSILIZED_BIRD
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_35
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_34:
# 512 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_FOSSILIZED_FISH
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_38
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_37:
# 515 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_FOSSILIZED_DRAKE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_41
RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_40:
# 518 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	compare VAR_FOSSIL_AT_SCIENTIST, ITEM_FOSSILIZED_DINO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_43
	return

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_2:
# 477 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_LILEEP
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_1

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_5:
# 480 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_ANORITH
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_4

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_8:
# 483 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_KABUTO
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_7

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_11:
# 486 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_AERODACTYL
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_10

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_14:
# 489 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_OMANYTE
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_13

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_17:
# 492 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_SHIELDON
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_16

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_20:
# 495 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_CRANIDOS
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_19

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_23:
# 498 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_TIRTOUGA
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_22

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_26:
# 501 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_ARCHEN
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_25

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_29:
# 504 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_TYRUNT
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_28

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_32:
# 507 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_AMAURA
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_31

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_35:
# 510 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_DRACOZOLT
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_34

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_38:
# 513 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_ARCTOVISH
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_37

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_41:
# 516 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_DRACOVISH
	goto RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_40

RustboroCity_DevonCorp_2F_EventScript_FossilPokemonChoosing_43:
# 519 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_ARCTOZOLT
	return


RustboroCity_DevonCorp_2F_EventScript_FossilScientist_MultipleFossil_Text_0:
# 227 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Which Fossil would you like to\n"
	.string "resurrect?$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_0:
# 262 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Dome Fossil$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_1:
# 265 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Old Amber$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_2:
# 268 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Helix Fossil$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_3:
# 271 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Root Fossil$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_4:
# 274 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Claw Fossil$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_5:
# 277 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Armor Fossil$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_6:
# 280 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Skull Fossil$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_7:
# 283 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Cover Fossil$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_8:
# 286 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Plume Fossil$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_9:
# 289 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Jaw Fossil$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_10:
# 292 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Sail Fossil$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_11:
# 295 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Fos. Bird$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_12:
# 298 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Fos. Fish$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_13:
# 301 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Fos. Drake$"

RustboroCity_DevonCorp_2F_EventScript_DynamicMultichoiceList_Text_14:
# 304 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Fos. Dino$"

RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife_Multiple::
# 524 "data/maps/RustboroCity_DevonCorp_2F/scripts.pory"
	.string "Wait! That thing you have there…\n"
	.string "Is that a Fossil?\p"
	.string "You have also multiples of them.\p"
	.string "Would you like to bring a POKéMON\n"
	.string "back to life?\p"
	.string "I can with my newly developed\n"
	.string "FOSSIL REGENERATOR.$"
