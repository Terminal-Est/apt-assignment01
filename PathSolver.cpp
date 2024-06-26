#include "PathSolver.h"
#include "Types.h"
#include <iostream>

PathSolver::PathSolver(){
    openList = new NodeList();
    nodesExplored = new NodeList();
    startNode = new Node(0, 0, 0);
    goalNode = new Node(0, 0, 0);
    goalReached = false;
}

PathSolver::~PathSolver(){
    delete nodesExplored;
    delete openList;
}

void PathSolver::forwardSearch(Env env){

    Coord end = getNodeParams(env, SYMBOL_GOAL);
    Coord start = getNodeParams(env, SYMBOL_START);

    // Get the start and end points of the maze.
    startNode = new Node(start.x, start.y, 0);
    goalNode = new Node(end.x, end.y, 0);

    // Set current node to start node.
    currentNode = new Node(start.x, start.y, 0);

    // Add the start node to the open list.
    openList->addElement(currentNode);

    // Print out maze starting info.
    std::cout << std::endl;
    std::cout << "Start Coordinates: " << start.x << "," << start.y << std::endl;
    std::cout << "Goal Coordinates: " << end.x << "," << end.y << std::endl;
    std::cout << "Distance to Goal: " << startNode->getEstimatedDist2Goal(goalNode) << std::endl;

    // Call the find goal algorithm.
    findGoal(env, startNode, goalNode);
}

void PathSolver::findGoal(Env env, Node* start, Node* goal){
    
    int x = 0;
    int y = 0;

    // Create a node to store the node previously visted.
    Node* prevNode = new Node(0 ,0, 0);

    // Add the start node to the nodes we have explored.
    nodesExplored->addElement(start);

    while (!goalReached) {

        // set the previous node to the current node.
        prevNode = currentNode;

        x = currentNode->getRow();
        y = currentNode->getCol();

        // Robot looks around, adds open nodes to open list.
        lookAround(env, x, y, currentNode);

        // Robot checks open list to see if it contains the goal node.
        setGoalReached(env, currentNode);

        // Robot searches the open list and chooses a node to move to.
        currentNode = forwardSearchAlg(currentNode, goal);

        // Robot back tracks if it encounters a dead end.
        currentNode = backTrack(prevNode, currentNode);

        // If the robot is hasn't reached the goal and the node is not on 
        // a blocked path, add it to the explored list.
        if (!goalReached && !currentNode->getOnBlockedPath()) {

            // Set the node direction char for later printing.        
            setNodeDirectionChar(prevNode, currentNode);
            nodesExplored->addElement(currentNode);

        } else {

            // If goal reached, add goal to nodesExplored for back tracking.
            nodesExplored->addElement(currentNode);
            nodesExplored->addElement(goal);
            currentNode = goal;
            setNodeDirectionChar(prevNode, currentNode);
            std::cout << "Conratulations, Goal Reached!" << std::endl;
        }
    }
}

void PathSolver::lookAround(Env env, int x, int y, Node* currentNode){
    
    // Look at each node surrounding the current node.
    popOpenList(env, x + 1, y, currentNode);
    popOpenList(env, x - 1, y, currentNode);
    popOpenList(env, x, y + 1, currentNode);
    popOpenList(env, x, y - 1, currentNode); 
}

void PathSolver::popOpenList(Env env, int x, int y, Node* currentNode){
    
    int ind = 0;
    bool closed = false;
    char envChar = env[x][y];

    // Returns false if the node searched is not closed.
    closed = checkNodeClosed(x, y);

    // If the node is '.' and not closed, add it to the
    // open list.
    if (envChar == SYMBOL_EMPTY && !closed) {
        
        int trav = currentNode->getDistanceTraveled() + 1;
        Node* open = new Node(x, y, trav);
        openList->addElement(open);
    }
}

void PathSolver::setNodeDirectionChar(Node* toSet, Node* currentNode){

    // Switcher IF to set node direction moved.
    if (toSet->getRow() < currentNode->getRow()) {

        toSet->setDirectionMoved(SYMBOL_RIGHT);

    } else if (toSet->getRow() > currentNode->getRow()) {

        toSet->setDirectionMoved(SYMBOL_LEFT);

    } else if (toSet->getCol() > currentNode->getCol()) {

        toSet->setDirectionMoved(SYMBOL_UP);

    } else if (toSet->getCol() < currentNode->getCol()) {

        toSet->setDirectionMoved(SYMBOL_DOWN);
    }
}

