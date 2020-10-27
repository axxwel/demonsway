//
//  StaticTest.hpp
//  demonsway
//
//  Created by alexandre gimeno on 13/10/2020.
//

#ifndef StaticTest_hpp
#define StaticTest_hpp

#include "../DisplayObjects/Demon.hpp"

// structure content where case two same demon match
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

class StaticTest
{
public:
    /**
     * @brief Get the demon list to move in the demons grid.
     * @param demonsActionList list content demon pointer can move.
     * @param demonsInGridList list content all demon pointer in grid.
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
     * @param l case tested line.
     * @param c case tested collumn.
     * @param demonsList list of demon pointer.
     * @return free grid case boolean.
    */
    static bool getCaseFree(int l, int c, std::vector<Demon*> demonsList);
    
private:
    
    /**
     * @brief is the demon win the conflict case.
     * @param demonsList list of demon pointer.
     * @param l case tested line.
     * @return true if case free false else.
    */
    static bool isConflictCaseWin(std::vector<Demon*> demonsList, Demon* demon);
    
    /**
     * @brief test if two demon had same name index.
     * @param demonMtch pointer to the demon mathc structure bitween the two demon.
     * @param demon_1 demon 1 to test.
     * @param demon_2 demon 2 to test.
    */
    static void testDemonMatch(DemonMatch* demonMatch, Demon* demon_1, Demon* demon_2);
    
    /**
     * @brief find a demon by his line collumn location in a list.
     * @param l case tested line.
     * @param c case tested collumn.
     * @param demonsList list of demon pointer.
    */
    static Demon* findDemonByLineCollumn(int l, int c, std::vector<Demon*> demonsList);
};

#endif /* StaticTest_hpp */
