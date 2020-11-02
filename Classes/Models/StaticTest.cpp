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
        if(newL >= 0 && newL < GRID_NBR_CASE &&
           newC >= 0 && newC < GRID_NBR_CASE &&
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
    
    // check witch demon removing in the list and put into a return list.
    for(int d = 0; d < demonsList.size(); d++)
    {
        // get demon tested grid position
        Demon* demon = demonsList[d];
        int l = demon->getDemonGridPosition().line;
        int c = demon->getDemonGridPosition().collumn;
        
        // init demon match structure
        DemonMatch* demonMatchPtr = new DemonMatch();
        for(int t = 0; t < demonsList.size(); t++)
        {
            testDemonMatch(demonMatchPtr, demonsList[d], demonsList[t]);
        }
        
        // set a vector position that content case can be removed
        std::vector<std::vector<int>> positionsRemoveList;
        
        // five demons beside remove all the grid
        if((demonMatchPtr->up && demonMatchPtr->upUp && demonMatchPtr->down && demonMatchPtr->downDown) ||
           (demonMatchPtr->left && demonMatchPtr->leftLeft && demonMatchPtr->right && demonMatchPtr->rightRight))
        {
            return demonsList;
        }
        
        // demon are place in cross or L, push all the cases line and collumn into the position list
            //cross
        if((demonMatchPtr->up && demonMatchPtr->down &&
           demonMatchPtr->left && demonMatchPtr->right)||
           // L, up-right
           (demonMatchPtr->up && demonMatchPtr->upUp &&
           demonMatchPtr->right && demonMatchPtr->rightRight)||
           // L, down-right
           (demonMatchPtr->down && demonMatchPtr->downDown &&
           demonMatchPtr->right && demonMatchPtr->rightRight)||
           // L, up-left
           (demonMatchPtr->up && demonMatchPtr->upUp &&
           demonMatchPtr->left && demonMatchPtr->leftLeft)||
           // L, down-left
           (demonMatchPtr->down && demonMatchPtr->downDown &&
           demonMatchPtr->left && demonMatchPtr->leftLeft))
        {
            positionsRemoveList.insert(positionsRemoveList.end(), {{l,0}, {l,1}, {l,2}, {l,3}, {l,4}, {l,5},{0,c}, {1,c}, {2,c}, {3,c}, {4,c}, {5,c}});
        }
        
        if(demonMatchPtr->up && demonMatchPtr->down)
        {
            // four demon beside in line, push all the cases line into the position list
            if(demonMatchPtr->upUp || demonMatchPtr->downDown)
            {
                positionsRemoveList.insert(positionsRemoveList.end(), {{0,c}, {1,c}, {2,c}, {3,c}, {4,c}, {5,c}});
            }
            // three demon beside in line, push the three cases into the the position list
            else
            {
                positionsRemoveList.insert(positionsRemoveList.end(),{{l-1,c}, {l,c}, {l+1,c}});
            }
        }
        
        if(demonMatchPtr->left && demonMatchPtr->right)
        {
            // four demon beside in collumn, push all the cases collumn into the position list
            if(demonMatchPtr->leftLeft || demonMatchPtr->rightRight)
            {
                positionsRemoveList.insert(positionsRemoveList.end(), {{l,0}, {l,1}, {l,2}, {l,3}, {l,4}, {l,5}});
            }
            // three demon beside in collumn, push the three cases into the the position list
            else
            {
                positionsRemoveList.insert(positionsRemoveList.end(),{{l,c-1}, {l,c}, {l,c+1}});
            }
        }
        
        // fill the remove demon list if cases content demon
        for(int p = 0; p < positionsRemoveList.size(); p++)
        {
            const int l = positionsRemoveList[p][0];
            const int c = positionsRemoveList[p][1];
            
            Demon* removeDemon = findDemonByLineCollumn(l, c, demonsList);
            if(removeDemon)
            {
                demonToRemoveList.push_back(findDemonByLineCollumn(l, c, demonsList));
            }
        }
    }
    
    // remove duplicate demon in remove demon list
    std::sort( demonToRemoveList.begin(), demonToRemoveList.end() );
    demonToRemoveList.erase( std::unique( demonToRemoveList.begin(), demonToRemoveList.end() ), demonToRemoveList.end() );
    
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

void StaticTest::testDemonMatch(DemonMatch* demonMatch, Demon* demon_1, Demon* demon_2)
{
    // get demon one position into the grid
    int demon_1Line = demon_1->getDemonGridPosition().line;
    int demon_1Collumn = demon_1->getDemonGridPosition().collumn;
    int demon_1NameIndex = demon_1->getNameIndex();
    
    // get demon two position into the grid
    int demon_2Line = demon_2->getDemonGridPosition().line;
    int demon_2Collumn = demon_2->getDemonGridPosition().collumn;
    int demon_2NameIndex = demon_2->getNameIndex();
    
    // set the demon match structure pointer position to true
    // if content same demon name index
    if(demon_1NameIndex == demon_2NameIndex)
    {
        if(demon_1Line - 1== demon_2Line && demon_1Collumn == demon_2Collumn)
            demonMatch->up = true;
        
        if(demon_1Line - 2== demon_2Line && demon_1Collumn == demon_2Collumn)
            demonMatch->upUp = true;
        
        if(demon_1Line + 1== demon_2Line && demon_1Collumn == demon_2Collumn)
            demonMatch->down = true;
            
        if(demon_1Line + 2== demon_2Line && demon_1Collumn == demon_2Collumn)
            demonMatch->downDown = true;
            
        if(demon_1Line == demon_2Line && demon_1Collumn - 1 == demon_2Collumn)
            demonMatch->left = true;
            
        if(demon_1Line == demon_2Line && demon_1Collumn - 2 == demon_2Collumn)
            demonMatch->leftLeft = true;
            
        if(demon_1Line == demon_2Line && demon_1Collumn + 1 == demon_2Collumn)
            demonMatch->right = true;
            
        if(demon_1Line == demon_2Line && demon_1Collumn + 2 == demon_2Collumn)
            demonMatch->rightRight = true;
    }
}

Demon* StaticTest::findDemonByLineCollumn(int l, int c, std::vector<Demon*> demonsList)
{
    Demon* demon = nullptr;
    
    // check all demon in the list.
    std::vector<Demon*>::iterator dIt;
    for(dIt = demonsList.begin(); dIt != demonsList.end(); dIt++)
    {
        // get demon position
        Demon* demonTested = *dIt;
        DemonPosition demonTestedPosition;
        demonTestedPosition = demonTested->getDemonGridPosition();
          
        // test what demon position match with line and collumn
        int lineTested = demonTestedPosition.line;
        int collumnTested = demonTestedPosition.collumn;
        if(lineTested == l && collumnTested == c)
        {
            demon = demonTested;
        }
    }
    
    return demon;
}
