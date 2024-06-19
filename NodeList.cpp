#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    length = 0;
}

NodeList::~NodeList(){
    //delete nodes;
}

NodeList::NodeList(NodeList& other){
    // TODO
}

int NodeList::getLength(){
    return length;
}

void NodeList::addElement(Node* newPos){
    nodes[length] = newPos;
    length++;
}

Node* NodeList::getNode(int i){
    Node* node = nodes[i];
    return node;
}