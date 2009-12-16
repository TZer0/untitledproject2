print("BFG9K1 locked and loaded!")

-- Chosen by fair dice roll. Randomness guaranteed!
function randint()
    return 4
end

function fire(x, y, dx, dy)
    spawn("data/bullet/test.lua", x, y, 300*dx, 300*dy)
end

-- What the fuck is this shit?
a = randint()
