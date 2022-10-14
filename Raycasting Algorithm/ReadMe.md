# Raycasting Algorithm

My Approach for the algorithm some references I gathered from the guideline of cub3D and some references from the videos of raycasting. 

Angles defined in the algorithm are mostly in degrees, some are mentioned in radians.

Thanks to @MisterTooh for collaborating with me on this fun project. Hope to work with you again in future projects. Now, Let's begin!

![begin](https://user-images.githubusercontent.com/81755254/195951594-38adbeff-ec0a-4c3b-9cce-2159907b9a0f.gif)

# Basic Raycasting

Let's talk about the field of view for the player. 
For my raycasting I took the field of view as 70 degree which will be 35 degree from the left and the 35 degree to the right.

Based on the project cub3D:
* If the player is facing North: Angle of the player will be 270 degree.
* If the player is facing South: Angle of the player will be 90 degree.
* If the player is facing East: Angle of the player will be 180 degree.
* If the player is facing West: Angle of the player will be 0 degree.

## Rotation of the player

Given the angle of the player, in order to rotate the player towards the left, we can subtract with any constant degree.
In my case, I deduct the angle of the player with 0.1(since we're working with radian, so in degree the constant will be 5.73 degrees)
On the other hand if we rotate towards right, we can add the angle with constant 0.1 (the same thing).

Observing the figure of polar coordinates, we can slice the angles in four quadrants.

* First quadrant: 0 <= angle < 90
* Second quadrant: 90 <= angle < 180
* Third quadrant: 180 <= angle < 270
* Fourth quadrant: 270 <= angle < 360

![quadrants](https://user-images.githubusercontent.com/81755254/195952993-769a7544-bb9c-446d-bffc-cf5db67e8199.png)

In case, if angle is less than 0, this indicates that the angle lies in the fourth quadrant, so we can add the resulted angle with 360. Vice versa, if the angle is greater than 360, this indicates that the angle lies in the first quadrant, so we can deduct the resulted angle with 360.