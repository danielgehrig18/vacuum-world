//
//  problem.cpp
//  VacuumSimulator
//
//  Created by Daniel Gehrig on 19/08/16.
//  Copyright © 2016 Daniel Gehrig. All rights reserved.
//

#include "problem.hpp"

int Problem::calculatePayoff(Environment environment)
{
    int payoff=0;
    bool* grid = environment.getGrid();
    int* dimensions = environment.getDimensions();
    
    for (int i=0; i<dimensions[0]*dimensions[1]; i++)
    {
        if (!grid[i]) {
            payoff += freeSpotCost;
        }
    }
    return payoff;
}