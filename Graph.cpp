#include "Graph.h"

Node* Graph::insert_to_hash(Node* node)
{
	this->hash_nodes->insert(node->name, node);
	//std::cout << " -> nar[" << node->arr_index << "]\n";
	this->nar[node->arr_index] = node;

	return node;
}

Node* Graph::get_from_hash(char* name)
{
	return this->hash_nodes->operator[](name);
}

Graph::Graph(int nodes_to_set)
	: nodes_n(nodes_to_set)
{
	this->hash_nodes = new HashTablet<Node>(nodes_to_set);
	this->nodes = new Node[nodes_n];
	this->nar = new Node*[nodes_n];
	for (int i = 0; i < nodes_n; i++)
	{
		nar[i] = nullptr;
	}
}

Graph::~Graph()
{
	delete hash_nodes;
	delete[] nar;
	delete[] nodes;
	nods.root_delete_list();
}

void Graph::print_graph()
{
	List2d<Node>* cur = this->nods.next;
	std::cout << "\n\t--- Graf ---\n\n";
	while (cur != nullptr) {
		cur->cont->print_node();
		cur = cur->next;
		std::cout << "\n";
	}
	std::cout << "\n\t--- Koniec ---\n\n";
}

void Graph::print_nodes()
{
	List2d<Node>* cur = this->nods.next;
	std::cout << "\n\t--- Graf ---\n\n";
	for (int i = 0; i < nodes_n; i++)
	{
		std::cout << i << " -- ";
		nodes[i].print_node();
	}
	std::cout << "\n\t--- Koniec ---\n\n";
}


List2d<Node>* Graph::get_city_by_name(char* name)
{
	List2d<Node>* cur = nods.next;
	while (cur != nullptr)
	{
		if (strcmp(cur->cont->name, name) == 0) 
			return cur;

		cur = cur->next;
	}

	return nullptr;
}

int Graph::get_city_node_i_by_name(char* name)
{
	for (int i = 0; i < nodes_n; i++)
	{
		if (strcmp(nodes[i].name, name) == 0) return i;
	}
	return -1;
}
