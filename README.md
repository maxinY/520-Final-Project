# 520-Final-Project
1. Goal of the project:

To make a robot leader that moves around the arena in long, looping path, and make some other robots as followers to follow and keep a distance from the leader. 

2. key challenges and addressment:
 
To make each of the followers follow the right "leader" and stay a respectful distance behind the leader. 

By making two robot type: leader and follower, and we can have the leader robot have its own path, which is looping around the arena, with the sensor being used in right way, the robot is able to turn 90 degrees at the corner and continue moving forward. Then for the follower robot, by using attach_to() method, we are able to make each of the follower stay a respect distance from its "leader" we subject to. And the distance is initialized at the beginning as the position of each of the robot being defined. 

3. run the code:

First start the docker image environment by using: docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.5 bash

To make the project and start the enviro sever, we just simply do:

make
enviro

By preseeing Ctrl-C at the bash interface, we can stop the enviro server.

4.special features:
Once clicking mouse, each of the follower will be drawn a red circle on its body.

5. sources used:
https://github.com/klavinslab/enviro





