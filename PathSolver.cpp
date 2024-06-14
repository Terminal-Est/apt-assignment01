#include "PathSolver.h"
#include "Types.h"
#include <iostream>

PathSolver::PathSolver(){
    // TODO
}

PathSolver::~PathSolver(){
    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env){

    Coord start = getStartEndCoordinates(env, SYMBOL_START);
    Coord end = getStartEndCoordinates(env, SYMBOL_GOAL);
}

NodeList* PathSolver::getNodesExplored(){
    return nodesExplored;
}

NodeList* PathSolver::getPath(Env env){
    return pathList;
}

Coord PathSolver::getStartEndCoordinates(Env env, char loc) {

    int xSize = ENV_DIM;
    int ySize = ENV_DIM;
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
//-----------------------------