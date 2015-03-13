# Introduction / Abstract #
This page will describe the surface part of the collision system. All internal structures will be deliberately hidden from view (mostly because they're messy and the algorithm isn't very apparent).

Basically, collision interaction is separated into two parts:
  * The collision object (cCollision), which is attached to a position vector.
  * The collision interaction (cApplyCollision), which is inherited by a module that handles a set of instances. Each instance glues itself onto the cApplyCollision system by attaching a sColSectorInstance to it.


# Details #
## cCollision ##
A cCollision object is created through mCollision. Using the create() function.

Its definition is:
```
cCollision *create(CollisionType type, cVector *pos, cVector offset, double arg1=0.0, double arg2=0.0);
```

Where CollisionType can be one of the following:
  * CollisionPoint: A single point of collision, faster to process than the other types. useful for bullets. Takes no arguments
  * CollisionRectangle: A collision rectangle, arg1 determines width, and arg2 determines the height of the collision box
  * CollisionTriangle: A collision _right_ triangle, arg1 determines the baseline width (negative width reverses the direction), and arg2 determines the height (again, negative reverses direction)
  * CollisionCircle: A circle object, arg1 determines the radius of the object.

The pos argument is a pointer to the actual position vector of the instance that owns this collision object.

The offset argument is the offset the collision object is from the position vector. This is useful for collision triangles, which have sort of "negative position" if the width is reversed.
---

To interact two collision objects, call either of:
```
bool cCollision::detect(cCollision *target);
sColReturn cCollision::collide(cCollision *target, cVector vel);
```

Each function is passed the target cCollision object to test collision against.

detect() should be slightly faster, as it only tries to find if the two instances collide.

collide() returns a sColReturn data object, which stores a flag if there was a collision, and additionally an "orp" vector which tells how far the pos vector should be moved to escape the collision. Special about the collide() function is that it should be passed the velocity of the instance that is colliding against target, so that it will escape collision in the right direction. Though I will ignore this argument initially.

## cApplyCollision ##
[todo](todo.md)