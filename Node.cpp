#include "Node.h"

Node::Node()
	: name(nullptr)
{
}

Node::Node(char* name)
{
	this->name = new char[strlen(name)];
	strcpy(this->name, name);
}

Node::Node(char* name, int index)
	: arr_index(index)
{
	this->name = new char[strlen(name)];
	strcpy(this->name, name);
}

Node::~Node()
{
	delete[] this->name;
	this->links.root_delete_list();
}

void Node::set_name(char* new_name)
{
	this->name = new char[strlen(new_name)+1];
	strcpy(this->name, new_name);
}

void Node::print_node()
{
	List2d<Link>* curl = this->links.next;

	std::cout << "Weze³ - miato o nazwie " << name << " o " << links.root_get_lenght() << " drogachi o numerze " << arr_index << "\n";
	int i = 0;
	while (curl != nullptr)
	{	
		std::cout << i;
		i++;
		curl->cont->print_link();
		
		curl = curl->next;
	}
}

Link::Link(int new_length, Node* new_start_node, Node* new_end_node)
	: length(new_length), start_node(new_start_node), end_node(new_end_node), special(false)
{
}

Link::Link(int new_length, Node* new_start_node, Node* new_end_node, bool new_special)
	: length(new_length), start_node(new_start_node), end_node(new_end_node), special(true)
{
}

void Link::print_link()
{
	if (!special) std::cout << "\tDroga o dlugoœci: " << length << " z miasta ";
	else if (special) std::cout << "\tLot o dlugoœci: " << length << " z miasta ";
	if (start_node != nullptr) std::cout << start_node->name;
	else std::cout << "null start";
	std::cout << " do miasta ";
	if (end_node != nullptr) std::cout << end_node->name;
	else std::cout << "null end";
	std::cout << "\n";
}