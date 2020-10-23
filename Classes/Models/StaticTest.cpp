//
//  StaticTest.cpp
//  demonsway
//
//  Created by alexandre gimeno on 13/10/2020.
//

#include "StaticTest.hpp"

#include "../Models/StaticGrid.hpp"


std::vector<Demon*> StaticTest::getMoveDemonList(std::vector<Demon*> demonsActionList, std::vector<Demon*> demonsInGridList)
{
    std::vector<Demon*> demonsMovingList;
    
    // check witch demon moving in the list and put into a return list.
    std::vector<Demon*>::iterator demonIt;
    for(demonIt = demonsActionList.begin(); demonIt != demonsActionList.end(); demonIt++)
    {
        Demon* demon = *demonIt;
        
        // get the future grid position
        DemonPosition demonPosition = demon->getDemonGridWayPosition();
        int newL = demonPosition.line;
        int newC = demonPosition.collumn;
        
        // check if new case is in grid and
        // if new case is free and
        // if new case is not occuped by an other demon deplacement
        if(newL >= 0 && newL < GRID_SIZE &&
           newC >= 0 && newC < GRID_SIZE &&
           StaticTest::getCaseFree(newL, newC, demonsInGridList) &&
           StaticTest::isConflictCaseWin(demonsActionList, demon))
        {
            demonsMovingList.push_back(demon);
        }
    }
    
    return demonsMovingList;
}

std::vector<Demon*> StaticTest::getRemoveDemonList(std::vector<Demon*> demonsList)
{
    std::vector<Demon*> demonToRemoveList;
    
    return demonToRemoveList;
}

bool StaticTest::getCaseFree(int l, int c, std::vector<Demon*> demonsList)
{
    // check if another demon is on the case (l c) tested
    // return false if find demon
    std::vector<Demon*>::iterator demonIt;
    for(demonIt = demonsList.begin(); demonIt != demonsList.end(); demonIt++)
    {
        Demon* demon = *demonIt;
        DemonPosition demonPos = demon->getDemonGridPosition();
        if(demonPos.line == l && demonPos.collumn == c)
        {
            return false;
        }
    }
    return true;
}

bool StaticTest::isConflictCaseWin(std::vector<Demon*> demonsList, Demon* demon)
{
    // get the future grid position
    DemonPosition demonWayPosition = demon->getDemonGridWayPosition();
    
    // check every demon into demonList
    std::vector<Demon*>::iterator dIt;
    for(dIt = demonsList.begin(); dIt != demonsList.end(); dIt++)
    {
        // check if another demon moving on the new demon position
        Demon* demonConflict = *dIt;
        DemonPosition demonConflictWayPosition = demonConflict->getDemonGridWayPosition();
        if(demonWayPosition.line == demonConflictWayPosition.line &&
           demonWayPosition.collumn == demonConflictWayPosition.collumn)
        {
            // check if demon index is bigger than demon tested
            long demonConflictIndex = std::distance(demonsList.begin(), dIt);
            long demonIndex = std::distance(demonsList.begin(), std::find(demonsList.begin(), demonsList.end(), demon));
            
            if(demonConflictIndex > demonIndex)
            {
                return false;
            }
        }
    }
    
    return true;
}
