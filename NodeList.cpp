#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    length = 0;
}

NodeList::~NodeList(){
    // TODO
}

NodeList::NodeList(NodeList& other){
    
    for (int i = 0; i < other.length; i++) {

        nodes[i] = other.getNode(i);
    }
}

int NodeList::getLength(){
    return length;
}

void NodeList::addElement(Node* newPos){
    nodes[length] = newPos;
    length++;
}

void NodeList::addElement(Node* newPos, int index){
    nodes[index] = newPos;
    length++;
}

Node* NodeList::getNode(int i){
    Node* node = nodes[i];
    return node;
}

void NodeList::deleteNodes(){

    for (int i = 0; i < length; i++) {
        delete nodes[i];
        length--;
    }
}