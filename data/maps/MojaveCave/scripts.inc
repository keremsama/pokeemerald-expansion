MojaveCave_MapScripts::
	.byte 0


MojaveCave_NPC_Hiker::
# 4 "data/maps/MojaveCave/scripts.pory"
	lock
# 5 "data/maps/MojaveCave/scripts.pory"
	faceplayer
# 6 "data/maps/MojaveCave/scripts.pory"
	msgbox MojaveCave_NPC_Hiker_Text_0
# 9 "data/maps/MojaveCave/scripts.pory"
	waitmessage
# 10 "data/maps/MojaveCave/scripts.pory"
	release
	end


MojaveCave_NPC_Scientist::
# 15 "data/maps/MojaveCave/scripts.pory"
	lock
# 16 "data/maps/MojaveCave/scripts.pory"
	faceplayer
# 17 "data/maps/MojaveCave/scripts.pory"
	msgbox MojaveCave_NPC_Scientist_Text_0
# 21 "data/maps/MojaveCave/scripts.pory"
	waitmessage
# 22 "data/maps/MojaveCave/scripts.pory"
	applymovement 6, MojaveCave_NPC_Scientist_Movement_0
# 25 "data/maps/MojaveCave/scripts.pory"
	waitmovement 6
# 26 "data/maps/MojaveCave/scripts.pory"
	release
	end


MojaveCave_NPC_OldMan::
# 31 "data/maps/MojaveCave/scripts.pory"
	lock
# 32 "data/maps/MojaveCave/scripts.pory"
	faceplayer
# 33 "data/maps/MojaveCave/scripts.pory"
	msgbox MojaveCave_NPC_OldMan_Text_0
# 38 "data/maps/MojaveCave/scripts.pory"
	waitmessage
# 39 "data/maps/MojaveCave/scripts.pory"
	release
	end


# 22 "data/maps/MojaveCave/scripts.pory"
MojaveCave_NPC_Scientist_Movement_0:
# 23 "data/maps/MojaveCave/scripts.pory"
	face_left
	step_end

MojaveCave_NPC_Hiker_Text_0:
# 7 "data/maps/MojaveCave/scripts.pory"
	.string "Hot, dusty, cramped… just the way a real\n"
	.string "cave adventure should be!$"

MojaveCave_NPC_Scientist_Text_0:
# 18 "data/maps/MojaveCave/scripts.pory"
	.string "Shh… I'm examining this rock.\p"
	.string "One wrong vibration and the readings\n"
	.string "get messed up!$"

MojaveCave_NPC_OldMan_Text_0:
# 34 "data/maps/MojaveCave/scripts.pory"
	.string "I'm visiting this cave for many years\n"
	.string "now.\p"
	.string "If you listen closely, you can hear the\n"
	.string "desert whisper through the stones.\p"
	.string "And you know what? I like it!$"
