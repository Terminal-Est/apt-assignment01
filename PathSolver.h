#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    // A list of reachable nodes.
    NodeList* openList;

    // Find the coordinates of a maze charactirstic.
    Coord getNodeParams(Env env, char loc);

    // Node that the robot is currently on.
    Node* currentNode;

    // Boolean to indicate if the goal is reached.
    bool goalReached;

    // Checks a node to see if it's open.
    void popOpenList(Env env, int x, int y, Node* goalNode);

    // checks a node against the closed list.
    bool checkNodeClosed(int x, int y);

    // Check for goal node.
    void setGoalReached(Env env, int x, int y);

    // Forward search algorithm.
    void forwardSearchAlg(Env env, Node* strat, Node* goal);
};

#endif //COSC_ASSIGN_ONE_PATHSOLVER