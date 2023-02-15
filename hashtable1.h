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

    node_buck();

    void add_to_back(string key_to_add);

    bool search(string key_to_search);

    void print();
};


class hashtable1{

    public:

    int misspelled_count = 0;
    int size_total;
    node_buck* hash_array;

    hashtable1(int size);

    // add key to bucket
    void add_key(string key_to_add);

    int hash_func(string key);

    // can prob delete this as well
    void print_index(int index);

    void search(string search_key);

    string make_low(string key);

    bool isPrime(int number);

    int findnextPrime(int number);
    
};

#endif