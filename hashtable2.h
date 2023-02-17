#ifndef hashtable2_H
#define hashtable2_H

#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;


class hashtable2{
    
    public: 

    int size_fill; 
    int size_total;
    int misspelled_count = 0; 
    string* hash_array; 
    bool check_mode = true; 

    hashtable2(int size);


    void add_key(string key_to_add);

    int hash_func(string key);

    void insert_key_at_index(string key, int hash_val_index);

    void search(string search_key);

    string make_low(string key);

    bool search_for_hash_key_pair(string key, int hash_ind);

    bool isPrime(int number);

    int findnextPrime(int number);

};


#endif