new_animation("PLAYER")

seq = {"IDLE", "LEFT", "RIGHT"}

i=1
while i<=3 do
	sequence(seq[i], "player.bmp", "")
	frame(0.1,	1+26*(i-1), 1,	24, 49,		0,0)
	
	i=i+1
end

