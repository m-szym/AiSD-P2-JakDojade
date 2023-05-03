#pragma once

#include <cmath>
#include <iostream>

#include "List2d.h"
#include "string_helpers.h"


template <typename content_type> class HashTablet
{

public:
	List2d<content_type>** harray;
	int array_size;

	bool is_prime(int number);


	HashTablet(int new_array_size);
	~HashTablet();

	int hash(char* key);

	content_type* operator[](int index);	//szukanie po indeksie
	content_type* operator[](char* key);	//szukanie po kluczu
	content_type* get_nth(int index) {
		return harray[index];
	}

	int get_index(char* key);				//szukanie indeksu po kluczu


	content_type* insert(char* key, content_type* content);
	HashTablet* remove(char* key);
	HashTablet* remove(int index);

};

template<typename content_type>
bool HashTablet<content_type>::is_prime(int number)
{
	if (number % 2 == 0) return false;

	for (int i = 3; i <= sqrt(number); i+=2)
	{
		if (number % i == 0) return false;
	}

	return true;
}



template<typename content_type>
inline HashTablet<content_type>::HashTablet(int new_array_size)
{
	//int new_size = 2 * new_array_size;
	//while (!is_prime(new_size))
	//{
	//	++new_size;
	//}
	int new_size = 10;
	while (new_size <= new_array_size)
	{
		new_size = new_size * 10;
	}


	this->array_size = new_size * 10;



	//this->harray = new content_type * [this->array_size];
	this->harray = new List2d<content_type> * [this->array_size];

	for (int i = 0; i < this->array_size; i++)
	{
		this->harray[i] = nullptr;
	}
}

template<typename content_type>
inline HashTablet<content_type>::~HashTablet()
{
	for (int i = 0; i < array_size; i++)
	{
		if (this->harray[i] != nullptr)
			delete this->harray[i];
	}

	delete this->harray;
}

template<typename content_type>
inline int HashTablet<content_type>::hash(char* key)
{
	long long string_hash = hash_string(key);

	//return string_hash % this->array_size;
	int res = array_size * fmod(string_hash*HASH_PRIME,1);
	return res;
}

template<typename content_type>
inline content_type* HashTablet<content_type>::operator[](int index)
{
	//return harray[index];
	return nullptr;
}

template<typename content_type>
inline content_type* HashTablet<content_type>::operator[](char* key)
{
	long long hs = hash_string(key);
	List2d<content_type>* c = this->harray[hash(key)];
	if (c != nullptr)
	{
		if (c->next == nullptr) return c->cont;
		else
		{
			while (c != nullptr)
			{
				if (c->cont->operator==(key)) return c->cont;
				else c = c->next;
			}
		}
	}
	return nullptr;

}

template<typename content_type>
inline content_type* HashTablet<content_type>::insert(char* key, content_type* content)
{
	long long hs = hash_string(key);
	int h = hash(key);
	//std::cout << " -> [" << h << "]";
	//this->harray[h] = content;

	if (this->harray[h] == nullptr)
	{
		this->harray[h] = new List2d<content_type>(content);
	}
	else if (this->harray[h] != nullptr)
	{
		this->harray[h]->add_after(content);
	}
	
	return content;
}
