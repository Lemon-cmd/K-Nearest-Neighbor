#ifndef KNN_DHEAP_H
#define KNN_DHEAP_H
#include <iostream>

using namespace std;

struct dedge 
{
    /* edge that stores double value of distance and y */
    double distance;
    double y;
    int row;            //keep entry #
};

class DHeap
{
    /* Min Heap that uses Double Value for Y */
    private:    
        struct node 
        {
            /* Node Struct */
            dedge* item;
            node* next;
            node* prev;
        };
        // initializes head bottom and size of heap
        node* head = new node();
        node* bottom = new node();
        int size = 0;

    public: 
        DHeap() 
        {
            //set item of head and bottom to nullptr
            head->item = nullptr;
            bottom->item = nullptr;
        }
        
        void display()
        {
            /* Display Method For Heap */
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

        dedge* pop()
        {
            /* Pop Method; Pop the smallest value which is stored at the bottom of the heap */

            if (size == 1)
            {
                //pop head
                dedge* item = new dedge();
                item = head->item;
                head->item = nullptr;
                size --;
                return item;
            }

            else if (size == 2)
            {
                //pop bottom and set its item to nullptr
                dedge* item = new dedge(); item = bottom->item;
                bottom->item = nullptr;
                size --;
                return item;
            }

            else if (size > 2)
            {
                //pop bottom and set it to equal its previous
                dedge* item = new dedge(); item = bottom->item;
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
                //size == 0
                cout << "\nHeap is EMPTY!" << endl;
            }

        }

        void insert(dedge* target)
        {
            /* Insert Method */
            if (size == 0)
            {
                //set head & points bottom->next to nullptr and head->prev to nullptr
                head->item = target;
                head->next = bottom; 
                bottom->prev = head;
                bottom->next = nullptr; head->prev = nullptr;
                size ++;
            }
            else if (size == 1)
            {
                //set bottom but first check to see if target is the new bottom or the new head
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
                //when size > 1
                if (head->item->distance <= target->distance)
                {
                    //new head if target is more than current head
                    node* old_head = new node();
                    old_head->item = head->item; old_head->next = head->next; 
                    head->item = target;
                    head->next->prev = old_head;
                    head->next = old_head;
                    old_head->prev = head;
                    
                }
                else if (bottom->item->distance >= target->distance )
                {
                    //new bottom if target is less than current bottom
                    node* old_bot = new node();
                    old_bot->item = bottom->item; old_bot->next = bottom;
                    bottom->item = target;
                    old_bot->prev = bottom->prev;
                    bottom->prev->next = old_bot;
                    bottom->prev = old_bot;
                    
                }
                else 
                {
                    /* search for node in between head & bottom that is less than target */
                    node* current = head;
                    while(current->next != nullptr && current->item->distance > target->distance)
                    {
                        //set to next
                        current = current->next;
                    }
                    //insert new entry in between current and current's previous
                    node* entry = new node();
                    entry->item = target; 
                    entry->next = current; current->prev->next = entry; 
                    entry->prev = current->prev; current->prev = entry;
                }
                //increment size of heap
                size ++;
            }
        }
};
#endif 