Node* PathSolver::forwardSearchAlg(Node* currentNode, Node* goal){

    Node* hold1 = new Node(0, 0, 0);
    Node* hold2 = new Node(0, 0 ,0);

    // Compares all open list nodes against each other and returns
    // the node closest to the goal node.
    for (int ind1 = 0; ind1 < openList->getLength(); ind1++) {
            
        hold1 = openList->getNode(ind1);

        for (int ind2 = 0; ind2 < openList->getLength(); ind2++) {

            hold2 = openList->getNode(ind2);
            currentNode = compareDistToGoal(hold1, hold2, goal);
        }
    }

    return currentNode;
}

Node* PathSolver::backTrack(Node* prevNode, Node* currentNode) {

    // Robot checks it's current node address aganst the previous.
    // If the address is the same, a blocked path is assumed and 
    // a backtrack is triggered.
    if (prevNode->getRow() == currentNode->getRow()
        && prevNode->getCol() == currentNode->getCol() 
        && !goalReached) {
        
        bool notExplored = false;

        std::cout << "Dead end, backtracking...." << std::endl;
        
        // Robot checks the openlist against the explored list
        // until it finds a node in the open list it hasn't 
        // explored, it will then set its current node to the 
        // unexplored node.
        for (int a = 0; a < openList->getLength(); a++) {

            notExplored = true;

            for (int b = 0; b < nodesExplored->getLength(); b++) {

                if (openList->getNode(a) == nodesExplored->getNode(b)) {
                    
                    notExplored = false;
                }
            }

            // Robot marks nodes along the backtracked path as blocked.
            if (a != 0 && notExplored) {

                int set = a;

                while (set < nodesExplored->getLength()) {

                    nodesExplored->getNode(set)->setOnBlockedPath(true);
                    set++;    
                }

                // Set current node to the next free on the open list.
                currentNode = openList->getNode(a - 1);
            }   
        }
    }

    return currentNode; 
}

NodeList* PathSolver::getNodesExplored(){

    NodeList* copy = new NodeList();

    // Creat a deep copy of nodes explored.
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

    // Return a Coord based on the node char.
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

bool PathSolver::checkNodeClosed(int x, int y){

    int ind = 0;
    bool closed = false;

    // Search the nodes explored against the supplied
    // x,y return true if the node exists in the list.
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

void PathSolver::setGoalReached(Env env, Node* currentNode){

    // IF network for checking if the current node is near 
    // the goal.
    if (env[currentNode->getRow()][currentNode->getCol() + 1] 
        == SYMBOL_GOAL) {
        goalReached = true;
    }

    if (env[currentNode->getRow()][currentNode->getCol() - 1] 
        == SYMBOL_GOAL) {
        goalReached = true;
    }

    if (env[currentNode->getRow() + 1][currentNode->getCol()] 
        == SYMBOL_GOAL) {
        goalReached = true;
    }

    if (env[currentNode->getRow() - 1][currentNode->getCol()] 
        == SYMBOL_GOAL) {
        goalReached = true;
    }
}

NodeList* PathSolver::getPath(Env env){

    int expLen = nodesExplored->getLength() - 1;
    NodeList* path = new NodeList();

    for (int i = 2; i < expLen; i++) {

        Node* first = nodesExplored->getNode(i);
        Node* next = nodesExplored->getNode(i - 1);
        Node* node = compareDistTrav(first, next);

        if (!node->getOnBlockedPath()) {

            path->addElement(node);
        }
    }

    return path;
}

Node* PathSolver::compareDistTrav(Node* nodeA, Node* nodeB){

    Node* node = new Node(0, 0, 0);

    if (nodeA->getDistanceTraveled() < nodeB->getDistanceTraveled()) {

        node = nodeA;

    } else {

        node = nodeB;
    }

    return node;
}

Node* PathSolver::compareDistToGoal(Node* nodeA, Node* nodeB, Node* goal){

    Node* node = new Node(0, 0, 0);

    if (nodeA->getEstimatedDist2Goal(goal) <= nodeB->getEstimatedDist2Goal(goal)) {

        node = nodeA;

    } else {

        node = nodeB;
    }

    return node;
}
