#include "PathSolver.h"
#include "Types.h"
#include <iostream>

PathSolver::PathSolver(){
    openList = new NodeList();
    nodesExplored = new NodeList();
    goalReached = false;
}

PathSolver::~PathSolver(){
    delete nodesExplored;
    delete openList;
}

void PathSolver::forwardSearch(Env env){

    Coord end = getNodeParams(env, SYMBOL_GOAL);
    Coord start = getNodeParams(env, SYMBOL_START);

    Node* startNode = new Node(start.x, start.y, 0);
    Node* goalNode = new Node(end.x, end.y, 0);

    currentNode = new Node(start.x, start.y, 0);

    openList->addElement(currentNode);

    std::cout << std::endl;
    std::cout << "Start Coordinates: " << start.x << "," << start.y << std::endl;
    std::cout << "Goal Coordinates: " << end.x << "," << end.y << std::endl;
    std::cout << "Distance to Goal: " << startNode->getEstimatedDist2Goal(goalNode) << std::endl;

    forwardSearchAlg(env, startNode, goalNode);
}

NodeList* PathSolver::getNodesExplored(){
    return nodesExplored;
}

Coord PathSolver::getNodeParams(Env env, char loc){

    int xSize = ENV_DIM;
    int ySize = ENV_DIM;
    int dist = 0;
    Coord node;

    for (int x = 0; x <= xSize; x++) {

        for (int y = 0; y <= ySize; y++) {

            if (env[x][y] == loc) {

                node.x = x;
                node.y = y;
            }
        }
    }

    return node;
}

void PathSolver::popOpenList(Env env, int x, int y, Node* startNode){
    
    int ind = 0;
    bool explored = false;
    char envChar = env[x][y];

    if (envChar == SYMBOL_GOAL) {

        goalReached = true;
    }

    explored = checkNodeClosed(x, y);

    if(envChar == SYMBOL_EMPTY && !explored) {
        
        int trav = (x - startNode->getRow()) + (y - startNode->getCol());
        Node* open = new Node(x, y, trav);
        openList->addElement(open);
    }
}

bool PathSolver::checkNodeClosed(int x, int y){

    int ind = 0;
    bool closed = false;

    while (ind < nodesExplored->getLength()) {

        Coord exist;

        exist.x = nodesExplored->getNode(ind)->getRow();
        exist.y = nodesExplored->getNode(ind)->getCol();

        if (exist.x == x && exist.y == y) {

            closed = true;
        }

        ind ++;
    }

    return closed;
}

void PathSolver::setGoalReached(Env env, int x, int y){
    if (env[x][y] == SYMBOL_GOAL) {
        goalReached = true;
    }
}

void PathSolver::forwardSearchAlg(Env env, Node* start, Node* goal){
    
    int x = 0;
    int y = 0;
    int hold = 0;
    int currentDist = 0;

    while (!goalReached) {

        x = currentNode->getRow();
        y = currentNode->getCol();

        currentDist = currentNode->getEstimatedDist2Goal(goal);

        //std::cout << "Current dist to Goal: " << currentDist << std::endl;

        popOpenList(env, x + 1, y, start);
        popOpenList(env, x - 1, y, start);
        popOpenList(env, x, y + 1, start);
        popOpenList(env, x, y - 1, start); 

        for (int ind1 = 0; ind1 < openList->getLength(); ind1++) {
            
            hold = openList->getNode(ind1)->getEstimatedDist2Goal(goal);

            for (int ind2 = 0; ind2 < openList->getLength(); ind2++) {

                if (hold < openList->getNode(ind2)->getEstimatedDist2Goal(goal)) {

                    currentNode = openList->getNode(ind2);
                }
            }
        } 

        nodesExplored->addElement(currentNode);

        std::cout << "Current node X: " << currentNode->getRow() << std::endl;
        std::cout << "Current node Y: " << currentNode->getCol() << std::endl;
        std::cout << "Dist to G: " << currentNode->getEstimatedDist2Goal(goal) << std::endl;  
        std::cout << "Dist travelled: " << currentNode->getDistanceTraveled() << std::endl;
    }
}
