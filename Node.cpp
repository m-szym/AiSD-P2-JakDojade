#include "Node.h"

Node::Node()
    : name(nullptr), arr_index(-1)
{}

Node::Node(char* name, int index = -1)
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

Link* Node::addLink(Link* new_link)
{
    this->links.add_after(new_link);
    return new_link;
}

void Node::setName(char* new_name)
{
    this->name = new char[strlen(new_name)+1];
    strcpy(this->name, new_name);
}


void Node::print()
{
    List2d<Link>* curl = this->links.next;

    std::cout << "Wezeł - miasto o nazwie " << name << " o " << links.root_get_lenght() << " drogach o numerze " << arr_index << "\n";
    int i = 0;
    while (curl != nullptr)
    {        
        std::cout << i;
        i++;
        curl->cont->print();
        
        curl = curl->next;
        
    }
}

bool Node::operator==(char* key)
{
    long long hn = hash_string(this->name);
    long long hk = hash_string(key);

    return hk == hn;
}



Link::Link(int newLength, Node* newStartNode, Node* newEndNode, bool isSpecial = false)
    : length(newLength), startNode(newStartNode), endNode(newEndNode), special(isSpecial)
{}


void Link::print()
{
    if (!special) 
        std::cout << "\tDroga o dlugości: " << length << " z miasta ";
    else if (special) 
        std::cout << "\tLot o dlugości: " << length << " z miasta ";

    if 
        (startNode != nullptr) 
        std::cout << startNode->name;
    else 
        std::cout << "null start";

    std::cout << " do miasta ";

    if (endNode != nullptr) 
        std::cout << endNode->name;
    else 
        std::cout << "null end";
    
    std::cout << "\n";
}
