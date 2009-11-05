new_animation("PLAYER")

seq = {"IDLE", "LEFT", "RIGHT"}

for i=1,3 do
	sequence(seq[i], "player.bmp", "")
	frame(0.1,	1+26*(i-1), 1,	24, 49,		0,0)
	
	i=i+1
end

