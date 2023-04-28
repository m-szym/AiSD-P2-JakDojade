#pragma once
#include "List2d.h"
#include <cstring>

class Link;

class Node
{
public:
	char* name;
	int arr_index;
	List2d<Link> links;
	Node();
	Node(char* name);
	Node(char* name, int index);
	~Node();
	void set_name(char* new_name);
	Node* sort_links();

	void print_node();
};

class Link
{
public:
	int length;
	bool special;
	Node* start_node;
	Node* end_node;

	Link(int new_length, Node* new_start_node, Node* new_end_node);
	Link(int new_length, Node* new_start_node, Node* new_end_node, bool new_special);

	void print_link();
};


