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

    findGoal(env, startNode, goalNode);
}

void PathSolver::findGoal(Env env, Node* start, Node* goal){
    
    int x = 0;
    int y = 0;
    Node* prevNode;

    while (!goalReached) {

        prevNode = currentNode;

        x = currentNode->getRow();
        y = currentNode->getCol();

        // Robot looks around, adds open nodes to open list.
        popOpenList(env, x + 1, y, currentNode);
        popOpenList(env, x - 1, y, currentNode);
        popOpenList(env, x, y + 1, currentNode);
        popOpenList(env, x, y - 1, currentNode); 

        // Robot searches the open list and chooses a node to move to.
        currentNode = forwardSearchAlg(currentNode, goal);

        // Robot back tracks if it encounters a dead end.
        currentNode = backTrack(prevNode, currentNode);
        
        // Current node is added to the nodes the robot has explored.
        nodesExplored->addElement(currentNode);

        std::cout << "Current node X: " << currentNode->getRow() << std::endl;
        std::cout << "Current node Y: " << currentNode->getCol() << std::endl;
        std::cout << "Dist to G: " << currentNode->getEstimatedDist2Goal(goal) << std::endl;  
        std::cout << "Dist travelled: " << currentNode->getDistanceTraveled() << std::endl;
    }
}

void PathSolver::popOpenList(Env env, int x, int y, Node* currentNode){
    
    int ind = 0;
    bool closed = false;
    char envChar = env[x][y];

    if (envChar == SYMBOL_GOAL) {

        goalReached = true;

        std::cout << "Conratulations, Goal Reached!" << std::endl;

    } else {

        closed = checkNodeClosed(x, y, currentNode);

        if(envChar == SYMBOL_EMPTY && !closed) {
            
            int trav = currentNode->getDistanceTraveled() + 1;
            Node* open = new Node(x, y, trav);
            openList->addElement(open);
        }
    }
}

Node* PathSolver::forwardSearchAlg(Node* currentNode, Node* goal){

    int hold1 = 0;
    int hold2 = 0;

    for (int ind1 = 0; ind1 < openList->getLength(); ind1++) {
            
        hold1 = openList->getNode(ind1)->getEstimatedDist2Goal(goal);

        for (int ind2 = 0; ind2 < openList->getLength(); ind2++) {

            hold2 = openList->getNode(ind2)->getEstimatedDist2Goal(goal);

            if (hold1 <= hold2) {

                currentNode = openList->getNode(ind2);
            }
        }
    }

    return currentNode;
}

Node* PathSolver::backTrack(Node* prevNode, Node* currentNode) {

    if (prevNode->getRow() == currentNode->getRow()
        && prevNode->getCol() == currentNode->getCol() 
        && !goalReached) {
            
        bool notExplored = true;
        std::cout << "Dead end, backtracking...." << std::endl;
        
        for (int a = 0; a < openList->getLength(); a++) {

            notExplored = true;

            for (int b = 0; b < nodesExplored->getLength(); b++) {

                if (openList->getNode(a) == nodesExplored->getNode(b)) {

                    notExplored = false;
                }
            }

            if (notExplored) {

                currentNode = openList->getNode(a);
            }   
        }
    }

    return currentNode; 
}

NodeList* PathSolver::getNodesExplored(){

    NodeList* copy = new NodeList();

    for (int i = 0; i < nodesExplored->getLength(); i++) {
        Node* node = nodesExplored->getNode(i);
        copy->addElement(node);
    }

    return copy;
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

bool PathSolver::checkNodeClosed(int x, int y, Node* currentNode){

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

