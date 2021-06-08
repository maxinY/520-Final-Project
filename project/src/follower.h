#ifndef __FOLLOWER_AGENT__H
#define __FOLLOWER_AGENT__H 

#include "enviro.h"
#include<iostream>
using namespace enviro;
using namespace std;
//this class is the follwer control class
class followerController : public Process, public AgentInterface {

    public:
    followerController() : Process(), AgentInterface(), goal_x(0), goal_y(0) {}
    
    double goal_x, goal_y;
    void init() {
        
        watch("screen_click", [this](Event e) {
            //if screen is clicked, then add a red dot on each of the follwer agent
            decorate("<circle x='-5' y='5' r='5' style='fill: red'></circle>");
            

            });
        //once the leader emits, let the follwer to recieve position from the leader
        watch("goal_change", [this](Event e) {
            goal_x = position().x;
            goal_y = position().y;
            });
        
        //for each different follwer, make it follow its former robot, and within certain distance
        if (id() == 1) {
            Agent& other_robot = find_agent(0);
            attach_to(other_robot);
            prevent_rotation();
        }if (id() == 2) {
            Agent& other_robot = find_agent(1);
            attach_to(other_robot);
            prevent_rotation();
        }if (id() == 3) {
            Agent& other_robot = find_agent(2);
            attach_to(other_robot);
            prevent_rotation();
        }if (id() == 4) {
            Agent& other_robot = find_agent(3);
            attach_to(other_robot);
            prevent_rotation();
        }
    }
    void start() {}
    void update() {  
        //give the follwer a specific target to move to while keep some distance within it
        move_toward(goal_x, goal_y, 25, 10);
    }
    void stop() {}

    

};

class follower : public Agent {
    public:
    follower(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    followerController c;
};

DECLARE_INTERFACE(follower)

#endif