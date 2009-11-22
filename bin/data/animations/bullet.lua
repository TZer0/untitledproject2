new_animation("BULLET")

seq = {"FRAMEA", "FRAMEB"}

for i=1,2 do
	sequence(seq[i], "bullet.bmp", "")
	frame(0.1,	16*(i-1), 1,	16, 16,		0,0)
end
