new_animation("BULLET")

sequence("IDLE", "bullet.bmp", "")
for i=1,2 do
	frame(0.1,	16*(i-1), 1,	16, 16,		0,0)
end
