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
    
    std::vector<Demon*>::iterator demonIt;
    for(demonIt = demonsActionList.begin(); demonIt != demonsActionList.end(); demonIt++)
    {
        Demon* demon = *demonIt;
        
        DemonPosition demonPosition = demon->getDemonGridWayPosition();
        int newL = demonPosition.line;
        int newC = demonPosition.collumn;
        
        
        
        // check if new case is in grid and if new case is free
        if(newL >= 0 && newL < GRID_SIZE &&
           newC >= 0 && newC < GRID_SIZE &&
           StaticTest::getCaseFree(newL, newC, demonsInGridList) &&
           StaticTest::getConflictCaseWin(demonsActionList, demon))
        {
            demonsMovingList.push_back(demon);
        }
    }
    
    return demonsMovingList;
}


std::vector<Demon*> StaticTest::getRemoveDemonList(std::vector<Demon*> demonsList)
{
    std::vector<Demon*> demonToRemoveList;
    
    for(int d = 0; d < demonsList.size(); d++)
    {
        Demon* demon = demonsList[d];
        if(demon)
        {
            int line = demon->getDemonGridPosition().line;
            int collumn = demon->getDemonGridPosition().collumn;
            
            
            DemonMatch* demonMatchPtr = new DemonMatch();
            for(int t = 0; t < demonsList.size(); t++)
            {
                testDemonMatch(demonMatchPtr, demonsList[d], demonsList[t]);
            }
            
            
            
            if(demonMatchPtr->up && demonMatchPtr->down)
            {
                demonToRemoveList.push_back(demon);
                demonToRemoveList.push_back(findDemonByLineCollumn(demonsList,line + 1, collumn));
                demonToRemoveList.push_back(findDemonByLineCollumn(demonsList,line - 1, collumn));
            }
            
            if(demonMatchPtr->left && demonMatchPtr->right)
            {
                demonToRemoveList.push_back(demon);
                demonToRemoveList.push_back(findDemonByLineCollumn(demonsList,line, collumn - 1));
                demonToRemoveList.push_back(findDemonByLineCollumn(demonsList,line, collumn + 1));
            }
            
            
            if(demonMatchPtr->up && demonMatchPtr->down &&
               (demonMatchPtr->upUp || demonMatchPtr->downDown))
            {
                demonToRemoveList.push_back(demon);
                for(int e = 0; e < demonsList.size(); e++)
                {
                    Demon* demonCollumn= demonsList[d];
                    if(demonCollumn&& demonCollumn->getDemonGridPosition().collumn == collumn)
                    {
                        demonToRemoveList.push_back(demonCollumn);
                    }
                }
            }
            
            if(demonMatchPtr->left && demonMatchPtr->right &&
               (demonMatchPtr->leftLeft || demonMatchPtr->rightRight))
            {
                demonToRemoveList.push_back(demon);
                for(int e = 0; e < demonsList.size(); e++)
                {
                    Demon* demonLine= demonsList[d];
                    if(demonLine&& demonLine->getDemonGridPosition().line == line)
                    {
                        demonToRemoveList.push_back(demonLine);
                    }
                }
            }
            
            if(
               
               (((demonMatchPtr->up && demonMatchPtr->upUp) ||
                (demonMatchPtr->down && demonMatchPtr->downDown)) &&
               ((demonMatchPtr->left && demonMatchPtr->leftLeft) ||
                (demonMatchPtr->right && demonMatchPtr->rightRight)))
               ||
               
               (demonMatchPtr->up && demonMatchPtr->down &&
               demonMatchPtr->left && demonMatchPtr->right)
               )
            {
                demonToRemoveList.push_back(demon);
                for(int e = 0; e < demonsList.size(); e++)
                {
                    Demon* demonCross= demonsList[d];
                    if(demonCross)
                    {
                        if(demonCross->getDemonGridPosition().collumn == collumn)
                        {
                            demonToRemoveList.push_back(demonCross);
                        }
                        if(demonCross->getDemonGridPosition().line == line)
                        {
                            demonToRemoveList.push_back(demonCross);
                        }
                    }
                }
            }
            
            if((demonMatchPtr->up && demonMatchPtr->upUp && demonMatchPtr->down && demonMatchPtr->downDown) ||
               (demonMatchPtr->left && demonMatchPtr->leftLeft && demonMatchPtr->right && demonMatchPtr->rightRight))
            {
                demonToRemoveList = demonsList;
            }
        }
    }
    std::set<Demon*> s;
    for(int i = 0; i < demonToRemoveList.size(); i++)
    {
        s.insert(demonToRemoveList[i]);
    }
    demonToRemoveList.assign(s.begin(), s.end());
    
    return demonToRemoveList;
}

bool StaticTest::getCaseFree(int l, int c, std::vector<Demon*> demonsList)
{
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

void StaticTest::testDemonMatch(DemonMatch* demonMatch, Demon* demon_1, Demon* demon_2)
{
    int demon_1Line = demon_1->getDemonGridPosition().line;
    int demon_1Collumn = demon_1->getDemonGridPosition().collumn;
    int demon_1NameIndex = demon_1->getNameIndex();
    
    int demon_2Line = demon_2->getDemonGridPosition().line;
    int demon_2Collumn = demon_2->getDemonGridPosition().collumn;
    int demon_2NameIndex = demon_2->getNameIndex();
    
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

Demon* StaticTest::findDemonByLineCollumn(std::vector<Demon*> demonsList, int line, int collumn)
{
    Demon* demon = nullptr;
    
    std::vector<Demon*>::iterator dIt;
    for(dIt = demonsList.begin(); dIt != demonsList.end(); dIt++)
    {
        Demon* demonTested = *dIt;
        if(demonTested)
        {
            DemonPosition demonTestedPosition;
            demonTestedPosition = demonTested->getDemonGridPosition();
              
            int lineTested = demonTestedPosition.line;
            int collumnTested = demonTestedPosition.collumn;
            if(lineTested == line && collumnTested == collumn)
            {
                demon = demonTested;
            }
        }
    }
    
    return demon;
}

bool StaticTest::getConflictCaseWin(std::vector<Demon*> demonsInGridList, Demon* demon)
{
    DemonPosition demonWayPosition = demon->getDemonGridWayPosition();
    
    std::vector<Demon*>::iterator dIt;
    for(dIt = demonsInGridList.begin(); dIt != demonsInGridList.end(); dIt++)
    {
        Demon* demonConflict = *dIt;
        DemonPosition demonConflictWayPosition = demonConflict->getDemonGridWayPosition();
        if(demonWayPosition.line == demonConflictWayPosition.line &&
           demonWayPosition.collumn == demonConflictWayPosition.collumn)
        {
            long demonConflictIndex = std::distance(demonsInGridList.begin(), dIt);
            
            long demonIndex = std::distance(demonsInGridList.begin(), std::find(demonsInGridList.begin(), demonsInGridList.end(), demon));
            
            if(demonConflictIndex > demonIndex)
            {
                return false;
            }
        }
    }
    
    return true;
}
