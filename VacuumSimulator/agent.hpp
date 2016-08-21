//
//  agent.hpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 07/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#ifndef agent_hpp
#define agent_hpp

#include "dirt_sensor.hpp"
#include "location_sensor.hpp"
#include "proximity_sensor.hpp"
#include "strategy.hpp"

using namespace std;

class Agent
// The agent is an object that can perform actions by consulting its strategy and update its belief state based on sensor input.
{
private:
    // sensor that is used to update the belief-state of the agent.
    LocationSensor* locationSensorPtr;
    DirtSensor* dirtSensorPtr;
    ProximitySensor* proximitySensorPtr;
    
    // strategy
    Strategy strategy;
    
public:
    void init(LocationSensor* ptr1, DirtSensor* ptr2, ProximitySensor* ptr3, char strategy);
    char actionSelection();
};

#endif /* agent_hpp */