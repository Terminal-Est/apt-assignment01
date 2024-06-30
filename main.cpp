#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <cstring>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env, std::string fname);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);

int main(int argc, char* argv[]){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    //std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    //testNode();
    //testNodeList();

    // will print out results of the path file passed as the first arg.   
    std::string fname = "";

    if (argc > 1) {
        fname = argv[1];
    }
 
    std::cout << "ROBOT PATHING PROGRAM!" << std::endl << std::endl;

    // Load Environment 
    Env env;

    if (fname != "") {

         readEnvStdin(env, fname);
    
        // Solve using forwardSearch
        // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
        PathSolver* pathSolver = new PathSolver();
        pathSolver->forwardSearch(env);

        NodeList* exploredPositions = nullptr;
        exploredPositions = pathSolver->getNodesExplored();

    
        // Get the path
        // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
        NodeList* solution = pathSolver->getPath(env);

        printEnvStdout(env, solution);

        delete pathSolver;
        delete exploredPositions;
        delete solution;

    } else {

        std::cout << "Please enter file name as Argument" << std::endl;

    }

    return EXIT_SUCCESS;
}

// Read a the input file from the fname supplied as arg.
void readEnvStdin(Env env, std::string fname){

    std::ifstream file("sampleTest/" + fname + ".env");
    std::string line = "";
    int y = 0;

    // Loop through the file line by line and read in each
    // line as a string.
    while (std::getline(file, line)) {
        
        // Copy line string into character array.
        char chrLnArr[ENV_DIM + 1];
        std::strcpy(chrLnArr, line.c_str());

        // Loop through char array and print out the environment
        // to console.
        for (int x = 0; x < (int)sizeof(chrLnArr) - 1; x++) {
       
            env[x][y] = chrLnArr[x];
            std::cout << env[x][y];
        }

        std::cout << std::endl;
        y++;
    }
}

// Loop through the environment and overlay the solution.
void printEnvStdout(Env env, NodeList* solution) {

    int x = 0;
    int y = 0;

    // Set a space first.
    std::cout << std::endl;

    for (int i = 0; i < solution->getLength(); i++){

        // Set node pointer to solution node i
        Node* node = solution->getNode(i);
        // 
        env[node->getRow()][node->getCol()] = node->getDirectionMoved();

    }

    // Print out solution.
    while (y < ENV_DIM) {

        x = 0;

        while (x < ENV_DIM) {

            std::cout << env[x][y];
            x++;
        }

        std::cout << std::endl;
        y++;
    }
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}