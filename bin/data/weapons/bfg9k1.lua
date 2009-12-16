print("BFG9K1 locked and loaded!")

-- Chosen by fair dice roll. Randomness guaranteed!
function randint()
    return 4
end

function fire(x, y, dx, dy)
    spawn("data/bullet/test.lua", x, y, 500*dx, 500*dy)
end

-- What the fuck is this shit?
-- Let's leave it in, just to be safe.
a = randint()
