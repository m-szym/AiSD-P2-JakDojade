#pragma once
#include "List2d.h"

template<typename T>
class PriorityQueueList2d
{
private:
        List2dRoot<T> arr;
        


public:
        int size;


        PriorityQueueList2d();
        ~PriorityQueueList2d();


        T* top();
        void pop();
        T* append(T* element);
        T* smart_before_insert(T* element, int size);


};

template<typename T>
PriorityQueueList2d<T>::PriorityQueueList2d()
        : size(0)
{
}

template<typename T>
PriorityQueueList2d<T>::~PriorityQueueList2d()
{
}

template<typename T>
inline T* PriorityQueueList2d<T>::top()
{
        if (arr.start != nullptr)
                return arr.start->cont;
        else
                return nullptr;
}

template<typename T>
inline void PriorityQueueList2d<T>::pop()
{
        this->arr.remove_at_start();
        size--;
}

template<typename T>
inline T* PriorityQueueList2d<T>::append(T* element)
{
        this->arr.add_at_end(element);
        size++;
        return element;
}

template<typename T>
inline T* PriorityQueueList2d<T>::smart_before_insert(T* element, int size)
{
        List2d<T>* cur = this->arr.start;
        if (cur == nullptr)
        {
                this->append(element);
                return element;
        
}

        bool ad = false;
        while (cur != nullptr)
        {
                if (cur->next != nullptr)
                {
                        if ((*cur->next->cont) == *element)
                                cur->next->remove_self();
                
}
                if (cur == nullptr)break;

                if (!ad)
                {
                        if (*element < *(cur->cont))
                        {
                                size++;
                                cur->add_before(element);
                                ad = true;
                                if (arr.start == cur) {
                                        arr.start = cur->prev;
                                
}
                                //return element;
                        
}
                
}


                //cur++;        //czy działa ?
                cur = cur->next;
        
}

        if (!ad)
        {
                size++;
                arr.add_at_end(element);
        
}
        return element;
}