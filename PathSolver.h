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

    // Node at the start of the Maze. Designated by S char.
    Node* startNode;

    // Goal node of the Maze. Designated by G char.
    Node* goalNode;

    // Boolean to indicate if the goal is reached.
    bool goalReached;

    // A general use holding node.
    Node* holding;

    // Populates a path list to check for valid travel nodes.
    void popOpenList(Env env, int x, int y, Node* currentNode);

    // checks a node against the closed list.
    bool checkNodeClosed(int x, int y);

    // Check for goal node.
    void setGoalReached(Env env, Node* currentNode);

    // Search forward through the maze to find G.
    void findGoal(Env env, Node* strat, Node* goal);

    // Search forward on a route. Returns a node that is closest on the
    // route towards the goal.
    Node* forwardSearchAlg(Node* currentNode, Node* goal);

    // Backtrack robot if the path is a dead end.
    Node* backTrack(Node* prevNode, Node* currentNode);

    // Instructs the robot to look at surrounding nodes.
    void lookAround(Env env, int x, int y, Node* currentNode);

    // Compare two nodes and return the node that is closest to the goal.
    Node* compareDistTrav(Node* nodeA, Node* nodeB);

    // Compare two nodes and return the node that is closest to the goal.
    Node* compareDistToGoal(Node* nodeA, Node* nodeB, Node* goal);

    // Sets the character which represents the direction travelled by the robot.
    void setNodeDirectionChar(Node* toSet, Node* currentNode);
};

#endif //COSC_ASSIGN_ONE_PATHSOLVER