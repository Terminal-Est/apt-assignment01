#ifndef COSC_ASSIGN_ONE_NODE
#define COSC_ASSIGN_ONE_NODE

#include "Types.h"

class Node{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Desctructor
    Node(int row, int col, int dist_traveled);
    ~Node();

    // get row-coodinate of the node
    int getRow();

    // get column-coodinate of the node
    int getCol();

    //getter and setter for distance traveled
    int getDistanceTraveled();
    void setDistanceTraveled(int dist_traveled);

    //getter for estimated dist to goal - need to return -> Manhatten distance + distance traveled
    int getEstimatedDist2Goal(Node* goal);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    // Setter for on blocked path bool.
    void setOnBlockedPath(bool blocked);

    // Getter for on blocked path bool.
    bool getOnBlockedPath();

    // Setter for direction moved char.
    void setDirectionMoved(char dir);

    // Getter for direction moved char.
    char getDirectionMoved();

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    int row;
    int col;
    int dist_traveled;  // distance from start node

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    // The direction in which the robot travelled from this node.
    char directionMoved;

    // Boolean to indicate that this node is on a blocked path.
    bool onNoPath;
};

#endif //COSC_ASSIGN_ONE_NODE