#ifndef hashtable1_H
#define hashtable1_H

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

struct node{
    string value;
    node* next_node;
    node* prev_node;

};

// this is a linked lis,t what i call a baucket, of nodes
class node_buck{
    public:

    node* head;

    node* tail;

    node_buck(){
        head = tail = nullptr;
    }

    void add_to_back(string key_to_add){
        
        node* cur_node = new node;
        
        cur_node->value = key_to_add;

        cur_node->next_node = nullptr;

        cur_node->prev_node = tail;

        if(head == nullptr){
            head = cur_node;
        }
        else{
            tail->next_node = cur_node;
        }

        tail = cur_node;


        return;

    }

    bool search(string key_to_search){
        if(head == nullptr){
            return false;
        }
        node* iter_node = new node;
        iter_node = head;
        while(iter_node != nullptr){
            if(iter_node->value == key_to_search){
                return true;
            }
            iter_node = iter_node->next_node;
        }
        return false;
    }

    // can prob delete this, i hope
    void print(){
        node* iter_node = new node;
        while(iter_node != nullptr){
            cout << iter_node->value << endl;
            }
        return;
    }
};


class hashtable1{

    public:

    int misspelled_count = 0;
    int size_total;
    node_buck* hash_array;

    hashtable1(int size){
        size_total = size;

        if(isPrime(size_total) == true){
            hash_array = new node_buck[size_total];
            
        }
        else{
            size_total = findnextPrime(size_total);

            hash_array = new node_buck[size_total];

        }

    }

    // add key to bucket
    void add_key(string key_to_add){
        
        int hash_number = hash_func(key_to_add);

        string lower_key_to_add;

        lower_key_to_add = make_low(key_to_add);

        // add error chekcing, prob like u did in other file
        hash_array[hash_number].add_to_back(lower_key_to_add);
        // go to index of hash array, and on this bucket call add

        return;
    }

    int hash_func(string key){
        unsigned int hash_val = 0;

        for (char ch: key){
            ch = tolower(ch);
            hash_val = 2129 * hash_val + ch;
        }

        return hash_val % size_total;
    }

    // can prob delete this as well
    void print_index(int index){
        hash_array[index].print();
        return;
    }

    void search(string search_key){
       
        int hash_of_key;

        string lower_key;

        lower_key = make_low(search_key);

        if(lower_key != "empty bad string"){
           
                hash_of_key = hash_func(search_key);

                if(hash_of_key >= 0 && hash_of_key < size_total)
                    {
                    
                    // cout << "about to search for " << lower_key << " at index " << hash_of_key << endl;
                    if(hash_array[hash_of_key].search(lower_key)){
                        return;
                    }
                    else{
                        misspelled_count = misspelled_count + 1;
                        return;
                    }
                    }
                else{
                    cout << "hash out of index" << endl;
                    return;
                    }
            }
            else{
                return;
            }
}


    string make_low(string key){
        if(key.length() > 0)
            {
            for (int i = 0; i < key.length(); i++){
                key[i] = tolower(key[i]);
            }
            return key;
            }
        else{
            return "empty bad string";
            }
        }

    bool isPrime(int number){
        for(int i = 2; i < number; i++){
            if(number % i == 0){
                return false;
            }
        }
        return true;
    }

    int findnextPrime(int number){
        int cur_number = number;
        while(isPrime(cur_number) != true)
        {
            cur_number = cur_number + 1;
        }
        return cur_number;
    }
    
};

#endif