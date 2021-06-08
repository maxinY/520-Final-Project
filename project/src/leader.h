#ifndef __LEADER_AGENT__H
#define __LEADER_AGENT__H 

#include <string>
#include <math.h>
#include "enviro.h"

namespace
{

    using namespace enviro;
    //this class making sure the robot can move in straight line
    class MovingForward : public State, public AgentInterface
    {
    public:
        void entry(const Event& e) {}
        void during()
        {                
            cpVect coord = position();
            //while moving forward, not let the leader to have angular velocity to avoid rotating
            track_velocity(45, 0, 8, 8);//(double linear_velocity, double angular_velocity, double kL = 10, double kR = 10)

            if (sensor_value(0) < 40)
            {
                emit(Event(tick_name));
            }
            //sending data from leader to let the follwer know the position
            emit(Event("goal_change", {
                {"x", position().x },
                {"y", position().y }

                }));
        }
        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };
    //this class make sure the robot can turn around at the corner
    class Rotating : public State, public AgentInterface
    {
    public:
        void entry(const Event& e) { rate = 1; }
        void during()
        {
            //while at the corner, let the robot to only have angular velocity and let it rotate
            track_velocity(0, rate);
            if (sensor_value(0) > 140) {
                emit(Event(tick_name));
            }
        }
        void exit(const Event& e) {}
        double rate;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };
    //this class is the leader control class to combine all the action of the leader including moving forward and rotating
    class leaderController : public StateMachine, public AgentInterface
    {
    

    public:
        leaderController() : StateMachine()
        {

            set_initial(moving_forward);
            tick_name = "tick_" + std::to_string(rand() % 1000); // use an agent specific generated
                                                                 // event name in case there are
                                                                 // multiple instances of this class
            add_transition(tick_name, moving_forward, rotating);
            add_transition(tick_name, rotating, moving_forward);
            moving_forward.set_tick_name(tick_name);
            rotating.set_tick_name(tick_name);
        }

        
        MovingForward moving_forward;
        Rotating rotating;
        std::string tick_name;
    };

    class leader : public Agent
    {

    public:
        leader(json spec, World& world) : Agent(spec, world)
        {
            add_process(wc);
        }

        leaderController wc;
    };

    DECLARE_INTERFACE(leader);

}

#endif