#ifndef KNN_SHEAP_H
#define KNN_SHEAP_H
#include <iostream>

using namespace std;

/* Same Heap as DHEAP but Y value here is string instead */

struct sedge 
{
    double distance;
    string y;
    int row;
};

class StrHeap
{
    private:    
        struct node 
        {
            sedge* item;
            node* next;
            node* prev;
        };
        node* head = new node();
        node* bottom = new node();
        int size = 0;

    public: 
        StrHeap() 
        {
            head->item = nullptr;
            bottom->item = nullptr;
        }
        
        void display()
        {
            if (size != 0)
            {
                cout << "\nsize: " << size << endl;
                node* current = head;
                while(current->next != nullptr)
                {
                    cout << "distance: " << current->item->distance << " y: " << current->item->y << endl;
                    current = current->next;
                }

                if (current->item != nullptr)
                    cout << "distance: " << current->item->distance << " y: " << current->item->y << endl;
            }
            cout << " " << endl;
        }

        sedge* pop()
        {
            if (size == 1)
            {
                sedge* item = new sedge();
                item = head->item;
                head->item = nullptr;
                size --;
                return item;
            }

            else if (size == 2)
            {
                sedge* item = new sedge(); item = bottom->item;
                bottom->item = nullptr;
                size --;
                return item;
            }

            else if (size > 2)
            {
                sedge* item = new sedge(); item = bottom->item;
                bottom->item = bottom->prev->item;
                node* prev = bottom->prev->prev;
                free(bottom->prev);
                prev->next = bottom;
                bottom->prev = prev;
                size --;
                return item;
            }

            else 
            {
                cout << "\nHeap is EMPTY!" << endl;
            }

        }

        void insert(sedge* target)
        {
            if (size == 0)
            {
                head->item = target;
                head->next = bottom; 
                bottom->prev = head;
                bottom->next = nullptr; head->prev = nullptr;
                size ++;
            }
            else if (size == 1)
            {
               
                if (head->item->distance <= target->distance)
                {
                    bottom->item = head->item;
                    head->item = target;
                }
                else
                {
                    bottom->item = target;
                }
                size ++;
            }
            else 
            {
                if (head->item->distance <= target->distance)
                {
                    //new head
                    node* old_head = new node();
                    old_head->item = head->item; old_head->next = head->next; 
                    head->item = target;
                    head->next->prev = old_head;
                    head->next = old_head;
                    old_head->prev = head;
                    
                }
                else if (bottom->item->distance >= target->distance )
                {
                    //new bottom
                    node* old_bot = new node();
                    old_bot->item = bottom->item; old_bot->next = bottom;
                    bottom->item = target;
                    old_bot->prev = bottom->prev;
                    bottom->prev->next = old_bot;
                    bottom->prev = old_bot;
                    
                }
                else 
                {
                    node* current = head;
                    while(current->next != nullptr && current->item->distance > target->distance)
                    {
                        current = current->next;
                    }
                    node* entry = new node();
                    entry->item = target; 
                    entry->next = current; current->prev->next = entry; 
                    entry->prev = current->prev; current->prev = entry;
                }
                size ++;
            }
        }
};

#endif 