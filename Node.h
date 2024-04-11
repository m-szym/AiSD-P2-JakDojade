#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>

#include "string_helpers.h"
#include "lib/LinkedList.hpp"

class Link;


class Node
{
private:
    char* name;
    int index;
    LinkedList<Link*> links;

public:
    Node();
    Node(char* name, int index = -1);
    ~Node();

    void print();

    void setName(char* newName);
    Link* addLink(Link* newLink);
    
    char* getName() { return name; }
    int getIndex() { return index; }
    LinkedList<Link*>& getLinks() { return links; }

friend class Graph;
friend class Link;
};


class Link
{
private:
    int length;
    bool special;
    Node* startNode;
    Node* endNode;

public:
    Link(int newLength, Node* newStartNode, Node* newEndNode, bool isSpecial = false);

    void print();

    int getLength() { return length; }
    bool isSpecial() { return special; }
    Node* getStartNode() { return startNode; }
    Node* getEndNode() { return endNode; }

friend class Node;
friend class Graph;
};