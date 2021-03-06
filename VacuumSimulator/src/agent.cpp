//
//  agent.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "vaccuumworld/agent.hpp"

void Agent::Initialize(DirtSensor *dirt_sensor_pointer,
                       ProximitySensor *proximity_sensor_pointer,
                       DirectionSensor *direction_sensor_pointer,
                       LocationSensor *location_sensor_pointer, Motor *motor_pointer,
                       Sucker *sucker_pointer, vector<vector<int> > map, Visualizer &visualizer)
{
    dirt_sensor_pointer_ = dirt_sensor_pointer;
    proximity_sensor_pointer_ = proximity_sensor_pointer;
    direction_sensor_pointer_ = direction_sensor_pointer;
    location_sensor_pointer_ = location_sensor_pointer;
    
    motor_pointer_ = motor_pointer;
    sucker_pointer_ = sucker_pointer;
    
    state_ = map;
    
    visualizer_ = visualizer;
    strategy_.Initialize(visualizer);
    
    strategy_.SetType(dirt_sensor_pointer_ -> GetStatus(),
                      proximity_sensor_pointer_ -> GetStatus(),
                      direction_sensor_pointer_ -> GetStatus(),
                      location_sensor_pointer_ -> GetStatus(),
                      motor_pointer_ -> GetStatus(),
                      sucker_pointer_ -> GetStatus());
};

void Agent::ExecuteAction()
{
    if (!strategy_.ActionPlanned())
    {
        if (visualizer_.visualize_)
        {
            cout << "planning action..." << endl;
        }
        
        strategy_.PlanAction(dirt_sensor_pointer_ -> GetValue(),
                             proximity_sensor_pointer_ -> GetValue(),
                             direction_sensor_pointer_ -> GetValue(),
                             location_sensor_pointer_ -> GetValue(), state_);
    }
    char action = strategy_.ActionSelection();
    
    // TODO: make smarter decision which actuator to take.
    if (motor_pointer_ -> IsApplicable(action))
    {
        motor_pointer_ -> Execute(action);
    }
    else if (sucker_pointer_ -> IsApplicable(action))
    {
        sucker_pointer_ -> Execute(action);
        array<int, 2> location = location_sensor_pointer_ -> GetValue();
        state_[location[0]][location[1]] = 0;
    }
}