#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>

#include "List2d.h"
#include "string_helpers.h"

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

	Link* add_link(Link* new_link);

	void set_name(char* new_name);
	void print_node();

	bool operator==(char* key);
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


