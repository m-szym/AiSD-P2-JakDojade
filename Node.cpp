#include "Node.h"

Node::Node()
        : name(nullptr), arr_index(-1)
{
}

Node::Node(char* name)
        : arr_index(-1)
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

Link* Node::add_link(Link* new_link)
{
        this->links.add_after(new_link);
        return new_link;
}

void Node::set_name(char* new_name)
{
        this->name = new char[strlen(new_name)+1];
        strcpy(this->name, new_name);
}


void Node::print_node()
{
        List2d<Link>* curl = this->links.next;

        std::cout << "Wezeł - miasto o nazwie " << name << " o " << links.root_get_lenght() << " drogachi o numerze " << arr_index << "\n";
        int i = 0;
        while (curl != nullptr)
        {        
                std::cout << i;
                i++;
                curl->cont->print_link();
                
                curl = curl->next;
        
}
}

bool Node::operator==(char* key)
{
        long long hn = hash_string(this->name);
        long long hk = hash_string(key);

        return hk == hn;
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
        if (!special) std::cout << "\tDroga o dlugości: " << length << " z miasta ";
        else if (special) std::cout << "\tLot o dlugości: " << length << " z miasta ";
        if (start_node != nullptr) std::cout << start_node->name;
        else std::cout << "null start";
        std::cout << " do miasta ";
        if (end_node != nullptr) std::cout << end_node->name;
        else std::cout << "null end";
        std::cout << "\n";
}
