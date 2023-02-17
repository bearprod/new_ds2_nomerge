#ifndef hashtable3_H
#define hashtable3_H

#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;

// this is double, make a second has function, and that hash value is the step factor 

// is h′(k) = q − (k mod q), for some prime number q < N


class hashtable3{
    
    public: 

    int size_fill; 
    int size_total;
    int misspelled_count = 0; 
    string* hash_array; 
    bool check_mode = false; 
    int hash_cof;

    hashtable3(int size){
        
        size_total = size * 2; 

        if(isPrime(size_total) == true){
            hash_array = new string[size_total];
            
            if(check_mode){
                cout << "initial size fond to be prime, init array of size:" << size_total << endl;
            }
        }
        else{
            size_total = findnextPrime(size_total);

            hash_array = new string[size_total];
            
            if(check_mode){
                cout << "found next prime number, init array of size:" << size_total << endl;
            }
        }

        hash_cof = findlastprime(size_total);

        cout << hash_cof << "this is hash coof" << endl;

        for(int i = 0; i < size_total; i++){
            hash_array[i] = "null";
        }
        if(check_mode){
            cout << "init hash array of size size:" << size_total << endl;
        }
    }

    void print(){
        for(int i = 0; i < size_total; i++){
            cout << hash_array[i] << endl;
        }
    }


    void add_key(string key_to_add){

        int hash_number;

        string lower_key;

        lower_key = make_low(key_to_add);

        hash_number = hash_func(lower_key);
        
        insert_key_at_index(lower_key, hash_number);

        return;

    }

    unsigned int hash_func(string key){
        unsigned int hash_val = 0;

        for (char ch: key){
            hash_val = 37 * hash_val + ch;
        }

        return hash_val % size_total;
    }



    void insert_key_at_index(string key, int hash_val_index){
        int sec_hash = second_hash(key);
        unsigned int new_index;
        new_index = hash_val_index;
        if(hash_array[hash_val_index] == "null"){
                hash_array[hash_val_index] = key;
                return;
        }
        else{
            for(int i = 0; i < size_total; i++){
                new_index = (new_index + (i * sec_hash)) % size_total;
                if(hash_array[new_index] == "null"){
                    hash_array[new_index] = key;
                    return;
                }                

            }
       }
       return;
    
    }

     bool new_search_for_hash_key_pair(string key, int hash_ind){
        unsigned int sec_hash = second_hash(key);
        unsigned int new_index;
        new_index = hash_ind;
        if(hash_array[hash_ind] == key){
                return true;
        }
        else{
            for(int i = 0; i < size_total; i++){
                new_index = (new_index + (i * sec_hash)) % size_total;
                if(hash_array[new_index] == key){
                    return true;
                }                

            }
            return false;
       }
       
    }
    
   
    // after a collision, call actual_second_open, find next open index using double hash * i as step
    /*int actual_second_open(int index, string key){
        int step;
        int step_factor;
        int index_to_search;
        int init_index;
        init_index = index;
        step_factor = second_hash(key);

        for(int i = 1; i < size_total/5; i++){
            step = step_factor * i;
            index_to_search = (init_index + step_factor) % size_total;
            if(hash_array[index_to_search] == key){
                return index_to_search; 
            }
        }
        return -1;
    }*/

    
    
    unsigned int second_hash(string key){

        unsigned int hash_val = 0;

        unsigned int ret_val;

        for (char ch: key){
            hash_val = 37 * hash_val + ch;
        }

        ret_val = hash_cof - (hash_val % hash_cof);

        return ret_val; // def keep thsi q - mod shit 

    }


    void search(string search_key){
        int hash_of_key;

        string lower_key;

        lower_key = make_low(search_key);

        if(lower_key != "empty bad string"){
           
            hash_of_key = hash_func(lower_key);

            if(new_search_for_hash_key_pair(lower_key, hash_of_key)){
                // cout << "found:" << lower_key << endl;
                return;
            }
            else{
                cout << "could not find " << search_key << endl;
                misspelled_count = misspelled_count + 1;
                // cout << "did not find: " << lower_key << endl;
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

    int findlastprime(int number){
        int cur_number = number;
        while(isPrime(cur_number) != true)
        {
            cur_number = cur_number - 1;
        }
        return cur_number;
    }


};

#endif