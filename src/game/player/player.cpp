#include "../port.h"
#include "player.h"
#include "../draw.h"
#include "../game.h"

/*
 * Initialize player.
 */
void cmPlayer::init() {
    pos = cVector(200, 50);
    vel = cVector(0, 0);
    acc = cVector(0, 0);
    gravity = 1.6;
    horSpeed = 48;
    jumpHeight = 8;
    height = 64;
    width = 64;
    flagDown = false;
    flagUp = false;
    flagLeft = false;
    flagRight = false;
    inAir = true;
}

/*
 * Set player flags based on keyboard input.
 */
void cmPlayer::input() {
    if (key[KEY_LEFT] || key[KEY_H]) {
        flagLeft = true;
    }

    if (key[KEY_RIGHT] || key[KEY_L]) {
        flagRight = true;
    }

    if (key[KEY_UP] || key[KEY_K]) {
        flagUp = true;
    }
    
    if (key[KEY_DOWN] || key[KEY_J]) {
        flagDown = true;
    }
}

/*
 * Process player flags. Update player position.
 *
 * @param delta Delta
 */
void cmPlayer::process(double delta) {

    /*
        Note form Stian, the evil inspector

        Honestly, the use of the cVector class actually annoys me..
        If the cVector class have to be used *at all*, use it properly.
        The code below actually uses very many unneccary processor
        cycles. For example the line

        vel = cVector(delta * horSpeed, vel.y);

        would
        1) allocate space for a temporary cVector in memory.
        2) fill the temporary cVector with the right values. (2 assignments)
        3) copy the values from the temporary cVector to val. (2 assignments)
        4) presumeably unallocate memory for the temporary vector.
    
        Instead the line

        vel.x = delta * horSpeed;

        would do exactly what we would like to do with the prev. line
        but would only
        1) assign a value to vel.x (1 assignment)

        And I would even say it is more readable, and obviously shorter.

        Yes yes, in principle we have about unlimited memory and
        cpu-cycles, but still, seriously.. :(
    */
    /*
        Stian (is getting a little confused)
    
        I think I smell some ill physics.. I will almost suggest an almost
        complete reimplementation of this function, but maybe substitution
        of lines will do.

        I kind of hope that the content of this procedure was intended to
        be temporary, but we seriously have no time for that.

        Ok, basically, what I want is that a value that measures something
        is tied to a specific unit *all the time*. That meaning for example
        vel that measures speed, is tied to the unit m/s. Think about it 
        while programming, it will probably save us for trouble.

        Time variables (think: measured in seconds (s)):
        delta

        Position variables (think: measured in meters (m)):
        pos.x, pos.y

        Speed variables (m/s):
        vel.x, vel.y, horSpeed
        
        Acceleration variables (m/s²):
        acc.x, acc.y

        What i see in the code is:
        vel = cVector(delta * horSpeed, vel.y);
        This will make vel.x become measured in meters :S (s * m/s = m)
        Later in the code:
        pos += vel;
        So, ok things MAY turn out right because pos is supposed to be 
        measured in meters, and vel is by some reason measured in meters.
    */
    /*
        Most importantly: (this will be in norwegean so it gets right)

        Jeg mener ikke å hakke på noen, virke sur eller virke smart, men
        jeg innser at det kan være nettopp det jeg gjør. Uansett, jeg
        tror at det å fikse denne funksjonen på en slik form jeg vil ha 
        den vil være enklere enn det var for meg å skrive disse notisene.

        For all del, det kan også være at det er jeg som tar feil, og at
        er jeg som sløser bort min og andres tid. Men uansett vil jeg ikke
        endre koden andre er ansvarlig for. Det er derimot håpet mitt at
        folk kan bli glad for at noen andre tar seg bryet med å se gjennom
        andres kode og kommer med tilbakemeldinger på det. 
        
        Vi samarbeider.

        Hvis man er usikker på f. eks fysikk har vi ekspertise på det
        blant andre pong-medlemmer.

        Jeg håper jeg ikke har drete meg ut..
        Hilsen inspektøren (dere var på en måte uansett advart..)

        PS: Ikke svar i denne filen. Kjeft kan dere ev. sende meg pr mail.
    */

    // Update horizontal velocity and clear flags.
    if (flagLeft) {
        flagLeft = false;
        vel = cVector(delta * -horSpeed, vel.y);
    } else if (flagRight) {
        flagRight = false;
        vel = cVector(delta * horSpeed, vel.y);
    } else {
        vel = cVector(0, vel.y);
    }

    // Jump handling.
    if (jumpLife > 0 && flagUp) {
        // inAir = true;
        --jumpLife;
        acc = cVector(acc.x, -1 * jumpHeight);
        vel = cVector(vel.x, -jumpHeight);
    }

    // Temporary collision detection.
    // Uses screen height instead of ground.
    if (pos.y >= SCREEN_H - height) {
        vel = cVector(vel.x, 0);
        pos.y = SCREEN_H - height;
        // inAir = false;
        jumpLife = 8;
    } else {
        acc = cVector(acc.x, acc.y + gravity);
    }

    // Update vertical velocity and clear flags.
    vel = cVector(vel.x + acc.x * delta, vel.y + acc.y * delta);
    
    // How about: vel += delta * acc
    // (still Stian)


    /*
        Anther note from Stian, the evil inspector

        1) Since when did the formula say s = s0 + v?
            To make things a _Little_ more precise: s = s0 + v * dt..
            In the code: pos += vel*delta

        2) The note above alone will is actually still unprecise, as
            the formula actually is as complex as:
            s = s0 + v * dt + 1/2 * a * dt²
            Code would be something like:
            pos += vel*delta + 1.0/2 * acc * delta * delta
        
        I will not perform these changes to the code, because, of
        course, I've not had physics for soon one and a half year, and
        I do not have any collection of formulas (a truth with 
        modifications), and I don't bother to wikipedia it, so I'm 
        only 98% sure I'm right.

        So someone should verify if my suggestion actually is correct,
        and someone who is responsible for the player class should
        ensure that everything is actually implemented correctly.

        PS: Yes, I have fun.. No hard feelings I hope..
    */
    pos += vel;
    flagUp = false;
}

/*
 * Draw player sprite.
 */
void cmPlayer::draw() {
    rectfill(mGame->mDraw->buffer, pos.x, pos.y, pos.x + width,
            pos.y + height, 0xff8800);
}

/*
 * Reset player position and velocity.
 */
void cmPlayer::clear_data() {
    pos = cVector(0, 0);
    vel = cVector(0, 0);
}
