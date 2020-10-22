//
//  StaticTest.hpp
//  demonsway
//
//  Created by alexandre gimeno on 13/10/2020.
//

#ifndef StaticTest_hpp
#define StaticTest_hpp

#include "../DisplayObjects/Demon.hpp"

struct DemonMatch
{
    bool up = false;
    bool upUp = false;
    
    bool down = false;
    bool downDown = false;
    
    bool left = false;
    bool leftLeft = false;
    
    bool right = false;
    bool rightRight = false;
};

class isSameDemonWay
{
    bool operator()(Demon* demon_A, Demon* demon_B)
    {
        DemonPosition demonPosition_A = demon_A->getDemonGridWayPosition();
        DemonPosition demonPosition_B = demon_B->getDemonGridWayPosition();
        
        if(demonPosition_A.line == demonPosition_B.line &&
           demonPosition_A.collumn == demonPosition_B.collumn)
        {
            return true;
        }
        return false;
    }
};

class StaticTest
{
public:
    /**
     * @brief Get the demon list to move in the demons grid.
     * @param demonsList list content demon pointer.
     * @return demon list to move.
    */
    static std::vector<Demon*> getMoveDemonList(std::vector<Demon*> demonsActionList, std::vector<Demon*> demonsInGridList);
    
    /**
     * @brief Get the demon list to remove in the demons grid.
     * @param demonsList list content demon pointer.
     * @return demon list to remove.
    */
    static std::vector<Demon*> getRemoveDemonList(std::vector<Demon*> demonsList);
    
    /**
     * @brief Get if the case is free on the grid.
     * @param demonsTested demon to test pointer.
     * @param demonsList list content demon pointer.
     * @return true if case free false else.
    */
    static bool getCaseFree(int l, int c, std::vector<Demon*> demonsList);
    
private:
    
    static void testDemonMatch(DemonMatch* demonMtch, Demon* demon_1, Demon* demon_2);
    
    static Demon* findDemonByLineCollumn(std::vector<Demon*> demonsList, int line, int collumn);
    
    static bool getConflictCaseWin(std::vector<Demon*> demonsList, Demon* demon);
};

#endif /* StaticTest_hpp */
