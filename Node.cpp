#include "Node.h"

Node::Node()
	: name(nullptr)
{
}

Node::Node(char* name)
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
}

Node::Node(char* name, int index)
	: arr_index(index)
{
	this->name = new char[strlen(name)+1];
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

Node* Node::sort_links()
{
	List2d<Link>* cur = this->links.next;
	List2d<Link>* tmp = nullptr;
	List2d<Link>* tmpprev = nullptr;
	List2d<Link>* tmpnext = nullptr;
	int n = this->links.root_get_lenght();
	bool swapped = true;

	while (swapped)
	{
		swapped = false;
		cur = this->links.next;
		for (int i = 0; i < n; i++)
		{
			if (cur == nullptr)
			{
				std::cout << "cur==nullptr i=" << i << " node: " << this->name << "\n";
				break;
			}

			if (cur->next != nullptr && cur->cont->length > cur->next->cont->length)
			{
				tmp = cur->next;
				tmpprev = cur->prev;
				tmpnext = cur->next->next;

				if (tmpprev != nullptr)
					tmpprev->next = tmp;

				if (tmpnext != nullptr)
					tmpnext->prev = cur;

				tmp->next = cur;
				tmp->prev = tmpprev;

				cur->prev = tmp;
				cur->next = tmp->next;

				swapped = true;
			}
			cur = cur->next;
		}
	}

	//for (int j = n-1; j > 0; j--)
	//{
	//	for (int i = 0; i < j; i++)
	//	{
	//		if (cur->next != nullptr && cur->cont->length > cur->next->cont->length)
	//		{
	//			tmp = cur->next;
	//			tmpprev = cur->prev;
	//			tmpnext = cur->next->next;

	//			if (tmpprev != nullptr)
	//				tmpprev->next = tmp;

	//			if (tmpnext != nullptr)
	//				tmpnext->prev = cur;

	//			tmp->next = cur;
	//			tmp->prev = tmpprev;

	//			cur->prev = tmp;
	//			cur->next = tmp->next;

	//			swapped = true;
	//		}
	//	}
	//}






	return this;
}

void Node::print_node()
{
	List2d<Link>* curl = this->links.next;

	std::cout << "Weze� - miato o nazwie " << name << " o " << links.root_get_lenght() << " drogachi o numerze " << arr_index << "\n";
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
	if (!special) std::cout << "\tDroga o dlugo�ci: " << length << " z miasta ";
	else if (special) std::cout << "\tLot o dlugo�ci: " << length << " z miasta ";
	if (start_node != nullptr) std::cout << start_node->name;
	else std::cout << "null start";
	std::cout << " do miasta ";
	if (end_node != nullptr) std::cout << end_node->name;
	else std::cout << "null end";
	std::cout << "\n";
}

bool Node::operator==(char* key)
{
	long long this_name_hash = hash_string(this->name);
	long long key_hash = hash_string(key);

	return key_hash == this_name_hash;
}
