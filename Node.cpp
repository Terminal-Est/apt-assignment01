#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    Node::row = row;
    Node::col = col;
    Node::dist_traveled = dist_traveled;
}

Node::~Node(){
}

int Node::getRow(){
    return row;
}

int Node::getCol(){
    return col;
}

int Node::getDistanceTraveled(){
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    Node::dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    int manhatten = abs(col - goal->col) + abs(row - goal->row);
    int est = dist_traveled + manhatten;
    return manhatten;
}
    
//--------------------------------                             